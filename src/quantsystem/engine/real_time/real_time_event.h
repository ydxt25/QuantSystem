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

#ifndef QUANTSYSTEM_ENGINE_REAL_TIME_REAL_TIME_EVENT_H_
#define QUANTSYSTEM_ENGINE_REAL_TIME_REAL_TIME_EVENT_H_

#include <functional>
using std::function;
#include "quantsystem/common/base/scoped_ptr.h"
#include "quantsystem/common/time/time_span.h"
#include "quantsystem/common/time/date_time.h"
namespace quantsystem {
namespace engine {
namespace realtime {
/**
 * Realtime event object for holding information on the event time and callback.
 * @ingroup EngineLayerRealTime
 */
class RealTimeEvent {
 public:
  typedef function<void()> CallBackType;
  /**
   * Setup new event to fire at a specific time. Managed by a RealTimeHandler
   * thread.
   * @param trigger_time Time of day to trigger this event
   * @param callback Action to run when the time passes
   */
  RealTimeEvent(const TimeSpan& trigger_time, const CallBackType* callback);

  /**
   * Scan this event to see if this real time event has been triggered.
   * @param name Current real or simulation time
   */
  void Scan(const DateTime& time);

  /**
   * Reset the triggered flag.
   */
  void Reset();

 private:
  TimeSpan trigger_time_;  // Trigger Timing
  scoped_ptr<const CallBackType> callback_;
  bool triggered_;  // Trigger Action
};

}  // namespace realtime
}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_REAL_TIME_REAL_TIME_EVENT_H_
