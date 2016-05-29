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

#ifndef QUANTSYSTEM_COMMON_SECURITIES_SECURITY_HOLDING_H_
#define QUANTSYSTEM_COMMON_SECURITIES_SECURITY_HOLDING_H_

#include <cstdlib>
#include <string>
using std::string;
#include "quantsystem/common/base/scoped_ptr.h"
#include "quantsystem/common/securities/interfaces/isecurity_transaction_model.h"

namespace quantsystem {
namespace securities {
/**
 * SecurityHolding is a base class for purchasing and
 * holding a market item which manages the asset portfolio.
 * @ingroup CommonBaseSecurities
 */
class SecurityHolding {
 public:
  /**
   * Construct a new holding class instance setting the initial
   * properties to $0.
   */
  SecurityHolding(const string& symbol,
                   ISecurityTransactionModel* model);

  /**
   * Standard destructor.
   */
  virtual ~SecurityHolding();

  /**
   * Average price of the security holdings.
   */
  double average_price() const { return average_price_; }

  /**
   * Quantity of the security holdings.
   *
   * Positive indicates long holdings,
   * negative quantity indicates a short holding.
   * @see AbsoluteQuantity
   */
  int quantity() const { return quantity_; }

  /**
   * Symbol identifier of the underlying security.
   */
  string symbol() const { return symbol_; }

  /**
   * Acquisiton cost of the security total holdings.
   */
  virtual double HoldingCost() const {
    return average_price_ * quantity_;
  }

  /**
   * Current market price of the security.
   */
  virtual double price() const { return price_; }

  /**
   * Absolute holdings cost for current holding.
   */
  virtual double AbsoluteHoldingsCost() const {
    return abs(HoldingCost());
  }

  /**
   * Market value of our holdings.
   */
  virtual double HoldingsValue() const {
    return price_ * quantity_;
  }

  /**
   * Absolute of the market value of our holdings.
   * @see HoldingsValue
   */
  virtual double AbsoluteHoldingsValue() const {
    return abs(HoldingsValue());
  }

  /**
   * Check if we hold any of the security.
   */
  virtual bool HoldStock() const {
    return AbsoluteQuantity() > 0;
  }

  /**
   * Check if we hold any of the security.
   * Alias of HoldStock.
   * @see HoldStock
   */
  virtual bool Invested() const {
    return HoldStock();
  }

  /**
   * The total transaction volume for this security since the algorithm started.
   */
  virtual double total_sale_volume() const { return total_sale_volume_; }

  /**
   * Total fees for this company since the algorithm started.
   */
  virtual double total_fees() const { return total_fees_; }

  /**
   * Boolean flag indicating we have a net positive holding of the security.
   */
  virtual bool IsLong() const { return quantity_ > 0; }

  /**
   * Boolean flag indicating we have a net negative holding of the security.
   */
  virtual bool IsShort() const { return quantity_ < 0; }

  /**
   * Absolute quantity of holdings of this security
   * @see quantity
   */
  virtual double AbsoluteQuantity() const {
    return abs(quantity_);
  }

  /**
   * Record of the closing profit from the last trade conducted.
   */
  virtual double last_trade_profit() const { return last_trade_profit_; }

  /**
   * Calculate the total profit for this security.
   * @see NetProfit
   */
  virtual double profit() const { return profit_; }

  /**
   * Return the net for this company measured by the profit less fees.
   * @see profit
   * @see total_fees
   */
  virtual double NetProfit() const {
    return profit_ - total_fees_;
  }

  /**
   * Unrealized profit of this security
   * when absolute quantity held is more than zero.
   */
  virtual double UnrealizedProfit() { return TotalCloseProfit(); }

  /**
   * Adds a fee to the running total of total fees.
   */
  void AddNewFee(const double& new_fee) {
    total_fees_ += new_fee;
  }

  /**
   * Adds a profit record to the running total of profit.
   * @see profit_loss The cash change in portfolio from closing a position
   */
  void AddNewProfit(const double& profit_loss) {
    profit_ += profit_loss;
  }

  /**
   * Adds a new sale value to the running total trading volume.
   */
  void AddNewSale(const double& sale_value) {
    total_sale_volume_ += sale_value;
  }

  /**
   * Set the last trade profit for this security
   * from a Portfolio.ProcessFill call.
   * @param last_trade_profit Value of the last trade profit
   */
  void SetLastTradeProfit(const double& last_trade_profit) {
    last_trade_profit_ = last_trade_profit;
  }

  /**
   * Set the quantity of holdings and
   * their average price after processing a portfolio fill.
   */
  virtual void SetHoldings(const double& average_price, int quantity) {
    average_price_ = average_price;
    quantity_ = quantity;
  }

  /**
   * Update local copy of closing price value.
   * @param closing_price Price of the underlying
   * asset to be used for calculating market price / portfolio value
   */
  virtual void UpdatePrice(const double& closing_price) {
    price_ = closing_price;
  }

  /**
   * Profit if we closed the holdings right now including the approximate fees.
   */
  virtual double TotalCloseProfit();

 private:
  double average_price_;
  int quantity_;
  double price_;
  string symbol_;
  double total_sale_volume_;
  double profit_;
  double last_trade_profit_;
  double total_fees_;
  ISecurityTransactionModel* model_;

  SecurityHolding();
};

/**
 * @ingroup CommonBaseSecurities
 *
 * Singular holding of assets from backend live nodes:
 */
class Holding {
 public:
  // Symbol of the Holding:
  string symbol;
  // Average price of our holding
  double average_price;
  // Quantity of symbol we hold
  double quantity;
  // Current market price of the asset
  double market_price;

  /**
   * Standard constructor.
   */
  Holding();

  /**
   * Standard constructor for an immutable data object instance.
   *
   * Create a simple JSON holdings from a Security holding class.
   * @param holding a Security holding class.
   *
   * @see SecurityHolding
   */
  explicit Holding(const securities::SecurityHolding& holding);

  /**
   * Standard destructor.
   */
  virtual ~Holding();
};
}  // namespace securities
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SECURITIES_SECURITY_HOLDING_H_
