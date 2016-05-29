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

#ifndef QUANTSYSTEM_INDICATORS_CONSTANT_INDICATOR_H_
#define QUANTSYSTEM_INDICATORS_CONSTANT_INDICATOR_H_

#include <string>
using std::string;
#include "quantsystem/indicators/indicator_base.h"
namespace quantsystem {
namespace indicators {
/**
 * An indicator that will always return the same value.
 * @ingroup IndicatorsLayer
 */
template <typename T>
class ConstantIndicator : public IndicatorBase<T> {
 public:
  /**
   * Creates a new ConstantIndicator that will always return the specified value
   * @param name The name of this indicator
   * @param value The constant value to be returned
   */
  ConstantIndicator(const string& name, double value)
      : IndicatorBase(name),
        value_(value) {
  }

  /**
   * Gets a flag indicating when this indicator is ready and fully initialized.
   */
  virtual bool is_ready() const {
    return true;
  }

 protected:
  /**
   * Computes the next value of this indicator from the given state.
   * @param input The input given to the indicator.
   * @return A new value for this indicator.
   */
  virtual double ComputeNextValue(const T& input) {
    return value_;
  }

 private:
  double value_;
};

}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_CONSTANT_INDICATOR_H_
