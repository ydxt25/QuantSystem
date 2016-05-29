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

#ifndef QUANTSYSTEM_COMMON_IDENTITY_DATA_CONSOLIDATOR_H_
#define QUANTSYSTEM_COMMON_IDENTITY_DATA_CONSOLIDATOR_H_

#include "quantsystem/common/data/base_data.h"
#include "quantsystem/common/data/consolidators/data_consolidator.h"

namespace quantsystem {
namespace data {
namespace consolidators {
/**
 * Represents a simplest DataConsolidator implementation, one that is defined
 * by a straight pass through of the data. No projection or aggregation is
 * performed.
 * @ingroup CommonBaseData
 */
class IdentityDataConsolidator : public DataConsolidator {
 public:
  /**
   * Standard constructor.
   */
  IdentityDataConsolidator();

  /**
   * Standard destructor.
   */
  virtual ~IdentityDataConsolidator();

  /**
   * Updates this consolidator with the specified data
   */
  virtual void Update(BaseData* data);
};

}  // namespace consolidators
}  // namespace data
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_IDENTITY_DATA_CONSOLIDATOR_H_
