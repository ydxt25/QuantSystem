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

#ifndef QUANTSYSTEM_ENGINE_DATA_FEEDS_TESTLIVE_TRADING_DATA_FEED_H_
#define QUANTSYSTEM_ENGINE_DATA_FEEDS_TESTLIVE_TRADING_DATA_FEED_H_

#include <vector>
using std::vector;
#include "quantsystem/common/data/market/tick.h"
#include "quantsystem/interfaces/ialgorithm.h"
#include "quantsystem/common/time/time_span.h"
#include "quantsystem/common/packets/live_node_packet.h"
#include "quantsystem/engine/data_feeds/paper_trading_data_feed.h"
namespace quantsystem {
using interfaces::IAlgorithm;
using data::market::Tick;
using packets::LiveNodePacket;
namespace engine {
namespace datafeeds {
/**
 * Test live trading data feed with fast forward capability
 * @ingroup EngineLayerDataFeeds
 */
class TestLiveTradingDataFeed : public PaperTradingDataFeed {
 public:
  /**
   * Creates a test live trading data feed with the specified
   * fast forward factor.
   * @param algorithm The algorithm under analysis
   * @param job The job for the algorithm
   */
  TestLiveTradingDataFeed(const IAlgorithm* algorithm,
                          const LiveNodePacket* job);

  virtual vector<Tick> GetNextTicks();

  int fast_forward() const {
    return fast_forward_;
  }

 private:
  DateTime current_;
  DateTime start_;
  TimeSpan tick_resolution_;
  // Defines the number of ticks produced per
  int fast_forward_;
  TimeSpan period_;
  int delay_;

  /**
   * Calculate the next fake value for our fake data.
   * @param start Start of the fake data period
   * @param current Current time for the fake data period
   * @param period Period we want the since to run over
   */
  double ComputeNextSineValue(const DateTime& start, const DateTime& current,
                              const TimeSpan& period);
};

}  // namespace datafeeds
}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_DATA_FEEDS_TESTLIVE_TRADING_DATA_FEED_H_
