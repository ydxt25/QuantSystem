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

#include <glog/logging.h>
#include <iostream>  // NOLINT
#include <thread>
#include <chrono>
#include <functional>
using std::cout;
using std::endl;
using std::ostream;  // NOLINT
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <queue>
using std::queue;

#include "quantsystem/common/strings/join.h"
#include "quantsystem/common/base/scoped_ptr.h"
using namespace quantsystem;  // NOLINT
#include "quantsystem/common/statistics/statistics.h"
using statistics::Statistics;
#include "quantsystem/configuration/configuration.h"
using configuration::Config;
#include "quantsystem/interfaces/iapi.h"
#include "quantsystem/interfaces/ialgorithm.h"
#include "quantsystem/interfaces/ibrokerage.h"
#include "quantsystem/interfaces/iqueue_handler.h"
#include "quantsystem/interfaces/imessaging_handler.h"
using interfaces::IApi;
using interfaces::IAlgorithm;
using interfaces::IBrokerage;
using interfaces::IMessagingHandler;
using interfaces::IQueueHandler;
#include "quantsystem/messaging/messaging.h"
using messaging::Messaging;
#include "quantsystem/brokerages/brokerage.h"
using brokerages::Brokerage;
#include "quantsystem/queues/queue.h"
using queues::Queue;
#include "quantsystem/api/api.h"
using api::Api;
#include "quantsystem/common/packets/algorithm_node_packet.h"
#include "quantsystem/common/packets/live_node_packet.h"
#include "quantsystem/common/packets/backtest_node_packet.h"
using packets::AlgorithmNodePacket;
using packets::BacktestNodePacket;
using packets::LiveNodePacket;
#include "quantsystem/engine/setup/console_setup_handler.h"
#include "quantsystem/engine/setup/backtesting_setup_handler.h"
#include "quantsystem/engine/setup/paper_trading_setup_handler.h"
using engine::setup::ConsoleSetupHandler;
using engine::setup::BacktestingSetupHandler;
using engine::setup::PaperTradingSetupHandler;
#include "quantsystem/engine/results/iresult_handler.h"
#include "quantsystem/engine/results/console_result_handler.h"
#include "quantsystem/engine/results/backtesting_result_handler.h"
#include "quantsystem/engine/results/live_trading_result_handler.h"
using engine::results::IResultHandler;
using engine::results::ConsoleResultHandler;
using engine::results::BacktestingResultHandler;
using engine::results::LiveTradingResultHandler;
#include "quantsystem/engine/data_feeds/backtesting_data_feed.h"
#include "quantsystem/engine/data_feeds/filesystem_data_feed.h"
#include "quantsystem/engine/data_feeds/paper_trading_data_feed.h"
#include "quantsystem/engine/data_feeds/testlive_trading_data_feed.h"
using engine::datafeeds::BacktestingDataFeed;
using engine::datafeeds::FileSystemDataFeed;
using engine::datafeeds::PaperTradingDataFeed;
using engine::datafeeds::TestLiveTradingDataFeed;
#include "quantsystem/engine/real_time/backtesting_real_time_handler.h"
#include "quantsystem/engine/real_time/live_trading_real_time_handler.h"
using engine::realtime::BacktestingRealTimeHandler;
using engine::realtime::LiveTradingRealTimeHandler;
#include "quantsystem/engine/transaction_handlers/tradier_transaction_handler.h"
#include "quantsystem/engine/transaction_handlers/backtesting_transaction_handler.h"
using engine::transaction_handlers::TradierTransactionHandler;
using engine::transaction_handlers::BacktestingTransactionHandler;
#include "quantsystem/engine/algorithm_manager.h"
using engine::AlgorithmManager;

namespace quantsystem {

/**
 * Get the setup handler for this algorithm, depending on its use case.
 * @param local a local algorithm and local datasources
 * @param setup_method Setup handler
 * @return Instance of a setup handler
 */
static ISetupHandler* GetSetupHandler(bool local,
    SetupHandlerEndpoint::Enum setup_method) {
  if (local) {
    LOG(INFO) << "Select Console setup handler.";
    return new ConsoleSetupHandler();
  }
  ISetupHandler* sh = NULL;
  switch (setup_method) {
    case SetupHandlerEndpoint::kConsole:
      sh = new ConsoleSetupHandler();
      LOG(INFO) << "Select Console setup handler.";
      break;
    case SetupHandlerEndpoint::kBacktesting:
      sh = new BacktestingSetupHandler();
      LOG(INFO) << "Select Backtesting setup handler.";
      break;
    case SetupHandlerEndpoint::kPaperTrading:
      sh = new PaperTradingSetupHandler();
      LOG(INFO) << "Select PaperTrading setup handler.";
      break;
    default:
      LOG(ERROR) << "Logic problem? setup_method = " << setup_method;
      break;
  }
  return sh;
}

/**
 * Get an instance of the data feed handler we're requesting for this work.
 * @param local a local algorithm and local datasources
 * @param job Algorithm Node Packet
 * @return Matching IResultHandler class
 */
static IResultHandler* GetResultHandler(bool local,
                                        AlgorithmNodePacket* job) {
  if (local) {
    LOG(INFO) << "Selected Console result handler.";
    return new ConsoleResultHandler(job);
  }
  IResultHandler* rh = NULL;
  switch (job->result_endpoint) {
    case ResultHandlerEndpoint::kConsole:
      LOG(INFO) << "Selected Console result handler.";
      rh = new ConsoleResultHandler(dynamic_cast<BacktestNodePacket*>(job));
      break;
    case ResultHandlerEndpoint::kBacktesting:
      LOG(INFO) << "Selected Backtesting result handler.";
      rh = new BacktestingResultHandler(
          dynamic_cast<BacktestNodePacket*>(job));
      break;
    case ResultHandlerEndpoint::kLiveTrading:
      LOG(INFO) << "Selected Live trading result handler.";
      rh = new LiveTradingResultHandler(dynamic_cast<LiveNodePacket*>(job));
      break;
    default:
      LOG(ERROR) << "Logic problem? result_endpoint = " << job->result_endpoint;
      break;
  }
  return rh;
}

/**
 * Get an instance of the data feed handler we're requesting for this work.
 * @param algorithm User algorithm to scan for securities
 * @param borkerage Brokerage instance to avoid access token duplication
 * @param job Algorithm Node Packet
 * @return Matching IDataFeed class
 */
static IDataFeed* GetDataFeedHandler(IAlgorithm* algorithm,
                                     const IBrokerage* brokerage,
                                     AlgorithmNodePacket* job,
                                     IResultHandler* result_handler) {
  IDataFeed* df = NULL;
  switch (job->data_endpoint) {
    case DataFeedEndpoint::kBacktesting:
      LOG(INFO) << "Selected Backtesting DataFeed.";
      df = new BacktestingDataFeed(algorithm,
                                  dynamic_cast<BacktestNodePacket*>(job),
                                  result_handler);
      break;
    case DataFeedEndpoint::kFileSystem:
      LOG(INFO) << "Selected FileSystem DataFeed.";
      df = new FileSystemDataFeed(algorithm,
                                  dynamic_cast<BacktestNodePacket*>(job),
                                  result_handler);
      break;
    case DataFeedEndpoint::kLiveTrading:
      LOG(INFO) << "Selected LiveTrading DataFeed.";
      df = new PaperTradingDataFeed(algorithm,
                                    dynamic_cast<LiveNodePacket*>(job));
      break;
    case DataFeedEndpoint::kTest:
      {
        TestLiveTradingDataFeed* feed =
            new TestLiveTradingDataFeed(algorithm,
                                        dynamic_cast<LiveNodePacket*>(job));
        df = feed;
        LOG(INFO) << "Selected Test DataFeed at " << feed->fast_forward()
                  << "x.";
        break;
      }
    default:
      LOG(ERROR) << "Logic problem? data_endpoint = " << job->data_endpoint;
      break;
  }
  return df;
}

/**
 * Select the realtime event handler set in the job.
 * @param algorithm Algorithm class
 * @param borkerage Brokerage instance to avoid access token duplication
 * @param feed IDataFeed Hanlder
 * @param results Result Hanlder
 * @param job Algorithm Node Packet
 * @return Matching IRealTimeHandler class
 */
static IRealTimeHandler* GetRealTimeHandler(IAlgorithm* algorithm,
                                            const IBrokerage* brokerage,
                                            const IDataFeed* feed,
                                            const IResultHandler* results,
                                            AlgorithmNodePacket* job) {
  IRealTimeHandler* rth = NULL;
  switch (job->real_time_endpoint) {
    case RealTimeEndpoint::kBacktesting:
      LOG(INFO) << "Selected Backtesting RealTimeEvent Handler.";
      rth = new BacktestingRealTimeHandler(algorithm, job);
      break;
    case RealTimeEndpoint::kLiveTrading:
      LOG(INFO) << "Selected LiveTrading RealTimeEvent Handler.";
      rth = new LiveTradingRealTimeHandler(algorithm, feed, results,
                                           brokerage, job);
      break;
    default:
      LOG(ERROR) << "Logic problem? real_time_endpoint = " <<
          job->real_time_endpoint;
      break;
  }
  return rth;
}

/**
 * Get an instance of the transaction handler set by the task.
 * @param algorithm Algorithm class
 * @param borkerage Brokerage instance to avoid access token duplication
 * @param results Result Hanlder
 * @param job Algorithm Node Packet
 * @return Matching ITransactionHandler class
 */
static ITransactionHandler* GetTransactionHandler(
    IAlgorithm* algorithm,
    const IBrokerage* brokerage,
    IResultHandler* results,
    AlgorithmNodePacket* job) {
  ITransactionHandler* th = NULL;
  switch (job->transaction_endpoint) {
    case TransactionHandlerEndpoint::kTradier:
      {
        LOG(INFO) << "Selected Tradier Transaction Handler.";
        LiveNodePacket* live = dynamic_cast<LiveNodePacket*>(job);
        if (live) {
          th = new TradierTransactionHandler(algorithm, brokerage, results,
                                             live->account_id);
        } else {
          LOG(FATAL) << "the job is not a LiveNodePacket.";
        }
        break;
      }
    default:
      LOG(INFO) << "Selected Backtesting Transaction Handler.";
      th = new BacktestingTransactionHandler(algorithm, results);
      break;
  }
  return th;
}

const Statistics::ChartPointVector&
GetChartPoints(const IResultHandler::ChartsMap& charts,
               const string& charts_name,
               const string& series_name) {
  return charts.at(charts_name)->series_map.at(series_name).values;
}

bool ChartsHasTheSeries(const IResultHandler::ChartsMap& charts,
                        const string& charts_name,
                        const string& series_name) {
  bool res = false;
  IResultHandler::ChartsMap::const_iterator found_chart =
      charts.find(charts_name);
  if (found_chart != charts.end()) {
    Chart::SeriesMap::const_iterator found_serie =
        found_chart->second->series_map.find(series_name);
    if (found_serie != found_chart->second->series_map.end()) {
      res = true;
    }
  }
  return res;
}

void DoStatisAndSendResult(AlgorithmNodePacket* job,
                           const IAlgorithm* algorithm,
                           const ITransactionHandler* transaction_handler,
                           const ISetupHandler* setup_handler,
                           IResultHandler* result_handler) {
  // Send result data back
  const IResultHandler::ChartsMap& charts = result_handler->charts();
  const securities::OrderMap& orders = transaction_handler->orders();
  map<string, Holding> holdings;
  map<string, string> statistics;
  map<string, string> banner;

  const securities::TransactionMap& profit_loss =
      algorithm->transactions()->transaction_record();
  if (ChartsHasTheSeries(charts, "Strategy Equity", "Equity") &&
      ChartsHasTheSeries(charts, "Strategy Equity", "Daily Performance")) {
    const Statistics::ChartPointVector& equity =
        GetChartPoints(charts, "Strategy Equity", "Equity");
    const Statistics::ChartPointVector& performance =
        GetChartPoints(charts, "Strategy Equity", "Daily Performance");
    if (equity.empty() || performance.empty() || profit_loss.empty()) {
      LOG(ERROR) << "Error generating statistics results";
    } else {
      Statistics::Generate(equity, profit_loss, performance,
                         setup_handler->starting_capital(), &statistics, 252);
    }
  } else {
    LOG(ERROR) << "Error generating statistics results";
  }
  // Diagnostics Completed
  result_handler->DebugMessage("Algorithm Id:(" + job->AlgorithmId() +
                               ") completed.");
  // Send the result packet
  result_handler->SendFinalResult(job, orders, profit_loss, holdings,
                                  statistics, banner);
}
}  // namespace quantsystem


int main(int argc, char* argv[]) {
  // Initialize
  bool live_mode_ = Config::GetBool("livemode");
  bool local_ = Config::GetBool("local");
  // Brokerage class holds manages the connection, transaction processing
  // and data retrieval from specific broker endpoints.
  scoped_ptr<IBrokerage> brokerage(new Brokerage());
  // Notification/messaging handler for pushing messages to the proper endpoint
  scoped_ptr<IMessagingHandler> notify(new Messaging());
  // Task requester / job queue handler for running the next algorithm task
  scoped_ptr<IQueueHandler> queue(new Queue());
  // Algorithm API handler for setting the per user restrictions
  // on algorithm behaviour where applicable
  scoped_ptr<IApi> api(new Api());

  notify->Initialize();
  queue->Initialize(live_mode_);
  api->Initialize();

  do {
    // Reset algo manager internal variables preparing for a new algorithm.
    AlgorithmManager::ResetManager();
    string algorithm_path;
    scoped_ptr<AlgorithmNodePacket> job;
    job.reset(queue->NextJob(&algorithm_path));
    // Initialize messaging system
    notify->SetChannel(job->channel);
    // Create SetupHandler to configure internal algorithm state
    scoped_ptr<ISetupHandler> setup_handler(
        GetSetupHandler(local_, job->setup_endpoint));
    // Set the result handler type for this algorithm job, and
    // launch the associated result thread
    scoped_ptr<IResultHandler> result_handler(GetResultHandler(local_,
                                                               job.get()));
    std::thread thread_results(std::bind(&IResultHandler::Run,
                                         result_handler.get()));
    scoped_ptr<IAlgorithm> algorithm(
        setup_handler->CreateAlgorithmInstance(algorithm_path));
    // Initialize the internal state of algorithm and job:
    // executes the algorithm.Initialize() method
    bool initialize_complete = setup_handler->Setup(algorithm.get(), job.get(),
                                                    brokerage.get());
    if (!initialize_complete || algorithm->error_messages().size() > 0 ||
        setup_handler->errors().size() > 0) {
      initialize_complete = false;
      string error_messages = common::strings::Join
                              (algorithm->error_messages(), ",");
      error_messages += common::strings::Join(setup_handler->errors(), ",");
      LOG(ERROR) << error_messages;
      return -1;
    }
    // Set algorithms
    algorithm->SetAlgorithmId(job->AlgorithmId());
    algorithm->SetLiveMode(live_mode_);
    algorithm->SetLocked();
    // Load the associated handlers for data, transaction and realtime events
    result_handler->SetAlgorithm(algorithm.get());
    scoped_ptr<IDataFeed> data_feed(
        GetDataFeedHandler(algorithm.get(),
                           brokerage.get(),
                           job.get(), result_handler.get()));
    scoped_ptr<ITransactionHandler> transaction_handler(
        GetTransactionHandler(algorithm.get(), brokerage.get(),
                              result_handler.get(), job.get()));
    scoped_ptr<IRealTimeHandler> realtime_handler(
        GetRealTimeHandler(algorithm.get(), brokerage.get(),  data_feed.get(),
                           result_handler.get(), job.get()));
    // Set the error handlers for the brokerage asynchronous errors
    setup_handler->SetupErrorHandler(result_handler.get(), brokerage.get());
    // Send status to user the algorithm is now executing
    result_handler->SendStatusUpdate(job->AlgorithmId(),
                                     AlgorithmStatus::kRunning);
    // Launch the data, transaction and realtime threads
    // Data feed pushing data packets into thread bridge
    std::thread thread_feed(std::bind(&IDataFeed::Run, data_feed.get()));
    // Transaction modeller scanning new order requests
    std::thread thread_transactions(std::bind(&ITransactionHandler::Run,
                                              transaction_handler.get()));
    // RealTime scan time for time based events
    std::thread thread_realtime(std::bind(&IRealTimeHandler::Run,
                                          realtime_handler.get()));


    // Run Algorithm Job:
    // -> Using this Data Feed
    // -> Send Orders to this TransactionHandler
    // -> Send Results to ResultHandler
    AlgorithmManager::Run(job.get(), transaction_handler.get(),
                          setup_handler.get(), algorithm.get(), data_feed.get(),
                          result_handler.get(),
                          realtime_handler.get());

    if (AlgorithmManager::runtime_error() != NULL) {
      string runtime_error = (*AlgorithmManager::runtime_error());
      LOG(ERROR) << "Algorithm run error:" << runtime_error;
      if (data_feed != NULL) {
        data_feed->Exit();
      }
      if (result_handler != NULL) {
        result_handler->RuntimeError("Runtime Error:" + runtime_error, "");
        api->SetAlgorithmStatus(job->AlgorithmId(),
                                AlgorithmStatus::kRuntimeError);
      }
    }

    DoStatisAndSendResult(job.get(), algorithm.get(),
                          transaction_handler.get(), setup_handler.get(),
                          result_handler.get());

    transaction_handler->Exit();
    data_feed->Exit();
    realtime_handler->Exit();
    AlgorithmManager::ResetManager();
    result_handler->Exit();
    // Wait for the threads to complete
    LOG(INFO) << "Waiting for threads to deactivate";
    DateTime stop_time = DateTime() + TimeSpan::FromSeconds(100);
    while ((result_handler->is_active() ||
            (transaction_handler != NULL && transaction_handler->is_active()) ||
            (data_feed != NULL && data_feed->is_active())) &&
           DateTime() < stop_time) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      data_feed->Exit();
      LOG(INFO) << "Waiting Result:" << result_handler->is_active() <<
          " Transaction:" << transaction_handler->is_active() <<
          " DataFeed:" << data_feed->is_active() << " RealTime:" <<
          realtime_handler->is_active();
    }
    LOG(INFO) << "before join";
    thread_results.join();
    thread_feed.join();
    thread_transactions.join();
    thread_realtime.join();
  } while (!local_);
  return 0;
}

