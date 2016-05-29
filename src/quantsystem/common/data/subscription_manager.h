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


#ifndef QUANTSYSTEM_COMMON_DATA_SUBSCRIPTION_MANAGER_H_
#define QUANTSYSTEM_COMMON_DATA_SUBSCRIPTION_MANAGER_H_

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <typeinfo>
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/strings/stringpiece.h"
#include "quantsystem/common/global.h"
#include "quantsystem/common/data/subscription_data_config.h"
#include "quantsystem/common/data/consolidators/data_consolidator.h"
#include "quantsystem/common/data/market/tick.h"
#include "quantsystem/common/data/market/tradebar.h"

namespace quantsystem {
namespace data {
using consolidators::DataConsolidator;
using market::Tick;
using market::TradeBar;

/**
 * Subscription Management.
 * @ingroup CommonBaseData
 *
 * Enumerable Subscription Management Class.
 */
class SubscriptionManager {
 public:
  /**
   * Standard constructor.
   */
  SubscriptionManager();

  /**
   * Standard destructor.
   */
  virtual ~SubscriptionManager();

  /**
   * Get the count of assets.
   *
   * @return the count of assets.
   */
  int Count() const {
    return subscriptions.size();
  }

  /**
   * Add market data
   *
   * @param security Security Type
   * @param symbol Symbol of the asset
   * @param resolution Resolution if asset
   * @param fill_data_forward Fill in gaps with historical data
   * @param extended_market_hours Request premarket data when true
   */
  void Add(const SecurityType::Enum security, const StringPiece& symbol,
           Resolution::Enum resolution = Resolution::kMinute,
           const bool fill_data_forward = true,
           const bool extended_market_hours = false) {
    // Set the type: market data only comes in two forms --
    // ticks(trade by trade) or tradebar(time summaries)
    string data_type_name = typeid(TradeBar).name();
    if (resolution == Resolution::kTick) {
      data_type_name = typeid(Tick).name();
    }
    Add(data_type_name, security, symbol, resolution, fill_data_forward,
        extended_market_hours);
  }

  /**
   * Add market data
   *
   * @param data_typ_name Data type name
   * @param security Security Type
   * @param symbol Symbol of the asset
   * @param resolution Resolution if asset
   * @param fill_data_forward Fill in gaps with historical data
   * @param extended_market_hours Request premarket data when true
   */
  void Add(const string& data_type_name,
           const SecurityType::Enum security, const StringPiece& symbol,
           Resolution::Enum resolution = Resolution::kMinute,
           const bool fill_data_forward = true,
           const bool extended_market_hours = false);

  /**
   * Add a consolidator for the symbol.
   *
   * @param symbol Symbol of the asset
   * @param consolidator The consolidator
   */
  void AddConsolidator(const StringPiece&  symbol,
                       DataConsolidator* consolidator);

  /**
   * Get the SubscriptionDataConfig object for this ticker.
   *
   * @param symbol Symbol we're searching for in the subscriptions list
   * @return SubscriptionDataConfig Configuration Object
   */
  SubscriptionDataConfig* GetSetting(const StringPiece& symbol) const;

  typedef vector<SubscriptionDataConfig*> SubscriptionsList;
  SubscriptionsList subscriptions;  // Generic market data requested
};

}  // namespace data
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_DATA_SUBSCRIPTION_MANAGER_H_
