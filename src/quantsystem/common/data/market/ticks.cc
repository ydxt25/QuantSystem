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

#include <utility>
using std::make_pair;
#include "quantsystem/common/data/market/ticks.h"
#include "quantsystem/common/util/stl_util.h"

namespace quantsystem {
namespace data {
namespace market {
Ticks::Ticks(const DateTime& frontier) {
  set_time(frontier);
  set_data_type(MarketDataType::kTick);
}

Ticks::~Ticks() {
  Clear();
}

void Ticks::Add(const string& key, const vector<Tick*>& value) {
  TickMap::iterator found = ticks_.find(key);
  if (found != ticks_.end()) {
    STLDeleteElements(&(found->second));
    ticks_.erase(found);
  }
  ticks_.insert(make_pair(key, value));
}

void Ticks::Add(const string& key, Tick* value) {
  ticks_[key].push_back(value);
}

void Ticks::Remove(const string& key) {
  TickMap::iterator found = ticks_.find(key);
  if (found != ticks_.end()) {
    STLDeleteElements(&(found->second));
    ticks_.erase(found);
  }
}

bool Ticks::Contains(const string& key) const {
  TickMap::const_iterator found = ticks_.find(key);
  if (found != ticks_.end()) {
    return true;
  }
  return false;
}

void Ticks::Clear() {
  TickMap::iterator it;
  for (it = ticks_.begin(); it != ticks_.end(); ++it) {
    STLDeleteElements(&(it->second));
  }
  ticks_.clear();
}
}  // namespace market
}  // namespace data
}  // namespace quantsystem
