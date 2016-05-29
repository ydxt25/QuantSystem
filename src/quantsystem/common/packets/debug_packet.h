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

#ifndef QUANTSYSTEM_COMMON_PACKETS_DEBUG_PACKET_H_
#define QUANTSYSTEM_COMMON_PACKETS_DEBUG_PACKET_H_

#include <string>
using std::string;
#include "quantsystem/common/packets/packet.h"

namespace quantsystem {
namespace packets {
/**
 * Send a simple debug message from the users algorithm to the console.
 * @ingroup CommonBasePackets
 */
class DebugPacket : public Packet {
 public:
  string message;  // String debug message to send to the user's console
  string algorithm_id;  // Associated algorithm id
  string compile_id;  // Compile id of the algorithm sending this message
  int project_id;  // Project id for this message

  /**
   * Boolean flag indicating this is a live message and
   * should bypass messaging restrictions
   */
  bool LiveMessage();

  /**
   * Standard constructor.
   */
  DebugPacket();

  /**
   * Create a new instance of the notify Log packet
   */
  DebugPacket(const string& in_message, const string& in_algorithm_id,
              const string& in_compile_id, int in_project_id);

  /**
   * Standard destructor.
   */
  virtual ~DebugPacket();
};

}  // namespace packets
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_PACKETS_DEBUG_PACKET_H_
