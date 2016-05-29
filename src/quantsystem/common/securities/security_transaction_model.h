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

#ifndef QUANTSYSTEM_COMMON_SECURITIES_SECURITY_TRANSACTION_MODEL_H_
#define QUANTSYSTEM_COMMON_SECURITIES_SECURITY_TRANSACTION_MODEL_H_

#include "quantsystem/common/securities/security.h"
#include "quantsystem/common/orders/order.h"
#include "quantsystem/common/orders/order_event.h"
#include "quantsystem/common/securities/interfaces/isecurity_transaction_model.h"
namespace quantsystem {
namespace securities {
/**
 * Default security transaction model for user defined securities.
 * @ingroup CommonBaseSecurities
 */
class SecurityTransactionModel : public ISecurityTransactionModel {
 public:
  /**
   * Standard constructor.
   */
  SecurityTransactionModel();

  /**
   * Standard destructor.
   */
  virtual ~SecurityTransactionModel();

  /**
   * Process an order to see if it has been filled and return the matching
   * order event.
   * @param asset Asset we're trading this order
   * @param order Order class to check if filled
   * @return Order fill informaton detailing the average price and quantity filled
   */
  virtual OrderEvent* Fill(const Security* asset, Order* order);

  /**
   * Get the Slippage approximation for this order.
   * @param asset Asset we're trading this order
   * @param order Order class to check if filled
   * @return Double approximation for slippage
   */
  virtual double GetSlippageApproximation(const Security* asset,
                                          const Order* order);

  /**
   * Default market fill model for the base security class. Fills at the last traded price.
   * @param asset Asset we're trading this order
   * @param order Order class to check if filled
   * @return Order fill informaton detailing the average price and quantity filled
   * @see StopFill
   * @see LimitFill
   */
  virtual OrderEvent* MarketFill(const Security* asset, Order* order);

  /**
   * Default stop fill model implementation in base class security.
   * @param asset Asset we're trading this order
   * @param order Order class to check if filled
   * @return Order fill informaton detailing the average price and quantity filled
   */
  virtual OrderEvent* StopFill(const Security* asset, Order* order);

  /**
   * Default limit order fill model in the base security class.
   * @param asset Asset we're trading this order
   * @param order Order class to check if filled
   * @return Order fill informaton detailing the average price and quantity filled.
   */
  virtual OrderEvent* LimitFill(const Security* asset, Order* order);

  /**
   * Default security transaction model - no fees.
   * @param quantity Quantity for this order
   * @param price Average price for this order
   */
  virtual double GetOrderFee(const double& quantity, const double& price) {
    return 0;
  }
};

}  // namespace securities
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SECURITIES_SECURITY_TRANSACTION_MODEL_H_
