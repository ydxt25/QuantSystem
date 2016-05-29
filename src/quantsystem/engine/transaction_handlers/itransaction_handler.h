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
 * @defgroup EngineLayerTransactionHandlers  Engine Layer - Transaction
 * Handlers Components
 *
 * Transaction Handlers Components in Engine Layer.
 */
#ifndef QUANTSYSTEM_ENGINE_TRANSACTION_ITRANSACTION_HANDLER_H_
#define QUANTSYSTEM_ENGINE_TRANSACTION_ITRANSACTION_HANDLER_H_

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <map>
using std::map;
#include <queue>
using std::queue;
#include "quantsystem/interfaces/ialgorithm.h"
#include "quantsystem/common/orders/order.h"
#include "quantsystem/common/orders/order_event.h"
#include "quantsystem/common/securities/security_transaction_manager.h"
namespace quantsystem {
using interfaces::IAlgorithm;
using orders::Order;
using orders::OrderEvent;
using securities::OrderMap;
using securities::OrderEventMap;
using securities::OrderQueue;
namespace engine {
namespace transaction_handlers {
/**
 * Transaction handlers define how the transactions are processed and
 * set the order fill information. The pass this information back to
 * the algorithm portfolio and ensure the cash and portfolio are synchronized.
 *
 * A new transaction handler is required for each each brokerage endpoint.
 * @ingroup EngineLayerTransactionHandlers
 */
class ITransactionHandler {
 public:
  /**
   * Primary thread entry point to launch the transaction thread.
   */
  virtual void Run() = 0;

  /**
   * Submit a new order to be processed.
   * @param order New order object
   * @return New unique quantconnect order id
   */
  virtual int NewOrder(Order* order) = 0;

  /**
   * Update and resubmit the order to the OrderQueue for processing.
   * @param order Order we'd like updated
   * @return True if successful, false if already cancelled or filled
   */
  virtual bool UpdateOrder(Order* order) = 0;

  /**
   * Cancel the order specified.
   * @param order Order we'd like to cancel
   * @return True if successful, false if its already been cancelled or filled
   */
  virtual bool CancelOrder(Order* order) = 0;

  /**
   * Set a local reference to the algorithm instance.
   * @param algorithm IAlgorithm object
   */
  virtual void SetAlgorithm(IAlgorithm* algorithm) = 0;

  /**
   * Signal a end of thread request to stop montioring the transactions.
   */
  virtual void Exit() = 0;

  virtual OrderMap& orders() = 0;
  virtual const OrderMap& orders() const = 0;
  virtual void set_orders(const OrderMap& orders) = 0;

  virtual OrderEventMap& order_events() = 0;
  virtual void set_order_events(const OrderEventMap& order_events) = 0;
      
  virtual OrderQueue& order_queue() = 0;
  virtual void set_order_queue(const OrderQueue& order_queue) = 0;

  bool is_active() const { return is_active_; }

  bool ready() const { return ready_; }

 protected:
  // Boolean flag indicating the thread is busy.
  // False indicates it is completely finished processing and
  // ready to be terminated.
  bool is_active_;
  // Boolean flag signalling the handler is ready and all orders
  // have been processed
  bool ready_;
};

}  // namespace transaction_handlers
}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_TRANSACTION_ITRANSACTION_HANDLER_H_
