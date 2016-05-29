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

#include "quantsystem/common/data/custom/quandl.h"
#include "quantsystem/common/strings/split.h"
#include "quantsystem/common/strings/strip.h"
#include "quantsystem/common/strings/numbers.h"

namespace quantsystem {
namespace data {
namespace custom {

Quandl::Quandl() : is_initialized_(false) {
}

Quandl::~Quandl() {
}

BaseData* Quandl::Reader(const SubscriptionDataConfig &config,
                         const StringPiece& line, const DateTime& date,
                         DataFeedEndpoint::Enum data_feed) {
  Quandl* data = new Quandl();
  data->set_symbol(config.symbol);
  vector<StringPiece> parts = strings::Split(line, ",");
  if (!is_initialized_) {
    is_initialized_ = true;
    for (int i = 0; i < parts.size(); ++i) {
      string part = parts[i].as_string();
      TrimString(&part, " ");
      data->SetProperty(part, "0");
      property_names_.push_back(part);
    }
    return data;
  }
  data->set_time(DateTime(parts[0].as_string()));
  for (int i = 1; i < parts.size(); ++i) {
    data->SetProperty(property_names_[i], parts[i]);
  }
  // there is a 'close' property, we want ot set that to 'value'
  double d;
  if (!safe_strtod(data->GetProperty("Close"), &d)) {
    LOG(ERROR) << "invalid close value=" << data->GetProperty("Close");
  }
  data->set_value(d);
  return data;
}

string Quandl::GetSource(const SubscriptionDataConfig& config,
                         const DateTime& date,
                         DataFeedEndpoint::Enum data_feed) {
  return "https://www.quandl.com/api/v1/datasets/" +
      config.symbol + ".csv?sort_order=asc&exclude_headers=false";
}

}  // namespace custom
}  // namespace data
}  // namespace quantsystem

