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

#include "quantsystem/common/data/dynamic_data.h"
#include "quantsystem/common/strings/numbers.h"

namespace quantsystem {

namespace data {
DynamicData::DynamicData() {
}

DynamicData::~DynamicData() {
}

bool DynamicData::SetProperty(const StringPiece& name,
                              const StringPiece& value) {
  if (name == "Time") {
    set_time(DateTime(value.as_string()));
  } else if (name == "Value") {
    double d;
    safe_strtod(value.as_string(), &d);
    set_value(d);
  } else if (name == "Symbol") {
    set_symbol(value);
  }
  storage_[name.as_string()] = value.as_string();
  return true;
}

string DynamicData::GetProperty(const StringPiece& name) const {
  if (name == "Time") {
    return time().ToString();
  } else if (name == "Value") {
    return SimpleDtoa(value());
  } else if (name == "Symbol") {
    return symbol();;
  }
  StorageMap::const_iterator found_name = storage_.find(name.as_string());
  if (found_name != storage_.end()) {
    return found_name->second;
  }
  return "";
}

}  // namespace data
}  // namespace quantsystem
