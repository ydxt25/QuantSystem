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

#ifndef QUANTSYSTEM_INTERFACES_IAPI_H_
#define QUANTSYSTEM_INTERFACES_IAPI_H_

#include <string>
using std::string;
#include <vector>
using std::vector;
#include "quantsystem/common/global.h"
#include "quantsystem/common/packets/market_today_packet.h"

namespace quantsystem {
using packets::MarketToday;
namespace interfaces {
/**
 * Messaging Interface with Cloud System
 * @ingroup Interfaces
 */
class IApi {
 public:
  /**
   * Standard constructor.
   */
  IApi() { }

  /**
   * Standard destructor.
   */
  virtual ~IApi() { }

  /**
   * Initialize the control system.
   */
  virtual void Initialize() = 0;

  /**
   * Read the maximum log allowance.
   */
  virtual vector<int> ReadLogAllowance(int user_id, const string& user_token) = 0;

  /**
   * Update running total of log usage.
   */
  virtual void UpdateDailyLogUsed(int user_id,
                                  const string& backtest_id,
                                  const string& url,
                                  int length,
                                  const string& user_token,
                                  bool hit_limit = false) = 0;

  /**
   * Get the algorithm current status, active or cancelled from the user.
   * @param algorithm_id Algorithm ID.
   */
  virtual AlgorithmStatus::Enum GetAlgorithmStatus(const string& algorithm_id) = 0;

  /**
   * Set the algorithm status from the worker to update the UX
   * e.g. if there was an error.
   * @param algorithm_id Algorithm id we're setting
   * @param status Status enum of the current worker
   */
  virtual void SetAlgorithmStatus(const string& algorithm_id,
                                  AlgorithmStatus::Enum status) = 0;

  /**
   * Market status today.
   * @param type Security type
   * @return Market today info
   */
  virtual MarketToday MarketStatusToday(SecurityType::Enum type) = 0;

  /**
   * Store the algoritym logs.
   */
  virtual void Store(const string& data,
                     const string& location,
                     StoragePermissions permissions,
                     bool async = false) = 0;
};

}  // namespace interfaces
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INTERFACES_IAPI_H_
