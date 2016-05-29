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

#ifndef QUANTSYSTEM_INDICATORS_AROON_OSCILLATOR_H_
#define QUANTSYSTEM_INDICATORS_AROON_OSCILLATOR_H_

#include <string>
using std::string;
#include "quantsystem/common/base/scoped_ptr.h"
#include "quantsystem/indicators/maximum.h"
#include "quantsystem/indicators/minimum.h"
#include "quantsystem/indicators/indicator_base.h"
#include "quantsystem/common/data/market/tradebar.h"
#include "quantsystem/indicators/indicator_data_point.h"
#include "quantsystem/indicators/tradebar_indicator.h"
namespace quantsystem {
using data::market::TradeBar;
namespace indicators {
/**
 * The Aroon Oscillator is the difference between AroonUp and AroonDown.
 * The value of this indicator fluctuats between -100 and +100.
 * An upward trend bias is present when the oscillator is positive,
 * and a negative trend bias is present when the oscillator is negative.
 * AroonUp/Down values over 75 identify strong trends in their
 * respective direction.
 * @ingroup IndicatorsLayer
 */
class AroonOscillator : public TradeBarIndicator {
 public:
  typedef IndicatorBase<IndicatorDataPoint> AroonType;

  AroonType* aroon_up() const { return aroon_up_.get(); }

  AroonType* aroon_down() const { return aroon_down_.get(); }

  /**
   * Gets a flag indicating when this indicator is ready and fully initialized.
   */
  virtual bool is_ready() {
    return aroon_up_->is_ready() && aroon_down_->is_ready();
  }

  /**
   * Creates a new AroonOscillator from the specified up/down periods.
   * @param up_period The lookback period to determine the highest
   * high for the AroonDown
   * @param down_period The lookback period to determine the lowest
   * low for the AroonUp
   */
  AroonOscillator(int up_period, int down_period);

  /**
   * Creates a new AroonOscillator from the specified up/down periods.
   * @param name The name of this indicator
   * @param up_period The lookback period to determine the highest
   * high for the AroonDown
   * @param down_period The lookback period to determine the lowest
   * low for the AroonUp
   */
  AroonOscillator(const string& name, int up_period, int down_period);

  /**
   * Computes the next value of this indicator from the given state.
   * @param input The input given to the indicator.
   * @return A new value for this indicator.
   */
  virtual double ComputeNextValue(const TradeBar& input);

  /**
   * AroonUp = 100 * (period - {periods since max})/period.
   * @param up_period The AroonUp period
   * @param max[out] A Maximum indicator used to compute periods since max
   * @param input The next input data
   * @return The AroonUp value
   */
  static double ComputeAroonUp(int up_period, Maximum* max,
                               const IndicatorDataPoint& input);

  /**
   * AroonDown = 100 * (period - {periods since min})/period.
   * @param down_period The AroonDown period
   * @param min[out] A Minimum indicator used to compute periods since min
   * @param input The next input data
   * @return The AroonDown value
   */
  static double ComputeAroonDown(int down_period, Minimum* min,
                                 const IndicatorDataPoint& input);

 private:
  scoped_ptr<AroonType> aroon_up_;
  scoped_ptr<AroonType> aroon_down_;

  void set_aroon_up(AroonType* aroon_up) { aroon_up_.reset(aroon_up); }

  void set_aroon_down(AroonType* aroon_down) { aroon_down_.reset(aroon_down); }

  void InitAroonOscillator(const string& name, int up_period, int down_period);
};

}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_AROON_OSCILLATOR_H_
