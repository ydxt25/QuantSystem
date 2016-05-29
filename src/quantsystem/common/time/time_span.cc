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
#include <glog/logging.h>

namespace quantsystem {
namespace {
inline struct timeval make_timeval(time_t sec, int usec) {
  struct timeval tv;
  tv.tv_sec = sec;
  tv.tv_usec = usec;
  return tv;
}
}  // anonymous namespace

static const struct timeval kInvalidTimeval_ = make_timeval(-1, 0);
const time_t TimeSpan::kInvalidEpoch_ = -1;

TimeSpan TimeSpan::FromDays(const double& days) {
  double secs;
  secs = days * 24 * 3600;
  return TimeSpan(secs);
}

TimeSpan TimeSpan::FromHours(const double& hours) {
  double secs;
  secs = hours * 3600;
  return TimeSpan(secs);
}

TimeSpan TimeSpan::FromMinutes(const double& minutes) {
  double secs;
  secs = minutes * 60;
  return TimeSpan(secs);
}

TimeSpan TimeSpan::FromSeconds(const double& seconds) {
  return TimeSpan(seconds);
}

TimeSpan TimeSpan::FromMilliseconds(const int& milliseconds)  {
  double secs;
  const double kMilliPerSecond = 1000.0;
  secs = milliseconds / kMilliPerSecond;
  return TimeSpan(secs);
}

TimeSpan TimeSpan::TimeSpanInvalid() {
  TimeSpan t;
  t.MarkInvalid();
  return t;
}

TimeSpan::TimeSpan() {
  span_.tv_sec = 0;
  span_.tv_usec = 0;
}

TimeSpan::TimeSpan(const TimeSpan& span) : span_(span.span_) {
}

TimeSpan::TimeSpan(const double& seconds) {
  int64 secs = static_cast<int64>(seconds);
  const int64 kMicrosPerSecond = 1000000;
  int64 microsecs = static_cast<int64>((seconds - secs) * kMicrosPerSecond);
  span_.tv_sec = secs;
  span_.tv_usec = microsecs;
}

TimeSpan::TimeSpan(const struct timeval& span) : span_(span) {
}

TimeSpan::TimeSpan(const int32& hours, const int32& minutes,
                       const int32& seconds) {
  int64 secs;
  secs = hours * 3600 + minutes * 60 + seconds;
  span_.tv_sec = secs;
  span_.tv_usec = 0;
}

TimeSpan::~TimeSpan() {
}

double TimeSpan::TotalSeconds() const {
  const double kMicrosPerSecond = 1000000.0;
  return static_cast<double>(span_.tv_sec + span_.tv_usec / kMicrosPerSecond);
}

double TimeSpan::TotalMinutes() const {
  return TotalSeconds() / 60.0;
}

double TimeSpan::TotalDays() const {
  return TotalMinutes() / 60.0 / 24.0;
}

void TimeSpan::MarkInvalid() {
  span_ = kInvalidTimeval_;
}

TimeSpan operator +(const TimeSpan& t1, const TimeSpan& t2) {
  TimeSpan result = t1;
  result += t2;
  return result;
}

TimeSpan operator -(const TimeSpan& t1, const TimeSpan& t2) {
  TimeSpan result = t1;
  result -= t2;
  return result;
}
}  // namespace quantsystem
