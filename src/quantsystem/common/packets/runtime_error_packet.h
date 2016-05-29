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

#ifndef QUANTSYSTEM_COMMON_PACKETS_RUNTIME_ERROR_PACKET_H_
#define QUANTSYSTEM_COMMON_PACKETS_RUNTIME_ERROR_PACKET_H_

#include <string>
using std::string;
#include "quantsystem/common/global.h"
#include "quantsystem/common/packets/packet.h"

namespace quantsystem {
namespace packets {
/**
 * Algorithm runtime error packet from the engine.
 * This is a managed error which stops the algorithm execution.
 * @ingroup CommonBasePackets
 */
class RuntimeErrorPacket : public Packet {
 public:
  string message;  // Runtime error message from the exception
  string algorithm_id;  // Algorithm id which generated this runtime error
  // Error stack trace information string passed through from the exception
  string stack_trace;

  /**
   * Standard constructor.
   */
  RuntimeErrorPacket();

  /**
   * Initialize the base class and setup the packet type.
   */
  RuntimeErrorPacket(const string& in_algorithm_id,
                     const string& in_message,
                     const string& in_stack_trace = "");

  /**
   * Standard destructor.
   */
  virtual ~RuntimeErrorPacket();
};

}  // namespace packets
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_PACKETS_RUNTIME_ERROR_PACKET_H_
