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

#ifndef QUANTSYSTEM_COMMON_SECURITIES_SECURITY_PORTFOLIO_MANAGER_H_
#define QUANTSYSTEM_COMMON_SECURITIES_SECURITY_PORTFOLIO_MANAGER_H_

#include <string>
using std::string;
#include "quantsystem/common/orders/order.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/securities/security_manager.h"
#include "quantsystem/common/securities/security_transaction_manager.h"
#include "quantsystem/common/securities/security_holding.h"

namespace quantsystem {
namespace securities {
class SecurityTransactionManager;
/**
 * Portfolio manager class groups popular properties and
 * makes them accessible through one interface.
 * It also provide indexing by the symbol to get the Security.Holding objects.
 * @ingroup CommonBaseSecurities
 */
class SecurityPortfolioManager {
 public:
  SecurityPortfolioManager(SecurityManager* security_manager,
                           SecurityTransactionManager* transactions);

  /**
   * Standard destructor.
   */
  virtual ~SecurityPortfolioManager();

  /**
   * Check if the portfolio contains this symbol string.
   * @param symbol String search symbol for the security.
   */
  bool ContainsKey(const string& string) const;

  /**
   * Count the securities objects in the portfolio.
   */
  int Count() const {
    return securities_->Count();
  }

  void Values(vector<SecurityHolding*>* values);

  void Keys(vector<string>* keys) const;

  /**
   * Cash allocated to this company, from which we can find
   * the buying power available.
   */
  double cash() const { return cash_; }

  /**
   * Set the cash this algorithm is to manage.
   * @param cash Cash value of portfolio.
   */
  void set_cash(const double& cash) { cash_ = cash; }

  /**
   * Absolute value of cash discounted from our total cash
   * by the holdings we own.
   *
   * When account has leverage the actual cash removed is a fraction of the
   * purchase price according to the leverage
   */
  double TotalUnleveredAbsoluteHoldingsCost() const;

  /**
   * Absolute sum the individual items in portfolio.
   */
  double TotalHoldingsValue() const;

  /**
   * Boolean flag indicating we have any holdings in the portfolio.
   */
  bool HoldStock() const { return TotalHoldingsValue() > 0; }

  /**
   * Alias for HoldStock. Check if we have and holdings.
   */
  bool Invested() const { return HoldStock(); }

  /**
   * Get the total unrealised profit in our portfolio from the individual
   * security unrealized profits.
   */
  double TotalUnrealisedProfit() const;

  /**
   * Get the total unrealised profit in our portfolio from the individual
   * security unrealized profits.
   *
   * Added alias for American spelling
   */
  double TotalUnreadlizedProfit() const { return TotalUnrealisedProfit(); }

  /**
   * Total portfolio value if we sold all holdings at current market rates.
   * 
   * @see cahs
   * @see TotalUnrealisedProfit
   * @see TotalUnreadlizedProfit
   */
  double TotalPortfolioValue() const {
    return cash() + TotalUnrealisedProfit()
        + TotalUnleveredAbsoluteHoldingsCost();
  }

  /**
   * Total fees paid during the algorithm operation
   * across all securities in portfolio.
   */
  double TotalFees() const;

  /**
   * Sum of all gross profit across all securities in portfolio.
   */
  double TotalProfit() const;

  /**
   * Total sale volume since the start of algorithm operations.
   */
  double TotalSaleVolume() const;

  /**
   * Indexer for the PortfolioManager class to access the underlying
   * security holdings objects.
   */
  SecurityHolding* operator[] (const string& symbol);

  /**
   * The total buying power remaining after factoring in leverage.
   *
   * Because each security has its own leverage the buying power
   * is a function of security.
   * Similarly the desired trade direction can impact the buying
   * power available
   * @return Total buying power for this symbol
   */
  double GetBuyingPower(const string& symbol,
                        orders::OrderDirection direction = orders::kHold) const;

  /**
   * Calculate the new average price after processing a
   * partial/complete order fill event. 
   *
   * For purchasing stocks from zero holdings, the new average price
   * is the sale price.
   * When simply partially reducing holdings the average price remains the same.
   * When crossing zero holdings the average price becomes the trade price
   * in the new side of zero.
   */
  virtual void ProcessFill(const OrderEvent& fill);

  /**
   * Scan the portfolio and the updated data for a potential margin
   * call situation
   *
   * which may get the holdings below zero! If there is a margin call,
   * liquidate the portfolio immediately before the portfolio gets sub zero.
   * @return True for a margin call on the holdings.
   */
  bool ScanForMarginCall() {
    // TODO(shishougang)
    return false;
  }

  /**
   * Record the transaction value and time in a list to later be
   * processed for statistics creation.
   * 
   * Bit of a hack -- but using datetime as dictionary key is dangerous
   * as you can process multiple orders within a second.
   * For the accounting / statistics generating purposes its not really
   * critical to know the precise time, so just add a millisecond
   * while there's an identical key.
   * @param time Time of order processed
   * @param transaction_profit_loss Profit loss
   */
  void AddTransactionRecord(const DateTime& time,
                            const double& transaction_profit_loss);

 private:
  // Local access to the securities collection for the portfolio summation.
  SecurityManager* securities_;
  // Local access to the transactions collection for the portfolio
  // summation and updates.
  SecurityTransactionManager* transactions_;
  double cash_;
  double last_trade_profit_;
  double profit_;
};

}  // namespace securities
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SECURITIES_SECURITY_PORTFOLIO_MANAGER_H_
