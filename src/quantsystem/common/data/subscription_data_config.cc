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
#include "quantsystem/common/data/subscription_data_config.h"

namespace quantsystem {

namespace data {

SubscriptionDataConfig::SubscriptionDataConfig(
    const string&  object_type_name,
    const SecurityType::Enum& security_type, const string& security_symbol,
    Resolution::Enum security_resolution,
    const bool& fill_forward, const bool& extended_hours) {
  type_name = object_type_name;
  security = security_type;
  symbol = security_symbol;
  resolution = security_resolution;
  fill_data_forward = fill_forward;
  extended_market_hours = extended_hours;
  price_scale_factor = 1.0;
  mapped_symbol = symbol;

  switch (security_resolution) {
    case Resolution::kTick:
      increment = TimeSpan::FromSeconds(0);
      break;
    case Resolution::kSecond:
      increment = TimeSpan::FromSeconds(1);
      break;
    case Resolution::kMinute:
      increment = TimeSpan::FromMinutes(1);
      break;
    case Resolution::kHour:
      increment = TimeSpan::FromHours(1);
      break;
    case Resolution::kDaily:
      increment = TimeSpan::FromDays(1);
      break;
    default:
      LOG(FATAL) << "This can't happend, Security resolution = " <<
          security_resolution;
      break;
  }
}

SubscriptionDataConfig::SubscriptionDataConfig(
    const string& object_type_name,
    const string& security_symbol,
    const string& source) {
  type_name = object_type_name;
  security = SecurityType::kBase;
  resolution = Resolution::kSecond;
  increment = TimeSpan::FromSeconds(1);
  symbol = security_symbol;

  // NOT needed for user data
  fill_data_forward = true;
  extended_market_hours = false;
  price_scale_factor = 1.0;
  mapped_symbol = security_symbol;
}

SubscriptionDataConfig::~SubscriptionDataConfig() {
  for (ConsolidatorsVector::const_iterator it = consolidators.begin();
       it != consolidators.end(); ++it) {
    delete *it;
  }
}

}  // namespace data

}  // namespace quantsystem
