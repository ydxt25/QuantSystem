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

#include "quantsystem/common/securities/security_holding.h"
namespace quantsystem {
namespace securities {
SecurityHolding::SecurityHolding(const string& symbol,
                                  ISecurityTransactionModel* model)
    : symbol_(symbol),
      total_sale_volume_(0),
      last_trade_profit_(0) {
  model_ = model;
}

SecurityHolding::~SecurityHolding() {
}

double SecurityHolding::TotalCloseProfit() {
  double gross = 0, net = 0, order_fee = 0;
  if (AbsoluteQuantity() > 0) {
    order_fee = model_->GetOrderFee(AbsoluteQuantity(), price_);
  }
  if (IsLong()) {
    // if we're long on a position, profit from selling off $10,000 stock
    gross = (price_ - average_price()) * AbsoluteQuantity();
  } else if (IsShort()) {
    // if we're short on a position, profit from buying $10,000 stock
    gross = (average_price() - price_) * AbsoluteQuantity();
  } else {
    // no holdings
    return 0;
  }
  net = gross - order_fee;
  return net;
}

Holding::Holding() : symbol(""), average_price(0.0), quantity(0.0) ,
                     market_price(0.0) {
}

Holding::Holding(const securities::SecurityHolding& holding) {
  symbol = holding.symbol();
  quantity = holding.quantity();
  average_price = holding.average_price();
  market_price = holding.price();
}

Holding::~Holding() {}
}  // namespace securities
}  // namespace quantsystem
