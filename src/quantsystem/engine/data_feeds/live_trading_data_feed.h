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

#ifndef QUANTSYSTEM_ENGINE_DATA_FEEDS_LIVE_TRADING_DATA_FEED_H_
#define QUANTSYSTEM_ENGINE_DATA_FEEDS_LIVE_TRADING_DATA_FEED_H_

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include "quantsystem/engine/stream_store.h"
#include "quantsystem/interfaces/ialgorithm.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/data/market/tick.h"
#include "quantsystem/engine/subscription_data_reader.h"
#include "quantsystem/engine/data_feeds/idata_feed.h"
namespace quantsystem {
using interfaces::IAlgorithm;
using data::market::Tick;
namespace engine {
namespace datafeeds {
/**
 * Live Data Feed Streamed From QS Source.
 * @ingroup EngineLayerDataFeeds
 */
class LiveTradingDataFeed : public IDataFeed {
 public:
  /**
   * Live trading datafeed handler provides a base implementation of
   * a live trading datafeed. Derived types need only implement
   * the GetNextTicks() function to return unprocessed ticks from
   * a data source.
   * This creates a new data feed with a DataFeedEndpoint of LiveTrading.
   * @param algorithm Algorithm requesting data
   */
  explicit LiveTradingDataFeed(const IAlgorithm* algorithm);

  /**
   * Standard destructor.
   */
  virtual ~LiveTradingDataFeed();

  /**
   * Stream thread handler uses the GetNextTicks() function to get current
   * ticks from a data source and then uses the stream store to compile
   * them into trade bars.
   */
  void Stream();

  /**
   * Returns the next ticks from the data source. The data source itself
   * is defined in the derived class's implementation of this function.
   * For example, if obtaining data from a brokerage, say IB, then the derived
   * implementation would ask the IB API for the next ticks.
   * @return The next ticks to be aggregated and sent to algorithm
   */
  virtual vector<Tick> GetNextTicks() = 0;

  /**
   * Conditionally hibernate if the market has closed to avoid constantly
   * pinging the API or trying to login while the market is closed.
   */
  bool Hibernate();

  /**
   * Main routine for datafeed analysis.
   */
  virtual void Run();

  /**
   * External controller calls to signal a terminate of the thread.
   */
  virtual void Exit();

  /**
   * Purge all remaining data in the thread.
   */
  virtual void PurgeData();

  /**
   * Update the algorithm market open and close hours on today's values
   * using controls
   */
  void UpdateSecurityMarketHours();

  /**
   * Return true when at least one security is open.
   * @return Boolean flag true when there is a market asset open.
   */
  bool AnySecurityOpen();

  /**
   * Boolean flag indicating there is no more data in any of our subscriptions.
   */
  virtual bool EndOfBridges() const {
    return end_of_bridges_;
  }

  void set_end_of_bridges(bool end_of_bridges) {
    end_of_bridges_ = end_of_bridges;
  }

  vector<SubscriptionDataReader*> subscription_reader_managers() const {
    return subscription_reader_managers_;
  }

  void set_subscription_reader_managers(
      const vector<SubscriptionDataReader*>& subscription_reader_managers) {
    subscription_reader_managers_ = subscription_reader_managers;
  }

  DateTime loaded_data_frontier() const {
    return loaded_data_frontier_;
  }

 private:
  vector<bool> is_quant_system_data_;
  vector<SubscriptionDataReader*> subscription_reader_managers_;
  bool end_of_bridges_;
  IAlgorithm* algorithm_;
  bool exit_triggered_;
  vector<string> symbols_;
  typedef map<int, StreamStore*> StreamStoreType;
  StreamStoreType stream_store_;
  bool hibernate_;
  DateTime loaded_data_frontier_;

  void set_loaded_data_frontier(const DateTime& loaded_data_frontier) {
    loaded_data_frontier_ = loaded_data_frontier;
  }
};

}  // namespace datafeeds
}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_DATA_FEEDS_LIVE_TRADING_DATA_FEED_H_
