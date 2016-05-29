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

#ifndef QUANTSYSTEM_COMMON_SERIES_SAMPLER_H_
#define QUANTSYSTEM_COMMON_SERIES_SAMPLER_H_

#include <map>
using std::map;
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/time/time_span.h"
#include "quantsystem/common/base/integral_types.h"
#include "quantsystem/common/util/charting.h"

namespace quantsystem {
/**
 * A type capable of taking a chart and resampling using
 * a linear interpolation strategy.
 * @ingroup CommonBaseUtil
 */
class SeriesSampler {
 public:
  /**
   * Standard constructor.
   */
  SeriesSampler();

  /**
   * Creates a new SeriesSampler to sample Series data
   * on the specified resolution
   * @param resolution The desired sampling resolution.
   */
  explicit SeriesSampler(const TimeSpan& resolution);

  /**
   * Standard destructor.
   */
  virtual ~SeriesSampler();

  /**
   * Samples the given series.
   * @param series The series to be sampled.
   * @param start The date to start sampling,
   * if before start of data then start of data will be used.
   * @param stop The date to stop sampling, if after stop of data,
   * then stop of data will be used
   * @return The sampled series
   */
  Series Sample(const Series& series, const DateTime& start,
                const DateTime& stop);

  /**
   * Samples the given charts
   * @param charts The charts to be sampled.
   * @param start The date to start sampling.
   * @param stop The date to stop sampling
   * @return The sampled charts
   */
  map<string, Chart> SampleCharts(const map<string, Chart>& charts,
                                  const DateTime& start,
                                  const DateTime& stop);

 private:
  double seconds_;

  /**
   * Linear interpolation used for sampling.
   */
  static double Interpolate(const ChartPoint& previous,
                            const ChartPoint& current,
                            int64 target);
};

}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SERIES_SAMPLER_H_
