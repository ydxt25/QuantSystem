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

#ifndef QUANTSYSTEM_ENGINE_DATA_FEEDS_BACKTESTING_DATA_FEED_H_
#define QUANTSYSTEM_ENGINE_DATA_FEEDS_BACKTESTING_DATA_FEED_H_

#include "quantsystem/interfaces/ialgorithm.h"
#include "quantsystem/engine/data_feeds/filesystem_data_feed.h"
#include "quantsystem/engine/results/iresult_handler.h"
#include "quantsystem/common/packets/backtest_node_packet.h"
namespace quantsystem {
using interfaces::IAlgorithm;
using packets::BacktestNodePacket;
using engine::results::IResultHandler;
namespace engine {
namespace datafeeds {
/**
 * Backtesting data feed extends the filesystem data feed with
 * almost no modifications. Later this method can be used for
 * implementing alternative sources/generation for backtesting data.
 * @ingroup EngineLayerDataFeeds
 */
class BacktestingDataFeed : public FileSystemDataFeed {
 public:
  /**
   * Pass through the backtesting datafeed to the underlying file system
   * datafeed implementation.
   * @param algorithm Algorithm we're operating with
   * @param job Algorithm worker job
   */
  BacktestingDataFeed(IAlgorithm* algorithm,
                      BacktestNodePacket* job, IResultHandler* result_handler);

  /**
   * Standard destructor.
   */
  virtual ~BacktestingDataFeed();
};

}  // namespace datafeeds
}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_DATA_FEEDS_BACKTESTING_DATA_FEED_H_
