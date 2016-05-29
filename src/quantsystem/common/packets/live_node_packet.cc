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

#include "quantsystem/common/packets/live_node_packet.h"
namespace quantsystem {
namespace packets {
LiveNodePacket::LiveNodePacket()
    : AlgorithmNodePacket(kLiveNode),
      deploy_id(""),
      brokerage(""),
      access_token(""),
      refresh_token(""),
      life_time(TimeSpan::FromSeconds(0)),
      account_id(0) {
}

LiveNodePacket::~LiveNodePacket() {
}
}  // namespace packets
}  // namespace quantsystem
