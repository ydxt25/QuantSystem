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
#include "quantsystem/common/util/real_time.h"
#include <unistd.h>
#include <glog/logging.h>
#include <cstdlib>

namespace quantsystem {
void* Scanner(void *arg) {
  RealTimeSynchronizedTimer *real_timer = static_cast<RealTimeSynchronizedTimer*>(arg);
  while (!real_timer->stopped_) {
    if (real_timer->callback_ != NULL &&
        DateTime() >= real_timer->trigger_time_) {
      real_timer->trigger_time_ = DateTime() + real_timer->period_;
      real_timer->callback_->Run();
    }
    while (real_timer->paused_ && !real_timer->stopped_) {
      sleep(10);
    }
    sleep(1);
  }
  pthread_exit(NULL);
}

RealTimeSynchronizedTimer::RealTimeSynchronizedTimer()
    : callback_(NULL),
      stopped_(false),
      paused_(false) {
  period_ = TimeSpan::FromSeconds(0);
}

RealTimeSynchronizedTimer::RealTimeSynchronizedTimer(
    const TimeSpan& period, Closure* callback)
    : period_(period),
      callback_(callback),
      stopped_(false),
      paused_(false) {
}

RealTimeSynchronizedTimer::~RealTimeSynchronizedTimer() {
}

void RealTimeSynchronizedTimer::Start() {
  int rt = pthread_create(&thread_, NULL, Scanner, static_cast<void *>(this));
  if (rt) {
    LOG(FATAL) << "ERROR: pthread_create failed, rt=" << rt;
    exit(0);
  }
  trigger_time_ = DateTime() + period_;
}
}  // namespace quantsystem
