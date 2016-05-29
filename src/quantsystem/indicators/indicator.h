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

#ifndef QUANTSYSTEM_INDICATORS_INDICATOR_H_
#define QUANTSYSTEM_INDICATORS_INDICATOR_H_

#include <string>
using std::string;
#include "quantsystem/indicators/indicator_base.h"
#include "quantsystem/indicators/indicator_data_point.h"

namespace quantsystem {
namespace indicators {
/**
 * Represents a type capable of ingesting a piece of data and
 * producing a new piece of data. Indicators can be used to filter
 * and transform data into a new, more informative form.
 * @ingroup IndicatorsLayer
 */
class Indicator : public IndicatorBase<IndicatorDataPoint> {
 protected:
  /**
   * Initializes a new instance of the Indicator class using the specified name.
   * @param name The name of this indicator.
   */
  explicit Indicator(const string& name)
      : IndicatorBase<IndicatorDataPoint>(name) {
  }

  /**
   * Computes the next value of this indicator from the given state.
   * @param input The input given to the indicator.
   * @return A new value for this indicator.
   */
  virtual double ComputeNextValue(const IndicatorDataPoint& input) = 0;
};

}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_INDICATOR_H_
