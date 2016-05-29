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

#ifndef QUANTSYSTEM_COMMON_DATA_SUBSCRIPTION_DATA_CONFIG_H_
#define QUANTSYSTEM_COMMON_DATA_SUBSCRIPTION_DATA_CONFIG_H_

#include <vector>
using std::vector;
#include <string>
using std::string;

#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/time/time_span.h"
#include "quantsystem/common/global.h"
#include "quantsystem/common/strings/stringpiece.h"
#include "quantsystem/common/data/consolidators/data_consolidator.h"

namespace quantsystem {
namespace data {

namespace consolidators {
class DataConsolidator;
}

/**
 * Subscription data configuration.
 * @ingroup CommonBaseData
 *
 * Subscription data required including the type of data.
 */
class SubscriptionDataConfig {
 public:
  // Type name of data
  string type_name;
  // Security type of this data dsubscription
  SecurityType::Enum security;
  // Symbol of the asset
  string symbol;
  // Resolution of the asset, second minute or tick
  Resolution::Enum resolution;
  // Timespan increment between triggers of this data:
  TimeSpan increment;
  // True if wish to send old data when time gaps in data feed.
  bool fill_data_forward;
  // If send Data from between 4am - 8am (Equities Setting Only)
  bool extended_market_hours;
  // Price Scaling Factor
  double price_scale_factor;
  // Symbol Mapping: When symbols change over time
  // (e.g. CHASE-> JPM) need to update the symbol requested
  string mapped_symbol;
  // Consolidators that are registred with this subscription
  typedef vector<consolidators::DataConsolidator*> ConsolidatorsVector;
  ConsolidatorsVector consolidators;

  /**
   * Constructor for Data Subscriptions
   *
   * @param security_type SecurityType Enum Set Equity/FOREX/Futures etc
   * @param security_symbol Symbol of the asset
   * @param security_resolution Resolution of the asset
   * @param fill_forward Fill in gaps with historical data
   * @param extended_hours Equities only - send in data from 4am - 8pm
   */
  SubscriptionDataConfig(const string& object_type_name,
                         const SecurityType::Enum& security_type =
                         SecurityType::kEquity,
                         const string& security_symbol = "",
                         Resolution::Enum security_resolution = Resolution::kMinute,
                         const bool& fill_forward = true,
                         const bool& extended_hours = false);

  /**
   * Constructor for user defined source of data configuration
   *
   * @param security_symbol Symbol of the asset
   * @param source String source of the data
   */
  SubscriptionDataConfig(const string& object_type_name, const string& security_symbol, const string& source);

  /**
   * Standard destructor.
   */
  virtual ~SubscriptionDataConfig();

  /**
   * Set the price scaling factor for this subscription.
   *
   * @param new_factor Price scaling factor
   */
  void set_price_scale_factor(const double& new_factor) {
    price_scale_factor = new_factor;
  }

  /**
   * Set the mapped symbol stored here.
   *
   * @param new_symbol Mapped symbol
   */
  void set_mapped_symbol(const string& new_symbol) {
    mapped_symbol = new_symbol;
  }
};

}  // namespace data

}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_DATA_SUBSCRIPTION_DATA_CONFIG_H_
