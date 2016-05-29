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
#include "quantsystem/common/util/charting.h"

namespace quantsystem {
Series::Series() : series_type(SeriesType::kLine),
                   update_position_(0) {
}

Series::Series(const string& in_name, SeriesType::Enum type)
    : update_position_(0) {
  name = in_name;
  series_type = type;
}

Series::~Series() {
}

void Series::AddPoint(const DateTime& time, double value, bool live_mode) {
  if (values.size() < 4000 || live_mode) {
    values.push_back(ChartPoint(time, value));
  }
}

Series Series::GetUpdates() {
  Series copy = Series(name, series_type);
  // Add the updates since the last
  for (int i = update_position_; i < values.size(); ++i) {
    copy.values.push_back(values[i]);
  }
  // Shuffle the update point to now
  update_position_ = values.size();
  return copy;
}

Chart::Chart() : chart_type(ChartType::kOverlay) {
}

Chart::Chart(const string& in_name, ChartType::Enum type) {
  name = in_name;
  chart_type = type;
}

Chart::~Chart() {
}

void Chart::AddSeries(const Series& series) {
  SeriesMap::iterator found = series_map.find(series.name);
  if (found == series_map.end()) {
    series_map.insert(make_pair(series.name, series));
  }
}

Chart Chart::GetUpdates() {
  Chart copy = Chart(name, chart_type);
  for (SeriesMap::const_iterator it = series_map.begin();
       it != series_map.end(); ++it) {
    copy.AddSeries(it->second);
  }
  return copy;
}
}  // namespace quantsystem
