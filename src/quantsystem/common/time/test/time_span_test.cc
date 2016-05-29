/*
 * \copyright Copyright 2013 Google Inc. All Rights Reserved.
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
#include <string>
using std::string;

#include "quantsystem/common/time/time_span.h"
#include "quantsystem/common/time/date_time.h"
#include <glog/logging.h>
#include <gtest/gtest.h>

namespace quantsystem {

TEST(TimeSpan, TestConstructor) {
  TimeSpan span_zero;
  struct timeval tv;
  span_zero.GetTimeval(&tv);
  EXPECT_EQ(tv.tv_sec, 0);
  EXPECT_EQ(tv.tv_usec, 0);

  double secs5 = 5;
  TimeSpan span_secs(secs5);
  EXPECT_TRUE(span_secs.is_valid());
  EXPECT_EQ(secs5, span_secs.TotalSeconds());

  struct timeval tv_5s;
  tv_5s.tv_sec = 5;
  tv_5s.tv_usec = 0;
  TimeSpan span_tv_5s(tv_5s);
  EXPECT_TRUE(span_tv_5s.is_valid());
  EXPECT_EQ(tv_5s.tv_sec, span_tv_5s.TotalSeconds());

  TimeSpan span_2min(0, 2, 0);
  EXPECT_TRUE(span_2min.is_valid());
  EXPECT_EQ(2 * 60, span_2min.TotalSeconds());

  TimeSpan span_1day = TimeSpan::FromDays(1);
  EXPECT_TRUE(span_1day.is_valid());
  EXPECT_EQ(1*24*60*60, span_1day.TotalSeconds());

  TimeSpan span_1hour = TimeSpan::FromHours(1);
  EXPECT_TRUE(span_1hour.is_valid());
  EXPECT_EQ(60*60, span_1hour.TotalSeconds());

  TimeSpan span_1min = TimeSpan::FromMinutes(1);
  EXPECT_TRUE(span_1min.is_valid());
  EXPECT_EQ(60, span_1min.TotalSeconds());

  TimeSpan span_1sec = TimeSpan::FromSeconds(1);
  EXPECT_TRUE(span_1sec.is_valid());
  EXPECT_EQ(1, span_1sec.TotalSeconds());

  TimeSpan span_1millisec = TimeSpan::FromMilliseconds(1);
  EXPECT_TRUE(span_1millisec.is_valid());
  EXPECT_EQ(1 / 1000.0, span_1millisec.TotalSeconds());
}

TEST(TimeSpan, TestInvalid) {
  TimeSpan span_invalid = TimeSpan::TimeSpanInvalid();
  EXPECT_FALSE(span_invalid.is_valid());
}

TEST(TimSpan, Operation) {
  TimeSpan span_sec(1);
  TimeSpan span_2sec(2);
  span_sec += span_2sec;
  EXPECT_TRUE(span_sec.is_valid());
  EXPECT_EQ(3, span_sec.TotalSeconds());

  TimeSpan span_5sec = span_sec + span_2sec;
  EXPECT_TRUE(span_5sec.is_valid());
  EXPECT_EQ(5, span_5sec.TotalSeconds());

  TimeSpan span_3sec(3);
  TimeSpan span_large(10);
  span_large -= span_3sec;
  EXPECT_TRUE(span_large.is_valid());
  EXPECT_EQ(7, span_large.TotalSeconds());

  TimeSpan span_4sec = span_large - span_3sec;
  EXPECT_TRUE(span_4sec.is_valid());
  EXPECT_EQ(4, span_4sec.TotalSeconds());
}

TEST(TimeSpan, Compare) {
  TimeSpan span(1, 2, 3);
  EXPECT_EQ(0, span.Compare(span));
  EXPECT_FALSE(span < span);
  EXPECT_FALSE(span > span);
  EXPECT_FALSE(span != span);
  EXPECT_TRUE(span == span);
  EXPECT_TRUE(span <= span);

  TimeSpan span_10secs(0, 0, 10);
  for (int secs = 0; secs < 10; ++secs) {
    TimeSpan span_small(secs);
    EXPECT_GT(0, span_small.Compare(span_10secs)) << "secs=" << secs;
    EXPECT_LT(0, span_10secs.Compare(span_small)) << "secs=" << secs;

    EXPECT_TRUE(span_small <= span_10secs) << "secs=" << secs;
    EXPECT_TRUE(span_small < span_10secs) << "secs=" << secs;
    EXPECT_TRUE(span_10secs > span_small) << "secs=" << secs;
    EXPECT_TRUE(span_10secs >= span_small) << "secs=" << secs;
  }
}

TEST(TimeSpan, OperationWithDateTime) {
  DateTime date;
  struct timeval tv_now;
  date.GetTimeval(&tv_now);
  TimeSpan span(0, 0, 10);
  date -= span;
  struct timeval tv_before;
  date.GetTimeval(&tv_before);
  EXPECT_EQ(tv_now.tv_sec - 10, tv_before.tv_sec);
  EXPECT_EQ(tv_now.tv_usec, tv_before.tv_usec);

  date += span;
  struct timeval tv;
  date.GetTimeval(&tv);
  EXPECT_EQ(tv_now.tv_sec, tv_before.tv_sec + 10);
  EXPECT_EQ(tv_now.tv_usec, tv_before.tv_usec);

  DateTime date_before = date - span;
  date_before.GetTimeval(&tv_before);
  EXPECT_EQ(tv_now.tv_sec - 10, tv_before.tv_sec);
  EXPECT_EQ(tv_now.tv_usec, tv_before.tv_usec);

  TimeSpan span_res = date - date_before;
  EXPECT_TRUE(span_res == span);

  DateTime date_after;
  date_after = date + span;
  struct timeval tv_after;
  date.GetTimeval(&tv_now);
  date_after.GetTimeval(&tv_after);
  EXPECT_EQ(tv_now.tv_sec + 10, tv_after.tv_sec);
  EXPECT_EQ(tv_now.tv_usec, tv_after.tv_usec);

  DateTime test_time;
  test_time = DateTime() + TimeSpan::FromSeconds(2);
  EXPECT_TRUE(test_time.is_valid());
}

}

