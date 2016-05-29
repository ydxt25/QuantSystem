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

/**
 * @defgroup EngineLayerResults  Engine Layer - Results Components
 *
 * Results Components in Engine Layer.
 */
#ifndef QUANTSYSTEM_ENGINE_RESULTS_IRESULT_HANDLER_H_
#define QUANTSYSTEM_ENGINE_RESULTS_IRESULT_HANDLER_H_

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <map>
using std::map;
#include <queue>
using std::queue;
#include "quantsystem/common/global.h"
#include "quantsystem/interfaces/ialgorithm.h"
#include "quantsystem/common/util/charting.h"
#include "quantsystem/common/orders/order.h"
#include "quantsystem/common/orders/order_event.h"
#include "quantsystem/common/time/time_span.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/securities/security_holding.h"
#include "quantsystem/common/packets/packet.h"
#include "quantsystem/common/packets/algorithm_node_packet.h"
#include "quantsystem/common/securities/security_transaction_manager.h"
namespace quantsystem {
using interfaces::IAlgorithm;
using orders::Order;
using orders::OrderEvent;
using packets::Packet;
using packets::AlgorithmNodePacket;
using securities::Holding;
namespace engine {
namespace results {
/**
 * Handle the results of the backtest: where should we send the profit,
 * portfolio updates:
 * Backtester or the Live trading platform:
 * @ingroup EngineLayerResults
 */
class IResultHandler {
 public:
    typedef queue<Packet*> MessQue;
    typedef map<string, Chart*> ChartsMap;
  /**
   * Primary result thread entry point to process the result message queue
   * and send it to whatever endpoint is set.
   */
  virtual void Run() = 0;

  /**
   * Process debug messages with the preconfigured settings.
   * @param message String debug message
   */
  virtual void DebugMessage(const string& message) = 0;

  /**
   * Send a list of security types to the browser.
   * @param types Security types list inside algorithm
   */
  virtual void SecurityType(const vector<SecurityType::Enum>& types) = 0;

  /**
   * Send a logging message to the log list for storage.
   * @param message Message we'd in the log
   */
  virtual void LogMessage(const string& message) = 0;

  /**
   * Send an error message back to the browser highlighted in red
   * with a stacktrace.
   * @param error Error message we'd like shown in console.
   * @param stacktrace Stacktrace information string
   */
  virtual void ErrorMessage(const string& error,
                            const string& stacktrace = "") = 0;

  /**
   * Send a runtime error message back to the browser highlighted with in red.
   * @param message Error message
   * @param stacktrace Stacktrace information string
   */
  virtual void RuntimeError(const string& message,
                            const string& stacktrace = "") = 0;

  /**
   * Add a sample to the chart specified by the chartName, and seriesName.
   * Sample can be used to create new charts or sample
   * equity - daily performance.
   * @param chart_name String chart name to place the sample
   * @param chart_type Type of chart we should create if it doesn't
   * already exist
   * @param series_name Series name for the chart
   * @param series_type Series type for the chart
   * @param time Time for the sample
   * @param value Value for the chart sample
   */
  virtual void Sample(const string& chart_name,
                      ChartType::Enum chart_type,
                      const string& series_name,
                      SeriesType::Enum series_type,
                      const DateTime& time,
                      double value) = 0;

  /**
   * Wrapper methond on sample to create the equity chart.
   * @param time Time of the sample
   * @param value Equity value at this moment in time
   */
  virtual void SampleEquity(const DateTime& time, double value) = 0;

  /**
   * Sample the current daily performance directly with a time-value pair.
   * @param time Current backtest date
   * @param value Current daily performance value
   */
  virtual void SamplePerformance(const DateTime& time, double value) = 0;

  /**
   * Sample the asset prices to generate plots.
   * @param symbol Symbol we're sampling
   * @param time Time of sample
   * @param value Value of the asset price
   */
  virtual void SampleAssetPrices(const string& symbol,
                                 const DateTime& time,
                                 double value) = 0;

  /**
   * Add a range of samples from the users algorithms to the
   * end of our current list.
   * @param samples Chart updates since the last request
   */
  virtual void SampleRange(const vector<Chart>& samples) = 0;

  /**
   * Set the algorithm of the result handler after its been initialized.
   * @param algorithm Algorithm object matching IAlgorithm interface
   */
  virtual void SetAlgorithm(IAlgorithm* algorithm) = 0;

  /**
   * Save the snapshot of the total results to storage.
   * @param packet Packet to store
   * @param async Store the packet asyncronously to speed up the thread
   */
  virtual void StoreResult(const Packet& packet, bool async = false) = 0;

  /**
   * Post the final result back to the controller worker if backtesting,
   * or to console if local.
   */
  virtual void SendFinalResult(AlgorithmNodePacket* job,
                          const securities::OrderMap& orders,
                          const map<DateTime, double>& profit_loss,
                          const map<string, Holding>& holdings,
                          const map<string, string>& statistics,
                          const map<string, string>& banner) = 0;

  /**
   * Send a algorithm status update to the user of the algorithms running
   * state.
   * @param algorithnm_id String Id of the algorithm
   * @param status Status enum of the algorithm
   * @param message Optional string message describing reason for status change
   */
  virtual void SendStatusUpdate(const string& algorithm_id,
                                AlgorithmStatus::Enum status,
                                const string& message = "") = 0;

  /**
   * Set a dynamic runtime statistic to show in the (live) algorithm header.
   * @param key Runtime headline statistic name
   * @param value Runtime headline statistic value
   */
  virtual void RuntimeStatistic(const string& key, const string& value) = 0;

  /**
   * Send a new order event.
   * @param new_event Update, processing or cancellation of an order,
   * update the IDE in live mode or ignore in backtesting
   */
  virtual void SendOrderEvent(const OrderEvent* new_event) = 0;

  /**
   * Terminate the result thread and apply any required exit proceedures.
   */
  virtual void Exit() = 0;

  /**
   * Purge/clear any outstanding messages in message queue.
   */
  virtual void PurgeQueue() = 0;

  MessQue& messages() { return messages_; }
  void set_messages(const MessQue& messages) {
    messages_ = messages;
  }

  ChartsMap& charts() { return charts_; }
  void set_charts(const ChartsMap& charts) {
    charts_ = charts;
  }

  TimeSpan resample_period() const { return resample_period_; }

  TimeSpan notification_period() const { return notification_period_; }

  bool is_active() const { return is_active_; }

 protected:
  // Put messages to process into the queue so they are processed
  // by this thread.
  MessQue messages_;
  // Charts collection for storing the master copy of user charting data.
  ChartsMap charts_;
  // Sampling period for timespans between resamples of the charting equity.
  TimeSpan resample_period_;
  // How frequently the backtests push messages to the browser.
  TimeSpan notification_period_;
  // Boolean flag indicating the result hander thread is busy.
  // False means it has completely finished and ready to dispose.
  bool is_active_;
};

}  // namespace results
}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_RESULTS_IRESULT_HANDLER_H_
