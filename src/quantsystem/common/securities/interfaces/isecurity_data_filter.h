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

#ifndef QUANTSYSTEM_COMMON_SECURITIES_ISECURITY_DATA_FILTER_H_
#define QUANTSYSTEM_COMMON_SECURITIES_ISECURITY_DATA_FILTER_H_

#include "quantsystem/common/data/base_data.h"
#include "quantsystem/common/securities/security.h"

namespace quantsystem {
namespace securities {
class Security;
/**
 * Security data filter interface.
 * Defines pattern for the user defined data filter techniques.
 * @ingroup CommonBaseSecurities
 */
class ISecurityDataFilter {
 public:
  /**
   * Filter out a tick from this security, with this new data.
   * @param security Security of this filter.
   * @param data New data packet we're checking
   */
  virtual bool Filter(const Security& asset, const BaseData& data) = 0;
};

}  // namespace securities
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SECURITIES_ISECURITY_DATA_FILTER_H_
