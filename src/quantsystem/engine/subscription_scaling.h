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

#ifndef QUANTSYSTEM_ENGINE_SUBSCRIPTION_SCALING_H_
#define QUANTSYSTEM_ENGINE_SUBSCRIPTION_SCALING_H_

#include <map>
using std::map;
#include <string>
using std::string;
#include "quantsystem/common/time/date_time.h"
namespace quantsystem {
namespace engine {
/**
 * Subscription price adjustment class adjusts the prices of equities
 * backwards to factor in dividends and splits.
 * @ingroup EngineLayer
 */
class SubscriptionAdjustment {
 public:
  typedef map<DateTime, double> FactorTableType;
  typedef map<DateTime, string> MapTableType;
  // Base Local Data Folder
  static string data_folder;

  /**
   * Overload for base method: using a memory table, find the priceFactor.
   * @param factor_table Memeory Price Factor Table
   * @param search_date Date we're looking for price scaling factor
   * @return Double scaling factor
   */
  static double GetTimePriceFactor(const FactorTableType& factor_table,
                                   const DateTime& search_date);

  /**
   * Get the factor-table in memory.
   * @param symbol Factor symbol requested
   * @return Map with the factors over time
   */
  static void GetFactorTable(const string& symbol,
                             FactorTableType* table);

  /**
   * Get a map table for the symbol requested into memory.
   * @param symbol Factor symbol requested
   * @return Map of the symbol mappings over time
   */
  static void GetMapTable(const string& symbol,
                          MapTableType* table);

  /**
   * Get a historical mapped symbol for this requested symbol
   * at this date in time.
   * @param base_folder Location of the map files
   * @param symbol Symbol used today
   * @param search_date Date we want in the past
   * @return Mapped symbol, potentially different
   */
  static string GetMappedSymbol(const string& base_folder,
                                const string& symbol,
                                const DateTime& search_date);

  /**
   * Memory overload search method for finding the mapped symbol for this date.
   * @param symbol_map_table Memory table of symbol-dates
   * @param search_date date for symbol we need to find
   * @return Symbol on this date
   */
  static string GetMappedSymbol(const MapTableType& symbol_map_table,
                                const DateTime& search_date);
};

}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_SUBSCRIPTION_SCALING_H_
