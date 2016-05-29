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

#include <functional>
using std::hash;
#include "quantsystem/indicators/indicator_data_point.h"
namespace quantsystem {
namespace indicators {
IndicatorDataPoint::IndicatorDataPoint(const DateTime& time, double value) {
  set_time(time);
  set_value(value);
}

IndicatorDataPoint::~IndicatorDataPoint() {
}

bool IndicatorDataPoint::Equals(const IndicatorDataPoint& other) const {
  return (other.time() == this->time()) && (other.value() == this->value());
}

int IndicatorDataPoint::GetHashCode() const {
  hash<double> hash_double_fn;
  hash<string> hash_string_fn;
  return (hash_double_fn(value()) * 397) ^ hash_string_fn(time().ToString());
}
}  // namespace indicators
}  // namespace quantsystem
