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

#ifndef QUANTSYSTEM_INDICATORS_IDENTITY_H_
#define QUANTSYSTEM_INDICATORS_IDENTITY_H_

#include <string>
using std::string;
#include "quantsystem/indicators/indicator.h"
#include "quantsystem/indicators/indicator_data_point.h"
namespace quantsystem {
namespace indicators {
/**
 * Represents an indicator that is a ready after ingesting a single sample and
 * always returns the same value as it is given.
 * @ingroup IndicatorsLayer
 */
class Identity : public Indicator {
 public:
  /**
   * Initializes a new instance of the Identity indicator
   * with the specified name.
   * @param name The name of the indicator
   */
  explicit Identity(const string& name);

  /**
   * Gets a flag indicating when this indicator is ready and fully initialized.
   */
  virtual bool is_ready() {
    return samples() > 0;
  }

 protected:
  /**
   * Computes the next value of this indicator from the given state.
   * @param input The input given to the indicator.
   * @return A new value for this indicator.
   */
  virtual double ComputeNextValue(const IndicatorDataPoint& input);
};

}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_IDENTITY_H_
