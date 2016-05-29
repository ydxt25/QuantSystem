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
 * @defgroup EngineLayerDataFeeds  Engine Layer - Data Feeds Components
 *
 * Data Feeds Components in Engine Layer.
 */
#ifndef QUANTSYSTEM_ENGINE_DATA_FEEDS_IDATA_FEED_H_
#define QUANTSYSTEM_ENGINE_DATA_FEEDS_IDATA_FEED_H_

#include <queue>
using std::queue;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include "quantsystem/common/global.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/data/base_data.h"
#include "quantsystem/common/data/subscription_data_config.h"
namespace quantsystem {
using data::BaseData;
using data::SubscriptionDataConfig;
namespace engine {
namespace datafeeds {
/**
 * Datafeed interface for creating custom datafeed sources.
 * @ingroup EngineLayerDataFeeds
 */
class IDataFeed {
 public:
  typedef vector<queue<vector<BaseData*> > > BridgeType;
  /**
   * Primary entry point.
   */
  virtual void Run() = 0;

  /**
   * External controller calls to signal a terminate of the thread.
   */
  virtual void Exit() = 0;

  /**
   * Purge all remaining data in the thread.
   */
  virtual void PurgeData() = 0;
  
  /**
   * Boolean flag indicating there is no more data in any of our subscriptions.
   */
  virtual bool EndOfBridges() const = 0;
  
  vector<SubscriptionDataConfig*>& subscriptions() {
    return subscriptions_;
  }

  BridgeType& bridge() {
    return bridge_;
  }
  
  const BridgeType& bridge() const {
    return bridge_;
  }

  void set_bridge(const BridgeType& bridge) {
    bridge_ = bridge;
  }

  vector<bool>& end_of_bridge() {
    return end_of_bridge_;
  }

  const vector<bool>& end_of_bridge() const {
    return end_of_bridge_;
  }

  DataFeedEndpoint::Enum data_feed() const {
    return data_feed_;
  }

  void set_data_feed(DataFeedEndpoint::Enum data_feed) {
    data_feed_ = data_feed;
  }

  bool is_active() const { return is_active_; }

  DateTime loaded_data_frontier() const {
    return loaded_data_frontier_;
  }

 protected:
  // List of the subscription the algorithm has requested. Subscriptions
  // contain the type, sourcing information and manage the enumeration of data.
  vector<SubscriptionDataConfig*> subscriptions_;

  // Cross-threading queues so the datafeed pushes data into the queue and
  // the primary algorithm thread reads it out.
  BridgeType bridge_;

  // Array of boolean flags indicating the data status for
  // each queue/subscription we're tracking
  vector<bool> end_of_bridge_;

  // Set the source of the data we're requesting for the type-readers to
  // know where to get data from
  DataFeedEndpoint::Enum data_feed_;

  // Flag indicator that the thread is still busy.
  bool is_active_;

  // The most advanced moment in time for which the data feed has
  // completed loading data
  DateTime loaded_data_frontier_;

  void set_subscriptions(const vector<SubscriptionDataConfig*>& subscriptions) {
    subscriptions_.clear();
    for (vector<SubscriptionDataConfig*>::const_iterator it =
             subscriptions.begin(); it != subscriptions.end(); ++it) {
      subscriptions_.push_back(*it);
    }
  }

  void set_is_active(bool is_active) { is_active_ = is_active; }

  void set_loaded_data_frontier(const DateTime& loaded_data_frontier) {
    loaded_data_frontier_ = loaded_data_frontier;
  }
  
};

}  // namespace datafeeds
}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_DATA_FEEDS_IDATA_FEED_H_
