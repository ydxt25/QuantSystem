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

#include <typeinfo>
#include <thread>
#include <chrono>
#include "quantsystem/common/util/stl_util.h"
#include "quantsystem/common/data/market/ticks.h"
#include "quantsystem/common/data/market/tradebars.h"
#include "quantsystem/common/time/time_helpers.h"
#include "quantsystem/engine/data_feeds/filesystem_data_feed.h"

namespace quantsystem {
using data::market::Ticks;
using data::market::TradeBars;
namespace engine {
namespace datafeeds {

namespace {
const int kBridgeMax = 500000;
}  // anonymous namespace

FileSystemDataFeed::FileSystemDataFeed(
    IAlgorithm* algorithm, BacktestNodePacket* job,
    IResultHandler* result_handler)
    : bridge_max_(kBridgeMax),
      exit_triggered_(false),
      end_of_streams_(false),
      ticks_type_(typeid(Ticks).name()),
      tradebars_type_(typeid(TradeBars).name()),
      algorithm_(algorithm),
      job_(job),
      result_handler_(result_handler) {
  is_active_ = true,
  subscriptions_ = algorithm->subscription_manager()->subscriptions;
  subscriptions_count_ = subscriptions_.size();
  data_feed_ = DataFeedEndpoint::kFileSystem;
  bridge_.resize(subscriptions_count_);
  end_of_bridge_.resize(subscriptions_count_);
  subscription_reader_managers_.resize(subscriptions_count_);
  fill_forward_frontiers_.resize(subscriptions_count_);
  bridge_max_ /= subscriptions_count_;
}

FileSystemDataFeed::~FileSystemDataFeed() {
  PurgeData();
}

void FileSystemDataFeed::ResetActivators() {
  for (int i = 0; i < subscriptions_count_; ++i) {
    end_of_bridge_[i] = false;
    subscription_reader_managers_[i] =
        new SubscriptionDataReader(
            subscriptions_[i],
            (*algorithm_->securities())[subscriptions_[i]->symbol],
            data_feed_, job_->period_start, job_->period_finish,
            result_handler_);
    fill_forward_frontiers_[i] = DateTime::DateTimeInvalid();
  }
}

int FileSystemDataFeed::GetActiveStreams() {
  int active_streams = 0;
  for (int i = 0; i < end_of_bridge_.size(); ++i) {
    if (end_of_bridge_[i] == false) {
      active_streams++;
    }
  }
  return active_streams;
}

TimeSpan FileSystemDataFeed::CalculateIncrement(bool include_tick) {
  TimeSpan increment = TimeSpan::FromDays(1);
  for (int i = 0; i < subscriptions_.size(); ++i) {
    SubscriptionDataConfig* config = subscriptions_[i];
    switch (config->resolution) {
      case Resolution::kHour:
        if (increment > TimeSpan::FromHours(1)) {
          increment = TimeSpan::FromHours(1);
        }
        break;
      case Resolution::kMinute:
        if (increment > TimeSpan::FromMinutes(1)) {
          increment = TimeSpan::FromMinutes(1);
        }
        break;
      case Resolution::kSecond:
        if (increment > TimeSpan::FromSeconds(1)) {
          increment = TimeSpan::FromSeconds(1);
        }
        break;
      case Resolution::kTick:
        if (increment > TimeSpan::FromMilliseconds(1) && include_tick) {
          increment = TimeSpan::FromMilliseconds(1);
        }
        break;
    }
  }
  return increment;
}

void FileSystemDataFeed::Run() {
  ResetActivators();
  TimeSpan tradebar_increments = CalculateIncrement(false);
  TimeSpan increment = CalculateIncrement(true);
  DateTime frontier;
  int active_streams = subscriptions_count_;
  vector<DateTime> dates;
  time::EachTradeableDay(algorithm_->securities(), job_->period_start,
                         job_->period_finish, &dates);
  for (int i = 0; i < dates.size(); ++i) {
    const DateTime& date = dates[i];
    frontier = date + increment;
    active_streams = subscriptions_count_;
    // Initialize the feeds to this date
    for (int j = 0; j < subscriptions_count_; ++j) {
      bool success = subscription_reader_managers_[j]->RefreshSource(date);
      // If we know the market is closed for security then
      // can declare bridge closed
      if (success) {
        end_of_bridge_[j] = false;
      } else {
        end_of_bridge_[j] = true;
      }
    }

    int bridge_full_count = 1;
    int bridge_zero_count = 0;
    int active = GetActiveStreams();
    // Pause here
    while (bridge_full_count > 0 &&
           ((subscriptions_count_ - active) == bridge_zero_count) &&
           !exit_triggered_) {
      bridge_full_count = GetBridgeFullCount();
      bridge_zero_count = GetBridgeZeroCount();
      std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    if (exit_triggered_) {
      break;
    }

    while ((frontier.Date() == date.Date() ||
            frontier == date.Date() + TimeSpan::FromDays(1)) &&
           !exit_triggered_) {
      vector<vector<BaseData*> > cache(subscriptions_count_);
      DateTime early_time = DateTime::DateTimeInvalid();
      for (int j = 0; j < subscriptions_count_; ++j) {
        SubscriptionDataReader* manager = subscription_reader_managers_[j];
        if (manager->EndOfStream() || end_of_bridge_[j]) {
          end_of_bridge_[j] = true;
          active_streams = GetActiveStreams();
          if (active_streams == 0) {
            frontier = frontier + TimeSpan::FromDays(1);
          }
          continue;
        }
        // Add the last iteration to the new list:
        // only if it falls into this time category
        while (manager->current()->time() < frontier) {
          cache[j].push_back(manager->current()->Clone());
          if (!manager->MoveNext()) {
            break;
          }
        }
        // Save the next earliest time from the bridges:
        // only if we're not filling forward
        if (manager->current() != NULL) {
          if (!early_time.is_valid() ||
              manager->current()->time() < early_time) {
            early_time = manager->current()->time();
          }
        }
      }
      if (active_streams == 0) {
        break;
      }
      // Add all the lists to the bridge, release the bridge
      // we push all the data up to this frontier into the bridge at once
      for (int j = 0; j < subscriptions_count_; ++j) {
        if (cache[j].size() > 0) {
          fill_forward_frontiers_[j] = cache[j][0]->time();
          bridge_[j].push(cache[j]);
        }
        ProcessFillForward(subscription_reader_managers_[j],
                           j, tradebar_increments);
      }
      // This will let consumers know we have loaded data up to this date
      // So that the data stream doesn't pull off data from the same time
      // period in different events
      loaded_data_frontier_ = frontier;
      if (early_time.is_valid() && early_time > frontier) {
        frontier = early_time;
      } else {
        frontier += increment;
      }
    }  // End of this day
    if (exit_triggered_) {
      break;
    }
  }  // End of all days
  LOG(INFO) << "DataFeed completed.";
  // Make sure all bridges empty before declaring "end of bridge"
  while (!EndOfBridges() && !exit_triggered_) {
    for (int i = 0; i < subscriptions_count_; ++i) {
      if (bridge_[i].size() == 0 &&
          subscription_reader_managers_[i]->EndOfStream()) {
        end_of_bridge_[i] = true;
      }
    }
    if (GetActiveStreams() == 0) {
      end_of_streams_ = true;
    }
    std::this_thread::sleep_for(std::chrono::seconds(100));
  }
  // Close up all streams
  for (int i = 0; i < subscriptions_count_; ++i) {
    subscription_reader_managers_[i]->Dispose();
  }
  LOG(INFO) << "DataFeed ending thread.";
  is_active_ = false;
}

void FileSystemDataFeed::ProcessFillForward(
    const SubscriptionDataReader* manager, int i,
    const TimeSpan& increment) {
  // Fillforward only applied to QS TradeBars
  if (!manager->is_qs_tradebar() || subscriptions_[i]->fill_data_forward ||
      manager->previous() == NULL) {
    return;
  }
  // Last tradebar and the current one we're about to add to queue
  BaseData* previous = manager->previous();
  BaseData* current = manager->current();
  if (!fill_forward_frontiers_[i].is_valid()) {
    fill_forward_frontiers_[i] = previous->time();
  }
  // Data ended before the market closed:
  // premature ending flag - continue filling forward until market close.
  if (manager->EndOfStream() && manager->MarketOpen(current->time())) {
    for (DateTime date = fill_forward_frontiers_[i] + increment;
         manager->MarketOpen(date); date += increment) {
      vector<BaseData*> cache;
      BaseData* fillforward_data = current->Clone();
      fillforward_data->set_time(date);
      fill_forward_frontiers_[i] = date;
      cache.push_back(fillforward_data);
      bridge_[i].push(cache);
    }
    return;
  }
  // Once per increment, add a new cache to the Bridge:
  // If the current.Time is before market close, (e.g. suspended trading at 2pm)
  // the date is always greater than currentTime and fillforward never runs.
  // In this circumstance we need to keep looping till market/extended
  // hours close even if no data.
  for (DateTime date = fill_forward_frontiers_[i] + increment;
       (date < current->time()); date += increment) {
    // If we don't want aftermarket data, rewind it backwards
    // until the market closes.
    if (!subscriptions_[i]->extended_market_hours) {
      if (!manager->MarketOpen(date)) {
        date = current->time();
        do {
          date -= increment;
        } while (manager->MarketOpen(date));
      }
    } else {
      if (!manager->ExtendedMarketOpen(date)) {
        continue;
      }
    }
    vector<BaseData*> cache;
    BaseData* fillforward_data = previous->Clone();
    fillforward_data->set_time(date);
    fill_forward_frontiers_[i] = date;
    cache.push_back(fillforward_data);
    bridge_[i].push(cache);
  }
}

int FileSystemDataFeed::GetBridgeFullCount() const {
  int count = 0;
  for (IDataFeed::BridgeType::const_iterator it = bridge_.begin();
       it != bridge_.end(); ++it) {
    if (it->size() >= bridge_max_) {
      count++;
    }
  }
  return count;
}

int FileSystemDataFeed::GetBridgeZeroCount() const {
  int count = 0;
  for (IDataFeed::BridgeType::const_iterator it = bridge_.begin();
       it != bridge_.end(); ++it) {
    if (it->size() == 0) {
      count++;
    }
  }
  return count;
}

void FileSystemDataFeed::Exit() {
  exit_triggered_ = true;
  ClearBridge();
}

void FileSystemDataFeed::PurgeData() {
  STLDeleteElements(&subscription_reader_managers_);
  fill_forward_frontiers_.clear();
  end_of_bridge_.clear();
  STLDeleteElements(&subscriptions_);
  ClearBridge();
}

void FileSystemDataFeed::ClearBridge() {
  for (IDataFeed::BridgeType::iterator it = bridge_.begin();
       it != bridge_.end(); ++it) {
    while (!it->empty()) {
      vector<BaseData*> data = it->front();
      it->pop();
      for (int i = 0; i < data.size(); ++i) {
        delete data[i];
      }
      data.clear();
    }
  }
}

bool FileSystemDataFeed::EndOfBridges() const {
  for (int i = 0; i < bridge_.size(); ++i) {
    if (bridge_[i].size() != 0 || end_of_bridge_[i] != true ||
        end_of_streams_ != true) {
      return false;
    }
  }
  return true;
}

}  // namespace datafeeds
}  // namespace engine
}  // namespace quantsystem
