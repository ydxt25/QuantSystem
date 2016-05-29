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

#ifndef QUANTSYSTEM_COMMON_PACKETS_LIVE_RESULT_PACKET_H_
#define QUANTSYSTEM_COMMON_PACKETS_LIVE_RESULT_PACKET_H_

#include <string>
using std::string;
#include <map>
using std::map;
#include "quantsystem/common/base/scoped_ptr.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/global.h"
#include "quantsystem/common/securities/security_holding.h"
#include "quantsystem/common/util/charting.h"
#include "quantsystem/common/orders/order.h"
#include "quantsystem/common/packets/packet.h"
#include "quantsystem/common/packets/live_node_packet.h"

namespace quantsystem {
using securities::Holding;
namespace packets {
class LiveResult;

/**
 * Live result packet from the engine algorithm.
 * @ingroup CommonBasePackets
 */
class LiveResultPacket : public Packet {
 public:
  int user_id;  // User id sending result packet
  int project_id;  // Projetc id of the result packet
  string session_id;  // User session id who issued the result packet
  string deploy_id;  // Live algorithm id for this result packet
  string compile_id;  // Compile id algorithm which generated this result packet
  scoped_ptr<LiveResult> results;  // Result data object for this result packet
  // Processing time / running time for the live algorithm
  double processing_time;

  /**
   * Standard constructor.
   */
  LiveResultPacket();

  /**
   * Compose the packet from a JSON string
   * @param json JSON string
   */
  explicit LiveResultPacket(const string& json);

  /**
   * Compose live result packet with tradable dates.
   * @param job Job that started this request
   * @param results Results class for the backtest job
   */
  LiveResultPacket(const LiveNodePacket& job, LiveResult* in_results);

  /**
   * Standard destructor.
   */
  virtual ~LiveResultPacket();
};

/**
 * Live results object class for packaging live result data.
 * @ingroup CommonBasePackets
 */
class LiveResult {
 public:
  // Charts updates for the live algorithm since the last result packet
  map<string, Chart*> charts;
  // Holdings dictionary of algorithm holdings information
  map<string, Holding*> holdings;
  // Order updates since the last result packet
  map<int, Order*> orders;
  // Trade profit and loss information since the last algorithm result packet
  map<DateTime, double> profit_loss;
  // Statistics information sent during the algorithm operations.
  map<string, string> statistics;
  // Runtime banner/updating statistics in the title banner of
  // the live algorithm GUI.
  map<string, string> runtime_statistics;
  // Server status information, including CPU/RAM usage, ect...
  map<string, string> server_statistics;

  /**
   * Standard constructor.
   */
  LiveResult();

  /**
   * Constructor for the result class for dictionary objects
   */
  LiveResult(const map<string, Chart*>& in_charts,
             const map<int, Order*>& in_orders,
             const map<DateTime, double>& in_profit_loss,
             const map<string, Holding*>& in_holdings,
             const map<string, string>& in_statistics,
             const map<string, string>& in_runtime,
             const map<string, string>& in_server_statistics);

  /**
   * Standard destructor.
   */
  virtual ~LiveResult();
};

}  // namespace packets
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_PACKETS_LIVE_RESULT_PACKET_H_
