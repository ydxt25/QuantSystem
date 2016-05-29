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

#ifndef QUANTSYSTEM_COMMON_SECURITIES_EQUITY_EQUITY_TRANSACTION_MODEL_H_
#define QUANTSYSTEM_COMMON_SECURITIES_EQUITY_EQUITY_TRANSACTION_MODEL_H_

#include "quantsystem/common/securities/security.h"
#include "quantsystem/common/securities/interfaces/isecurity_transaction_model.h"

namespace quantsystem {
namespace securities {
namespace equity {
/**
 * Transaction model for equity security trades. 
 * @ingroup CommonBaseSecurities
 */
class EquityTransactionModel : public ISecurityTransactionModel {
 public:
  /**
   * Standard constructor.
   */
  EquityTransactionModel();

  /**
   * Standard destructor.
   */
  virtual ~EquityTransactionModel();

  /**
   * Process a order fill with the supplied security and order.
   * @param asset Asset we're trading this order
   * @param order[out] Order class to check if filled
   * @return OrderEvent packet with the full or partial fill information
   */
  virtual OrderEvent* Fill(const Security* asset, Order* order);

  /**
   * Get the Slippage approximation for this order.
   * @param asset Asset we're trading this order
   * @param order[out] Order class to check if filled
   * @return Double approximation for slippage
   */
  virtual double GetSlippageApproximation(const Security* asset,
                                          const Order* order) {
    return 0;
  }

  /**
   * Default equity transaction model for a market fill on this order.
   * @param asset Asset we're trading this order
   * @param order[out] Order class to check if filled
   * @return OrderEvent packet with the full or partial fill information
   * @see StopFill
   * @see LimitFill
   */
  virtual OrderEvent* MarketFill(const Security* asset, Order* order);

  /**
   * Check if the model has stopped out our position yet,
   * @param asset Asset we're trading this order
   * @param order[out] Order class to check if filled
   * @return OrderEvent packet with the full or partial fill information
   */
  virtual OrderEvent* StopFill(const Security* asset, Order* order);

  /**
   * Model for a limit fill.
   * @param asset Asset we're trading this order
   * @param order[out] Order class to check if filled
   * @return OrderEvent packet with the full or partial fill information
   */
  virtual OrderEvent* LimitFill(const Security* asset, Order* order);

  /**
   * Get the fees from one order.
   * Default implementation uses the Interactive Brokers fee model
   * of 1c per share with a maximum of 0.5% per order.
   * @param quantity Quantity for this order
   * @param price Average price for this order
   * @return Double value of the order fee given this quantity and order price
   */
  virtual double GetOrderFee(const double& quantity, const double& price);
};

}  // namespace equity
}  // namespace securities
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SECURITIES_EQUITY_EQUITY_TRANSACTION_MODEL_H_
