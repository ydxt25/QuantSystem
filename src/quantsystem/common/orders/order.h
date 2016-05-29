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
 * @defgroup CommonBaseOrders Common - Base Orders Components
 *
 * Base order components of Quantsystem.
 */

#ifndef QUANTSYSTEM_COMMON_ORDERS_ORDER_H_
#define QUANTSYSTEM_COMMON_ORDERS_ORDER_H_

#include <cstdlib>
#include <map>
using std::map;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include "quantsystem/common/base/integral_types.h"
#include "quantsystem/common/time/date_time.h"

namespace quantsystem {
namespace orders {
/**
 * Order class definition.
 * @ingroup CommonBaseOrders
 */

/**
 * Type of the order: market, limit or stop
 */
enum OrderType {
  kMarket,  // Market order type
  kLimit,  // Limit order type
  // Stop market order type - fill at market price when break target price
  kStopMarket
};

/**
 * Order durartion in market
 */
enum OrderDuration {
  kGTC,  // Order good until its filled
  kDay  // Order valid for today only
};

/**
 * Direction of the order
 */
enum OrderDirection {
  kBuy,  // Buy order
  kSell,  // Sell order
  kHold  // Default value - no order direction
};

/**
 * Fill status of the order class
 */
enum OrderStatus {
  // New order pre-submission to the order processor
  kNew,
  // Order flagged for updating the in market order
  kUpdate,
  // Order submitted to the market
  kSubmitted,
  // Partially filled in market order
  kPartiallyFilled,
  // Completed filled in market order
  kFilled,
  // Order cancelled before it was filled
  kCanceled,
  // No order state yet
  kNone,
  // Order invalidated before it hit the market (e.g. insufficient capital)
  kInvalid
};

/**
 * Indexed order error codes.
 */
class OrderErrors {
 public:
  static const map<int, string> kErrorTypes;
};

/**
 * Order struct for placing new trade
 */
class Order {
 public:
  int id;  // Order ID
  // Order id to process before processing this order
  int contingent_id;
  vector<int64> broker_id;  // Brokerage id for this order
  string symbol;  // Symbol of the asset
  double price;  // Price of the order
  DateTime time;  // Time the order was created
  int quantity;  // Number of shares to execute
  OrderType type;  // Order type
  OrderStatus status;  // Status of the order
  OrderDuration duration;  // Order duration - GTC or Day
  string tag;  // Tag the order with some custom data

  /**
   * Order direction property based off quantity
   * @return the order direction
   */
  OrderDirection Direction() const;

  /**
   * Get the absolute quantity for this order
   */
  double AbsoluteQuantity() const { return abs(quantity); }

  /**
   * Value of the order at limit price if a limit order,
   * or market price if a market order.
   */
  double value() const { return static_cast<double>(quantity) * price; }

  /**
   * Standard constructor.
   */
  Order();

  /**
   * Construct a new order from values.
   *
   * @param symbol Symbol asset we're seeking to trade
   * @param quantity Quantity of the asset we're seeking to trade
   * @param order Order type(market, limit or stoploss order)
   * @param time Time the order was placed
   * @param price Price the order should be filled at if a limit order
   * @param tag User defined data a tag for this order
   */
  Order(const string& in_symbol, int in_quantity, OrderType in_order,
        const DateTime& in_time, const double& in_price = 0,
        const string& in_tag = "");

  /**
   * Standard destructor.
   */
  virtual ~Order();
};

}  // namespace orders
}  // namespace quantsystem

#endif  // QUANTSYSTEM_COMMON_ORDERS_ORDER_H_
