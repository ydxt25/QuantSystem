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

#include "quantsystem/common/data/consolidators/tradebar_consolidator.h"

namespace quantsystem {
namespace data {
namespace consolidators {
TradeBarConsolidator::TradeBarConsolidator(
    const TimeSpan& period)
    : max_count_(-1),
      current_count_(0),
      last_emit_(DateTime::DateTimeInvalid()) {
  period_ = period;
}

TradeBarConsolidator::TradeBarConsolidator(
    int max_count)
    : period_(TimeSpan::TimeSpanInvalid()),
      current_count_(0),
      last_emit_(DateTime::DateTimeInvalid()) {
  max_count_ = max_count;
}

TradeBarConsolidator::TradeBarConsolidator(
    int max_count,
    const TimeSpan& period)
    : current_count_(0),
      last_emit_(DateTime::DateTimeInvalid()) {
  max_count_ = max_count;
  period_ = period;
}

TradeBarConsolidator::~TradeBarConsolidator() {
}

void TradeBarConsolidator::Update(BaseData* data) {
  scoped_ptr<const TradeBar> trade_data;
  trade_data.reset(
      dynamic_cast<const TradeBar*>(data));
  if (!trade_data.get()) {
    LOG(FATAL) << "Input are not TradeBar instance?";
    return;
  }
  AggregateBar(*trade_data, working_bar_.get());
  bool fire_data_consolidated = false;
  if (max_count_ >= 0) {
    current_count_++;
    if (current_count_ >= max_count_) {
      current_count_ = 0;
      fire_data_consolidated = true;
    }
  }
  if (period_.is_valid()) {
    if (!last_emit_.is_valid()) {
      last_emit_ = trade_data->time();
    }
    if (trade_data->time() - last_emit_ >= period_) {
      fire_data_consolidated = true;
    }
  }
  if (fire_data_consolidated) {
    if (period_.is_valid()) {
      last_emit_ = trade_data->time();
    }
    OnDataConsolidated(working_bar_.get());
    working_bar_.reset(NULL);
  }
}

TradeBarConsolidator* TradeBarConsolidator::FromResolution(
    Resolution::Enum resolution) {
  switch (resolution) {
    case Resolution::kTick:
      return new TradeBarConsolidator(0);
    case Resolution::kSecond:
      return new TradeBarConsolidator(TimeSpan::FromSeconds(1));
    case Resolution::kMinute:
      return new TradeBarConsolidator(TimeSpan::FromMinutes(1));
    case Resolution::kHour:
      return new TradeBarConsolidator(TimeSpan::FromHours(1));
    case Resolution::kDaily:
      return new TradeBarConsolidator(TimeSpan::FromDays(1));
    default:
      // Should not be reached
      LOG(FATAL) << "Wrong input? resolution = " << resolution;
      return NULL;
  }
}

void TradeBarConsolidator::AggregateBar(const TradeBar& data,
                                        TradeBar* working_bar) {
  if (working_bar == NULL) {
    working_bar = new TradeBar(data);
  } else {
    working_bar->set_close(data.close());
    working_bar->set_volume(data.volume());
    if (data.low() < working_bar->low()) {
      working_bar->set_low(data.low());
    }
    if (data.high() > working_bar->high()) {
      working_bar->set_high(data.high());
    }
  }
}

void TradeBarConsolidator::OnDataConsolidated(BaseData* consolidated) {
  DataConsolidated(consolidated);
  DataConsolidator::OnDataConsolidated(consolidated);
}

}  // namespace consolidators
}  // namespace data
}  // namespace quantsystem
