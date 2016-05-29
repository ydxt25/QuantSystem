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

#ifndef QUANTSYSTEM_COMMON_PACKETS_ALGORITHM_STATUS_PACKET_H_
#define QUANTSYSTEM_COMMON_PACKETS_ALGORITHM_STATUS_PACKET_H_

#include <string>
using std::string;
#include "quantsystem/common/global.h"
#include "quantsystem/common/packets/packet.h"
namespace quantsystem {
namespace packets {
/**
 * Algorithm status update information packet
 * @ingroup CommonBasePackets
 */
class AlgorithmStatusPacket : public Packet {
 public:
  AlgorithmStatus::Enum status;  // Current algorithm status
  string message;  // Optional message or reason for state change
  string algorithm_id;  // Algorithm id associated with this status package

  /**
   * Standard constructor.
   */
  AlgorithmStatusPacket();

  /**
   * Construct a algorithm state packet from values.
   */
  AlgorithmStatusPacket(const string& in_algorithm_id,
                        AlgorithmStatus::Enum in_status,
                        const string& in_message="");

  /**
   * Standard destructor.
   */
  virtual ~AlgorithmStatusPacket();
};

}  // namespace packets
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_PACKETS_ALGORITHM_STATUS_PACKET_H_
