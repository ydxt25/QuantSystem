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

#include "quantsystem/common/packets/order_event_packet.h"

namespace quantsystem {
namespace packets {
OrderEventPacket::OrderEventPacket() : Packet(kOrderEvent) {
}

OrderEventPacket::OrderEventPacket(
    const string& in_algorithm_id,
    const OrderEvent& in_event)
    : Packet(kOrderEvent),
      algorithm_id(in_algorithm_id),
      event(in_event) {
}

OrderEventPacket::~OrderEventPacket() {
}

}  // namespace packets
}  // namespace quantsystem
