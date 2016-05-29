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

#ifndef QUANTSYSTEM_COMMON_PACKETS_SECURITY_TYPES_PACKET_H_
#define QUANTSYSTEM_COMMON_PACKETS_SECURITY_TYPES_PACKET_H_

#include <string>
using std::string;
#include <vector>
using std::vector;
#include "quantsystem/common/global.h"
#include "quantsystem/common/packets/packet.h"
namespace quantsystem {
namespace packets {
/**
 * Security types packet contains information
 * on the markets the user data has requested.
 * @ingroup CommonBasePackets
 */
class SecurityTypesPacket : public Packet {
 public:
  vector<SecurityType::Enum> types;

  /**
   * CSV formatted, lower case list of SecurityTypes for the web API.
   */
  string TypesCVS();

  /**
   * Standard constructor.
   */
  SecurityTypesPacket();

  /**
   * Standard destructor.
   */
  virtual ~SecurityTypesPacket();
};

}  // namespace packets
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_PACKETS_SECURITY_TYPES_PACKET_H_
