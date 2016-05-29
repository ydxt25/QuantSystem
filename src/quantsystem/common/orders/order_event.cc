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

#include "quantsystem/common/orders/order_event.h"
namespace quantsystem {
namespace orders {
OrderEvent::OrderEvent() {
}

OrderEvent::OrderEvent(int in_id, const string& in_symbol,
                       OrderStatus in_status, double in_fill_price,
                       int in_fill_quantity, const string& in_message)
    : order_id(in_id),
      status(in_status),
      symbol(in_symbol),
      fill_price(in_fill_price),
      fill_quantity(in_fill_quantity),
      message(in_message) {
}

OrderEvent::OrderEvent(Order order, const string& message)
    : order_id(order.id),
      status(order.status),
      symbol(order.symbol),
      message(message),
      fill_quantity(0),
      fill_price(0) {
}

OrderEvent::~OrderEvent() {
}
}  // namespace orders
}  // namespace quantsystem
