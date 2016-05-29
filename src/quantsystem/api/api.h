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
 * @defgroup ApiLayer Api Layer
 *
 * Api Layer.
 */

#ifndef QUANTSYSTEM_API_API_H_
#define QUANTSYSTEM_API_API_H_

#include <string>
using std::string;
#include <vector>
using std::vector;
#include "quantsystem/common/global.h"
#include "quantsystem/interfaces/iapi.h"
#include "quantsystem/common/packets/market_today_packet.h"
namespace quantsystem {
using packets::MarketToday;
using interfaces::IApi;
namespace api {

/**
 * Cloud algorithm activity controls
 * @ingroup ApiLayer
 */
class Api : public IApi {
 public:
  /**
   * Standard constructor.
   */
  Api();

  /**
   * Standard destructor.
   */
  virtual ~Api();

  /**
   * Initialize the control system.
   */
  virtual void Initialize() {
    // Nothing to initialize in the local copy of the engine.
  }

  /**
   * Read the maximum log allowance.
   * @return UserBacktestLimit, UserDailyLimit, remaining
   */
  virtual vector<int> ReadLogAllowance(int user_id, const string& user_token);

  /**
   * Update running total of log usage.
   * @param user_id Id of the User
   * @param backtest_id Backtest id
   * @param url URL of the log entry
   * @param length length of data
   * @param user_token User access token
   * @param hitLimit Boolean flag to  hit log limit
   */
  virtual void UpdateDailyLogUsed(int user_id,
                                  const string& backtest_id,
                                  const string& url,
                                  int length,
                                  const string& user_token,
                                  bool hit_limit = false) {
  }

  /**
   * Get the algorithm current status, active or cancelled from the user.
   * @param algorithm_id Algorithm ID.
   * @return Algorithm status enum
   */
  virtual AlgorithmStatus::Enum GetAlgorithmStatus(const string& algorithm_id) {
    return AlgorithmStatus::kRunning;
  }

  /**
   * Set the algorithm status from the worker to update the UX
   * e.g. if there was an error.
   * @param algorithm_id Algorithm id we're setting
   * @param status Status enum of the current worker
   */
  virtual void SetAlgorithmStatus(const string& algorithm_id,
                                  AlgorithmStatus::Enum status) {
  }

  /**
   * Market status today.
   * @param type Security type
   * @return Market today info
   */
  virtual MarketToday MarketStatusToday(SecurityType::Enum type) {
    return MarketToday();
  }

  /**
   * Store the algoritym logs.
   */
  virtual void Store(const string& data,
                     const string& location,
                     StoragePermissions permissions,
                     bool async = false) {
  }
};

}  // namespace api
}  // namespace quantsystem
#endif  // QUANTSYSTEM_API_API_H_
