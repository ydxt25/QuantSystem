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

/**
 * @defgroup BrokeragesLayer Brokerages Layer
 *
 * The Brokerages Layer provides different brokerages support.
 * It includes paper and tradier brokerages.
 */

#ifndef QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_BROKERAGE_H_
#define QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_BROKERAGE_H_

#include <string>
using std::string;
#include <map>
using std::map;
#include <vector>
using std::vector;
#include "quantsystem/brokerages/brokerage.h"
#include "quantsystem/common/base/callback.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/time/time_span.h"
#include "quantsystem/brokerages/tradier/tradier_common.h"
#include "quantsystem/brokerages/tradier/tradier_fault.h"

namespace quantsystem {
namespace brokerages {
/**
 * Tradier brokerage include:
 *  - Handle authentication.
 *  - Data requests.
 *  - Rate limiting.
 *  - Placing orders.
 *  - Getting user data.
 * @ingroup BrokeragesLayer
 */
class TradierBrokerage : public Brokerage {
 public:
  /**
   * Standard constructor.
   */
  TradierBrokerage();

  /**
   * Standard destructor.
   */
  virtual ~TradierBrokerage();

  /**
   * Add an error handler for the specific brokerage error.
   * @param key String error name
   * @param callback Action call back
   */
  virtual void AddErrorHander(const string& key, Closure* callback);

  /**
   * Refresh brokerage login session where applicable.
   */
  virtual bool RefreshSession();

 private:
  // Access and refresh tokens
  string access_token_;
  string refresh_token_;
  string previous_request_raw_;
  int user_id_;
  string name_;
  DateTime issued_at_;
  string scope_;
  TimeSpan life_span_;
  // Tradier Spec
  map<TradierApiRequestType::Enum, TimeSpan> rate_limit_period_;
  map<TradierApiRequestType::Enum, DateTime> rate_limit_next_request_;
  map<string, Closure*> error_handlers_;
  vector<TradierFault> faults;
  // Endpoint
  string request_endpoint_;

};

}  // namespace brokerages
}  // namespace quantsystem
#endif  // QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_BROKERAGE_H_
