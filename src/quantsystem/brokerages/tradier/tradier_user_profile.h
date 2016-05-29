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

#ifndef QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_USER_PROFILE_H_
#define QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_USER_PROFILE_H_

#include <string>
using std::string;
#include <vector>
using std::vector;
#include "quantsystem/common/base/integral_types.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/brokerages/tradier/tradier_common.h"

namespace quantsystem {
namespace brokerages {
class TradierUserAccount;
/**
 * User profile array.
 * @ingroup BrokeragesLayer
 */
class TradierUser {
 public:
  string id;  // Unique brokerage user id
  string name;  // Name of user
  vector<TradierUserAccount> accounts;
};

/**
 * Model for a TradierUser returned from the API.
 * @ingroup BrokeragesLayer
 */
class TradierUserContainer {
 public:
  TradierUser profile;
};

/**
 * Account only settings for a tradier user.
 * @ingroup BrokeragesLayer
 */
class TradierUserAccount {
 public:
  int64 account_number;
  bool day_trader;  // Pattern Trader
  int option_level;  // Options level permissions on account
  TradierAccountType type;  // Cash or Margin Account
  DateTime last_updated;
  TradierAccountStatus status;
  TradierAccountClassification classification;  // Type of user account

  /**
   * Standard constructor.
   */
  TradierUserAccount();

  /**
   * Standard destructor.
   */
  virtual ~TradierUserAccount();
};

}  // namespace brokerages
}  // namespace quantsystem
#endif  // QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_USER_PROFILE_H_
