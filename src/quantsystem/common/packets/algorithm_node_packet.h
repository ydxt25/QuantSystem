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

#ifndef QUANTSYSTEM_COMMON_PACKETS_ALGORITHM_NODE_PACKET_H_
#define QUANTSYSTEM_COMMON_PACKETS_ALGORITHM_NODE_PACKET_H_

#include <string>
using std::string;
#include "quantsystem/common/global.h"
#include "quantsystem/common/packets/packet.h"

namespace quantsystem {
namespace packets {
/**
 * Algorithm Node Packet is a work task for the Engine
 * @ingroup CommonBasePackets
 */
class AlgorithmNodePacket : public Packet {
 public:
  int user_id;  // User id placing request
  int project_id;  // Project id of the request
  string session_id;  // User session id for authentication
  UserPlan user_plan;   // User subscriptions state - free or paid
  string compile_id;  // Unique compile id of this backtest
  string algorithm;
  // Request source - Web IDE or APi - for controlling result handler
  string request_source;
  // DataFeed plugin name to select for the task
  DataFeedEndpoint::Enum data_endpoint;
  // Transaction handler plugin to select for the task
  TransactionHandlerEndpoint::Enum transaction_endpoint;
  // Result endpoint plugin to select for the task
  ResultHandlerEndpoint::Enum result_endpoint;
  // Setup handler endpoint for this task
  SetupHandlerEndpoint::Enum setup_endpoint;
  // Realtime events hander for this task
  RealTimeEndpoint::Enum real_time_endpoint;

  /**
   * Default constructor for the algorithm node
   * @param type Packet type
   */
  explicit AlgorithmNodePacket(PacketType type);

  /**
   * Standard destructor.
   */
  virtual ~AlgorithmNodePacket();

  /**
   * Algorithm Id - BacktestId or DeployId -
   * Common Id property between packets.
   */
  string AlgorithmId() const;

 private:
  AlgorithmNodePacket();
};

}  // namespace packet
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_PACKETS_ALGORITHM_NODE_PACKET_H_
