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
#include <utility>
using std::make_pair;
#include "quantsystem/common/util/stl_util.h"
#include "quantsystem/common/strings/case.h"
#include "quantsystem/common/securities/equity/equity.h"
#include "quantsystem/common/securities/forex/forex.h"
#include "quantsystem/common/securities/security_manager.h"

namespace quantsystem {
using securities::equity::Equity;
using securities::forex::Forex;

namespace securities {
SecurityManager::SecurityManager() {
}

SecurityManager::~SecurityManager() {
  Clear();
}

void SecurityManager::Add(const string& symbol, Security* security) {
  ManagerMap::iterator found = security_manager_.find(symbol);
  if (found != security_manager_.end()) {
    delete found->second;
    security_manager_.erase(found);
  }
  security_manager_.insert(make_pair(symbol, security));;
}
void SecurityManager::Add(const string& symbol,
                           SecurityType::Enum type,
                           Resolution::Enum resolution,
                           bool fill_data_forward,
                           const double& leverage,
                           bool extended_market_hours,
                           bool use_quant_system_data) {
  string symbol_ = symbol;
  UpperString(&symbol_);
  const int kMaxTick = 30;
  const int kMaxSecond = 100;
  const int kMaxMinute = 1000;
  if (GetResolutionCount(Resolution::kTick) == kMaxTick &&
      resolution == Resolution::kTick) {
    LOG(ERROR) << "Currently only support " << kMaxTick << " tick at a time.";
    return;
  }
  if (GetResolutionCount(Resolution::kSecond) == kMaxSecond &&
      resolution == Resolution::kSecond) {
    LOG(ERROR) << "Currently only support " << kMaxSecond <<
        " second resolution at a time.";
    return;
  }
  if (GetResolutionCount(Resolution::kMinute) == kMaxMinute &&
      resolution == Resolution::kMinute) {
    LOG(ERROR) << "Currently only support " << kMaxMinute <<
        " minute resolution at a time.";
    return;
  }
  ManagerMap::iterator it = security_manager_.find(symbol_);
  if (it == security_manager_.end()) {
    LOG(INFO) << "Adding security; " << symbol_;
    switch (type) {
      case SecurityType::kEquity:
        Add(symbol_, new Equity(symbol_, resolution, fill_data_forward,
                                leverage, extended_market_hours,
                                use_quant_system_data));
        break;
      case SecurityType::kForex:
        Add(symbol_, new Forex(symbol_, resolution, fill_data_forward, leverage,
                              extended_market_hours, use_quant_system_data));
        break;
      case SecurityType::kBase:
        Add(symbol_, new Security(symbol_, SecurityType::kBase, resolution,
                                 fill_data_forward, leverage,
                                 extended_market_hours, use_quant_system_data));
        break;
    }
  } else {
    LOG(INFO) << "Changing security(" << symbol_ <<
        ") inforamtion will overwrite portfolio";
    delete it->second;
    switch (type) {
      case SecurityType::kEquity:
        security_manager_[symbol_] =
            new Equity(symbol_, resolution, fill_data_forward, leverage,
                       extended_market_hours, use_quant_system_data);
        break;
      case SecurityType::kForex:
        security_manager_[symbol_] =
            new Forex(symbol_, resolution, fill_data_forward, leverage,
                      extended_market_hours, use_quant_system_data);
        break;
      case SecurityType::kBase:
        security_manager_[symbol_] =
            new Security(symbol_, SecurityType::kBase, resolution,
                         fill_data_forward, leverage,
                         extended_market_hours, use_quant_system_data);
        break;
    }
  }
}

void SecurityManager::Add(const ManagerMap::value_type& pair) {
  security_manager_.insert(pair);
  security_holdings_.insert(HoldingMap::value_type(
      pair.first, pair.second->holdings()));
}

void SecurityManager::Remove(const string& key) {
  ManagerMap::iterator it = security_manager_.find(key);
  if (it != security_manager_.end()) {
    security_manager_.erase(it);
  }
}

bool SecurityManager::ContainsKey(const string& key) const {
  ManagerMap::const_iterator it = security_manager_.find(key);
  if (it != security_manager_.end()) {
    return true;
  }
  return false;
}

void SecurityManager::Clear() {
  STLDeleteContainerPairSecondPointers(
      security_manager_.begin(),
      security_manager_.end());
  STLDeleteContainerPairSecondPointers(
      security_holdings_.begin(),
      security_holdings_.end());
}

const Security* SecurityManager::Get(const string& symbol) const {
  ManagerMap::const_iterator it = security_manager_.find(symbol);
  if (it != security_manager_.end()) {
    return it->second;
  }
  return NULL;
}

Security* SecurityManager::Get(const string& symbol) {
  ManagerMap::iterator it = security_manager_.find(symbol);
  if (it != security_manager_.end()) {
    return it->second;
  }
  return NULL;
}

void SecurityManager::Values(vector<const Security*>* values) const {
  for (ManagerMap::const_iterator it = security_manager_.begin();
       it != security_manager_.end(); ++it) {
    values->push_back(it->second);
  }
}

void SecurityManager::Keys(vector<string>* keys) const {
  for (ManagerMap::const_iterator it = security_manager_.begin();
       it != security_manager_.end(); ++it) {
    keys->push_back(it->first);
  }
}

int SecurityManager::GetResolutionCount(Resolution::Enum resolution) const {
  int count = 0;
  for (ManagerMap::const_iterator it = security_manager_.begin();
       it != security_manager_.end(); ++it) {
    if (it->second->resolution() == resolution) {
      count++;
    }
  }
  return count;
}

void SecurityManager::Update(const DateTime& time, BaseData* data) {
  for (ManagerMap::iterator it = security_manager_.begin();
       it != security_manager_.end(); ++it) {
    if (it->second->symbol() == data->symbol()) {
      it->second->Update(time, data);
    } else {
      it->second->Update(time, NULL);
    }
  }
}
}  // namespace securities
}  // namespace quantsystem
