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

#ifndef QUANTSYSTEM_COMMON_TIME_TIME_SPAN_H_
#define QUANTSYSTEM_COMMON_TIME_TIME_SPAN_H_

#include <time.h>
#ifndef _MSC_VER
#include <sys/time.h>
#else
#include <stdlib.h>
#endif

#include "quantsystem/common/base/integral_types.h"
#include "quantsystem/common/base/port.h"

namespace quantsystem {
/**
 * Represents a time interval.
 * @ingroup CommonGeneric
 */
class TimeSpan {
 public:
  /**
   * Construct a Timespan from a specified number of days.
   * @return A TimeSpan.
   *
   * @see FromHours
   */
  static TimeSpan FromDays(const double& days);

  /**
   * Construct a Timespan from a specified number of hours.
   * @return A TimeSpan.
   *
   * @see FromDays
   * @see FromMinutes
   */
  static TimeSpan FromHours(const double& hours);

  /**
   * Construct a Timespan from a specified number of minutes.
   * @return A TimeSpan.
   *
   * @see FromHours
   * @see FromSeconds
   */
  static TimeSpan FromMinutes(const double& minutes);

  /**
   * Construct a Timespan from a specified number of seconds.
   * @return A TimeSpan.
   *
   * @see FromMinutes
   */
  static TimeSpan FromSeconds(const double& seconds);

  /**
   * Construct a Timespan from a specified number of milliseconds.
   * @return A TimeSpan.
   *
   */
  static TimeSpan FromMilliseconds(const int& milliseconds);

  /**
   * Construct an invalid Timespan.
   * @return An invalid Timespan.
   */
  static TimeSpan TimeSpanInvalid();

  /**
   * Standard constructor.
   */
  TimeSpan();

  /**
   * Copy constructor.
   */
  TimeSpan(const TimeSpan& span);

  /**
   * Construct a Timespan from seconds.
   */
  explicit TimeSpan(const double& seconds);

  /**
   * Construct a TimeSpan from a timeval.
   *
   * param time Can contain fractional seconds.
   */
  explicit TimeSpan(const struct timeval& span);

  /**
   * Construct a Timespan from hours, minutes, and seconds.
   */
  TimeSpan(const int32& hours, const int32& minutes, const int32& seconds);

  /**
   * Standard destructor.
   */
  virtual ~TimeSpan();

  /**
   * Determine if we have a valid TimeSpan or not.
   */
  bool is_valid() const { return span_.tv_sec != kInvalidEpoch_; }

  /**
   * Determine relative ordering of this time span relative to another.
   * @param span The time span to compare against.
   * @return <0 if this time span is smallier, >0 if this time span is larger,
   *   or 0 if the time span are equal.
   */
  int Compare(const TimeSpan& span) const {
    return span_.tv_sec == span.span_.tv_sec
        ? span_.tv_usec - span.span_.tv_usec
        : span_.tv_sec - span.span_.tv_sec;
  }

  /**
   * Determine if this time span is equal to another.
   */
  bool operator ==(const TimeSpan& span) const {
    return Compare(span) == 0 && is_valid();
  }

  /**
   * Determine if this time span is smaller than another.
   */
  bool operator <(const TimeSpan& span) const {
    return Compare(span) < 0 && is_valid();
  }

  /**
   * Determine if this time span is larger than another.
   */
  bool operator >(const TimeSpan& span) const {
    return Compare(span) > 0 && span.is_valid();
  }

  /**
   * Determine if this date is different from another.
   */
  bool operator !=(const TimeSpan& span) const {
    return Compare(span) != 0 && is_valid();
  }

  /**
   * Determine if this smaller or equal to another.
   */
  bool operator <=(const TimeSpan& span) const {
    return Compare(span) <= 0 && is_valid();
  }

  /**
   * Determine if this larger or equal to another.
   */
  bool operator >=(const TimeSpan& span) const {
    return Compare(span) >= 0 && span.is_valid();
  }

  /**
   * Reasign this date to another.
   */
  TimeSpan& operator=(const TimeSpan& span) {
    span_ = span.span_;
    return *this;
  }

  /**
   * Add another TimeSpan.
   */
  TimeSpan& operator +=(const TimeSpan& span) {
    span_.tv_sec += span.span_.tv_sec;
    span_.tv_usec += span.span_.tv_usec;
    return *this;
  }

  /**
   * Minus another TimeSpan.
   */
  TimeSpan& operator -=(const TimeSpan& span) {
    span_.tv_sec -= span.span_.tv_sec;
    span_.tv_usec -= span.span_.tv_usec;
    return *this;
  }

  /**
   * Get timeval.
   */
  void GetTimeval(struct timeval* timeval) const { *timeval = span_; }

  /**
   * Get total seconds.
   */
  double TotalSeconds() const;

  /**
   * Get total minutes.
   */
  double TotalMinutes() const;

  /*
   * Get total days.
   */
  double TotalDays() const;

 private:
  struct timeval span_;
  static const time_t kInvalidEpoch_;

  /**
   * Mark this TimeSpan as being invalid.
   */
  void MarkInvalid();
};

/**
 * @relates TimeSpan
 */
TimeSpan operator +(const TimeSpan& t1, const TimeSpan& t2);

/**
 * @relates TimeSpan
 */
TimeSpan operator -(const TimeSpan& t1, const TimeSpan& t2);

}  // namespace quantsystem

#endif  // QUANTSYSTEM_COMMON_TIME_TIME_SPAN_H_
