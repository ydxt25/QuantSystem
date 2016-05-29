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

#ifndef QUANTSYSTEM_INDICATORS_MOVING_AVERAGE_CONVERAGENCE_DIVERGENCE_H_
#define QUANTSYSTEM_INDICATORS_MOVING_AVERAGE_CONVERAGENCE_DIVERGENCE_H_

#include <string>
using std::string;
#include "quantsystem/common/base/scoped_ptr.h"
#include "quantsystem/indicators/indicator.h"
#include "quantsystem/indicators/indicator_data_point.h"
#include "quantsystem/indicators/moving_average_type.h"
#include "quantsystem/indicators/indicator_base.h"
namespace quantsystem {
namespace indicators {
/**
 * This indicator creates two moving averages defined on a base indicator
 * and produces the difference between the fast and slow averages.
 * @ingroup IndicatorsLayer
 */
class MovingAverageConvergenceDivergence : public Indicator {
 public:
  typedef IndicatorBase<IndicatorDataPoint> IndicatorAverageType;
  /**
   * Creates a new MACD with the specified parameters.
   * @param fast_period The fast moving average period
   * @param slow_period The slow moving average period
   * @param signal_period The signal period
   * @param type The type of moving average to use
   */
  MovingAverageConvergenceDivergence(int fast_period, int slow_period,
                                     int signal_period,
                                     MovingAverageType type = kSimple);

  /**
   * Creates a new MACD with the specified parameters.
   * @param name The name of this indicator
   * @param fast_period The fast moving average period
   * @param slow_period The slow moving average period
   * @param signal_period The signal period
   * @param type The type of moving average to use
   */
  MovingAverageConvergenceDivergence(const string& name,
                                     int fast_period, int slow_period,
                                     int signal_period,
                                     MovingAverageType type = kSimple);

  /**
   * Gets a flag indicating when this indicator is ready and fully initialized.
   */
  virtual bool is_ready() const {
    return signal_->is_ready();
  }

  /**
   * Resets this indicator to its initial state.
   */
  virtual void Reset();

  IndicatorAverageType* fast() const { return fast_.get();}

  IndicatorAverageType* slow() const { return slow_.get(); }

  IndicatorAverageType* signal() const { return signal_.get(); }

 protected:
  /**
   * Computes the next value of this indicator from the given state.
   * @param input The input given to the indicator.
   * @return A new value for this indicator.
   */
  virtual double ComputeNextValue(const IndicatorDataPoint& input);

 private:
  // The fast average indicator
  scoped_ptr<IndicatorAverageType> fast_;
  // The slow average indicator
  scoped_ptr<IndicatorAverageType> slow_;
  // The signal of the MACD
  scoped_ptr<IndicatorAverageType> signal_;

  void set_fast(IndicatorAverageType* fast) {
    fast_.reset(fast);
  }

  void set_slow(IndicatorAverageType* slow) {
    slow_.reset(slow);
  }

  void set_signal(IndicatorAverageType* signal) {
    signal_.reset(signal);
  }

  void Init(const string& name, int fast_period, int slow_period,
            int signal_period,
            MovingAverageType type);
};

}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_MOVING_AVERAGE_CONVERAGENCE_DIVERGENCE_H_
