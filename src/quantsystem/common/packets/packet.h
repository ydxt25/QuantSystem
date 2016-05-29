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

/**
 * @defgroup CommonBasePackets Common - Base Packets Components
 * 
 * Base packets components of Quantsystem.
 */
#ifndef QUANTSYSTEM_COMMON_PACKETS_PACKET_H_
#define QUANTSYSTEM_COMMON_PACKETS_PACKET_H_

#include <string>
using std::string;

namespace quantsystem {
namespace packets {
enum PacketType {
  kNone,  // Default, unset
  kAlgorithmNode,  // Base type for backtest and live work
  kAutocompleteWork,  // Autocomplete Work Packet
  kAutocompleteResult,  // Result of the Autocomplete Job:
  kBacktestNode,  // Controller->Backtest Node Packet:
  kBacktestResult,  // Packet out of backtest node:
  kBacktestWork,  // API-> Controller Work Packet:
  kLiveNode,  // Controller -> Live Node Packet:
  kLiveResult,  // Live Node -> User Packet:
  kLiveWork,  // API -> Controller Packet:
  kSecurityTypes,  // Node -> User Algo Security Types
  kBacktestError,  // Controller -> User Error in Backtest Settings:
  kAlgorithmStatus,  // Nodes -> User Algorithm Status Packet:
  kBuildWork,  // API -> Compiler Work Packet:
  kBuildSuccess,  // Compiler -> User Build Success
  kBuildError,  // Compiler -> User, Compile Error
  kRuntimeError,  // Node -> User Algorithm Runtime Error
  kLog,  // Nodes -> User Log Message
  kDebug,  // Nodes -> User Debug Message
  kOrderEvent,  // Nodes -> User, Order Update Event
  kSuccess  // Boolean true/false success
};

/**
 * Base class for packet messaging system
 * @ingroup CommonBasePackets
 */
class Packet {
 public:
  PacketType type;
  string channel;

  /**
   * Standard constructor.
   */
  Packet();

  /**
   * Initialize the base class and setup the packet type.
   * @param in_type PaketType for the class.
   */
  explicit Packet(PacketType in_type);

  /**
   * Standard destructor.
   */
  virtual ~Packet();
};

}  // namespace packets
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_PACKETS_PACKET_H_
