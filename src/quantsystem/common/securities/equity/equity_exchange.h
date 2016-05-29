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

#ifndef QUANTSYSTEM_COMMON_SECURITIES_EQUITY_EXCHANGE_H_
#define QUANTSYSTEM_COMMON_SECURITIES_EQUITY_EXCHANGE_H_

#include "quantsystem/common/time/time_span.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/securities/security_exchange.h"
namespace quantsystem {
namespace securities {
namespace equity {
/**
 * Equity exchange information.
 * @ingroup CommonBaseSecurities
 */
class EquityExchange : public SecurityExchange {
 public:
  /**
   * Standard constructor.
   */
  EquityExchange();

  /**
   * Standard destructor.
   */
  virtual ~EquityExchange();

  /**
   * Boolean flag indicating the equities exchange markets are open.
   */
  virtual bool ExchangeOpen() const {
    return DateTimeIsOpen(Time());
  }

  /**
   * Number of trading days in an equity calendar year - 252.
   */
  int TradingDaysPerYear() const { return 252; }

  /**
   * Check if this DateTime is open. Ignores early market closing times.
   * @param datetime DateTime to check
   * @return true if the market is open
   */
  virtual bool DateTimeIsOpen(const DateTime& datetime) const;

  /**
   * Set the incoming datetime object date to the market open time.
   * @param time Date we want to set
   * @return DateTime adjusted to market open
   */
  virtual DateTime TimeOfDayOpen(const DateTime& time);

  /**
   * Time of the day the market closes.
   * @param time DateTime object for this date
   * @param DateTime the market is considered closed
   */
  virtual DateTime TimeOfDayClosed(const DateTime& time);

  /**
   * Check if the US Equity markets are open on today's *date*.
   * Check the calendar holidays as well.
   * @param date Date to check
   * @return True if open
   */
  virtual bool DateIsOpen(const DateTime& date) const;

  /**
   * Check if the object is open including the *Extended* market hours
   * @param time Current time of day
   * @return true if we are in extended or primary marketing hours
   */
  virtual bool DateTimeIsExtendedOpen(const DateTime& time) const;
};

}  // namespace equity
}  // namespace securities
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SECURITIES_EQUITY_EXCHANGE_H_
