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

#ifndef QUANTSYSTEM_INDICATORS_MOMENTUM_H_
#define QUANTSYSTEM_INDICATORS_MOMENTUM_H_

#include <string>
using std::string;
#include "quantsystem/indicators/indicator_data_point.h"
#include "quantsystem/indicators/iread_only_window.h"
#include "quantsystem/indicators/window_indicator.h"
namespace quantsystem {
namespace indicators {
/**
 * This indicator computes the n-period change in a value using the following:
 * value_0 - value_n
 * @ingroup IndicatorsLayer
 */
class Momentum : public WindowIndicator<IndicatorDataPoint> {
 public:
  /**
   * Creates a new Momentum indicator with the specified period.
   * @param period The period over which to perform to computation
   */
  explicit Momentum(int period);

  /**
   * Creates a new Momentum indicator with the specified period.
   * @param name The name of this indicator
   * @param period The period over which to perform to computation
   */
  Momentum(const string& name, int period);

 protected:
  /**
   * Computes the next value for this indicator from the given state.
   * @param window[out] The window of data held in this indicator
   * @param input The input value to this indicator on this time step
   * @return A new value for this indicator
   */
  virtual double ComputeNextValue(IReadOnlyWindow<IndicatorDataPoint>* window,
                                  IndicatorDataPoint input);
};

}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_MOMENTUM_H_
