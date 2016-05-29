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

/**
 * @defgroup EngineLayerRealTime  Engine Layer - Real Time Components
 *
 * Real Time Components in Engine Layer.
 */
#ifndef QUANTSYSTEM_ENGINE_REAL_TIME_IREAL_TIME_HANDLER_H_
#define QUANTSYSTEM_ENGINE_REAL_TIME_IREAL_TIME_HANDLER_H_

#include <vector>
using std::vector;
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/engine/real_time/real_time_event.h"
namespace quantsystem {
namespace engine {
namespace realtime {
/**
 * Real time event handler, trigger functions at regular or pretimed intervals.
 * @ingroup EngineLayerRealTime
 */
class IRealTimeHandler {
 public:
  /**
   * Main entry point to scan and trigger the realtime events.
   */
  virtual void Run() = 0;

  /**
   * Given a list of events, set it up for this day.
   * @param date Date for event
   */
  virtual void SetupEvents(const DateTime& date) = 0;

  /**
   * Add a new event to the processing list.
   * @param new_event Event object to montitor daily.
   */
  virtual void AddEvent(RealTimeEvent* new_event) = 0;

  /**
   * Scan the event list with the current market time and see
   * if we need to trigger the callback.
   */
  virtual void ScanEvents() = 0;

  /**
   * Reset all the event flags for a new day.
   */
  virtual void ResetEvents() = 0;

  /**
   * Clear all the events in the list.
   */
  virtual void ClearEvents() = 0;

  /**
   * Set the current time for the event scanner (so we can use
   * same code for backtesting and live events).
   * @param time Current real or backtest time
   */
  virtual void SetTime(const DateTime& time) = 0;

  /**
   * Trigger and exit signal to terminate real time event scanner.
   */
  virtual void Exit() = 0;

  DateTime time() const { return time_; }

  vector<RealTimeEvent*>& events() { return events_; }

  bool is_active() const { return is_active_; }

 protected:
  // The real time handlers internal record of current time
  // used to scan the events
  DateTime time_;

  // List of events we're monitoring
  vector<RealTimeEvent*> events_;

  // Thread status flag
  bool is_active_;
};

}  // namespace realtime
}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_REAL_TIME_IREAL_TIME_HANDLER_H_
