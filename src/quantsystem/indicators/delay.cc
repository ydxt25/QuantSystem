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
#include "quantsystem/indicators/delay.h"
namespace quantsystem {
namespace indicators {
Delay::Delay(int period)
    : WindowIndicator("DELAY" + to_string(period), period) {
}

Delay::Delay(const string& name, int period)
    : WindowIndicator(name, period) {
}

double Delay::ComputeNextValue(IReadOnlyWindow<IndicatorDataPoint>* window,
                               IndicatorDataPoint input) {
  if (!window->is_ready()) {
    // Grab the initial value until we're ready
    return (*window)[window->count() - 1].value();
  }
  return (window->most_recently_removed()).value();
}
}  // namespace indicators
}  // namespace quantsystem
