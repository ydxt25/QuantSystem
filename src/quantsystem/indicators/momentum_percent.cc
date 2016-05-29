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
#include "quantsystem/indicators/momentum_percent.h"
namespace quantsystem {
namespace indicators {
MomentumPercent::MomentumPercent(int period)
    : Momentum("MOM%" + to_string(period), period) {
  average_.reset(new SimpleMovingAverage(period));
}

MomentumPercent::MomentumPercent(const string& name, int period)
    : Momentum(name, period) {
  average_.reset(new SimpleMovingAverage(period));
}

double MomentumPercent::ComputeNextValue(
    IReadOnlyWindow<IndicatorDataPoint>* window,
    IndicatorDataPoint input) {
  average_->Update(input);
  double absolute_change = Momentum::ComputeNextValue(window, input);
  if (average_->value() == 0) {
    return 0;
  }
  return absolute_change / average_->value();
}
}  // namespace indicators
}  // namespace quantsystem
