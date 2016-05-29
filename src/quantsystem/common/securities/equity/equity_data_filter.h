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

#ifndef QUANTSYSTEM_COMMON_SECURITIES_EQUITY_EQUITY_DATA_FILTER_H_
#define QUANTSYSTEM_COMMON_SECURITIES_EQUITY_EQUITY_DATA_FILTER_H_

#include "quantsystem/common/data/base_data.h"
#include "quantsystem/common/securities/security.h"
#include "quantsystem/common/securities/security_data_filter.h"
namespace quantsystem {
namespace securities {
namespace equity {
/**
 * Equity security type data filter.
 * @ingroup CommonBaseSecurities
 */
class EquityDataFilter : public SecurityDataFilter {
 public:
  /**
   * Standard constructor.
   */
  EquityDataFilter();

  /**
   * Standard destructor.
   */
  virtual ~EquityDataFilter();

  /**
   * Equity filter the data: true - accept, false - fail.
   * @param asset Asset for filter
   * @param data BaseData data object we're filtering
   */
  virtual bool Filter(const Security& asset, const BaseData& data) {
    // By default the filter does not change data.
    return true;
  }
};
}  // namespace equity
}  // namespace securities
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SECURITIES_EQUITY_EQUITY_DATA_FILTER_H_
