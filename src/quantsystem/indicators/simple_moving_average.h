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

#ifndef QUANTSYSTEM_INDICATORS_SIMPLE_MOVING_AVERAGE_H_
#define QUANTSYSTEM_INDICATORS_SIMPLE_MOVING_AVERAGE_H_

#include <string>
using std::string;
#include "quantsystem/indicators/window_indicator.h"
#include "quantsystem/indicators/iread_only_window.h"
#include "quantsystem/indicators/indicator_data_point.h"
namespace quantsystem {
namespace indicators {
/**
 * Represents the traditional simple moving average indicator (SMA)
 * @ingroup IndicatorsLayer
 */
class SimpleMovingAverage : public  WindowIndicator<IndicatorDataPoint> {
 public:
  /**
   * Initializes a new instance of the SimpleMovingAverage class
   * with the specified name and period.
   * @param name The name of this indicator
   * @param period The period of the SMA
   */
  SimpleMovingAverage(const string&name, int period);

  /**
   * Initializes a new instance of the SimpleMovingAverage class with
   * the default name and period.
   * @param period The period of the SMA
   */
  explicit SimpleMovingAverage(int period);

 protected:
  /**
   * Computes the next value for this indicator from the given state.
   * @param[out] window The window of data held in this indicator
   * @param input The input value to this indicator on this time step
   * @return A new value for this indicator
   */
  virtual double ComputeNextValue(IReadOnlyWindow<IndicatorDataPoint>* window,
                                  const IndicatorDataPoint& input);

 private:
  double sum_;
};

}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_SIMPLE_MOVING_AVERAGE_H_
