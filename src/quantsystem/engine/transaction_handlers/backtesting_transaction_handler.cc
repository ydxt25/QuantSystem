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

#include <thread>
#include <chrono>
#include <string>
using std::to_string;
#include "quantsystem/common/base/scoped_ptr.h"
#include "quantsystem/engine/transaction_handlers/\
backtesting_transaction_handler.h"

namespace quantsystem {
namespace engine {
namespace transaction_handlers {
BacktestingTransactionHandler::BacktestingTransactionHandler(
    IAlgorithm* algorithm, IResultHandler* result_handler)
    : order_id_(1),
      exit_triggered_(false),
      algorithm_(algorithm),
      result_handler_(result_handler) {
  is_active_ = true;
  ready_ = false;
}

void BacktestingTransactionHandler::Run() {
  while (!exit_triggered_) {
    // 1. Add order commands from queue to primary order list
    if (order_queue().size() == 0) {
      // We've processed all the orders in queue
      ready_ = true;
      algorithm_->set_processing_order(false);
      std::this_thread::sleep_for(std::chrono::seconds(1));
    } else {
      ready_ = false;
      // Scan jobs in the new orders queue
      Order* order;
      order = order_queue().front();
      order_queue().pop();
      OrderMap::iterator it;
      if (order) {
        switch (order->status) {
          case orders::kNew:
            // If we don't have this key, add it to the dictionary
            if (orders().find(order->id) == orders().end()) {
              // Tell the algorithm to wait
              algorithm_->set_processing_order(true);
              orders()[order->id] = order;
            }
            break;
          case orders::kCanceled:
	    it = orders().find(order->id);
            if (it != orders().end() &&
                orders()[order->id]->status == orders::kSubmitted) {
              delete it->second;
              orders()[order->id] = order;
            }
            break;
          case orders::kUpdate:
            it = orders().find(order->id);
            if (it != orders().end() &&
                orders()[order->id]->status == orders::kSubmitted) {
              delete it->second;
              orders()[order->id] = order;
            }
            break;
          default:
            LOG(ERROR) << "Logic error? order status:" << order->status;
            delete order;
            break;
        }
      }
    }
    vector<int> keys;
    GetProcessOrderKeys(keys);
    for (int i = 0; i < keys.size(); ++i) {
      int id = keys[i];
      scoped_ptr<OrderEvent> fill_event;
      ready_ = false;
      Order* order = orders()[id];
      bool sufficient_buying_power =
          algorithm_->transactions()->GetSufficientCapitalForOrder(
              algorithm_->portfolio(), order);
      if (sufficient_buying_power) {
        fill_event.reset(algorithm_->securities()->Get(order->symbol)->
            model()->Fill(algorithm_->securities()->Get(order->symbol), order));
        if (fill_event->status == orders::kFilled ||
            fill_event->status == orders::kPartiallyFilled) {
          //If the fill models come back suggesting filled,
          // process the affects on portfolio
          algorithm_->portfolio()->ProcessFill(*fill_event);
        }
      } else {
        order->status = orders::kInvalid;
        algorithm_->Error("Order Errror: id:" + to_string(id) +
                          ":Insufficient buying power to complete order.");
      }
      if (fill_event->status != orders::kNone) {
        result_handler_->SendOrderEvent(fill_event.get());
        algorithm_->OnOrderEvent(fill_event.get());
      }
    }
  } // End while
  LOG(INFO) << "Ending thread";
  is_active_ = false;
}

void BacktestingTransactionHandler::GetProcessOrderKeys(
    vector<int>& keys) {
  for (OrderMap::const_iterator it = orders().begin();
       it != orders().end(); ++it) {
    orders::OrderStatus status = it->second->status;
    if (status != orders::kFilled && status != orders::kCanceled &&
        status != orders::kInvalid) {
      keys.push_back(it->first);
    }
  }
}
  
int BacktestingTransactionHandler::NewOrder(Order* order) {
  // if this a new order (with no id), set it
  if (order->id == 0) {
    order->id = order_id_++;
  }
  // Submit to queue
  order->status = orders::kNew;
  order_queue().push(order);
  ready_ = false;
  return order->id;
}

bool BacktestingTransactionHandler::UpdateOrder(Order* order) {
  if (orders()[order->id]->status == orders::kFilled ||
      orders()[order->id]->status == orders::kCanceled) {
    return false;
  }
  order->status = orders::kUpdate;
  order_queue().push(order);
  ready_ = false;
  return true;
}

bool BacktestingTransactionHandler::CancelOrder(Order* order) {
  if (orders()[order->id]->status == orders::kFilled ||
      orders()[order->id]->status == orders::kCanceled) {
    return false;
  }
  order->status = orders::kCanceled;
  order_queue().push(order);
  ready_ = false;
  return true;
}

}  // namespace transaction_handlers
}  // namespace engine
}  // namespace quantsystem
