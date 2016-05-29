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

#include "quantsystem/common/packets/algorithm_node_packet.h"
#include "quantsystem/common/packets/live_node_packet.h"
#include "quantsystem/common/packets/backtest_node_packet.h"
namespace quantsystem {
namespace packets {
AlgorithmNodePacket::AlgorithmNodePacket(PacketType type)
    : Packet(type),
      user_id(0),
      project_id(0),
      session_id(""),
      user_plan(kFree),
      compile_id(""),
      request_source("WebIDE"),
      data_endpoint(DataFeedEndpoint::kBacktesting),
      transaction_endpoint(TransactionHandlerEndpoint::kBacktesting),
      result_endpoint(ResultHandlerEndpoint::kBacktesting) {
}

AlgorithmNodePacket::~AlgorithmNodePacket() {
}

string AlgorithmNodePacket::AlgorithmId() const{
  if (type == kLiveNode) {
    LiveNodePacket* p = NULL;
    p = dynamic_cast<LiveNodePacket*>(const_cast<AlgorithmNodePacket*>(this));
    if (p) {
      return p->deploy_id;
    } else {
      return "";
    }
  }
  BacktestNodePacket* p = NULL;
  p = dynamic_cast<BacktestNodePacket*>(const_cast<AlgorithmNodePacket*>(this));
  if (p) {
    return p->backtest_id;
  }
  return "";
}

}  // namespace packets
}  // namespace quantsystem
