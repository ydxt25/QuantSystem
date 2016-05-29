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

#ifndef QUANTSYSTEM_COMMON_PACKETS_LIVE_NODE_PACKET_H_
#define QUANTSYSTEM_COMMON_PACKETS_LIVE_NODE_PACKET_H_

#include <string>
using std::string;
#include "quantsystem/common/global.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/time/time_span.h"
#include "quantsystem/common/packets/algorithm_node_packet.h"

namespace quantsystem {
namespace packets {
/**
 * Live job task packet: container for any live specific job variables.
 * @ingroup CommonBasePackets
 */
class LiveNodePacket : public AlgorithmNodePacket {
 public:
  string deploy_id;  // Deploy id for this live algorithm
  string brokerage;  // string name of the brokerage we're trading with
  string access_token;  // Access token for the broker login(oAuth 2.0)
  string refresh_token;  // Refresh token for brokerage login(oAuth 2.0)
  DateTime issued_at;  // DateTime the refresh token was issued(oAuth 2.0)
  TimeSpan life_time;  // Life span fo the issued access token(oAuth 2.0)
  int account_id;  // Account id for specified brokerage

  /**
   * Standard constructor.
   */
  LiveNodePacket();

  /**
   * Standard destructor.
   */
  virtual ~LiveNodePacket();
};

}  // namespace packets
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_PACKETS_LIVE_NODE_PACKET_H_
