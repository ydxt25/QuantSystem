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

#include <glog/logging.h>
#include "quantsystem/indicators/moving_average_type_extensions.h"
#include "quantsystem/indicators/simple_moving_average.h"
#include "quantsystem/indicators/exponential_indicator.h"
namespace quantsystem {
namespace indicators {
IndicatorBase<IndicatorDataPoint>* ToIndicator(
    MovingAverageType moving_average_type,
    int period) {
  switch (moving_average_type) {
    case kSimple:
      return new SimpleMovingAverage(period);
    case kExponential:
      return new ExponentialMovingAverage(period);
    case kWilders:
      return new ExponentialMovingAverage(period, 1.0 / period);
    default:
      LOG(FATAL) << "Input problem? moving average type = "
                 << moving_average_type;
      return NULL;
  }
}

IndicatorBase<IndicatorDataPoint>* ToIndicator(
    MovingAverageType moving_average_type,
    const string& name,
    int period) {
  switch (moving_average_type) {
    case kSimple:
      return new SimpleMovingAverage(name, period);
    case kExponential:
      return new ExponentialMovingAverage(name, period);
    case kWilders:
      return new ExponentialMovingAverage(name, period, 1.0 / period);
    default:
      LOG(FATAL) << "Input problem? moving average type = "
                 << moving_average_type;
      return NULL;
  }
}
}  // namespace indicators
}  // namespace quantsystem
