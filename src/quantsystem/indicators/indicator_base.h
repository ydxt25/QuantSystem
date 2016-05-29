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

/**
 * @defgroup IndicatorsLayer Indicators Layer
 * All indicators are in the Indicators Layer.
 */

#ifndef QUANTSYSTEM_INDICATORS_INDICATOR_BASE_H_
#define QUANTSYSTEM_INDICATORS_INDICATOR_BASE_H_

#include <string>
using std::string;
#include "quantsystem/common/base/integral_types.h"
#include "quantsystem/indicators/indicator_data_point.h"
namespace quantsystem {
namespace indicators {
/**
 * Provides a base type for all indiators.
 * @ingroup IndicatorsLayer
 */
template <typename T>
class IndicatorBase {
 public:
  /**
   * Get a name for this indicator.
   */
  string name() const { return name_; }

  /**
   * Gets a flag indicating when this indicator is ready and fully initialized.
   */
  virtual bool is_ready() const { return is_ready_; }

  /**
   * Gets the current state of this indicator. If the state has not been updated
   * then the time on the value will equal DateTime.MinValue.
   */
  IndicatorDataPoint current() const { return current_; }

  /**
   * Return the current value of this indicate.
   */
  virtual double value() const {
    return current_.value();
  }

  /**
   * Gets the number of samples processed by this indicator.
   */
  int64 samples() const { return samples_; }

  /**
   * Updates the state of this indicator with the given value and returns true.
   * if this indicator is ready, false otherwise.
   * @param input The value to use to update this indicator
   * @return True if this indicator is ready, false otherwise
   */
  bool Update(const T& input) {
  }

  /**
   * Resets this indicator to its initial state.
   */
  virtual void Reset() {
    samples_ = 0;
  }

 protected:
  /**
   * Initializes a new instance of the Indicator class using the specified name.
   */
  explicit IndicatorBase(const string& name)
      : name_(name) {
  }

  /**
   * Computes the next value of this indicator from the given state.
   * @param input The input given to the indicator.
   * @return A new value for this indicator.
   */
  virtual double ComputeNextValue(const T& input) = 0;

 private:
  // The most recent input that was given to this indicator
  T previous_input_;
  string name_;  // Indicator name
  bool is_ready_;  // Whether this indicator is ready
  IndicatorDataPoint current_;  // Current state of this indicator
  int64 samples_;  // The number of samples processed by this indicator

  void set_name(const string& name) { name_ = name; }

  void set_current(const IndicatorDataPoint& current) { current_ = current; }

  void set_samples(int64 samples) { samples_ = samples; }
};

}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_INDICATOR_BASE_H_
