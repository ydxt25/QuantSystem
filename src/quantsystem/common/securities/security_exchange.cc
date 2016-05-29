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

#include <time.h>
#include "quantsystem/common/securities/security_exchange.h"
namespace quantsystem {
namespace securities {
SecurityExchange::SecurityExchange()
    : market_open_(TimeSpan::FromHours(0)),
      market_close_(TimeSpan::FromHours(23.999999)) {
}

SecurityExchange::~SecurityExchange() {
}

bool SecurityExchange::TimeIsPast(int hour, int min, int sec) {
  struct tm time;
  frontier_.GetLocalTime(&time);
  if (time.tm_hour > hour) {
    return true;
  } else if (time.tm_hour < hour) {
    return false;
  } else if (time.tm_hour == hour) {
    if (time.tm_min > min) {
      return true;
    } else if (time.tm_min < min) {
      return false;
    } else if (time.tm_min == min) {
      if (time.tm_sec >= sec) {
        return true;
      } else if (time.tm_sec < sec) {
        return false;
      }
    }
  }
  return false;
}

}  // namespace securities
}  // namespace quantsystem
