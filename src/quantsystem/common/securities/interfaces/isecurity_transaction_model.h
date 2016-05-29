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

#ifndef QUANTSYSTEM_COMMON_SECURITIES_ISECURITY_TRANSACTION_MODEL_H_
#define QUANTSYSTEM_COMMON_SECURITIES_ISECURITY_TRANSACTION_MODEL_H_

#include "quantsystem/common/orders/order.h"
#include "quantsystem/common/orders/order_event.h"
namespace quantsystem {
using orders::Order;
using orders::OrderEvent;
namespace securities {
class Security;
/**
 * Security transaction model interface for Quantsystem security objects
 * @ingroup CommonBaseSecurities
 * @see EquityTransactionModel
 * @see ForexTransactionModel
 */
class ISecurityTransactionModel {
 public:
  /**
   * Perform neccessary check to see if the model has been filled,
   * appoximate the best we can.
   * @param asset Asset we're trading this order
   * @param order[out] Order class to check if filled
   * @return OrderEvent packet with the full or partial fill information
   */
  virtual OrderEvent* Fill(const Security* asset, Order* order) = 0;

  /**
   * Get the Slippage approximation for this order.
   * @param asset Asset we're trading this order
   * @param order Order class to check if filled
   * @return Double approximation for slippage
   */
  virtual double GetSlippageApproximation(const Security* asset,
                                  const Order* order) = 0;

  /**
   * Model the slippage on a market order: fixed percentage of order price.
   * @param asset Asset we're trading this order
   * @param order Order class to check if filled
   * @return OrderEvent packet with the full or partial fill information
   * @see StopFill
   * @see LimitFill
   */
  virtual OrderEvent* MarketFill(const Security* asset, Order* order) = 0;

  /**
   * Check if the model has stopped out our position yet,
   * @param asset Asset we're trading this order
   * @param order Order class to check if filled
   * @return OrderEvent packet with the full or partial fill information
   */
  virtual OrderEvent* StopFill(const Security* asset, Order* order) = 0;

  /**
   * Model for a limit fill.
   * @param asset Asset we're trading this order
   * @param order Order class to check if filled
   * @return OrderEvent packet with the full or partial fill information
   */
  virtual OrderEvent* LimitFill(const Security* asset, Order* order) = 0;

  /**
   * Get the fees from one order. Currently defaults to interactive.
   * @param quantity Quantity for this order
   * @param price Average price for this order
   * @return Double value of the order fee given this quantity and order price
   */
  virtual double GetOrderFee(const double& quantity, const double& price) = 0;
};

}  // namespace securities
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SECURITIES_ISECURITY_TRANSACTION_MODEL_H_
