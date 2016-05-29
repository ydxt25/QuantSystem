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

#ifndef QUANTSYSTEM_COMMON_SECURITIES_SECURITY_DATA_FILTER_H_
#define QUANTSYSTEM_COMMON_SECURITIES_SECURITY_DATA_FILTER_H_

#include "quantsystem/common/data/base_data.h"
#include "quantsystem/common/securities/security.h"
#include "quantsystem/common/securities/interfaces/isecurity_data_filter.h"
namespace quantsystem {
namespace securities {
/**
 * Base class implementation for packet by packet data
 * filtering mechanism to dynamically detect bad ticks.
 * @ingroup CommonBaseSecurities
 */
class SecurityDataFilter : public ISecurityDataFilter {
 public:
  /**
   * Standard constructor.
   */
  SecurityDataFilter();

  /**
   * Standard destructor.
   */
  virtual ~SecurityDataFilter();

  /**
   * Filter the data packet passing through this method
   * by returning true to accept, or false to fail/reject the data point.
   * @param asset Asset for filter
   * @param data BaseData data object we're filtering
   */
  virtual bool Filter(const Security& asset, const BaseData& data) {
    // By default the filter does not change data.
    return true;
  }
};
}  // namespace securities
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SECURITIES_SECURITY_DATA_FILTER_H_
