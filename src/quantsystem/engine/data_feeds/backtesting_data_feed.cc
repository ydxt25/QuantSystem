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

#include "quantsystem/common/global.h"
#include "quantsystem/engine/data_feeds/backtesting_data_feed.h"
namespace quantsystem {
namespace engine {
namespace datafeeds {
BacktestingDataFeed::BacktestingDataFeed(
    IAlgorithm* algorithm, BacktestNodePacket* job,
    IResultHandler* result_handler)
    : FileSystemDataFeed(algorithm, job, result_handler) {
    data_feed_ = DataFeedEndpoint::kBacktesting;
}

BacktestingDataFeed::~BacktestingDataFeed() {
  
}
}  // namespace datafeeds
}  // namespace engine
}  // namespace quantsystem
