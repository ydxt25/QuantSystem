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
#include "quantsystem/indicators/average_true_range.h"
#include "quantsystem/indicators/moving_average_type_extensions.h"
namespace quantsystem {
namespace indicators {
AverageTrueRange::AverageTrueRange(const string& name, int period,
                                   MovingAverageType moving_average_type)
    : TradeBarIndicator(name) {
  string tmp_name = name + "_" + MovingAverageTypeToString(moving_average_type);
  smoother_.reset(ToIndicator(moving_average_type, tmp_name, period));
}

AverageTrueRange::AverageTrueRange(int period,
                                   MovingAverageType moving_average_type)
    : TradeBarIndicator("ATR" + to_string(period)) {
  string tmp_name = "ATR" + to_string(period) + "_" +
      MovingAverageTypeToString(moving_average_type);
  smoother_.reset(ToIndicator(moving_average_type, tmp_name, period));
}

double AverageTrueRange::ComputeTrueRange(
    const TradeBar* previous,
    const TradeBar* current) {
}

double AverageTrueRange::ComputeNextValue(const TradeBar& input) {
}

}  // namespace indicators
}  // namespace quantsystem
