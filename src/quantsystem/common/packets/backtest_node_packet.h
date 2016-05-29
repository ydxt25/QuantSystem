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

#ifndef QUANTSYSTEM_COMMON_PACKETS_BACKTEST_NODE_PACKET_H_
#define QUANTSYSTEM_COMMON_PACKETS_BACKTEST_NODE_PACKET_H_

#include <string>
using std::string;
#include "quantsystem/common/global.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/packets/algorithm_node_packet.h"

namespace quantsystem {
namespace packets {
/**
 * Algorithm backtest task information packet.
 * @ingroup CommonBasePackets
 */
class BacktestNodePacket : public AlgorithmNodePacket {
 public:
  string name;  // Name of the backtest as randomly defined in the IDE
  string backtest_id;  // Backtest/Agorithm id for this task
  DateTime period_start;  // Backtest start
  DateTime period_finish;  // Backtest end date
  // Estimated number of trading days in this backtest task
  // based on the start - end dates
  int tradeable_dates;
  RunMode run_mode;  // Series or parallel runmode for the backtest

  /**
   * Standard constructor.
   */
  BacktestNodePacket();

  /**
   * Initialize the backtest task packet.
   */
  BacktestNodePacket(int in_user_id, int in_project_id,
                     const string& in_session_id, const string& algorithm_data,
                     const double& starting_capital, const string& in_name,
                     UserPlan in_user_plan = kFree);

  /**
   * Standard destructor.
   */
  virtual ~BacktestNodePacket();
};

}  // namespace packets
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_PACKETS_BACKTEST_NODE_PACKET_H_
