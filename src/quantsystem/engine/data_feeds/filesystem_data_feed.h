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

#ifndef QUANTSYSTEM_ENGINE_DATA_FEEDS_FILESYSTEM_DATA_FEED_H_
#define QUANTSYSTEM_ENGINE_DATA_FEEDS_FILESYSTEM_DATA_FEED_H_

#include <vector>
using std::vector;
#include <string>
using std::string;
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/time/time_span.h"
#include "quantsystem/common/packets/backtest_node_packet.h"
#include "quantsystem/interfaces/ialgorithm.h"
#include "quantsystem/engine/data_feeds/idata_feed.h"
#include "quantsystem/engine/subscription_data_reader.h"
#include "quantsystem/engine/results/iresult_handler.h"

namespace quantsystem {
using packets::BacktestNodePacket;
using interfaces::IAlgorithm;
using engine::results::IResultHandler;
namespace engine {
namespace datafeeds {
/**
 * Historical datafeed stream reader for processing files on a local disk.
 * @ingroup EngineLayerDataFeeds
 */
class FileSystemDataFeed : public IDataFeed {
 public:
  /**
   * Create a new backtesting data feed.
   * @param algorithm instance of the algorithm
   * @param job Algorithm work task
   */
  FileSystemDataFeed(IAlgorithm* algorithm,
                     BacktestNodePacket* job, IResultHandler* result_handler);

  /**
   * Standard destructor.
   */
  virtual ~FileSystemDataFeed();

  /**
   * Initialize activators to invoke types in the algorithm.
   */
  void ResetActivators();

  /**
   * Get the number of active streams still EndOfBridge array.
   * @return Count of the number of streams with data
   */
  int GetActiveStreams();

  /**
   * Calculate the minimum increment to scan for data based
   * on the data requested.
   * @param include_tick When true the subscriptions include a tick data
   source, meaning there is almost no increment
   * @return Timespan to jump the data source so it efficiently
   * orders the results
   */
  TimeSpan CalculateIncrement(bool include_tick);

  /**
   * Main routine for datafeed analysis.
   */
  virtual void Run();

  /**
   * If this is a fillforward subscription, look at the previous time,
   * and current time, and add new objects to queue until current time
   * to fill up the gaps.
   * @param manager Subscription to process
   * @param i Subscription position in the bridge
   * (which queue are we pushing data to)
   * @param increment Timespan increment to jump the fillforward results
   */
  void ProcessFillForward(const SubscriptionDataReader* manager, int i,
                          const TimeSpan& increment);

  /**
   * External controller calls to signal a terminate of the thread.
   */
  virtual void Exit();

  /**
   * Purge all remaining data in the thread.
   */
  virtual void PurgeData();

  /**
   * Boolean flag indicating there is no more data in any of our subscriptions.
   */
  virtual bool EndOfBridges() const;

  vector<SubscriptionDataReader*>& subscription_reader_managers() {
    return subscription_reader_managers_;
  }

  void set_subscription_reader_managers(
      const vector<SubscriptionDataReader*>& subscription_reader_managers) {
    subscription_reader_managers_ = subscription_reader_managers;
  }

  vector<DateTime>& fill_forward_frontiers() {
    return fill_forward_frontiers_;
  }

 private:
  // Stream created from the configuration settings.
  vector<SubscriptionDataReader*> subscription_reader_managers_;

  // Frontiers for each fill forward high water mark
  vector<DateTime> fill_forward_frontiers_;

  IAlgorithm* algorithm_;
  BacktestNodePacket* job_;
  IResultHandler* result_handler_;
  string ticks_type_;
  string tradebars_type_;
  bool end_of_streams_;
  int subscriptions_count_;
  int bridge_max_;
  bool exit_triggered_;

  void ClearBridge();

  int GetBridgeFullCount() const;

  int GetBridgeZeroCount() const;
};

}  // namespace datafeeds
}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_DATA_FEEDS_FILESYSTEM_DATA_FEED_H_
