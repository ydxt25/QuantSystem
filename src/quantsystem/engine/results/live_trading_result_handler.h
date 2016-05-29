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

#ifndef QUANTSYSTEM_ENGINE_RESULTS_LIVE_TRADING_RESULT_HANDLER_H_
#define QUANTSYSTEM_ENGINE_RESULTS_LIVE_TRADING_RESULT_HANDLER_H_

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <map>
using std::map;
#include "quantsystem/interfaces/ialgorithm.h"
#include "quantsystem/common/global.h"
#include "quantsystem/common/util/charting.h"
#include "quantsystem/common/packets/packet.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/orders/order.h"
#include "quantsystem/common/orders/order_event.h"
#include "quantsystem/common/packets/live_node_packet.h"
#include "quantsystem/common/packets/live_result_packet.h"
#include "quantsystem/common/packets/algorithm_node_packet.h"
#include "quantsystem/common/securities/security_holding.h"
#include "quantsystem/engine/results/iresult_handler.h"
namespace quantsystem {
using interfaces::IAlgorithm;
using orders::Order;
using orders::OrderEvent;
using packets::Packet;
using packets::LiveNodePacket;
using packets::LiveResultPacket;
using packets::LiveResult;
using packets::AlgorithmNodePacket;
using securities::Holding;
namespace engine {
namespace results {
/**
 * Live trading result handler implementation passes the messages to
 * the System live trading interface.
 * @ingroup EngineLayerResults
 */
class LiveTradingResultHandler : public IResultHandler {
 public:
  /**
   * Initialize the live trading result handler.
   * @param job Live trading job
   */
  explicit LiveTradingResultHandler(const LiveNodePacket* job);

  /**
   * Primary result thread entry point to process the result message queue
   * and send it to whatever endpoint is set.
   */
  virtual void Run();

  /**
   * Every so often send an update to the browser with the current state
   * of the algorithm.
   */
  void Update();

  /**
   * Process debug messages with the preconfigured settings.
   * @param message String debug message
   */
  virtual void DebugMessage(const string& message);

  /**
   * Send a list of security types to the browser.
   * @param types Security types list inside algorithm
   */
  virtual void SecurityType(const vector<SecurityType::Enum>& types);

  /**
   * Send a logging message to the log list for storage.
   * @param message Message we'd in the log
   */
  virtual void LogMessage(const string& message);

  /**
   * Send an error message back to the browser highlighted in red
   * with a stacktrace.
   * @param error Error message we'd like shown in console.
   * @param stacktrace Stacktrace information string
   */
  virtual void ErrorMessage(const string& error,
                            const string& stacktrace = "");

  /**
   * Send a runtime error message back to the browser highlighted with in red.
   * @param message Error message
   * @param stacktrace Stacktrace information string
   */
  virtual void RuntimeError(const string& message,
                            const string& stacktrace = "");

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
                      double value);

  /**
   * Wrapper methond on sample to create the equity chart.
   * @param time Time of the sample
   * @param value Equity value at this moment in time
   */
  virtual void SampleEquity(const DateTime& time, double value);

  /**
   * Sample the current daily performance directly with a time-value pair.
   * @param time Current backtest date
   * @param value Current daily performance value
   */
  virtual void SamplePerformance(const DateTime& time, double value);

  /**
   * Sample the asset prices to generate plots.
   * @param symbol Symbol we're sampling
   * @param time Time of sample
   * @param value Value of the asset price
   */
  virtual void SampleAssetPrices(const string& symbol,
                                 const DateTime& time,
                                 double value);

  /**
   * Add a range of samples from the users algorithms to the
   * end of our current list.
   * @param samples Chart updates since the last request
   */
  virtual void SampleRange(const vector<Chart>& samples);

  /**
   * Set the algorithm of the result handler after its been initialized.
   * @param algorithm Algorithm object matching IAlgorithm interface
   */
  virtual void SetAlgorithm(IAlgorithm* algorithm);

  /**
   * Save the snapshot of the total results to storage.
   * @param packet Packet to store
   * @param async Store the packet asyncronously to speed up the thread
   */
  virtual void StoreResult(const Packet& packet, bool async = false);

  /**
   * Post the final result back to the controller worker if backtesting,
   * or to console if local.
   */
  virtual void SendFinalResult(AlgorithmNodePacket* job,
                          const securities::OrderMap& orders,
                          const map<DateTime, double>& profit_loss,
                          const map<string, Holding>& holdings,
                          const map<string, string>& statistics,
                          const map<string, string>& banner);

  /**
   * Process the log list and save it to storage.
   * @param date Today's date for this log
   * @param logs Log list
   */
  void StoreLog(const DateTime& date, const vector<string>& logs);

  /**
   * Send a algorithm status update to the user of the algorithms running
   * state.
   * @param algorithnm_id String Id of the algorithm
   * @param status Status enum of the algorithm
   * @param message Optional string message describing reason for status change
   */
  virtual void SendStatusUpdate(const string& algorithm_id,
                                AlgorithmStatus::Enum status,
                                const string& message = "");

  /**
   * Set a dynamic runtime statistic to show in the (live) algorithm header.
   * @param key Runtime headline statistic name
   * @param value Runtime headline statistic value
   */
  virtual void RuntimeStatistic(const string& key, const string& value);

  /**
   * Send a new order event.
   * @param new_event Update, processing or cancellation of an order,
   * update the IDE in live mode or ignore in backtesting
   */
  virtual void SendOrderEvent(const OrderEvent* new_event);

  /**
   * Terminate the result thread and apply any required exit proceedures.
   */
  virtual void Exit();

  /**
   * Purge/clear any outstanding messages in message queue.
   */
  virtual void PurgeQueue();
  
 private:
  string compile_id_;
  string deploy_id_;
  IAlgorithm* algorithm_;
  bool exit_triggered_;
  DateTime start_time_;
  LiveNodePacket* job_;
  map<string, string> runtime_statistics_;
  // Update loop
  DateTime next_update_;
  DateTime next_equity_update_;
  DateTime next_charts_update_;
  DateTime next_log_store_update_;
  DateTime last_update_;
  int last_order_id_;
  // Log message store
  map<DateTime, vector<string> > log_store_;

  vector<LiveResultPacket*> SplitPackets(
      const map<string, Chart>& delta_charts,
      const map<int, Order>& delta_orders,
      const map<string, Holding>& holdings,
      const map<string, string>& delta_statistics,
      const map<string, string>& runtime_statistics,
      const map<string, string>& server_statistics);

  /**
   * Save an algorithm message to the log store.
   * Uses a different timestamped method of adding messaging to
   * interweve debug and logging messages.
   * @param message String message to send to browser
   */
  void AddToLogStore(const string& message);

  /**
   * Truncates the chart and order data in the result packet to
   * within the specified time frame.
   */
  static void Truncate(const LiveResult& result,
                       const DateTime& start,
                       const DateTime& stop);

  string CreateKey(const string& suffix,
                   const string& dateFormat = "yyyy-MM-dd");
};

}  // namespace results
}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_RESULTS_LIVE_TRADING_RESULT_HANDLER_H_
