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
 * @defgroup CommonBaseOrders Common - Base Orders Components
 *
 * Base order components of Quantsystem.
 */

#ifndef QUANTSYSTEM_COMMON_ORDERS_ORDER_EVENT_H_
#define QUANTSYSTEM_COMMON_ORDERS_ORDER_EVENT_H_

#include <cstdlib>
#include <string>
using std::string;
#include "quantsystem/common/orders/order.h"

namespace quantsystem {
namespace orders {
/**
 * Order Event - Messaging class signifying a change in an order state and
 * record the change in the user's alogrithm portfolio.
 *
 * @ingroup CommonBaseOrders
 */
class OrderEvent {
 public:
  int order_id;  // Id of the order this event comes from
  string symbol;  // Order symbol associated with this event
  OrderStatus status;  // Status message of the order
  double fill_price;  // Fill price information about the order
  // Number of shares of the order that was filled in this event
  int fill_quantity;
  string message;  // Any message from the exchange

  /**
   * Absolute of quantity - filled.
   */
  int AbsoluteFillQuantity() const { return abs(fill_quantity); }

  /**
   * Order direction
   */
  OrderDirection Direction() const {
    return (fill_quantity > 0) ? kBuy : kSell;
  }

  /**
   * Standard constructor.
   */
  OrderEvent();

  /*
   * Construct from values.
   * @param in_id Id of the parent order
   * @param in_symbol Asset symbol
   * @param in_status Status of the order
   * @param in_fill_price Fill price information if applicable
   * @param in_fill_quantity Fill quantity
   * @param in_message Message from the exchange
   */
  OrderEvent(int in_id, const string& in_symbol="",
             OrderStatus in_status=kNone, double in_fill_price=0,
             int in_fill_quantity=0, const string& in_message="");
  /*
   * Construt a new OrderEvent using order.
   * @param order Order for this order status
   * @param message Message from exchange.
   */
  OrderEvent(Order order, const string& message="");

  /**
   * Standard destructor.
   */
  virtual ~OrderEvent();
};  
}  // namespace orders
}  // namespace quantsystem

#endif  // QUANTSYSTEM_COMMON_ORDERS_ORDER_EVENT_H_
