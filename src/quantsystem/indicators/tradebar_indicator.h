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

#ifndef QUANTSYSTEM_INDICATORS_TRADERBAR_INDICATOR_H_
#define QUANTSYSTEM_INDICATORS_TRADERBAR_INDICATOR_H_

#include <string>
using std::string;
#include "quantsystem/common/data/market/tradebar.h"
#include "quantsystem/indicators/indicator_base.h"
namespace quantsystem {
using data::market::TradeBar;
namespace indicators {
/**
 * The TradeBarIndicator is an indicator that accepts
 * TradeBar data as its input.
 * @ingroup IndicatorsLayer
 */
class TradeBarIndicator : public IndicatorBase<TradeBar> {
 protected:
  /**
   * The TradeBarIndicator is an indicator that
   * accepts TradeBar data as its input.
   */
  explicit TradeBarIndicator(string name);

  /**
   * Computes the next value of this indicator from the given state.
   * @param input The input given to the indicator.
   * @return A new value for this indicator.
   */
  virtual double ComputeNextValue(const TradeBar& input) = 0;
};

}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_TRADERBAR_INDICATOR_H_
