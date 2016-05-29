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

#include <cstdlib>
#include <limits>
#include "quantsystem/common/util/stl_util.h"
#include "quantsystem/common/securities/security_transaction_manager.h"
namespace quantsystem {
namespace securities {
SecurityTransactionManager::SecurityTransactionManager(
    SecurityManager* security)
    : order_id_(1),
      minimum_order_size_(0),
      minimum_order_quantity_(0),
      securities_(security) {
}

SecurityTransactionManager::~SecurityTransactionManager() {
  STLDeleteValues(&orders_);
  //STLDeleteElements(&order_queue_);
  STLDeleteMapElements(&order_queue_);
  for (int i = 0; i < order_events_.size(); ++i) {
    vector<OrderEvent*>& event_vector = order_events_[i];
    STLDeleteElements(&event_vector);
  }
}

int SecurityTransactionManager::AddOrder(Order* order) {
  order->id = order_id_++;
  order->status = orders::kNew;
  order_queue_.push(order);
  return order->id;
}

int SecurityTransactionManager::UpdateOrder(Order* order) {
  int id = order->id;
  if (securities_->Get(order->symbol) == NULL) {
    return -7;
  }
  order->time = securities_->Get(order->symbol)->Time();
  if (order->price == 0 || order->quantity == 0) {
    return -1;
  }
  if (orders_.count(id)) {
    // If its already filled or canceled return false; can't be updated
    if (orders_[id]->status == orders::kFilled ||
        orders_[id]->status == orders::kCanceled) {
      return -5;
    }
    // Flag the order to be resubmitted
    order->status = orders::kUpdate;
    delete orders_[id];
    orders_[id] = order;
    order_queue_.push(order);
  } else {
    return -6;
  }
  return 0;
}

void SecurityTransactionManager::RemoveOrder(int order_id) {
  if (!orders_.count(order_id)) {
    LOG(ERROR) << "RemoveOutstandingOrder(): Cannot find this id.";
    return;
  }
  if (orders_[order_id]->status != orders::kSubmitted) {
    LOG(ERROR) << "RemoveOutstandingOrder(): Order already filled.";
    return;
  }
  Order* order_to_remove = new Order("", 0, orders::kMarket, DateTime());
  order_to_remove->id = order_id;
  order_to_remove->status = orders::kCanceled;
  order_queue_.push(order_to_remove);
}

bool SecurityTransactionManager::GetSufficientCapitalForOrder(
    const SecurityPortfolioManager* portfolio,
    const Order* order) {
  if (abs(GetOrderRequiredBuyingPower(order)) >
      portfolio->GetBuyingPower(order->symbol, order->Direction())) {
    return false;
  }
  return true;
}

double SecurityTransactionManager::GetOrderRequiredBuyingPower(const Order* order) const {
  if (securities_->Get(order->symbol) == NULL) {
    LOG(ERROR) << "Security manager donot have this symbol";
    // Prevent all orders if finding error
    return std::numeric_limits<double>::max();
  }
  const double leverage = securities_->Get(order->symbol)->leverage();
  if (leverage == 0) {
    LOG(ERROR) << "symbol(" << order->symbol << ")'s leverage is 0";
    // Prevent all orders if leverage is 0
    return std::numeric_limits<double>::max();
  }
  return abs(order->value()) / leverage;
}
}  // namespace securities
}  // namespace quantsystem
