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

#ifndef QUANTSYSTEM_INDICATORS_RELATIVE_STRENGTH_INDEX_H_
#define QUANTSYSTEM_INDICATORS_RELATIVE_STRENGTH_INDEX_H_

#include <string>
using std::string;
#include "quantsystem/common/base/scoped_ptr.h"
#include "quantsystem/indicators/indicator.h"
#include "quantsystem/indicators/indicator_base.h"
#include "quantsystem/indicators/indicator_data_point.h"
#include "quantsystem/indicators/moving_average_type.h"
namespace quantsystem {
namespace indicators {
/**
 * Represents the  Relative Strength Index (RSI) developed by K. Welles Wilder.
 * You can optionally specified a different moving average type to be used
 * in the computation.
 * @ingroup IndicatorsLayer
 */
class RelativeStrengthIndex : public Indicator {
 public:
    typedef IndicatorBase<IndicatorDataPoint> IndicatorType;
  /**
   * Initializes a new instance of the RelativeStrengthIndex class
   * with the specified name and period.
   * @param period The period used for up and down days
   * @param moving_average_type The type of moving average to be used
   * for computing the average gain/loss values
   */
  RelativeStrengthIndex(int period,
                        MovingAverageType moving_average_type = kWilders);

  /**
   * Initializes a new instance of the RelativeStrengthIndex class
   * with the specified name and period.
   * @param name The name of this indicator
   * @param period The period used for up and down days
   * @param moving_average_type The type of moving average to be used
   * for computing the average gain/loss values
   */
  RelativeStrengthIndex(const string& name,
                        int period,
                        MovingAverageType moving_average_type = kWilders);

  /**
   * Gets a flag indicating when this indicator is ready and fully initialized.
   */
  virtual bool is_ready() const {
    return average_gain_->is_ready() && average_loss_->is_ready();
  }

  MovingAverageType moving_average_type() const {
    return moving_average_type_;
  }

  IndicatorType* average_loss() const {
    return average_loss_.get();
  }

  IndicatorType* average_gain() const {
    return average_gain_.get();
  }

  /**
   * Resets this indicator to its initial state.
   */
  virtual void Reset();

 protected:
  /**
   * Computes the next value of this indicator from the given state.
   * @param input The input given to the indicator.
   * @return A new value for this indicator.
   */
  virtual double ComputeNextValue(const IndicatorDataPoint& input);

 private:
  IndicatorDataPoint previous_input_;
  // The type of indicator used to compute AverageGain and AverageLoss
  MovingAverageType moving_average_type_;
  scoped_ptr<IndicatorType> average_loss_;
  scoped_ptr<IndicatorType> average_gain_;

  void set_moving_average_type(MovingAverageType type) {
    moving_average_type_ = type;
  }

  void set_average_loss(IndicatorType* average_loss) {
    average_loss_.reset(average_loss);
  }

  void set_average_gain(IndicatorType* average_gain) {
    average_gain_.reset(average_gain);
  }

  void Init(const string& name, int period,
            MovingAverageType moving_average_type);
};

}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_RELATIVE_STRENGTH_INDEX_H_
