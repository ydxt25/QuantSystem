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

#include "quantsystem/engine/real_time/real_time_event.h"
namespace quantsystem {
namespace engine {
namespace realtime {
RealTimeEvent::RealTimeEvent(const TimeSpan& trigger_time,
                             const CallBackType* callback)
    : triggered_ (false),
      trigger_time_(trigger_time) {
  callback_.reset(callback);
}

void RealTimeEvent::Scan(const DateTime& time) {
  if (triggered_) {
    return;
  }
  if (time.TimeOfDay() > trigger_time_) {
    triggered_ = true;
    (*callback_)();
  }
}

void RealTimeEvent::Reset() {
  triggered_ = false;
}

}  // namespace realtime
}  // namespace engine
}  // namespace quantsystem
