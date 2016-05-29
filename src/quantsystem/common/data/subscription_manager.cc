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
#include "quantsystem/common/data/subscription_manager.h"
#include "quantsystem/common/strings/case.h"

namespace quantsystem {
namespace data {
SubscriptionManager::SubscriptionManager() {
}

SubscriptionManager::~SubscriptionManager() {
  for (SubscriptionsList::const_iterator it = subscriptions.begin();
       it != subscriptions.end(); ++it) {
    delete *it;
  }
}

void SubscriptionManager::Add(const string& data_type_name,
                              const SecurityType::Enum security,
                              const StringPiece& symbol,
                              Resolution::Enum resolution,
                              const bool fill_data_forward,
                              const bool extended_market_hours) {
  string symbol_upper = symbol.as_string();
  UpperString(&symbol_upper);
  SubscriptionDataConfig *newConfig =
      new SubscriptionDataConfig(data_type_name, security,
                                 symbol_upper, resolution,
                                 fill_data_forward, extended_market_hours);
  subscriptions.push_back(newConfig);
}

void SubscriptionManager::AddConsolidator(const StringPiece& symbol,
                                          DataConsolidator* consolidator
                                          ) {
  string symbol_upper = symbol.as_string();
  UpperString(&symbol_upper);
  for (SubscriptionsList::const_iterator it = subscriptions.begin();
       it != subscriptions.end(); ++it) {
    if ((*it)->symbol == symbol_upper) {
      (*it)->consolidators.push_back(consolidator);
    }
  }
  LOG(FATAL) << "Please subscribe to this symbol before " <<
      "adding a consolidator for it. Symbol: " << symbol_upper;
}


SubscriptionDataConfig* SubscriptionManager::GetSetting(
    const StringPiece& symbol) const {
  string symbol_upper = symbol.as_string();
  UpperString(&symbol_upper);
  for (SubscriptionsList::const_iterator it = subscriptions.begin();
       it != subscriptions.end(); ++it) {
    if ((*it)->symbol == symbol_upper) {
      return *it;
    }
  }
  return NULL;
}

}  // namespace data
}  // namespace quantsystem
