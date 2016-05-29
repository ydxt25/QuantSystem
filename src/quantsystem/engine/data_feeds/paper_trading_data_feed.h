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

#ifndef QUANTSYSTEM_ENGINE_DATA_FEEDS_PAPER_TRADING_DATA_FEED_H_
#define QUANTSYSTEM_ENGINE_DATA_FEEDS_PAPER_TRADING_DATA_FEED_H_

#include <vector>
using std::vector;
#include "quantsystem/common/data/market/tick.h"
#include "quantsystem/interfaces/ialgorithm.h"
#include "quantsystem/common/packets/live_node_packet.h"
#include "quantsystem/engine/data_feeds/live_trading_data_feed.h"
namespace quantsystem {
using interfaces::IAlgorithm;
using data::market::Tick;
using packets::LiveNodePacket;
namespace engine {
namespace datafeeds {
/**
 * Live trading data feed used for paper trading.
 * @ingroup EngineLayerDataFeeds
 */
class PaperTradingDataFeed : public LiveTradingDataFeed {
 public:
  /**
   * Creates a new PaperTradingDataFeed for the algorithm/job.
   * @param algorithm The algorithm to receive the data,
   * used for a complete listing of active securities
   * @param job The job being run
   */
  PaperTradingDataFeed(const IAlgorithm* algorithm,
                       const LiveNodePacket* job);

  /**
   * Standard destructor.
   */
  virtual ~PaperTradingDataFeed();

  /**
   * Returns the next ticks from the data source. The data source itself
   * is defined in the derived class's implementation of this function.
   * For example, if obtaining data from a brokerage, say IB, then the derived
   * implementation would ask the IB API for the next ticks.
   * @return The next ticks to be aggregated and sent to algorithm
   */
  virtual vector<Tick> GetNextTicks();

 private:
  LiveNodePacket job_;
};

}  // namespace datafeeds
}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_DATA_FEEDS_PAPER_TRADING_DATA_FEED_H_
