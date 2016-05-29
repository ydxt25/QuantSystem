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


#ifndef QUANTSYSTEM_ALGORITYM_BASIC_TEMPLATE_ALGORITHM_
#define QUANTSYSTEM_ALGORITYM_BASIC_TEMPLATE_ALGORITHM_

#include <glog/logging.h>
#include "quantsystem/algorithm/qsalgorithm.h"
#include "quantsystem/common/global.h"
#include "quantsystem/common/data/market/tradebars.h"

namespace quantsystem {
using data::market::TradeBars;
namespace algorithm {
class BasicTemplateAlgorithm : public QSAlgorithm {
 public:
  virtual void Initialize() {
    LOG(INFO) << "Initialize algorithm";
    SetStartDate(2013, 10, 7);
    SetEndDate(2013, 10, 11);
    SetCash(100000);
    AddSecurity(SecurityType::kEquity, "SPY", Resolution::kSecond);
  }

  virtual void OnData(const TradeBars* data) {
    //LOG(INFO) << "OnData algorithm";
    if (!portfolio()->Invested()) {
       SetHoldings("SPY", 1);
       Debug("Purchased Stock");
    }
  }
};

}  // namespace algorithm
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ALGORITYM_BASIC_TEMPLATE_ALGORITHM_
