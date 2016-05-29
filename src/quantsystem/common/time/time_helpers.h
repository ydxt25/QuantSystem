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

#ifndef QUANTSYSTEM_COMMON_TIME_H_
#define QUANTSYSTEM_COMMON_TIME_H_

#include <vector>
using std::vector;
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/securities/security_manager.h"

namespace quantsystem {
using securities::SecurityManager;
namespace time {
/**
 * Time helper class collection for working with trading dates
 * @ingroup CommonGeneric
 */
/**
 * Get a vector of datetime objects in a date range.
 * @param from DateTime start date
 * @param thru DateTime end date
 * @param[out] days Vector datetime
 */
void EachDay(const DateTime& from, const DateTime& thru,
             vector<DateTime>* days);

/**
 * Get a vector of datetime objects of tradeable dates - skip he holidays
 * and weekends when securities in this algorithm don't trade.
 * @param securities Securities manager from the algorithm
 * @param from Start date
 * @param thru End date
 * @param[out] days Vector tradeable datetime 
 */
void EachTradeableDay(const SecurityManager* securities,
                      const DateTime& from,
                      const DateTime& thru,
                      vector<DateTime>* days);

/**
 * Make sure this date is not a holiday, or weekend for the
 * securities in this algorithm.
 * @param securities Securities manager from the algorithm
 * @param day DateTime to check if tradeable
 * @return True if tradeable date
 */
bool TradeableDate(const SecurityManager* securities,
                   const DateTime& day);

/**
 * The number of tradeable dates within this period.
 * @param securities Securities manager from the algorithm
 * @param start Start of Date
 * @param finish End of Date
 * @return Number of dates
 */
int TradeableDates(const SecurityManager* securities,
                   const DateTime& start,
                   const DateTime& finish);
}  // namespace time
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_TIME_H_
