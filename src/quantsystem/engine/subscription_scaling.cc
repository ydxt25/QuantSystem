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
#include <vector>
using std::vector;
#include <sstream>
using std::istringstream;
#include "quantsystem/common/util/file.h"
#include "quantsystem/common/util/status.h"
#include "quantsystem/common/strings/case.h"
#include "quantsystem/common/strings/split.h"
#include "quantsystem/common/strings/numbers.h"
#include "quantsystem/common/strings/stringpiece.h"
#include "quantsystem/engine/subscription_scaling.h"
namespace quantsystem {
namespace engine {
string SubscriptionAdjustment::data_folder = "./data/";  // NOLINT

double SubscriptionAdjustment::GetTimePriceFactor(
    const FactorTableType& factor_table,
    const DateTime& search_date) {
  double factor = 1.0;
  for (FactorTableType::const_reverse_iterator rit = factor_table.rbegin();
           rit != factor_table.rend(); ++rit) {
    if (rit->first < search_date) {
      break;
    }
    factor = rit->second;
  }
  return factor;
}

void SubscriptionAdjustment::GetFactorTable(const string& symbol,
                                            FactorTableType* table) {
  string lower_symbol = symbol;
  LowerString(&lower_symbol);
  string path = data_folder+"equity/factor_files/"+lower_symbol+".csv";
  if (!File::Exists(path)) {
    LOG(ERROR) << path << " doesnot exist.";
    return;
  }
  string file_content;
  common::util::Status status = File::ReadPath(path, &file_content);
  if (!status.ok()) {
    LOG(ERROR) << "symbol's(" << symbol << ") factor file is empty";
    return;
  }
  istringstream iss(file_content);
  string line;
  while (getline(iss, line)) {
    if (line == "") {
      continue;
    }
    vector<StringPiece> parts = strings::Split(line, ",");
    double value1, value2;
    if (!safe_strtod(parts[1].as_string(), &value1) ||
        !safe_strtod(parts[2].as_string(), &value2)) {
      LOG(ERROR) << "Convert data to double fail in the file " << path;
    }
    (*table)[DateTime::ParseDate(parts[0].as_string())] =
        value1 * value2;
  }
}

void SubscriptionAdjustment::GetMapTable(const string& symbol,
                                         MapTableType* table) {
  string lower_symbol = symbol;
  LowerString(&lower_symbol);
  string path = data_folder+"equity/map_files/"+lower_symbol+".csv";
  if (!File::Exists(path)) {
    LOG(ERROR) << path << " doesnot exist.";
    return;
  }
  string file_content;
  common::util::Status status = File::ReadPath(path, &file_content);
  if (!status.ok()) {
    LOG(ERROR) << "symbol's(" << symbol << ") factor file is empty";
    return;
  }
  istringstream iss(file_content);
  string line;
  while (getline(iss, line)) {
    if (line == "") {
      continue;
    }
    vector<StringPiece> parts = strings::Split(line, ",");
    (*table)[DateTime::ParseDate(parts[0].as_string())] =
        parts[1].as_string();
  }
}

string SubscriptionAdjustment::GetMappedSymbol(
    const string& base_folder,
    const string& symbol,
    const DateTime& search_date) {
  string mapped_symbol = symbol;
  MapTableType table;
  GetMapTable(symbol, &table);
  for (MapTableType::const_iterator it = table.begin();
       it != table.end(); ++it) {
    if (it->first < search_date) {
      continue;
    }
    mapped_symbol = it->second;
    break;
  }
  return mapped_symbol;
}

string SubscriptionAdjustment::GetMappedSymbol(
    const MapTableType& symbol_map_table,
    const DateTime& search_date) {
  string mapped_symbol = "";
  for (MapTableType::const_iterator it = symbol_map_table.begin();
       it != symbol_map_table.end(); ++it) {
    if (it->first < search_date) {
      continue;
    }
    mapped_symbol = it->second;
    break;
  }
  return mapped_symbol;
}

}  // namespace engine
}  // namespace quantsystem
