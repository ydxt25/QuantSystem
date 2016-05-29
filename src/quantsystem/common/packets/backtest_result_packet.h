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

#ifndef QUANTSYSTEM_COMMON_PACKETS_BACKTEST_RESULT_PACKET_H_
#define QUANTSYSTEM_COMMON_PACKETS_BACKTEST_RESULT_PACKET_H_

#include <string>
using std::string;
#include <map>
using std::map;
#include "quantsystem/common/global.h"
#include "quantsystem/common/packets/packet.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/util/charting.h"
#include "quantsystem/common/orders/order.h"
#include "quantsystem/common/packets/backtest_node_packet.h"

namespace quantsystem {
namespace packets {
/**
 * Backtest results object class - result specific items from the packet.
 * @ingroup CommonBasePackets
 */
class BacktestResult {
 public:
  // Chart updates in this backtest since the last backtest result
  // packet was sent.
  map<string, Chart> charts;
  // Order updates since the last backtest result packet was sent.
  map<int, Order> orders;
  // Profit and loss results from closed trades.
  map<DateTime, double> profit_loss;
  // Statistics information for the backtest.
  map<string, string> statistics;

  /**
   * Standard constructor.
   */
  BacktestResult();

  /**
   * Constructor for the result class using objects.
   */
  BacktestResult(const map<string, Chart>& in_charts,
                 const map<int, Order>& in_orders,
                 const map<DateTime, double>& in_profit_loss,
                 const map<string, string>& in_statistics);

  /**
   * Standard destructor.
   */
  virtual ~BacktestResult();
};

/**
 * Backtest result packet: send backtest information to GUI
 * for user consumption.
 * @ingroup CommonBasePackets
 */
class BacktestResultPacket : public Packet {
 public:
  int user_id;  // User id placing this task
  int project_id;  // Project id of this task
  string session_id;  // User session id
  string backtest_id;  // Backtest id for this result packet
  // Compile id for the algorithm which generated this result packet.
  string compile_id;
  // Start time of the backtest period as defined in Initialize() method.
  DateTime period_start;
  // End time of the backtest period as defined in the Initialize() method.
  DateTime period_finish;
  // DateTime (EST) the user requested this backtest.
  DateTime data_requested;
  // DateTime (EST) when the backtest was completed.
  DateTime data_finished;
  // Progress of the backtest as a percentage from 0-1 based
  // on the days lapsed from start-finish.
  double progress;
  // Runmode for this backtest.
  RunMode run_mode;
  string name;  // Name of this backtest
  BacktestResult results;  // Result data object for this backtest
  // Processing time of the algorithm
  // (from moment the algorithm arrived on the algorithm node)
  double processing_time;
  // Estimated number of tradeable days in the backtest based on
  // the start and end date or the backtest
  int tradeable_dates;

  /**
   * Standard constructor.
   */
  BacktestResultPacket();

  /**
   * Compose the packet from a JSON string.
   */
  explicit BacktestResultPacket(const string& jason);

  /**
   * Compose result data packet - with tradable dates
   * from the backtest job task and the partial result packet.
   * @param job Job that started this request
   * @param results Results class for the Backtest job
   * @param progress Progress of the packet. For the packet
   * we assume progess of 100%.
   */
  BacktestResultPacket(const BacktestNodePacket& job,
                       const BacktestResult& in_results,
                       double in_progress = 1.0);

  /**
   * Standard destructor.
   */
  virtual ~BacktestResultPacket();
};

}  // namespace packets
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_PACKETS_BACKTEST_RESULT_PACKET_H_
