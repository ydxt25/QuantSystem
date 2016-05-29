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

#ifndef QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_BALANCE_H_
#define QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_BALANCE_H_

#include "quantsystem/common/base/integral_types.h"
#include "quantsystem/brokerages/tradier/tradier_common.h"

namespace quantsystem {
namespace brokerages {
class TradierBalanceDetails;
/**
 * Inside "Account" User-account balance information.
 * @ingroup BrokeragesLayer
 */
class TradierBalance {
 public:
  TradierBalanceDetails balances;
};

class TradierAccountTypeCash;
class TradierAccountTypeDayTrader;
class TradierAccountTypeMargin;
/**
 * Trader Balance Detail
 * @ingroup BrokeragesLayer
 */
class TradierBalanceDetails {
 public:
  int64 account_number;  // Account number
  TradierAccountType type;  // Account Type (margin, cash, pdt)
  // The amount of cash that could be withdrawn or invested
  // in new investments, cash that is not required to support existing positions
  double cash_available;
  // The ProfitLoss of the current trading day closed positions.
  double closing_profit_loss;
  // The option requirement of current account positions.
  double current_requirement;
  double dividend_balance;  // Dividend balance
  double equity;  // Equity value
  double long_liquid_value;  // Long liquid value
  double long_market_value;  // Long market value
  double market_value;  // Market value
  double net_value;  // Net value
  double open_profit_loss;  // The Profit Loss of current account positions
  double option_long_value;  // The value of long options held in the account
  double option_requirement;  // Option Requirement
  double option_short_value;  // The value of short options held in the account
  // The amount of cash that is being held for open orders.
  double pending_cash;
  int pending_orders_count;  // The amount of open orders
  double short_liquid_value;  // Short Liquid value
  double short_market_value;  // Short market value
  double stock_long_value;  // The value of long stocks held in the account
  // The amount of funds that are not currently available for trading.
  double uncleared_funds;
  // Cash that is in the account from recent stock or option sales,
  // but has not yet settled; cash from stock sales occurring during
  // the last 3 trading days or from option sales occurring
  // during the previous trading day.
  double unsettled_funds;
  double total_cash;  // The total amount of cash in the account
  double total_equity;  // The total account value
  // Settings class for PDT specific accounts
  TradierAccountTypeCash cash_type_settings;
  // Settings class for PDT specific accounts
  TradierAccountTypeDayTrader pattern_trader_type_settings;
  // Settings class for margin specific accounts
  TradierAccountTypeMargin margin_type_settings;
};

/**
 * Common Account Settings.
 * @ingroup BrokeragesLayer
 */
class TradierAccountTypeSettings {
 public:
  // The amount that the account is in deficit for trades
  // that have occurred but not been paid for
  double fed_call;
  // The amount that the account is under the minimum equity
  // required in the account to support the current holdings
  double maintenance_call;
  // The amount of funds available to purchase fully marginable securities
  double stock_buying_power;
  // The amount of funds available to purchase non-marginable securities
  double option_buying_power;
  // The value of short stocks held in the account
  double stock_short_value;
};

/**
 * Account Type Day Trader Settings
 * @ingroup BrokeragesLayer
 */
class TradierAccountTypeDayTrader : public TradierAccountTypeSettings {
 public:
  // The total amount of funds available for the purchase of fully
  // marginable stock during that trading day,
  // a portion of these funds cannot be held overnight.
  double day_trade_buying_power;
};

/**
 * Account Type margin settings
 * @ingroup BrokeragesLayer
 */
class TradierAccountTypeMargin : public TradierAccountTypeSettings {
 public:
  int sweep;
};

/**
 * Account Type Cash
 * @ingroup BrokeragesLayer
 */
class TradierAccountTypeCash {
 public:
  int sweep;
  int cash_available;
  int unsettled_funds;
};
}  // namespace brokerages
}  // namespace quantsystem
#endif  // QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_BALANCE_H_
