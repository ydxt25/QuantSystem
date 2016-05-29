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

#ifndef QUANTSYSTEM_INDICATORS_EXPONENTIAL_INDICATOR_H_
#define QUANTSYSTEM_INDICATORS_EXPONENTIAL_INDICATOR_H_

#include <string>
using std::string;
#include "quantsystem/indicators/indicator.h"
#include "quantsystem/indicators/indicator_data_point.h"
namespace quantsystem {
namespace indicators {
/**
 * Represents the traditional exponential moving average indicator (EMA).
 * @ingroup IndicatorsLayer
 */
class ExponentialMovingAverage : public Indicator {
 public:
  /**
   * Initializes a new instance of the ExponentialMovingAverage class
   * with the specified name and period.
   * @param name The name of this indicator
   * @param period The period of the EMA
   */
  ExponentialMovingAverage(const string& name, int period);

  /**
   * Initializes a new instance of the ExponentialMovingAverage class
   * with the specified name and period.
   * @param name The name of this indicator
   * @param period The period of the EMA
   * @param smoothing_factor The percentage of data from the previous value
   * to be carried into the next value
   */
  ExponentialMovingAverage(const string& name, int period,
                           double smoothing_factor);

  /**
   * Initializes a new instance of the ExponentialMovingAverage class
   * with the default name and period.
   * @param period The period of the EMA
   */
  explicit ExponentialMovingAverage(int period);

  /**
   * Initializes a new instance of the ExponentialMovingAverage class
   * with the default name and period.
   * @param period The period of the EMA
   * @param smoothing_factor The percentage of data from the previous value
   * to be carried into the next value
   */
  ExponentialMovingAverage(int period, double smoothing_factor);

  /**
   * Gets a flag indicating when this indicator is ready and fully initialized.
   */
  virtual bool is_ready() {
    return samples() > period_;
  }

 protected:
  /**
   * Computes the next value of this indicator from the given state.
   * @param input The input given to the indicator.
   * @return A new value for this indicator.
   */
  virtual double ComputeNextValue(const IndicatorDataPoint& input);

 private:
  double k_;
  int period_;
};

}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_EXPONENTIAL_INDICATOR_H_
