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

#include "quantsystem/common/packets/market_today_packet.h"

namespace quantsystem {
namespace packets {
MarketToday::MarketToday()
    : pre_market(MarketHours(4, 9.5)),
      open(MarketHours(9.5, 16)),
      post_market(MarketHours(16, 20)) {
}

MarketToday::~MarketToday() {
}

MarketHours::MarketHours() {
}

MarketHours::MarketHours(double default_start, double default_end) {
  start = TimeSpan::FromHours(default_start);
  end = TimeSpan::FromHours(default_end);
}

MarketHours::~MarketHours() {
}
}  // namespace packets
}  // namespace quantsystem
