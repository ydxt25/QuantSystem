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

#ifndef QUANTSYSTEM_COMMON_SECURITIES_FOREX_FOREX_HOLDING_H_
#define QUANTSYSTEM_COMMON_SECURITIES_FOREX_FOREX_HOLDING_H_


#include <string>
using std::string;
#include "quantsystem/common/securities/security_holding.h"
#include "quantsystem/common/securities/interfaces/isecurity_transaction_model.h"
namespace quantsystem {
namespace securities {
namespace forex {
/**
 * FOREX holdings implementation of the base securities class.
 * @ingroup CommonBaseSecurities
 */
class ForexHolding : public SecurityHolding {
 public:
  /**
   * Construct an equities holdings.
   */
  ForexHolding(const string& symbol,
               ISecurityTransactionModel* transaction_model);

  /**
   * Standard destructor.
   */
  virtual ~ForexHolding();

 private:
  ForexHolding();
};

}  // namespace forex
}  // namespace securities
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SECURITIES_FOREX_FOREX_HOLDING_H_
