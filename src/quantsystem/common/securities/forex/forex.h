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

#ifndef QUANTSYSTEM_COMMON_SECURITIES_FOREX_FOREX_H_
#define QUANTSYSTEM_COMMON_SECURITIES_FOREX_FOREX_H_

#include <string>
using std::string;
#include "quantsystem/common/global.h"
#include "quantsystem/common/securities/security.h"
#include "quantsystem/common/securities/forex/forex_cache.h"
#include "quantsystem/common/securities/forex/forex_exchange.h"
#include "quantsystem/common/securities/forex/forex_holding.h"
#include "quantsystem/common/securities/forex/forex_transaction_model.h"
namespace quantsystem {
namespace securities {
namespace forex {
/**
 * FOREX Security Object Implementation for FOREX Assets
 * @ingroup CommonBaseSecurities
 */
class Forex : public Security {
 public:
  /**
   * Construct a Forex securtiy.
   */
  Forex(const string& symbol, Resolution::Enum resolution,
        bool fill_data_forward, double leverage, bool extended_market_hours,
        bool use_quant_system_data = false);

  /**
   * Standard destructor.
   */
  virtual ~Forex();

  /**
   * Forex cache class for caching data, charting and orders.
   */
  ForexCache* cache() const {
    return dynamic_cast<ForexCache*>(Security::cache());
  }
  void set_cache(ForexCache* cache) {
    Security::set_cache(cache);
  }

  /**
   * Forex holdings class for managing cash, quantity held, portfolio
   */
  ForexHolding* holdings() const {
    return dynamic_cast<ForexHolding*>(Security::holdings());
  }
  void set_holdings(ForexHolding* holdings) {
    Security::set_holdings(holdings);
  }

  /**
   * Forex exchange class for manaing time open and close.
   */
  ForexExchange* exchange() const {
    return dynamic_cast<ForexExchange*>(Security::exchange());
  }
  void set_exchange(ForexExchange* exchange) {
    Security::set_exchange(exchange);
  }

  /**
   * Equity security transaction and fill models.
   */
  ISecurityTransactionModel* model() const {
    return dynamic_cast<ForexTransactionModel*>(Security::model());
  }
  void set_model(ISecurityTransactionModel* model) {
    Security::set_model(model);
  }

 private:
  Forex();
};

}  // namespace forex
}  // namespace securities
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SECURITIES_FOREX_FOREX_H_
