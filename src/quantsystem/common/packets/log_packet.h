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

#ifndef QUANTSYSTEM_COMMON_PACKETS_LOG_PACKET_H_
#define QUANTSYSTEM_COMMON_PACKETS_LOG_PACKET_H_

#include <string>
using std::string;
#include "quantsystem/common/packets/packet.h"

namespace quantsystem {
namespace packets {
/**
 * Simple log message instruction 
 * @ingroup CommonBasePackets
 */
class LogPacket : public Packet {
 public:
  string message;  // Log message to the users console
  string algorithm_id;  // Algorithm id requesting this logging

  /**
   * Standard constructor.
   */
  LogPacket();

  /**
   * Create a new instance of the notify Log packet
   */
  LogPacket(const string& in_algorithm_id, const string& in_message);

  /**
   * Standard destructor.
   */
  virtual ~LogPacket();
};

}  // namespace packets
}  // namespace quantsystem

#endif  // QUANTSYSTEM_COMMON_PACKETS_LOG_PACKET_H_
