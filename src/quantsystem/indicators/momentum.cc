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
#include "quantsystem/indicators/momentum.h"
namespace quantsystem {
namespace indicators {
Momentum::Momentum(int period)
    : WindowIndicator("MOM" + to_string(period), period) {
}

Momentum::Momentum(const string& name, int period)
    : WindowIndicator(name, period) {
}

double Momentum::ComputeNextValue(IReadOnlyWindow<IndicatorDataPoint>* window,
                                  IndicatorDataPoint input) {
  if (!window->is_ready()) {
    // keep returning the delta from the first item put in there to init
    return input.value() - (*window)[window->count() - 1].value();
  }
  return input.value() - window->most_recently_removed().value();
}
}  // namespace indicators
}  // namespace quantsystem
