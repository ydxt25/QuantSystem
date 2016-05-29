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

/**
 * @defgroup CommonBaseUtil Common - Base Util Components
 *
 * The base util components of Quantsystem.
 */
#ifndef QUANTSYSTEM_COMMON_CHARTING_H_
#define QUANTSYSTEM_COMMON_CHARTING_H_

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include "quantsystem/common/base/integral_types.h"
#include "quantsystem/common/securities/security.h"
#include "quantsystem/common/time/date_time.h"

namespace quantsystem {
/**
 * Available types of charts.
 */
namespace SeriesType {
enum Enum {
  // Line plot for value types
  kLine,
  // Scatter plot for chart distinct types
  kScatter,
  // Charts
  kCandle,
  // Bar chart
  kBar
};
};  // namespace SeriesType

/**
 * Type of chart - should we draw the series as overlayed or stacked
 */
namespace ChartType {
enum Enum {
  // Overlayed stacked
  kOverlay,
  // Stacked series on top of each other
  kStacked
};
};

/**
 * Single Chart Point Value Type for QCAlgorithm.Plot();
 * @ingroup CommonBaseUtil
 */
class ChartPoint {
 public:
  // Time of this chart point
  int64 x;
  // Value of this chart point
  double y;
  ChartPoint(const DateTime& time, double value) {
    x = time.ToEpochTime();
    y = value;
  }

  explicit ChartPoint(const ChartPoint& point) {
    x = point.x;
    y = point.y;
  }
};

/**
 * Chart Series Object - Series data and properties for a chart:
 * @ingroup CommonBaseUtil
 */
class Series {
 public:
  string name;  // Name of the series
  // Values for the series plot:
  // These values are assumed to be in ascending time order
  // (first points earliest, last points latest)
  vector<ChartPoint> values;
  // Chart type for the series
  SeriesType::Enum series_type;

  /**
   * Standard constructor.
   */
  Series();

  /**
   * Construct from input values for Series
   * @param name Name of the char series
   * @param type Type of the chart series
   */
  Series(const string& in_name, SeriesType::Enum type = SeriesType::kLine);

  /**
   * Standard destructor.
   */
  virtual ~Series();

  /**
   * Add a new point to this series:
   * @param time Time of the chart point
   * @param value Value of the chart point
   * @param live_mode Bool indicate a live mode point
   */
  void AddPoint(const DateTime& time, double value, bool live_mode = false);

  /**
   * Get the updates since the last call to this function.
   * @return Updates from the series
   */
  Series GetUpdates();

 private:
  // Get the index of the last fetch update request to
  // only retrieve the "delta" of the previous request.
  int update_position_;
};

/**
 * Single Parent Chart Object for Custom Charting
 * @ingroup CommonBaseUtil
 */
class Chart {
 public:
  string name;  // Name of the Chart
  // Type of the Chart, Overlayed or Stacked.
  ChartType::Enum chart_type;
  typedef map<string, Series> SeriesMap;
  // List of Series objects for this chart
  SeriesMap series_map;

  /**
   * Standard constructor.
   */
  Chart();

  /**
   * Construct from input values for Chart
   * @param name Name of the Chart
   * @param type Type of the Chart
   */
  Chart(const string& in_name, ChartType::Enum type = ChartType::kOverlay);

  /**
   * Standard destructor.
   */
  virtual ~Chart();

  /**
   * Add a reference to this chart series.
   * @param series Chart series class object
   */
  void AddSeries(const Series& series);

  /**
   * Fetch the updates of the chart, and save the index position.
   * @return Chart object
   */
  Chart GetUpdates();
};

}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_CHARTING_H_
