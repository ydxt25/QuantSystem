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

#include <cstdlib>
#include <utility>
using std::make_pair;
#include <vector>
using std::vector;
#include "quantsystem/common/securities/security_portfolio_manager.h"
namespace quantsystem {
namespace securities {
SecurityPortfolioManager::SecurityPortfolioManager(
    SecurityManager* security_manager,
    SecurityTransactionManager* transactions)
    : cash_(100000),
      last_trade_profit_(0),
      profit_(0),
      securities_(security_manager),
      transactions_(transactions) {
}

SecurityPortfolioManager::~SecurityPortfolioManager() {
}

bool SecurityPortfolioManager::ContainsKey(const string& string) const {
  return securities_->ContainsKey(string);
}

void SecurityPortfolioManager::Values(vector<SecurityHolding*>* values) {
  vector<const Security*> securities;
  securities_->Values(&securities);
  for (int i = 0; i < securities.size(); ++i) {
    const Security* security = securities[i];
    values->push_back(security->holdings());
  }
}

void SecurityPortfolioManager::Keys(vector<string>* keys) const {
  securities_->Keys(keys);
}

double SecurityPortfolioManager::TotalUnleveredAbsoluteHoldingsCost() const {
  vector<const Security*> values;
  securities_->Values(&values);
  double holdings_cost = 0;
  for (int i = 0; i < values.size(); ++i) {
    const Security* security = values[i];
    holdings_cost += security->holdings()->AbsoluteHoldingsCost() /
                    security->leverage();
  }
  return holdings_cost;
}

double SecurityPortfolioManager::TotalHoldingsValue() const {
  vector<const Security*> values;
  securities_->Values(&values);
  double holdings_value = 0;
  for (int i = 0; i < values.size(); ++i) {
    const Security* security = values[i];
    holdings_value += security->holdings()->AbsoluteHoldingsValue();
  }
  return holdings_value;
}

double SecurityPortfolioManager::TotalUnrealisedProfit() const {
  vector<const Security*> values;
  securities_->Values(&values);
  double profit = 0;
  for (int i = 0; i < values.size(); ++i) {
    const Security* security = values[i];
    profit += security->holdings()->UnrealizedProfit();
  }
  return profit;
}

double SecurityPortfolioManager::TotalFees() const {
  vector<const Security*> values;
  securities_->Values(&values);
  double fees = 0;
  for (int i = 0; i < values.size(); ++i) {
    const Security* security = values[i];
    fees += security->holdings()->total_fees();
  }
  return fees;
}

double SecurityPortfolioManager::TotalProfit()const  {
  vector<const Security*> values;
  securities_->Values(&values);
  double profit = 0;
  for (int i = 0; i < values.size(); ++i) {
    const Security* security = values[i];
    profit += security->holdings()->profit();
  }
  return profit;
}

double SecurityPortfolioManager::TotalSaleVolume() const {
  vector<const Security*> values;
  securities_->Values(&values);
  double volume = 0;
  for (int i = 0; i < values.size(); ++i) {
    const Security* security = values[i];
    volume += security->holdings()->total_sale_volume();
  }
  return volume;
}

SecurityHolding* SecurityPortfolioManager::operator[] (
    const string& symbol) {
  Security* security = (*securities_)[symbol];
  if (security == NULL) {
    LOG(INFO) << "The security(" << symbol <<
        ") is not in the security manager";
    return NULL;
  }
  return security->holdings();
}

double SecurityPortfolioManager::GetBuyingPower(
    const string& symbol,
    orders::OrderDirection direction) const {
  Security* security = (*securities_)[symbol];
  if (security == NULL) {
    LOG(INFO) << "The security(" << symbol <<
        ") is not in the security manager";
    return 0;
  }
  double holdings = security->holdings()->AbsoluteQuantity() *
      security->Close();
  double remaining_buying_power = cash_ * security->leverage();
  if (direction == orders::kHold) {
    return remaining_buying_power;
  }
  if (security->holdings()->IsLong()) {
    switch (direction) {
      case orders::kBuy:
        return remaining_buying_power;
      case orders::kSell:
        return holdings * 2 + remaining_buying_power;
    }
  } else if (security->holdings()->IsShort()) {
    switch (direction) {
      case orders::kBuy:
        return holdings * 2 + remaining_buying_power;
      case orders::kSell:
        return remaining_buying_power;
    }
  }
  return remaining_buying_power;
}

void SecurityPortfolioManager::ProcessFill(const OrderEvent& fill) {
  const string& symbol = fill.symbol;
  Security* security = (*securities_)[symbol];
  if (security == NULL) {
    LOG(ERROR) << "security(" << symbol << ") is not in the securty mananger";
    return;
  }
  SecurityHolding *holdings = security->holdings();
  bool is_long = holdings->IsLong();
  bool is_short = holdings->IsShort();
  bool closed_position = false;
  // //Make local decimals to avoid any rounding errors from int multiplication
  double quantity_holdings = holdings->quantity();
  double absolute_holdings_quantity = holdings->AbsoluteQuantity();
  double average_holdings_price = holdings->average_price();
  double leverage = security->leverage();

  holdings->AddNewSale(fill.fill_price * fill.AbsoluteFillQuantity());
  // Get the Fee for this Order - Update the Portfolio Cash Balance:
  // Remove Transacion Fees
  double fee_this_order = abs(security->model()->GetOrderFee(
      fill.AbsoluteFillQuantity(), fill.fill_price));
  holdings->AddNewFee(fee_this_order);
  cash_ -= fee_this_order;

  // Update the last trade profit
  if (is_long && fill.Direction() == orders::kSell) {
    if (quantity_holdings >= fill.AbsoluteFillQuantity()) {
      // close up a part of a long position
      last_trade_profit_ = (fill.fill_price - average_holdings_price) *
                           fill.AbsoluteFillQuantity();
      cash_ += last_trade_profit_ + ((average_holdings_price *
                                      fill.AbsoluteFillQuantity()) / leverage);
    } else {
      // close up to Short position - Only calc profit on the stock
      // we have to sell
      last_trade_profit_ = (fill.fill_price - average_holdings_price) *
          quantity_holdings;
      cash_ += last_trade_profit_ + ((average_holdings_price *
                                      quantity_holdings) / leverage);
    }
    closed_position = true;
  } else if (is_short && fill.Direction() == orders::kBuy) {
    if (absolute_holdings_quantity >= fill.fill_quantity) {
      // close up a part of a short position
      last_trade_profit_ = (average_holdings_price - fill.fill_price) *
          fill.AbsoluteFillQuantity();
      cash_ += last_trade_profit_ + ((average_holdings_price *
                                      fill.AbsoluteFillQuantity()) / leverage);
    } else {
      // close up to long position
      last_trade_profit_ = (average_holdings_price - fill.fill_price) *
          absolute_holdings_quantity;
      cash_ += last_trade_profit_ + ((average_holdings_price *
                                      absolute_holdings_quantity) / leverage);
    }
    closed_position = true;
  }
  if (closed_position) {
    profit_ += last_trade_profit_;
    holdings->AddNewProfit(last_trade_profit_);
    holdings->SetLastTradeProfit(last_trade_profit_);
    AddTransactionRecord(security->Time(), last_trade_profit_ - 2 *
                         fee_this_order);
  }
  // Update holdings quantity, average price
  if (quantity_holdings == 0) {
    average_holdings_price = fill.fill_price;
    quantity_holdings = fill.fill_quantity;
    cash_ -= (fill.fill_price  * fill.AbsoluteFillQuantity()) / leverage;
  } else if (is_long) {
    switch (fill.Direction()) {
      case orders::kBuy:
        average_holdings_price =
            ((average_holdings_price * quantity_holdings) +
             (static_cast<double>(fill.fill_quantity) * fill.fill_price)) /
            (quantity_holdings + static_cast<double>(fill.fill_quantity));
        quantity_holdings += fill.fill_quantity;
        cash_ -= (fill.fill_price * static_cast<double>(
            fill.AbsoluteFillQuantity())) / leverage;
        break;
      case orders::kSell:
        quantity_holdings += fill.fill_quantity;  // + a short = a subtraction
        if (quantity_holdings < 0) {
          average_holdings_price = fill.fill_price;
          cash_ -= (fill.fill_price * abs(quantity_holdings)) / leverage;
        } else if (quantity_holdings == 0) {
          average_holdings_price = 0;
        }
        break;
    }
  } else if (is_short) {
    switch (fill.Direction()) {
      case orders::kBuy:
        quantity_holdings += fill.fill_quantity;
        if (quantity_holdings > 0) {
          average_holdings_price = fill.fill_price;
          cash_ -= (fill.fill_price * abs(quantity_holdings)) / leverage;
        } else if (quantity_holdings == 0) {
          average_holdings_price = 0;
        }
        break;
      case orders::kSell:
        average_holdings_price =
            ((average_holdings_price * quantity_holdings) +
             (static_cast<double>(fill.fill_quantity) * fill.fill_price)) /
            (quantity_holdings + static_cast<double>(fill.fill_quantity));
        quantity_holdings += fill.fill_quantity;
        cash_ -= (fill.fill_price * static_cast<double>(
            fill.AbsoluteFillQuantity())) / leverage;
        break;
    }
  }
  holdings->SetHoldings(average_holdings_price,
                        static_cast<int>(quantity_holdings));
}

void SecurityPortfolioManager::AddTransactionRecord(
    const DateTime& time,
    const double& transaction_profit_loss) {
  DateTime done = time;
  while (transactions_->transaction_record().count(done)) {
    done += TimeSpan::FromMilliseconds(1);
  }
  transactions_->transaction_record().insert(
      make_pair(done, transaction_profit_loss));
}

}  // namespace securities
}  // namespace quantsystem
