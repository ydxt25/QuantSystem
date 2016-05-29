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

#ifndef QUANTSYSTEM_ENGINE_TRANSACTION_TRADIER_TRANSACTION_HANDLER_H_
#define QUANTSYSTEM_ENGINE_TRANSACTION_TRADIER_TRANSACTION_HANDLER_H_

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <map>
using std::map;
#include <queue>
using std::queue;
#include "quantsystem/common/orders/order.h"
#include "quantsystem/common/orders/order_event.h"
#include "quantsystem/interfaces/ibrokerage.h"
#include "quantsystem/interfaces/ialgorithm.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/engine/results/iresult_handler.h"
#include "quantsystem/brokerages/tradier/tradier_orders.h"
#include "quantsystem/brokerages/tradier/tradier_brokerage.h"
#include "quantsystem/engine/transaction_handlers/itransaction_handler.h"

namespace quantsystem {
using interfaces::IAlgorithm;
using interfaces::IBrokerage;
using engine::results::IResultHandler;
using orders::Order;
using orders::OrderEvent;
using brokerages::TradierOrder;
using brokerages::TradierBrokerage;
using securities::OrderMap;
using securities::OrderEventMap;
using securities::OrderQueue;
namespace engine {
namespace transaction_handlers {
/**
 * Handle the Transactions Requests from Live Trading Cloud Algorithms.
 * @ingroup EngineLayerTransactionHandlers
 */
class TradierTransactionHandler : public ITransactionHandler {
 public:
  /**
   * Constructor for the tradier transaction handler.
   * @param algorithm Algorithm instance
   * @param brokerage Brokerage instance
   * @param results Result handler
   * @param account_id Tradier account id
   */
  TradierTransactionHandler(const IAlgorithm* algorithm,
                            const IBrokerage* brokerage,
                            const IResultHandler* results,
                            int account_id);

  /**
   * Primary thread entry point to launch the transaction thread.
   */
  virtual void Run();

  /**
   * Submit a new order to be processed.
   * @param order New order object
   * @return New unique quantconnect order id
   */
  virtual int NewOrder(Order* order);

  /**
   * Update and resubmit the order to the OrderQueue for processing.
   * @param order Order we'd like updated
   * @return True if successful, false if already cancelled or filled
   */
  virtual bool UpdateOrder(Order* order);

  /**
   * Cancel the order specified.
   * @param order Order we'd like to cancel
   * @return True if successful, false if its already been cancelled or filled
   */
  virtual bool CancelOrder(Order* order);

  /**
   * Set a local reference to the algorithm instance.
   * @param algorithm IAlgorithm object
   */
  virtual void SetAlgorithm(IAlgorithm* algorithm);

  /**
   * Signal a end of thread request to stop montioring the transactions.
   */
  virtual void Exit();

  virtual OrderMap& orders() {
  }
  virtual const OrderMap& orders() const {
  }

  virtual void set_orders(const OrderMap& orders) {
  }

  virtual OrderEventMap& order_events() {
  }
  virtual void set_order_events(const OrderEventMap& order_events) {
  }
      
  virtual OrderQueue& order_queue() {
  }
  virtual void set_order_queue(const OrderQueue& order_queue) {
  }

 private:
  TradierBrokerage* tradier_;
  int order_id_;
  bool exit_triggered_;
  int account_id_;
  DateTime refresh_orders_;
  vector<TradierOrder> previous_orders_;
  IAlgorithm* algorithm_;
  IResultHandler* results_;
};

}  // namespace transaction_handlers
}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_TRANSACTION_TRADIER_TRANSACTION_HANDLER_H_
