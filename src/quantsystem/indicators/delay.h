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

#ifndef QUANTSYSTEM_INDICATORS_DELAY_H_
#define QUANTSYSTEM_INDICATORS_DELAY_H_

#include <string>
using std::string;
#include "quantsystem/indicators/window_indicator.h"
#include "quantsystem/indicators/indicator_data_point.h"
#include "quantsystem/indicators/iread_only_window.h"
namespace quantsystem {
namespace indicators {
/**
 * An indicator that delays its input for a certain period.
 * @ingroup IndicatorsLayer
 */
class Delay : public WindowIndicator<IndicatorDataPoint> {
 public:
  /**
   * Creates a new Delay indicator that delays its input
   * by the specified period.
   * @param period The period to delay input, must be greater than zero
   */
  explicit Delay(int period);

  /**
   * Creates a new Delay indicator that delays its input by the specified period
   * @param name The name of this indicator
   * @param period The period to delay input, must be greater than zero
   */
  Delay(const string& name, int period);

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
#endif  // QUANTSYSTEM_INDICATORS_DELAY_H_
