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

#ifndef QUANTSYSTEM_INDICATORS_WINDOW_INDICATOR_H_
#define QUANTSYSTEM_INDICATORS_WINDOW_INDICATOR_H_

#include <string>
using std::string;
#include "quantsystem/indicators/iread_only_window.h"
#include "quantsystem/indicators/rolling_window.h"
#include "quantsystem/indicators/indicator_base.h"

namespace quantsystem {
namespace indicators {
/**
 * Represents an indicator that acts on a rolling window of data.
 * @ingroup IndicatorsLayer
 */
template <typename T>
class WindowIndicator : public IndicatorBase<T> {
 public:
  /**
   * Gets a flag indicating when this indicator is ready and fully initialized.
   */
  virtual bool is_ready() const {
    return window_.is_ready();
  }

  /**
   * Resets this indicator to its initial state.
   */
  virtual void Reset() {
    IndicatorBase<T>::Reset();
    window_.Reset();
  }

  /**
   * Gets the period of this window indicator.
   */
  int period() const {
    return window_.size();
  }

 protected:
  /**
   * Initializes a new instance of the WindowIndicator class.
   * @param name The name of this indicator.
   * @param period The number of data points to hold in the window.
   */
  WindowIndicator(const string& name, int period)
      : IndicatorBase<T>(name),
      window_(RollingWindow<T>(period)) {
}

  /**
   * Computes the next value of this indicator from the given state.
   * @param input The input given to the indicator.
   * @return A new value for this indicator.
   */
  virtual double ComputeNextValue(const T& input) {
    window_.Add(input);
    return ComputeNextValue(&window_, input);
  }

  /**
   * Computes the next value for this indicator from the given state.
   * @param window[out] The window of data held in this indicator
   * @param input The input value to this indicator on this time step
   * @return A new value for this indicator
   */
  virtual double ComputeNextValue(
      IReadOnlyWindow<T>* window, const T& input) = 0;

 private:
  // a window of data over a certain look back period
  RollingWindow<T> window_;
};

}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_WINDOW_INDICATOR_H_
