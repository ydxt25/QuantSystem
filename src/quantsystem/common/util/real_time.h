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

#ifndef QUANTSYSTEM_COMMON_REAL_TIME_H_
#define QUANTSYSTEM_COMMON_REAL_TIME_H_
#include <pthread.h>
#include "quantsystem/common/base/callback.h"
#include "quantsystem/common/time/time_span.h"
#include "quantsystem/common/time/date_time.h"

namespace quantsystem {
/**
 * Real time timer class for precise callbacks on
 * a millisecond resolution in a self managed thread.
 * @ingroup CommonBaseUtil
 */
class RealTimeSynchronizedTimer {
 public:
  /**
   * Standard constructor.
   */
  RealTimeSynchronizedTimer();

  /**
   * Trigger an event callback after precisely milliseconds lapsed.
   * @param period delay period between event callbacks.
   * @param callback Callback event.
   */
  RealTimeSynchronizedTimer(const TimeSpan& period, Closure* callback);

  /**
   * Standard destructor.
   */
  virtual ~RealTimeSynchronizedTimer();

  /**
   * Start the synchronized real time timer - fire events
   * at start of each second or minute.
   */
  void Start();

  /**
   * Hang the real time event.
   */
  void Pause() {
    paused_ = true;
  }

  /**
   * Resume clock.
   */
  void Resume() {
    paused_ = false;
  }

  /**
   * Stop the real time timer.
   */
  void Stop() {
    stopped_ = true;
  }

 private:
  friend void* Scanner(void *arg);
  TimeSpan period_;
  Closure* callback_;
  pthread_t thread_;
  bool stopped_;
  DateTime trigger_time_;
  bool paused_;
};

}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_REAL_TIME_H_
