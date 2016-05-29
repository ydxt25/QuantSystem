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

#include <string>
using std::to_string;
#include "quantsystem/indicators/simple_moving_average.h"
namespace quantsystem {
namespace indicators {
SimpleMovingAverage::SimpleMovingAverage(const string&name, int period)
    : WindowIndicator<IndicatorDataPoint>(name, period),
      sum_(0) {
}

SimpleMovingAverage::SimpleMovingAverage(int period)
    : WindowIndicator<IndicatorDataPoint>("SMA" + to_string(period), period),
      sum_(0) {
}

double SimpleMovingAverage::ComputeNextValue(
    IReadOnlyWindow<IndicatorDataPoint>* window,
    const IndicatorDataPoint& input) {
  sum_ += input.value();
  if (window->is_ready()) {
    sum_ -= window->most_recently_removed().value();
  }
  return sum_ / window->count();
}

}  // namespace indicators
}  // namespace quantsystem
