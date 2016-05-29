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
 * @defgroup Engine - Entry Point
 *
 * The quant engine loads new tasks, create the algorithms and threads,
 * and sends them to Algorithm Manager to be executed.
 */
#ifndef QUANTSYSTEM_COMMON_TRADEBAR_CONSOLIDATOR_H_
#define QUANTSYSTEM_COMMON_TRADEBAR_CONSOLIDATOR_H_

#include "quantsystem/common/global.h"
#include "quantsystem/common/base/scoped_ptr.h"
#include "quantsystem/common/time/time_span.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/data/base_data.h"
#include "quantsystem/common/data/market/tradebar.h"
#include "quantsystem/common/data/consolidators/data_consolidator.h"

namespace quantsystem {
namespace data {
using market::TradeBar;
namespace consolidators {
/**
 * A data consolidator that can make bigger bars from smaller ones over
 * a given time span or a count of pieces of data, for example, if you
 * subscribe to minute data but want to have a 15 minute bar.
 *
 * @ingroup CommonBaseData
 */
class TradeBarConsolidator : public DataConsolidator {
 public:
  /**
   * Constructs a consolidator to produce a new 'TradeBar'
   * represeting the period.
   *
   * @param period The minimum span of time before emitting a consolidated bar
   */
  explicit TradeBarConsolidator(const TimeSpan& period);

  /**
   * Constructs a consolidator to produce a new 'TradeBar'
   * repereseting the last count pieces of data.
   *
   * @param max_count The number of pieces to accept before
   * emiting a consolidated bar
   */
  explicit TradeBarConsolidator(int max_count);

  /**
   * Constructs a consolidator to produce a new 'TradeBar' representing
   * the last count pieces of data or the period, whichever comes first.
   *
   * @param max_count The number of pieces to accept
   * before emiting a consolidated bar
   * @param period The minimum span of time before emitting a consolidated bar
   */
  TradeBarConsolidator(int max_count, const TimeSpan& period);

  /**
   * Standard destructor.
   */
  virtual ~TradeBarConsolidator();

  /**
   * Updates this consolidator with the specified data. This method is
   * responsible for raising the DataConsolidated event.
   *
   * @param data The new data for the consolidator
   */
  virtual void Update(BaseData* data);

  /**
   * Constructs a new TradeBarConsolidator for the desired resolution.
   *
   * @param resolution The resolution desired
   * @return A consolidator that produces data on the resolution interval
   */
  static TradeBarConsolidator* FromResolution(Resolution::Enum resolution);

 protected:
  /**
   * Aggregates the new data into the 'working_bar', The 'working_bar' will be
   * null following the event firing.
   *
   * @param data The new data
   * @param[out] working_bar The bar we're building
   */
  virtual void AggregateBar(const TradeBar& data, TradeBar* working_bar);

  /**
   * Event invocator for the DataConsolidated event. This should be invoked
   * by derived classes when they have consolidated  a new piece of data.
   *
   * @param consolidated The newly consolidated data
   */
  virtual void OnDataConsolidated(BaseData* consolidated);

 private:
  // The minimum timespan between creating new bars
  // is_valid: false if unknown
  TimeSpan period_;
  // The number of data updates between creating new bars
  // <0 if unknown
  int max_count_;
  // The number of pieces of data we've acuumulated since our last emit
  int current_count_;
  // The working bar used for aggregating the data
  // Can be NULL
  scoped_ptr<TradeBar> working_bar_;
  // The last time we emitted a consolidated bar
  // is_valid: false if unknown
  DateTime last_emit_;
};

}  // namespace consolidators
}  // namespace data
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_TRADEBAR_CONSOLIDATOR_H_
