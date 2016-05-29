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
#include "quantsystem/indicators/relative_strength_index.h"
#include "quantsystem/indicators/moving_average_type_extensions.h"

namespace quantsystem {
namespace indicators {
RelativeStrengthIndex::RelativeStrengthIndex(
    int period,
    MovingAverageType moving_average_type)
    : Indicator("RSI" + to_string(period)) {
  Init("RSI" + to_string(period), period, moving_average_type);
}

RelativeStrengthIndex::RelativeStrengthIndex(
    const string& name,
    int period,
    MovingAverageType moving_average_type)
    : Indicator(name) {
  Init(name, period, moving_average_type);
}

void RelativeStrengthIndex::Init(const string& name, int period,
                                 MovingAverageType moving_average_type) {
  moving_average_type_ = moving_average_type;
  average_gain_.reset(ToIndicator(moving_average_type, name + "Up", period));
  average_loss_.reset(ToIndicator(moving_average_type, name + "Down", period));
}

void RelativeStrengthIndex::Reset() {
  average_gain_->Reset();
  average_loss_->Reset();
  Indicator::Reset();
}

double RelativeStrengthIndex::ComputeNextValue(
    const IndicatorDataPoint& input) {
}

}  // namespace indicators
}  // namespace quantsystem
