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
#include "quantsystem/common/packets/security_types_packet.h"
#include "quantsystem/common/strings/case.h"

namespace quantsystem {
namespace packets {
SecurityTypesPacket::SecurityTypesPacket() : Packet(kSecurityTypes) {
}

SecurityTypesPacket::~SecurityTypesPacket() {
}

string SecurityTypesPacket::TypesCVS() {
  string result = "";
  for (int i = 0; i < types.size(); ++i) {
    result += SecurityType::SecurityTypeToString(types[i]);
    result += ",";
  }
  result = result.substr(0, result.size() - 1);
  LowerString(&result);
  return result;
}

}  // namespace packets
}  // namespace quantsystem
