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
#include "quantsystem/indicators/moving_average_converagence_divergence.h"
#include "quantsystem/indicators/moving_average_type_extensions.h"
namespace quantsystem {
namespace indicators {
MovingAverageConvergenceDivergence::MovingAverageConvergenceDivergence(
    int fast_period, int slow_period,
    int signal_period,
    MovingAverageType type)
    : Indicator("MACS(" + to_string(fast_period) + "," +
                to_string(slow_period) + ")") {
  Init("MACS(" + to_string(fast_period) + "," +
       to_string(slow_period) + ")",
       fast_period, slow_period, signal_period, type);
}

MovingAverageConvergenceDivergence::MovingAverageConvergenceDivergence(
    const string& name,
    int fast_period, int slow_period,
    int signal_period,
    MovingAverageType type)
    : Indicator(name) {
  Init(name, fast_period, slow_period, signal_period, type);
}

void MovingAverageConvergenceDivergence::Init(
    const string& name,
    int fast_period, int slow_period,
    int signal_period,
    MovingAverageType type) {
  fast_.reset(ToIndicator(type, name + "_Fast", fast_period));
  slow_.reset(ToIndicator(type, name + "_Slow", slow_period));
  signal_.reset(ToIndicator(type, name + "_Signal", signal_period));
}

void MovingAverageConvergenceDivergence::Reset() {
  fast_->Reset();
  slow_->Reset();
  signal_->Reset();
  Indicator::Reset();
}

double MovingAverageConvergenceDivergence::ComputeNextValue(
    const IndicatorDataPoint& input) {
  fast_->Update(input);
  slow_->Update(input);
  int macd = fast_->value() - slow_->value();
  if (fast_->is_ready() && slow_->is_ready()) {
    IndicatorDataPoint new_input(input.time(), macd);
    signal_->Update(new_input);
  }
  return macd;
}
}  // namespace indicators
}  // namespace quantsystem
