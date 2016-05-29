/*
 * \copyright Copyright 2015 All Rights Reserved.
 * \license @{
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @}
 */

#include <typeinfo>
#include <chrono>
#include <thread>
#include <utility>
using std::pair;
#include "quantsystem/algorithm/basic_template_algorithm.h"
#include "quantsystem/engine/data_stream.h"
#include "quantsystem/common/packets/packet.h"
#include "quantsystem/common/data/market/tick.h"
#include "quantsystem/common/data/market/tradebar.h"
#include "quantsystem/common/securities/security.h"
#include "quantsystem/engine/algorithm_manager.h"
namespace quantsystem {
using data::market::Tick;
using data::market::TradeBar;
using securities::Security;
namespace engine {
DateTime AlgorithmManager::previous_time_ = DateTime();
DateTime AlgorithmManager::frontier_ = DateTime();
DateTime AlgorithmManager::next_sample_ = DateTime();
AlgorithmStatus::Enum AlgorithmManager::algorithm_state_ =
    AlgorithmStatus::kRunning;
string AlgorithmManager::algorithm_id_ = "";
scoped_ptr<string> AlgorithmManager::runtime_error_;

void AlgorithmManager::Run(
    const AlgorithmNodePacket* job,
    const ITransactionHandler* transactions,
    const ISetupHandler* setup,
    IAlgorithm* algorithm,
    IDataFeed* feed,
    IResultHandler* results,
    IRealTimeHandler* realtime) {
  double starting_performance = setup->starting_capital();
  bool backtest_mode = (job->type == packets::kBacktestNode);
  next_sample_ = DateTime(0, 0, 0);
  frontier_ = setup->starting_date();
  algorithm_id_ = job->AlgorithmId();
  algorithm_state_ = AlgorithmStatus::kRunning;
  previous_time_ = setup->starting_date().Date();

  LOG(INFO) << "Algorithm initialized, launching time loop.";
  DataStream::DataVector data_vector;
  DataStream::GetData(feed, setup->starting_date(), &data_vector);
  for (DataStream::DateMapValue& new_data : data_vector) {
    if (algorithm_state_ != AlgorithmStatus::kRunning) {
      break;
    }
    // Go over each time stamp we've collected,
    // pass it into the algorithm in order
    // map<DateTime, map<int, vector<BaseData*> > >
    for (DataStream::DateMapValue::iterator it = new_data.begin();
         it != new_data.end(); ++it) {
      const DateTime& time = it->first;
      frontier_ = time;
      // Refresh the realtime event monitor
      realtime->SetTime(time);
      // Fire EOD if the time packet we just processed is greater
      if (backtest_mode && (previous_time_.Date() != time.Date())) {
        // Sample the portfolio value over time for chart
        results->SampleEquity(previous_time_,
                              algorithm->portfolio()->TotalPortfolioValue());
        if (starting_performance == 0) {
          results->SamplePerformance(previous_time_.Date(), 0);
        } else {
          double performance_percent =
              (algorithm->portfolio()->TotalPortfolioValue() -
               starting_performance) * 100 / starting_performance;
          results->SamplePerformance(previous_time_.Date(),
                                     performance_percent);
        }
        starting_performance = algorithm->portfolio()->TotalPortfolioValue();
      }
      if (algorithm->GetQuit()) {
        algorithm_state_ = AlgorithmStatus::kQuit;
        break;
      }
      algorithm->SetDateTime(time);
      // Trigger the data events
      scoped_ptr<TradeBars> new_bars(new TradeBars(time));
      scoped_ptr<Ticks> new_ticks(new Ticks(time));
      // map<int, vector<BaseData*>>
      for (DataStream::BaseDataVectorMap::iterator map_it = it->second.begin();
         map_it != it->second.end(); ++map_it) {
        SubscriptionDataConfig* config = feed->subscriptions()[map_it->first];
        for (BaseData* data_point :  map_it->second) {
          // Update the securities properties:
          // first before calling user code to avoid issues with data
          algorithm->securities()->Update(time, data_point);
          // Update registered consolidators for this symbol index
          for (int i = 0; i < config->consolidators.size(); ++i) {
            config->consolidators[i]->Update(data_point);
          }
          if (config->type_name == typeid(TradeBar).name()) {
            TradeBar* bar = dynamic_cast<TradeBar*>(data_point);
            if (bar != NULL && !new_bars->Contains(bar->symbol())) {
              new_bars->Add(bar->symbol(), bar);
            }
          } else if (config->type_name == typeid(Tick).name()) {
            Tick* tick = dynamic_cast<Tick*>(data_point);
            if (tick != NULL) {
              new_ticks->Add(tick->symbol(), tick);
            }
          } else {
            // Send data into the generic algorithm event handlers
            algorithm->OnData(data_point);
            delete data_point;
          }
        }  // for (BaseData* data_point
      }  // for (DataStream::BaseDataVectorMap::iterator
      if (new_bars->Count() > 0) {
        algorithm->OnData(new_bars.get());
      }
      if (new_ticks->Count() > 0) {
        algorithm->OnData(new_ticks.get());
      }
        // If this not backtesting, wait the trading model is ready
      if (job->transaction_endpoint !=
          TransactionHandlerEndpoint::kBacktesting) {
        while (!transactions->ready()) {
          std::this_thread::yield();
        }
      }
      if (time > next_sample_) {
        next_sample_ = time + results->resample_period();
        results->SampleEquity(time,
                              algorithm->portfolio()->TotalPortfolioValue());
        vector<Chart> charts;
        algorithm->GetChartUpdates(&charts);
        results->SampleRange(charts);
        vector<const Security*> values;
        algorithm->securities()->Values(&values);
        for (const Security* security : values) {
          results->SampleAssetPrices(security->symbol(), time, security->Price());
        }
      }
      ProcessMessages(results, algorithm);
      previous_time_ = time;
    }  // for (DataStream::DateMapValue::iterator it
  }  // for (DataStream::DateMapValue& new_data
  LOG(INFO) << "AlgorithmManager.Run(): Firing On End Of Algorithm.";
  algorithm->OnEndOfAlgorithm();
  ProcessMessages(results, algorithm);
  // Liquidate Holdings for Calculations
  if (algorithm_state_ == AlgorithmStatus::kLiquidated ||
      job->transaction_endpoint == TransactionHandlerEndpoint::kBacktesting) {
    LOG(INFO) << "AlgorithmManager.Run(): Liquidating algorithm holdings.";
   vector<int> order_list;
    algorithm->Liquidate(&order_list);
    results->SendStatusUpdate(job->AlgorithmId(), AlgorithmStatus::kLiquidated);
  }
  if (algorithm_state_ == AlgorithmStatus::kStopped) {
    LOG(INFO) << "AlgorithmManager.Run(): Stopping algorithm";
    results->SendStatusUpdate(job->AlgorithmId(), AlgorithmStatus::kStopped);
  }
  // Backtest deleted
  if (algorithm_state_ == AlgorithmStatus::kDeleted) {
    LOG(INFO) << "AlgorithmManager.Run(): Deleting algorithm";
    results->DebugMessage("Algorithm Id:(" + job->AlgorithmId() +
                          ") deleted by request.");
    results->SendStatusUpdate(job->AlgorithmId(), AlgorithmStatus::kDeleted);
  }
  results->SendStatusUpdate(job->AlgorithmId(), AlgorithmStatus::kCompleted);

  // Take final samples
  vector<Chart> charts;
  algorithm->GetChartUpdates(&charts);
  results->SampleRange(charts);
  results->SampleEquity(frontier_,
                        algorithm->portfolio()->TotalPortfolioValue());
  double performance_percent =
      (algorithm->portfolio()->TotalPortfolioValue() -
       starting_performance) * 100 / starting_performance;
  results->SamplePerformance(frontier_, performance_percent);
}

void AlgorithmManager::ProcessMessages(IResultHandler* results,
                                       IAlgorithm* algorithm) {
  for (string& message : algorithm->debug_messages()) {
    results->DebugMessage(message);
  }
  algorithm->debug_messages().clear();
  for (string& message : algorithm->error_messages()) {
    results->ErrorMessage(message);
  }
  algorithm->error_messages().clear();
  for (string& message : algorithm->log_messages()) {
    results->LogMessage(message);
  }
  algorithm->log_messages().clear();
  for (pair<const string, string>& statistic :
  algorithm->runtime_statistics()) {
    results->RuntimeStatistic(statistic.first, statistic.second);
  }
  algorithm->runtime_statistics().clear();
}

void AlgorithmManager::ResetManager() {
  next_sample_ = DateTime();
  frontier_ = DateTime();
  algorithm_id_ = "";
  algorithm_state_ = AlgorithmStatus::kRunning;
}

void AlgorithmManager::SetStatus(AlgorithmStatus::Enum state) {
  algorithm_state_ = state;
}

}  // namespace engine
}  // namespace quantsystem
