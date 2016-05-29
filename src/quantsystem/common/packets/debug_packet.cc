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

#include "quantsystem/common/packets/debug_packet.h"

namespace quantsystem {
namespace packets {
DebugPacket::DebugPacket()
    : Packet(kDebug),
      message(""),
      algorithm_id(""),
      compile_id(""),
      project_id(0) {
}


DebugPacket::DebugPacket(const string& in_message,
                         const string& in_algorithm_id,
                         const string& in_compile_id, int in_project_id)
    : Packet(kDebug),
      message(in_message),
      algorithm_id(in_algorithm_id),
      compile_id(in_compile_id),
      project_id(in_project_id) {
}

DebugPacket::~DebugPacket() {
}

bool DebugPacket::LiveMessage() {
  if (algorithm_id.size() > 2) {
    return algorithm_id.substr(0, 2) == "L:";
  }
  return false;
}
}  // namespace packets
}  // namespace quantsystem
