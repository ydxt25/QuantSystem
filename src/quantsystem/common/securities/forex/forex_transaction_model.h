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

#ifndef QUANTSYSTEM_COMMON_SECURITIES_FOREX_FOREX_TRANSACTION_MODEL_H_
#define QUANTSYSTEM_COMMON_SECURITIES_FOREX_FOREX_TRANSACTION_MODEL_H_

#include "quantsystem/common/securities/security.h"
#include "quantsystem/common/securities/interfaces/isecurity_transaction_model.h"
namespace quantsystem {
namespace securities {
namespace forex {
/**
 * Forex Transaction Model Class: Specific transaction fill models
 * for FOREX orders.
 * @ingroup CommonBaseSecurities
 */
class ForexTransactionModel : public ISecurityTransactionModel {
 public:
  /**
   * Standard constructor.
   */
  ForexTransactionModel();

  /**
   * Standard destructor.
   */
  virtual ~ForexTransactionModel();

  /**
   * Process a order fill with the supplied security and order.
   * @param asset Asset we're trading this order
   * @param order Order class to check if filled
   * @return OrderEvent packet with the full or partial fill information
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
   * Model the slippage on a market order: fixed percentage of order price.
   * @param asset Asset we're trading this order
   * @param order Order class to check if filled
   * @return OrderEvent packet with the full or partial fill information
   * @see StopFill
   * @see LimitFill
   */
  virtual OrderEvent* MarketFill(const Security* asset,  Order* order);

  /**
   * Check if the model has stopped out our position yet,
   * @param asset Asset we're trading this order
   * @param order Order class to check if filled
   * @return OrderEvent packet with the full or partial fill information
   */
  virtual OrderEvent* StopFill(const Security* asset,  Order* order);

  /**
   * Model for a limit fill.
   * @param asset Asset we're trading this order
   * @param order Order class to check if filled
   * @return OrderEvent packet with the full or partial fill information
   */
  virtual OrderEvent* LimitFill(const Security* asset,  Order* order);

  /**
   * Get the fees from one order.
   * FXCM now uses a flat fee per trade instead of a spread model.
   * This spread model is out of date but the data has the spread built
   * into historical data. >> New data source needed.
   * @param quantity Quantity for this order
   * @param price Average price for this order
   * @return Double value of the order fee given this quantity and order price
   */
  virtual double GetOrderFee(const double& quantity, const double& price) {
    // Modelled order fee to 0; Assume spread is the fee for most FX brokerages.
    return 0;
  }
};

}  // namespace forex
}  // namespace securities
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SECURITIES_FOREX_FOREX_TRANSACTION_MODEL_H_
