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

#ifndef QUANTSYSTEM_ENGINE_REAL_TIME_BACKTESTING_REAL_TIME_HANDLER_H_
#define QUANTSYSTEM_ENGINE_REAL_TIME_BACKTESTING_REAL_TIME_HANDLER_H_

#include <vector>
using std::vector;
#include "quantsystem/interfaces/ialgorithm.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/engine/real_time/real_time_event.h"
#include "quantsystem/engine/real_time/ireal_time_handler.h"
#include "quantsystem/common/packets/algorithm_node_packet.h"
namespace quantsystem {
using interfaces::IAlgorithm;
using packets::AlgorithmNodePacket;
namespace engine {
namespace realtime {
/**
 * Psuedo realtime event processing for backtesting to
 * simulate realtime events in fast forward.
 * @ingroup EngineLayerRealTime
 */
class BacktestingRealTimeHandler : public IRealTimeHandler {
 public:
  /**
   * Setup the algorithm data, cash, job start end date etc.
   */
  BacktestingRealTimeHandler(IAlgorithm* algorithm,
                             AlgorithmNodePacket* job);

  virtual ~BacktestingRealTimeHandler();

  /**
   * Given a list of events, set it up for this day.
   * @param date Date for event
   */
  virtual void SetupEvents(const DateTime& date);

  /**
   * Normally this would run the realtime event monitoring, but
   * since the backtesting is in fastforward he realtime is linked to
   * the backtest clock.
   * This thread does nothing. Wait until the job is over.
   */
  virtual void Run();

  /**
   * Add a new event to the processing list.
   * @param new_event Event object to montitor daily.
   */
  virtual void AddEvent(RealTimeEvent* new_event);

  /**
   * Scan the event list with the current market time and see
   * if we need to trigger the callback.
   */
  virtual void ScanEvents();

  /**
   * Reset all the event flags for a new day.
   */
  virtual void ResetEvents();

  /**
   * Clear all the events in the list.
   */
  virtual void ClearEvents();

  /**
   * Set the current time for the event scanner (so we can use
   * same code for backtesting and live events).
   * @param time Current real or backtest time
   */
  virtual void SetTime(const DateTime& time);

  /**
   * Trigger and exit signal to terminate real time event scanner.
   */
  virtual void Exit();

 private:
  bool exit_triggered_;
  AlgorithmNodePacket* job_;
  IAlgorithm* algorithm_;
};

}  // namespace realtime
}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_REAL_TIME_BACKTESTING_REAL_TIME_HANDLER_H_
