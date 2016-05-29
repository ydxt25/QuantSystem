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

#include "quantsystem/common/util/stl_util.h"
#include "quantsystem/common/orders/order.h"

namespace quantsystem {
namespace orders {

const map<int, string> OrderErrors::kErrorTypes = {
    {-1, "Order quantity must not be zero"},
    {-2, "There is no data yet for this security - "
     "please wait for data {market order price not available yet"},
    {-3, "Attempting market order outside of market hours"},
    {-4, "Insufficient capital to execute order"},
    {-5, "Exceeded maximum allowed orders for one analysis period"},
    {-6, "Order timestamp error. Order appears to be executing in the future"},
    {-7, "General error in order"},
    {-8, "Order has already been filled and cannot be modified"}};

OrderDirection Order::Direction() const {
  if (quantity > 0) {
    return kBuy;
  } else if (quantity < 0) {
    return kSell;
  } else {
    return kHold;
  }
}

Order::Order()
    : duration(kGTC),
      tag("") {
}
Order::Order(const string& in_symbol, int in_quantity, OrderType in_order,
             const DateTime& in_time, const double& in_price,
             const string& in_tag)
    : time(in_time),
      price(in_price),
      type(in_order),
      quantity(in_quantity),
      symbol(in_symbol),
      status(kNone),
      tag(in_tag),
      duration(kGTC),
      contingent_id(0) {
}

Order::~Order() {
}

}  // namespace orders
}  // namespace quantsystem
