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

#include "quantsystem/common/time/time_span.h"
#include "quantsystem/common/time/time_helpers.h"
#include "quantsystem/common/securities/security.h"

namespace quantsystem {
using securities::Security;
namespace time {
void EachDay(const DateTime& from, const DateTime& thru,
             vector<DateTime>* days) {
}

void EachTradeableDay(const SecurityManager* securities,
                      const DateTime& from,
                      const DateTime& thru,
                      vector<DateTime>* days) {
  for (DateTime day = from.Date(); day.Date() <= thru.Date();
       day += TimeSpan::FromDays(1)) {
    if (TradeableDate(securities, day)) {
      days->push_back(day);
    }
  }
}

bool TradeableDate(const SecurityManager* securities,
                   const DateTime& day) {
  bool tradeable = false;
  vector<const Security*> values;
  securities->Values(&values);
  for (const Security* security : values) {
    if (security->exchange()->DateIsOpen(day)) {
      tradeable = true;
      return tradeable;
    }
  }
  return tradeable;
}

int TradeableDates(const SecurityManager* securities,
                   const DateTime& start,
                   const DateTime& finish) {
}

}  // namespace time
}  // namespace quantsystem
