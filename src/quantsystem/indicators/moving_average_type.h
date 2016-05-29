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

#ifndef QUANTSYSTEM_INDICATORS_MOVING_AVERAGE_TYPE_H_
#define QUANTSYSTEM_INDICATORS_MOVING_AVERAGE_TYPE_H_

#include <string>
using std::string;
namespace quantsystem {
namespace indicators {
/**
 * Defines the different types of moving averages.
 * @ingroup IndicatorsLayer
 */
enum MovingAverageType {
  // An unweighted, arithmetic mean
  kSimple,
  // The standard exponential moving average,
  // using a smoothing factor of 2/(n+1)
  kExponential,
  // The standard exponential moving average, using a smoothing factor of 1/n
  kWilders
};

#define CASE(type) case type:  return string(#type).substr(1)
static string MovingAverageTypeToString(MovingAverageType type) {
  switch (type) {
    CASE(kSimple);
    CASE(kExponential);
    CASE(kWilders);
    default:
      return "";
  }
}

}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_MOVING_AVERAGE_TYPE_H_
