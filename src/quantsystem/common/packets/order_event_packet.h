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

#ifndef QUANTSYSTEM_COMMON_PACKETS_ORDER_EVENT_PACKET_H_
#define QUANTSYSTEM_COMMON_PACKETS_ORDER_EVENT_PACKET_H_

#include <string>
using std::string;
#include "quantsystem/common/global.h"
#include "quantsystem/common/orders/order_event.h"
#include "quantsystem/common/packets/packet.h"

namespace quantsystem {
using orders::OrderEvent;
namespace packets {
/**
 * Order event packet for passing updates
 * on the state of an order to the portfolio.
 *
 * As an order is updated in pieces/partial fills
 * the order fill price is passed back to the Algorithm Portfolio method.
 * @ingroup CommonBasePackets
 */
class OrderEventPacket : public Packet {
 public:
  OrderEvent event;  // Order event object
  string algorithm_id;  // Algorithm id for this order event

  /**
   * Standard constructor.
   */
  OrderEventPacket();

  /**
   * Initialize the base class and setup the packet type.
   * @param in_type PaketType for the class.
   */
  OrderEventPacket(const string& in_algorithm_id, const OrderEvent& in_event);

  /**
   * Standard destructor.
   */
  virtual ~OrderEventPacket();
};

}  // namespace packets
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_PACKETS_ORDER_EVENT_PACKET_H_
