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

#ifndef QUANTSYSTEM_COMMON_SECURITIES_EQUITY_EQUITY_H_
#define QUANTSYSTEM_COMMON_SECURITIES_EQUITY_EQUITY_H_

#include <string>
using std::string;
#include "quantsystem/common/global.h"
#include "quantsystem/common/securities/security.h"
#include "quantsystem/common/securities/equity/equity_cache.h"
#include "quantsystem/common/securities/equity/equity_exchange.h"
#include "quantsystem/common/securities/equity/equity_holding.h"
#include "quantsystem/common/securities/equity/equity_transaction_model.h"
namespace quantsystem {
namespace securities {
namespace equity {
/**
 * Equity Security Type : Extension of the underlying Security class
 * for equity specific behaviours.
 * @ingroup CommonBaseSecurities
 * @see Security
 */
class Equity : public Security {
 public:
  /**
   * Construct the Equity.
   */
  Equity(const string& symbol, Resolution::Enum resolution,
         bool fill_data_forward, double leverage, bool extended_market_hours,
         bool use_quant_system_data = false);

  /**
   * Standard destructor.
   */
  virtual ~Equity();

  /**
   * Equity cache class for caching data, charting and orders.
   */
  EquityCache* cache() const {
    return dynamic_cast<EquityCache*>(Security::cache());
  }
  void set_cache(EquityCache* cache) {
    Security::set_cache(cache);
  }

  /**
   * Equity holdings class for managing cash, quantity held, portfolio
   */
  EquityHolding* holdings() const {
    return dynamic_cast<EquityHolding*>(Security::holdings());
  }
  void set_holdings(EquityHolding* holdings) {
    Security::set_holdings(holdings);
  }

  /**
   * Equity exchange class for manaing time open and close.
   */
  EquityExchange* exchange() const {
    return dynamic_cast<EquityExchange*>(Security::exchange());
  }
  void set_exchange(EquityExchange* exchange) {
    Security::set_exchange(exchange);
  }

  /**
   * Equity security transaction and fill models.
   */
  ISecurityTransactionModel* model() const {
    return dynamic_cast<EquityTransactionModel*>(Security::model());
  }
  void set_model(ISecurityTransactionModel* model) {
    Security::set_model(model);
  }

 private:
  Equity();
};

}  // namespace equity
}  // namespace securities
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SECURITIES_EQUITY_EQUITY_H_
