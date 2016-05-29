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

#ifndef QUANTSYSTEM_COMMON_SECURITIES_SECURITY_TRANSACTION_MANAGER_H_
#define QUANTSYSTEM_COMMON_SECURITIES_SECURITY_TRANSACTION_MANAGER_H_

#include <map>
using std::map;
#include <queue>
using std::queue;
#include <vector>
using std::vector;
#include "quantsystem/common/base/mutex.h"
#include "quantsystem/common/orders/order.h"
#include "quantsystem/common/orders/order_event.h"
#include "quantsystem/common/securities/security_manager.h"
#include "quantsystem/common/securities/security_portfolio_manager.h"
namespace quantsystem {
namespace securities {
class SecurityPortfolioManager;

typedef map<int, Order*> OrderMap;
typedef queue<Order*> OrderQueue;
typedef map<int, vector<OrderEvent*> > OrderEventMap;
typedef map<DateTime, double> TransactionMap;

/**
 * Algorithm Transactions Manager - Recording Transactions.
 * @ingroup CommonBaseSecurities
 */
class SecurityTransactionManager {
 public:
  /**
   * Initialise the transaction manager for holding and processing orders.
   */
  explicit SecurityTransactionManager(SecurityManager* security);

  /**
   * Standard destructor.
   */
  virtual ~SecurityTransactionManager();

  /**
   * Queue for holding all orders sent for processing.
   */
  OrderMap& orders() { return orders_; }

  void set_orders(const OrderMap& orders) { orders_ = orders; }

  /**
   * Temporary storage for orders while waiting to process via transaction
   * handler. Once processed they are added to the primary order queue.
   * @see orders
   */
  OrderQueue& order_queue()  { return order_queue_; }

  void set_order_queue(const OrderQueue& order_queue) {
    order_queue_ = order_queue;
  }

  /**
   * Order event storage - a list of the order events attached to each order.
   * @see orders
   * @see order_queue
   */
  OrderEventMap& order_events() { return order_events_; }

  void set_order_events(const OrderEventMap& order_events) {
    order_events_ = order_events;
  }

  /**
   * Trade record of profits and losses for each trade statistics calculations
   */
  TransactionMap& transaction_record() { return transaction_record_; }
  const TransactionMap& transaction_record() const { return transaction_record_; }

  void set_transaction_record(const TransactionMap& transaction_record) {
    transaction_record_ = transaction_record;
  }

  /**
   * Configurable minimum order value to ignore bad orders,
   * or orders with unrealistic sizes.
   * Default minimum order size is $0 value.
   */
  double minimum_order_size() const { return minimum_order_size_; }

  /**
   * Configurable minimum order quantity to ignore bad orders,
   * or orders with unrealistic quantities.
   */
  double minimum_order_quantity() const { return minimum_order_quantity_; }

  /**
   * Add an order to collection and return the unique order id or
   * negative if an error.
   * @param order New order object to add to processing list
   * @return New unique, increasing order id.
   */
  virtual int AddOrder(Order* order);

  /**
   * Update an order yet to be filled such as stop or limit orders.
   * Does not apply if the order is already fully filled.
   * @param order Order to Update
   * @return Id of the order we modified or
   * -5 if the order was already filled or cancelled,
   * -6 if the order was not found in the cache
   * -7 if other errors.
   */
  int UpdateOrder(Order* order);

  /**
   * Remove this order from outstanding queue: user is requesting a cancel.
   * @param order_id Specific order id to remove
   */
  virtual void RemoveOrder(int order_id);

  /**
   * Check if there is sufficient capital to execute this order.
   * @param portfolio Our portfolio
   * @param order Order we're checking
   * @return True if sufficient capital
   */
  bool GetSufficientCapitalForOrder(const SecurityPortfolioManager* portfolio,
                                    const Order* order);

  /**
   * Get a new order id, and increment the internal counter.
   * @return New unique int order id.
   */
  int GetIncrementOrderId() {
    return order_id_++;
  }

 private:
  SecurityManager* securities_;
  OrderMap orders_ GUARDED_BY(mutex_);
  OrderQueue order_queue_ GUARDED_BY(mutex_);
  OrderEventMap order_events_ GUARDED_BY(mutex_);
  TransactionMap transaction_record_;
  int order_id_;
  double minimum_order_size_;
  int minimum_order_quantity_;
  Mutex mutex_;

  /**
   * Using leverage property of security find the required cash for this order.
   * @param order Order to check
   * @return Cash requred to purchase order
   */
  double GetOrderRequiredBuyingPower(const Order* order) const;
};

}  // namespace securities
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SECURITIES_SECURITY_TRANSACTION_MANAGER_H_
