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

#ifndef QUANTSYSTEM_INDICATORS_SEQUENTIAL_INDICATOR_H_
#define QUANTSYSTEM_INDICATORS_SEQUENTIAL_INDICATOR_H_

#include <string>
using std::string;
#include "quantsystem/common/base/scoped_ptr.h"
#include "quantsystem/indicators/indicator_data_point.h"
#include "quantsystem/indicators/indicator_base.h"
namespace quantsystem {
namespace indicators {
/**
 * This indicator is capable of wiring up two separate indicators into
 * a single indicator such that data will be pumped into the First,
 * and the output of the First will be pumped into the Second,
 * after the First IsReady.
 * @ingroup IndicatorsLayer
 */
template <typename TFirst>
class SequentialIndicator : public IndicatorBase<TFirst> {
 public:
  typedef IndicatorBase<TFirst> FirstType;
  typedef IndicatorBase<IndicatorDataPoint> SecondType;
  /**
   * Creates a new SequentialIndicator that will pipe the output of
   * the first into the second.
   * @param name The name of this indicator
   * @param first The first indicator to receive data
   * @param second The indicator to receive the first's output data
   */
  SequentialIndicator(const string& name, const FirstType* first,
                      const SecondType* second)
      : IndicatorBase(name),
        first_(first),
        second_(second) {
  }

  /**
   * Creates a new SequentialIndicator that will pipe the output of
   * the first into the second.
   * @param first The first indicator to receive data
   * @param second The indicator to receive the first's output data
   */
  SequentialIndicator(const FirstType* first,
                      const SecondType* second)
      : IndicatorBase("SEQUENTIAL(" + first->name() + "->" +
                      second->name() + ")"),
        first_(first),
        second_(second) {
  }

  /**
   * Gets a flag indicating when this indicator is ready and fully initialized.
   */
  virtual bool is_ready() {
    return second_->is_ready() && first_->is_ready();
  }

  /**
   * Resets this indicator to its initial state.
   */
  virtual void Reset() {
    first_->Reset();
    second_->Reset();
    IndicatorBase::Reset();
  }

  FirstType* first() const { return first_; }

  SecondType* second() const { return second_; }

 protected:
  /**
   * Computes the next value of this indicator from the given state.
   * @param input The input given to the indicator.
   * @return A new value for this indicator.
   */
  virtual double ComputeNextValue(const TFirst& input) {
    first_->Updata(input);
    if (!first_->is_ready()) {
      // if the first isn't ready just send out a default value
      return 0;
    }
    second_->Update(first_->current());
    return second_->current().value();
  }

 private:
  // The first indicator to receive data
  scoped_ptr<FirstType> first_;
  // The second indicator that receives the output from the first
  // as its input data
  scoped_ptr<SecondType> second_;

  void set_first(FirstType* first) { first_ = first; }

  void set_second(SecondType* second) { second_ = second; }
};

}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_SEQUENTIAL_INDICATOR_H_
