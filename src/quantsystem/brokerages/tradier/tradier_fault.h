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

#ifndef QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_FAULT_H_
#define QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_FAULT_H_

#include <string>
using std::string;

namespace quantsystem {
namespace brokerages {
/**
 * Error code associated with this fault.
 * @ingroup BrokeragesLayer
 */
class TradierFaultDetail {
 public:
  string error_code;
};

/**
 * Tradier fault object.
 * {"fault":{"faultstring":"Access Token expired",
 * "detail":{"errorcode":"keymanagement.service.access_token_expired"}}}
 * @ingroup BrokeragesLayer
 */
class TradierFault {
 public:
  string description;
  TradierFaultDetail details;
};

/**
 * Wrapper container for fault.
 * @ingroup BrokeragesLayer
 */
class TradierFaultContainer {
 public:
  TradierFault fault;
};

}  // namespace brokerages
}  // namespace quantsystem
#endif  // QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_FAULT_H_
