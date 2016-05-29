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

#ifndef QUANTSYSTEM_COMMON_SECURITIES_SECURITY_EXCHANGE_H_
#define QUANTSYSTEM_COMMON_SECURITIES_SECURITY_EXCHANGE_H_

#include <string>
using std::string;
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/time/time_span.h"
namespace quantsystem {
namespace securities {
/**
 * Base exchange class providing information and
 * helper tools for reading the current exchange situation,
 * @ingroup CommonBaseSecurities
 */
class SecurityExchange {
 public:
  /**
   * Standard constructor.
   */
  SecurityExchange();

  /**
   * Standard destructor.
   */
  virtual ~SecurityExchange();

  string time_zone() const { return time_zone_; }
  void set_time_zone(const string& time_zone) { time_zone_ = time_zone; }

  TimeSpan market_open() const { return market_open_; }
  void set_market_open(const TimeSpan& value) { market_open_ = value; }

  TimeSpan market_close() const { return market_close_; }
  void set_market_close(const TimeSpan& value) { market_close_ = value; }

  /**
   * Number of trading days per year for this security.
   * By default the market is open 365 days per year.
   *
   * Used for performance statistics to calculate sharpe ratio accurately.
   */
  int TradingDaysPerYear() const { return 356; }

  /**
   * Time from the most recent data.
   */
  DateTime Time() const { return frontier_; }

  /**
   * set the current datetime.
   * @param time Most recent data tick
   */
  void SetDataTimeFrontier(const DateTime& time) {
    frontier_ = time;
  }

  /**
   * Check if the exchange is open.
   */
  virtual bool ExchangeOpen() const { return DateTimeIsOpen(frontier_); }

  /**
   * Check if we are past a certain time: simple method for wrapping datetime.
   */
  bool TimeIsPast(int hour, int min, int sec = 0);

  /**
   * Check if the input date is open.
   * @param date Date to check
   * @return true if exchange is open for this date
   */
  virtual bool DateIsOpen(const DateTime& date) const { return true; }

  /**
   * Time of the day the market opens.
   * @param time DateTime object for this date
   * @return DateTime the market is considered open
   */
  virtual DateTime TimeOfDayOpen(const DateTime& time) {
    // Default to midnight, start of day
    return time;
  }

  /**
   * Time of the day the market closes.
   * @param time DateTime object for this date
   * @param DateTime the market is considered closed
   */
  virtual DateTime TimeOfDayClosed(const DateTime& time) {
    // Default to midnight, start of *next* day
    TimeSpan span = TimeSpan::FromDays(1);
    return (time + span);
  }

  /**
   * Check if this DateTime is open.
   * @param datetime DateTime to check
   * @return true if the market is open
   */
  virtual bool DateTimeIsOpen(const DateTime& datetime) const {
    return DateIsOpen(datetime);
  }

  /**
   * Check if the object is open including the *Extended* market hours
   * @param time Current time of day
   * @return true if we are in extended or primary marketing hours
   */
  virtual bool DateTimeIsExtendedOpen(const DateTime& time) const {
    return DateIsOpen(time);
  }

 private:
  DateTime frontier_;
  TimeSpan market_open_;  // Default market open time 00:00
  TimeSpan market_close_;  // Defualt market closing time 24:00
  string time_zone_;  // Timezone for the exchange
};

}  // namespace securities
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SECURITIES_SECURITY_EXCHANGE_H_
