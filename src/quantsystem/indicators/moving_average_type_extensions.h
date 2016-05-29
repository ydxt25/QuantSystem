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

#ifndef QUANTSYSTEM_INDICATORS_MOVING_AVERAGE_TYPE_EXTENSIONS_H_
#define QUANTSYSTEM_INDICATORS_MOVING_AVERAGE_TYPE_EXTENSIONS_H_

#include <string>
using std::string;
#include "quantsystem/indicators/moving_average_type.h"
#include "quantsystem/indicators/indicator_base.h"
#include "quantsystem/indicators/indicator_data_point.h"
namespace quantsystem {
namespace indicators {
/**
 * Provides extension methods for the MovingAverageType enumeration.
 * @ingroup IndicatorsLayer
 */
/**
 * Creates a new indicator from the specified MovingAverageType.
 * So if MovingAverageType.Simple is specified, then a
 * new SimpleMovingAverage will be returned.
 * @param moving_average_type The type of averaging indicator to create
 * @param period The smoothing period
 * @return A new indicator that matches the MovingAverageType
 */
IndicatorBase<IndicatorDataPoint>* ToIndicator(
    MovingAverageType moving_average_type,
    int period);

/**
 * Creates a new indicator from the specified MovingAverageType.
 * So if MovingAverageType.Simple is specified, then a
 * new SimpleMovingAverage will be returned.
 * @param moving_average_type The type of averaging indicator to create
 * @param name The name of the new indicator
 * @param period The smoothing period
 * @return A new indicator that matches the MovingAverageType
 */
IndicatorBase<IndicatorDataPoint>* ToIndicator(
    MovingAverageType moving_average_type,
    const string& name,
    int period);
}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_MOVING_AVERAGE_TYPE_EXTENSIONS_H_
