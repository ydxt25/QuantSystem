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

#ifndef QUANTSYSTEM_INDICATORS_AVERAGE_TRUE_RANGE_H_
#define QUANTSYSTEM_INDICATORS_AVERAGE_TRUE_RANGE_H_

#include <string>
using std::string;
#include "quantsystem/common/base/scoped_ptr.h"
#include "quantsystem/common/data/market/tradebar.h"
#include "quantsystem/indicators/tradebar_indicator.h"
#include "quantsystem/indicators/indicator_data_point.h"
#include "quantsystem/indicators/moving_average_type.h"
#include "quantsystem/indicators/indicator_base.h"
namespace quantsystem {
using data::market::TradeBar;
namespace indicators {
/**
 * The AverageTrueRange indicator is a measure of volatility introduced
 * by Welles Wilder in his book: New Concepts in Technical Trading Systems.
 * This indicator computes the TrueRange and then smoothes the TrueRange
 * over a given period.
 *
 * TrueRange is defined as the maximum of the following:
 *  + High - Low
 *  + ABS(High - PreviousClose)
 *  + ABS(Low  - PreviousClose)
 * @ingroup IndicatorsLayer
 */
class AverageTrueRange : public TradeBarIndicator {
 public:
  /**
   * Creates a new AverageTrueRange indicator using the specified period
   * and moving average type.
   * @param name The name of this indicator
   * @param period The smoothing period used to smooth the true range values
   * @param moving_average_type The type of smoothing used to smooth
   * the true range values
   */
  AverageTrueRange(const string& name, int period,
                   MovingAverageType moving_average_type = kWilders);

  /**
   * Creates a new AverageTrueRange indicator using the
   * specified period and moving average type.
   * @param period The smoothing period used to smooth the true range values
   * @param moving_average_type The type of smoothing used to smooth
   * the true range values
   */
  AverageTrueRange(int period,
                   MovingAverageType moving_average_type = kWilders);

  /**
   * Computes the TrueRange from the current and previous trade bars.
   *
   * TrueRange is defined as the maximum of the following:
   *  + High - Low
   *  + ABS(High - PreviousClose)
   *  + ABS(Low  - PreviousClose)
   * @param previous The previous trade bar
   * @param current The current trade bar
   * @return The trune range value
   */
  static double ComputeTrueRange(const TradeBar* previous,
                                 const TradeBar* current);

  /**
   * Gets a flag indicating when this indicator is ready and fully initialized.
   */
  virtual bool is_ready() {
    return smoother_->is_ready();
  }

 protected:
  /**
   * Computes the next value of this indicator from the given state.
   * @param input The input given to the indicator.
   * @return A new value for this indicator.
   */
  virtual double ComputeNextValue(const TradeBar& input);

 private:
  // The input we received last time, this is used in ComputeTrueRange
  TradeBar previous_input_;
  // Indicate having the previous input
  bool have_previous_input_ : 1;
  // This indicator is used to smooth the TrueRange computation
  scoped_ptr<IndicatorBase<IndicatorDataPoint> > smoother_;
};

}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_AVERAGE_TRUE_RANGE_H_
