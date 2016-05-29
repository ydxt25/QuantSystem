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

#ifndef QUANTSYSTEM_ENGINE_DATA_STREAM_H_
#define QUANTSYSTEM_ENGINE_DATA_STREAM_H_

#include <vector>
using std::vector;
#include <map>
using std::map;
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/data/base_data.h"
#include "quantsystem/engine/data_feeds/idata_feed.h"

namespace quantsystem {
using data::BaseData;
using engine::datafeeds::IDataFeed;
namespace engine {
/**
 * Data stream class takes a datafeed hander and converts it into a
 * synchronized enumerable data format for looping  in the primary
 * algorithm thread.
 * @ingroup EngineLayer
 */
class DataStream {
 public:
  typedef map<int, vector<BaseData*>> BaseDataVectorMap;
  typedef map<DateTime, BaseDataVectorMap> DateMapValue;
  typedef vector<DateMapValue> DataVector;
  /**
   * Process over the datafeed cross thread bridges to generate an enumerable
   * sorted collection of the data, ready for a consumer to use and
   * already synchronized in time.
   * @param feed DataFeed object
   * @param frontier_origin Starting date for the data feed
   * @param data[out] The collection of the data
   */
  static void GetData(
       IDataFeed* feed, const DateTime& frontier_origin, DataVector* data);

  /**
   * Waits until the data feed is ready for the data stream to
   * pull data from it.
   * @param feed The IDataFeed instance populating the bridges
   * @param data_stream_frontier The frontier of the data stream
   */
  static void WaitForDataOrEndOfBridges(
      const IDataFeed* feed, const DateTime& data_stream_frontier);

  /**
   * Check if all the bridges have data or are dead before starting the analysis
   * This determines whether or not the data stream can pull data
   * from the data feed..
   * @param feed Feed Interface with concurrent connection
   * between producer and consumer
   * @return Boolean true more data to download
   */
  static bool AllBridgesHaveData(const IDataFeed* feed);

 private:
  // Count of bridges and subscriptions
  static int subscriptions_;
};

}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_DATA_STREAM_H_
