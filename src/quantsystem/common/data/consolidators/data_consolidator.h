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

#ifndef QUANTSYSTEM_COMMON_DATA_CONSOLIDATOR_H_
#define QUANTSYSTEM_COMMON_DATA_CONSOLIDATOR_H_

#include "quantsystem/common/base/event.h"
#include "quantsystem/common/base/scoped_ptr.h"
#include "quantsystem/common/data/base_data.h"

namespace quantsystem {
namespace data {
class BaseData;
namespace consolidators {
/**
 * Represents a type that consumes BaseData instances
 * and fires an event with consolidated and/or aggregated data.
 * @ingroup CommonBaseData
 */
class DataConsolidator {
 public:
  typedef Delegate<BaseData*> DataConsolidatedHandler;
  //  Event handler that fires when a new piece of data is produced.
  DataConsolidatedHandler DataConsolidated;

  /**
   * Standard constructor.
   */
  DataConsolidator();

  /**
   * Standard destructor.
   */
  virtual ~DataConsolidator();

  /**
   * Update this consolidator with the specified data.
   *
   * This method is responsible for raising the DataConsolidated event.
   * @param data The new data for the consolidator.
   */
  virtual void Update(BaseData* data) = 0;

  /**
   * Get the most recently consolidated piece of data.
   * This will be null if this consolidator has not produced any data yet.
   *
   * @return The consolidated piece of data
   */
  BaseData* consolidated() const { return consolidated_; }

 protected:
  /*
   * Event invocator for the DataConsolidated event.
   *
   * This should be invoked by derived classes when they have
   * consolidated a new piece of data.
   *
   * @param consolidated The newly consolidated data
   */
  virtual void OnDataConsolidated(BaseData* consolidated);

 private:
  BaseData* consolidated_;

  /**
   * Set the most recently consolidated piece of data.
   *
   * @param consolidated The consolidated data
   */
  void set_consolidated(BaseData* consolidated) {
    consolidated_ = consolidated; }
};

}  // namespace consolidators
}  // namespace data
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_DATA_CONSOLIDATOR_H_
