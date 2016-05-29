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

#ifndef QUANTSYSTEM_COMMON_PACKETS_MARKET_TODAY_PACKET_H_
#define QUANTSYSTEM_COMMON_PACKETS_MARKET_TODAY_PACKET_H_

#include <string>
using std::string;
#include <map>
using std::map;
#include "quantsystem/common/global.h"
#include "quantsystem/common/time/time_span.h"
#include "quantsystem/common/time/date_time.h"

namespace quantsystem {
namespace packets {
class MarketToday;
/**
 * Wrapper Containers for Deserializing Calendar Information from API.
 * @ingroup CommonBasePackets
 */
class MarketTodayContainer {
 public:
  map<SecurityType::Enum, MarketToday> markets;
};

/**
 * Market open hours model for pre, normal and post market hour definitions.
 * @ingroup CommonBasePackets
 */
class MarketHours {
 public:
  TimeSpan start;  // Start time for this market hour category
  TimeSpan end;  // End time for this market hour category

  /**
   * Standard constructor.
   */
  MarketHours();

  /**
   * Market hours initializer given an hours
   * since midnight measure for the market hours today
   * @param default_start Time in hours since midnight to start this open period
   * @param default_end Time in hours since midnight to end this open period
   */
  MarketHours(double default_start, double default_end);

  /**
   * Standard destructor.
   */
  virtual ~MarketHours();
};

/**
 * Market today information class.
 * @ingroup CommonBasePackets
 */
class MarketToday {
 public:
  DateTime now;

  /**
   * Date this packet was generated.
   */
  DateTime Date() const { return now; }

  // Given the dates and times above,
  // what is the current market status - open or closed.
  string status;
  MarketHours pre_market;  // Premarket hours for today
  MarketHours open;  // Normal trading market hours for today
  MarketHours post_market;  // Post market hours for today

  /**
   * Standard constructor.
   */
  MarketToday();

  /**
   * Standard destructor.
   */
  virtual ~MarketToday();
};

}  // namespace packets
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_PACKETS_MARKET_TODAY_PACKET_H_
