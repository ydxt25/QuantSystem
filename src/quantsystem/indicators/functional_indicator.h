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

#ifndef QUANTSYSTEM_INDICATORS_FUNCTIONAL_INDICATOR_H_
#define QUANTSYSTEM_INDICATORS_FUNCTIONAL_INDICATOR_H_

#include <string>
using std::string;
#include <functional>
using std::function;
#include "quantsystem/common/base/macros.h"
#include "quantsystem/indicators/indicator_base.h"
namespace quantsystem {
namespace indicators {
/**
 * The functional indicator is used to lift any function into an indicator.
 * This can be very useful when trying to combine output of several indicators,
 * or for expression a mathematical equation
 * @ingroup IndicatorsLayer
 */
template <typename T>
class FunctionalIndicator : IndicatorBase<T> {
 public:
  typedef function<bool()> ReadyHandler;
  typedef function<double(const T&)> ComputeNewHandler;  //NOLINT
  /**
   * Creates a new FunctionalIndicator using the specified functions
   * as its implementation.
   * @param name The name of this indicator
   * @param compute_next_value A function accepting the input value
   * and returning this indicator's output value
   * @param is_ready A function returning true if the indicator is ready,
   * false otherwise
   */
  FunctionalIndicator(const string& name,
                      const ComputeNewHandler& compute_new_value,
                      const ReadyHandler& is_ready)
      : IndicatorBase<T>(name),
        compute_new_value_(compute_new_value),
        is_ready_(is_ready) {
  }

  /**
   * Standard destructor.
   */
  virtual ~FunctionalIndicator() {
  }

  /**
   * Gets a flag indicating when this indicator is ready and fully initialized
   */
  virtual bool is_ready() const {
    return is_ready_();
  }

 protected:
  /**
   * Computes the next value of this indicator from the given state.
   * @param input The input given to the indicator
   * @return A new value for this indicator
   */
  virtual double ComputeNextValue(const T& input) {
    return compute_new_value_(input);
  }

 private:
  ReadyHandler is_ready_;
  ComputeNewHandler compute_new_value_;

  DISALLOW_COPY_AND_ASSIGN(FunctionalIndicator);
};

}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_FUNCTIONAL_INDICATOR_H_
