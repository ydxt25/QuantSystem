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

#ifndef QUANTSYSTEM_COMMON_SECURITIES_SECURITY_MANAGER_H_
#define QUANTSYSTEM_COMMON_SECURITIES_SECURITY_MANAGER_H_

#include <map>
using std::map;
#include <utility>
using std::make_pair;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include "quantsystem/common/global.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/data/base_data.h"
#include "quantsystem/common/securities/security.h"

namespace quantsystem {
namespace securities {
/**
 * Enumerable security management class for grouping security objects
 * into an array and providing any common properties.
 * @ingroup CommonBaseSecurities
 */
class SecurityManager {
 public:
  typedef map<const string, Security*> ManagerMap;
  typedef map<const string, SecurityHolding*> HoldingMap;
  /**
   * Standard constructor.
   */
  SecurityManager();

  /**
   * Standard destructor.
   */
  virtual ~SecurityManager();

  /**
   * Add a new security with this symbol to the collection.
   * @param symbol Symbol for security we're adding
   * @param security Securtiy object
   */
  void Add(const string& symbol, Security* security);

  /**
   * Add a new security to the collection
   * by symbol defaulting to SecurityType.Equity
   * @param symbol Symbol for the equity we're adding
   * @param resolution Resolution of the security we're adding
   * @param fiil_data_forward Boolean flag indicating the security
   * is fillforward
   */
  void Add(const string& symbol,
           Resolution::Enum resolution = Resolution::kMinute,
           bool fill_data_forward = true) {
    Add(symbol, SecurityType::kEquity, resolution, fill_data_forward);
  }

  /**
   * Add a new security by all of its properties.
   * @param symbol Symbol of the security
   * @param type Type of security: Equity, Forex or Future
   * @param resolution Resolution of data required: currently
   * @param fiil_data_forward Return previous bar's data
   * when there is no trading in this bar
   * @param leverage Leverage for this security, default = 1
   * @param extended_market_hours Request all the data available,
   * including the extended market hours
   * @param use_quant_system_data Use quantsystem's data
   * for equity and forex requests
   */
  void Add(const string& symbol,
           SecurityType::Enum type = SecurityType::kEquity,
           Resolution::Enum resolution = Resolution::kMinute,
           bool fill_data_forward = true,
           const double& leverage = 1,
           bool extended_market_hours = false,
           bool use_quant_system_data = false);

  /**
   * Add a symbol-security by its key value pair.
   */
  void Add(const ManagerMap::value_type& pair);

  int Count() const {
    return security_manager_.size();
  }

  void Remove(const string& key);

  bool ContainsKey(const string& key) const;

  void Clear();

  const Security* Get(const string& symbol) const;
  Security* Get(const string& symbol);

  void Values(vector<const Security*>* values) const;

  void Keys(vector<string>* keys) const;

  /**
   * Indexer method for the security manager to
   * access the securities objects by their symbol.
   * @param symbol Symbol string indexer
   */
  Security* operator[](const string& symbol) {
    return Get(symbol);
  }

  /**
   * Get the number of securities that have this resolution.
   * @param resolution Search resolution value
   * @return Count of the securites
   */
  int GetResolutionCount(Resolution::Enum resolution) const;

  /**
   * Update the security properties/online functions with
   * new data/price packets.
   * @param time Time frontier
   * @param data Data packets to update
   */
  void Update(const DateTime& time, BaseData* data);

 private:
  ManagerMap security_manager_;
  HoldingMap security_holdings_;
};

}  // namespace securities
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SECURITIES_SECURITY_MANAGER_H_
