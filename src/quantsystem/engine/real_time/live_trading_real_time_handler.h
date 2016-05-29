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

#ifndef QUANTSYSTEM_ENGINE_REAL_TIME_LIVE_TRADING_REAL_TIME_HANDLER_H_
#define QUANTSYSTEM_ENGINE_REAL_TIME_LIVE_TRADING_REAL_TIME_HANDLER_H_

#include <map>
using std::map;
#include <vector>
using std::vector;
#include "quantsystem/interfaces/ialgorithm.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/interfaces/ibrokerage.h"
#include "quantsystem/engine/data_feeds/idata_feed.h"
#include "quantsystem/engine/results/iresult_handler.h"
#include "quantsystem/engine/real_time/real_time_event.h"
#include "quantsystem/engine/real_time/ireal_time_handler.h"
#include "quantsystem/common/packets/algorithm_node_packet.h"
#include "quantsystem/common/packets/market_today_packet.h"
namespace quantsystem {
using interfaces::IAlgorithm;
using interfaces::IBrokerage;
using engine::datafeeds::IDataFeed;
using engine::results::IResultHandler;
using packets::MarketToday;
using packets::AlgorithmNodePacket;
namespace engine {
namespace realtime {
/**
 * Live trading realtime event processing.
 * @ingroup EngineLayerRealTime
 */
class LiveTradingRealTimeHandler : public IRealTimeHandler {
 public:
  /**
   * Initialize the realtime event handler with all information required
   * for triggering daily events.
   */
  LiveTradingRealTimeHandler(const IAlgorithm* algorithm,
                             const IDataFeed* feed,
                             const IResultHandler* results,
                             const IBrokerage* brokerage,
                             const AlgorithmNodePacket* job);

  /**
   * Main entry point to scan and trigger the realtime events.
   */
  virtual void Run();

  /**
   * Given a list of events, set it up for this day.
   * @param date Date for event
   */
  virtual void SetupEvents(const DateTime& date);

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
  typedef map<SecurityType::Enum, MarketToday*> TodayMap;
  TodayMap today_;
  IDataFeed* feed_;
  IResultHandler* results_;
  TimeSpan end_of_day_delta_;
  IAlgorithm* algorithm_;
};

}  // namespace realtime
}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_REAL_TIME_LIVE_TRADING_REAL_TIME_HANDLER_H_
