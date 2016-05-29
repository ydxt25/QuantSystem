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

#include "quantsystem/common/packets/runtime_error_packet.h"
namespace quantsystem {
namespace packets {
RuntimeErrorPacket::RuntimeErrorPacket() : Packet(kRuntimeError) {
}

RuntimeErrorPacket::RuntimeErrorPacket(const string& in_algorithm_id,
                                       const string& in_message,
                                       const string& in_stack_trace)
    : Packet(kRuntimeError),
      algorithm_id(in_algorithm_id),
      message(in_message),
      stack_trace(in_stack_trace) {
}

RuntimeErrorPacket::~RuntimeErrorPacket() {
}
}  // namespace packets
}  // namespace quantsystem
