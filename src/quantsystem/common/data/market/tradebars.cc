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
#include "quantsystem/common/data/market/tradebars.h"
#include "quantsystem/common/util/stl_util.h"

namespace quantsystem {
namespace data {
namespace market {
TradeBars::TradeBars() {
  set_data_type(MarketDataType::kTradeBar);
}

TradeBars::TradeBars(const DateTime& frontier) {
  set_time(frontier);
  set_data_type(MarketDataType::kTradeBar);
}

TradeBars::~TradeBars() {
  Clear();
}

void TradeBars::Add(const string& key, TradeBar* value) {
  TradeBarMap::iterator found = trade_bars_.find(key);
  if (found != trade_bars_.end()) {
    delete found->second;
    if (!value) {
      trade_bars_.erase(found);
    }
  }
  if (value) {
    trade_bars_.insert(make_pair(key, value));
  }
}

void TradeBars::Remove(const string& key) {
  TradeBarMap::iterator found = trade_bars_.find(key);
  if (found != trade_bars_.end()) {
    delete found->second;
    trade_bars_.erase(found);
  }
}

bool TradeBars::Contains(const string& key) const {
  TradeBarMap::const_iterator found = trade_bars_.find(key);
  if (found != trade_bars_.end()) {
    return true;
  }
  return false;
}

void TradeBars::Clear() {
  STLDeleteContainerPairSecondPointers(
      trade_bars_.begin(),
      trade_bars_.end());
}

}  // namespace market
}  // namespace data
}  // namespace quantsystem
