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

#include <glog/logging.h>
#include <thread>
#include <chrono>
#include "quantsystem/configuration/configuration.h"
#include "quantsystem/engine/data_stream.h"

namespace quantsystem {
using configuration::Config;

namespace engine {
int DataStream::subscriptions_ = 0;

void DataStream::GetData(
    IDataFeed* feed, const DateTime& frontier_origin, DataVector* data) {
  DateTime early_time = DateTime::DateTimeInvalid();
  TimeSpan increment = TimeSpan::FromSeconds(1);
  subscriptions_ = feed->subscriptions().size();
  DateTime frontier = frontier_origin;
  while (feed->bridge().size() != subscriptions_) {
    std::this_thread::sleep_for(std::chrono::seconds(100));
  }
  while (!feed->EndOfBridges()) {
    early_time = DateTime::DateTimeInvalid();
    DateMapValue new_data;

    WaitForDataOrEndOfBridges(feed, frontier);
    for (int i = 0; i < subscriptions_; ++i) {
      while (feed->bridge()[i].size() > 0) {
        vector<BaseData*> result;
        result = feed->bridge()[i].front();
        if (result.size() > 0 && result[0]->time() > frontier) {
          if (!early_time.is_valid() || early_time >  result[0]->time()) {
            early_time = result[0]->time();
          }
          break;
        }
        // PUll a grouped time list out of the bridge
        vector<BaseData*> data_points;
        data_points = feed->bridge()[i].front();
        feed->bridge()[i].pop();
        for (int j = 0; j < data_points.size(); ++j) {
          BaseData* point = data_points[j];
          new_data[point->time()][i].push_back(point);
        }
      }
    }  // end for (int i = 0; i < subscriptions_; ++i)
    if (early_time.is_valid()) {
      frontier = early_time;
    } else {
      frontier += increment;
    }
    if (new_data.size() > 0) {
      data->push_back(new_data);
    }
  }
  LOG(INFO) << "All Streams Completed.";
}

void DataStream::WaitForDataOrEndOfBridges(
    const IDataFeed* feed, const DateTime& data_stream_frontier) {
  bool live_mode = Config::GetBool("livemode");
  // timeout to prevent infinite looping: 2sec for live and 30sec for non-live
  int sec = live_mode? 2 : 3;
  DateTime timeout = DateTime() + TimeSpan::FromSeconds(sec);
  while (!AllBridgesHaveData(feed) && DateTime() < timeout) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  // we want to verify that our data stream is never ahead of our data feed.
  // if we're out of data then the feed will never update
  while (data_stream_frontier > feed->loaded_data_frontier() &&
         !feed->EndOfBridges() &&  DateTime() < timeout) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

bool DataStream::AllBridgesHaveData(const IDataFeed* feed) {
  for (int i = 0; i < subscriptions_; ++i) {
    if ((feed->end_of_bridge())[i]) continue;
    if (feed->bridge()[i].size() == 0) {
      return false;
    }
  }
  return true;
}

}  // namespace engine
}  // namespace quantsystem
