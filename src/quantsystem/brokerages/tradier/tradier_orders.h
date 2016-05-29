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

#ifndef QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_ORDERS_H_
#define QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_ORDERS_H_

#include <string>
using std::string;
#include <vector>
using std::vector;
#include "quantsystem/common/base/integral_types.h"
#include "quantsystem/brokerages/tradier/tradier_common.h"
#include "quantsystem/common/time/date_time.h"

namespace quantsystem {
namespace brokerages {
class TradierOrder;

/**
 * Order container class
 * @ingroup BrokeragesLayer
 */
class TradierOrders {
 public:
  vector<TradierOrder> orders;
};

/**
 * Order parent class for deserialization.
 * @ingroup BrokeragesLayer
 */
class TradierOrdersContainer {
 public:
  TradierOrders orders;
};

class TradierOrderLeg;
/**
 * Intraday or pending order for user
 * @ingroup BrokeragesLayer
 */
class TradierOrder {
 public:
  int64 id;  // Unique order id
  TradierOrderType type;  // Market, limit order etc.
  string symbol;
  TradierOrderDirection direction;  // Long short
  double quantity;
  // Status of the order (filled, canceled, open, expired, rejected,
  // pending, partially_filled, submitted).
  TradierOrderStatus::Enum status;
  TradierOrderDuration duration;  // Duration of the order (day, gtc)
  double price;
  double average_fill_price;
  double quantity_executed;
  double last_fill_price;
  double last_fill_quantity;
  double remaining_quantity;
  DateTime created_date;
  DateTime transaction_date;
  // Classification of order (equity, option, multileg, combo)
  TradierOrderClass::Enum order_class;
  int number_of_legs;
  vector<TradierOrderLeg> legs;
};

/**
 * Errors result from an order request.
 * @ingroup BrokeragesLayer
 */
class TradierOrderResponseError {
 public:
  vector<string> errors;  // vector of errors
};

/**
 * Order response when purchasing equity.
 * @ingroup BrokeragesLayer
 */
class TradierOrderResponseOrder {
 public:
  int64 id;
  string partner_id;
  string status;
};

/**
 * Deserialization wrapper for order response.
 * @ingroup BrokeragesLayer
 */
class TradierOrderResponse {
 public:
  TradierOrderResponseOrder order;  // Tradier order information
  TradierOrderResponseError errors;  // Errors in request
};

/**
 * Detailed order type.
 * @ingroup BrokeragesLayer
 */
class TradierOrderDetailed : public TradierOrder {
 public:
  string exchange;
  string execution_exchange;
  TradierOptionType option_type;
  DateTime option_expiration_date;
  string stop_price;
};

/**
 * Detailed order parent class.
 * @ingroup BrokeragesLayer
 */
class TradierOrderDetailedContainer {
 public:
  TradierOrderDetailed detailed_order;
};

/**
 * Leg of a tradier order.
 * @ingroup BrokeragesLayer
 */
class TradierOrderLeg {
 public:
  TradierOrderType type;  // Limit, market, stop etc.
  string symbol;
  TradierOrderDirection direction;  // Long short
  double quantity;
  // Status of the order (filled, canceled, open, expired, rejected,
  // pending, partially_filled, submitted)
  TradierOrderStatus::Enum status;
  // Duration of the order (day, gtc)
  TradierOrderDuration duration;
  double price;
  double average_fill_price;
  double quantity_executed;
  double last_fill_price;
  double last_fill_quantity;
  double remaining_quantity;
  DateTime created_date;
  DateTime transaction_date;

  /**
   * Standard constructor.
   */
  TradierOrderLeg();

  /**
   * Standard destructor.
   */
  virtual ~TradierOrderLeg();
};
}  // namespace brokerages
}  // namespace quantsystem
#endif  // QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_ORDERS_H_
