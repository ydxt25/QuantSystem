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

#include "quantsystem/common/packets/live_result_packet.h"
namespace quantsystem {
namespace packets {
LiveResultPacket::LiveResultPacket()
    : Packet(kLiveResult),
      user_id(0),
      project_id(0),
      processing_time(0) {
}


LiveResultPacket::LiveResultPacket(const string& json)
    : Packet(kLiveResult) {
  // TODO(shishougang)
}

LiveResultPacket::LiveResultPacket(
    const LiveNodePacket& job,
    LiveResult* in_results)
    : Packet(kLiveResult),
      user_id(job.user_id),
      project_id(job.project_id),
      session_id(job.session_id),
      deploy_id(job.deploy_id),
      compile_id(job.compile_id) {
  results.reset(in_results);
  channel = job.channel;
}

LiveResultPacket::~LiveResultPacket() {
}

LiveResult::LiveResult() {
}

LiveResult::LiveResult(const map<string, Chart*>& in_charts,
                       const map<int, Order*>& in_orders,
                       const map<DateTime, double>& in_profit_loss,
                       const map<string, Holding*>& in_holdings,
                       const map<string, string>& in_statistics,
                       const map<string, string>& in_runtime,
                       const map<string, string>& in_server_statistics) {
  charts = in_charts;
  orders = in_orders;
  profit_loss = in_profit_loss;
  holdings = in_holdings;
  statistics = in_statistics;
  runtime_statistics = in_runtime;
  server_statistics = in_server_statistics;
}

LiveResult::~LiveResult() {
}
}  // namespace packets
}  // namespace quantsystem
