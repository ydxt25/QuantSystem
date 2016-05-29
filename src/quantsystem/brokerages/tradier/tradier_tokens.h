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

#ifndef QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_TOKENS_H_
#define QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_TOKENS_H_

#include <string>
using std::string;
#include "quantsystem/common/time/date_time.h"

namespace quantsystem {
namespace brokerages {
/**
 * Token response model from Quantsystem terminal
 * @ingroup BrokeragesLayer
 */
class TokenResponse {
 public:
  string access_token;  // Access token for current requests.
  string refresh_token;  // Refresh token for next time.
  int expires;  // Seconds the tokens expires
  string scope;  // Scope of token access
  DateTime issued_at;  // Time the token was issued
  bool success;

  /**
   * Standard constructor.
   */
  TokenResponse();

  /**
   * Standard destructor.
   */
  virtual ~TokenResponse();
};

}  // namespace brokerages
}  // namespace quantsystem
#endif  // QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_TOKENS_H_
