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

#ifndef QUANTSYSTEM_COMMON_SECURITIES_EQUITY_EQUITY_HOLDING_H_
#define QUANTSYSTEM_COMMON_SECURITIES_EQUITY_EQUITY_HOLDING_H_

#include <string>
using std::string;
#include "quantsystem/common/securities/security_holding.h"
#include "quantsystem/common/securities/interfaces/isecurity_transaction_model.h"
namespace quantsystem {
namespace securities {
namespace equity {
/**
 * Holdings class for equities securities: no specific properties
 * here but it is a placeholder for future equities specific behaviours.
 * @ingroup CommonBaseSecurities
 */
class EquityHolding : public SecurityHolding {
 public:
  /**
   * Construct an equities holdings.
   */
  EquityHolding(const string& symbol,
                ISecurityTransactionModel* transaction_model);

  /**
   * Standard destructor.
   */
  virtual ~EquityHolding();

 private:
  EquityHolding();
};

}  // namespace equity
}  // namespace securities
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SECURITIES_EQUITY_EQUITY_HOLDING_H_
