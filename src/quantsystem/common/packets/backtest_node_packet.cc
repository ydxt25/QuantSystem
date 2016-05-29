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

#include "quantsystem/common/packets/backtest_node_packet.h"
namespace quantsystem {
namespace packets {
BacktestNodePacket::BacktestNodePacket()
    : AlgorithmNodePacket(kBacktestNode),
      name(""),
      backtest_id(""),
      tradeable_dates(0),
      run_mode(kSeries) {
}

BacktestNodePacket::BacktestNodePacket(
    int in_user_id,
    int in_project_id,
    const string& in_session_id,
    const string& algorithm_data,
    const double& starting_capital,
    const string& in_name,
    UserPlan in_user_plan)
    : AlgorithmNodePacket(kBacktestNode),
      backtest_id(""),
      tradeable_dates(0),
      run_mode(kSeries) {
  user_id = in_user_id;
  project_id = in_project_id;
  session_id = in_session_id;
  algorithm = algorithm_data;
  name = in_name;
  user_plan = in_user_plan;
}

BacktestNodePacket::~BacktestNodePacket() {
}

}  // namespace packets
}  // namespace quantsystem
