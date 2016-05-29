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

#ifndef QUANTSYSTEM_COMMON_SEQUENTIAL_CONSOLIDATOR_H_
#define QUANTSYSTEM_COMMON_SEQUENTIAL_CONSOLIDATOR_H_

#include "quantsystem/common/base/scoped_ptr.h"
#include "quantsystem/common/data/consolidators/data_consolidator.h"

namespace quantsystem {
namespace data {
namespace consolidators {
/**
 * This consolidator wires up the event s on its First and Second consolidators
 * such the data flows from the First to Second consolidator. Its output comes
 * from the Second.
 */
class SequentialConsolidator : public DataConsolidator {
 public:
  /**
   * Standard constructor.
   * Create a new consolidator that will pump data through the first, and then
   * the output of the first into the second. This enables 'wrapping' or
   * 'composing' of consolidators.
   *
   * @param first The first consolidator to recceive data.
   * @param second The consolidator to receive first's output.
   */
  SequentialConsolidator(DataConsolidator *first,
                         DataConsolidator *second);

  /**
   * Standard destructor.
   */
  virtual ~SequentialConsolidator();

  /**
   * Get the first consolidator to receive data
   *
   * @return The first consolidator
   */
  DataConsolidator* first() const { return first_.get(); }

  /**
   * Get the second consolidator that ends up receiving data produced
   * by the first
   *
   * @return The second consolidator
   */
  DataConsolidator* second() const { return second_.get(); }

  /**
   * Get the most recently consolidated piece of data. This will be null if this
   * consolidatorhas not produced any data yet.
   * For a SequentialConsolidator, this is the output from the 'Second'
   * consolidator
   *
   * @return The consolidated piece of data
   */
  BaseData* conolidated() const { return second_->consolidated(); }

  /**
   * Updates this consolidator with the specified data.
   *
   * @param data The new data for the consolidator
   */
  virtual void Update(BaseData* data);

 protected:
  virtual void OnDataConsolidated(BaseData* consolidated);

 private:
  scoped_ptr<DataConsolidator> first_;
  scoped_ptr<DataConsolidator> second_;

  /**
   * Set the first consolidator to receive data
   *
   * @param first The first consolidator
   */
  void set_first(DataConsolidator* first) { first_.reset(first); }

  /**
   * Set the second consolidator that ends up receiving data produced
   * by the first
   *
   * @param second The second consolidator
   */
  void set_second(DataConsolidator *second) { second_.reset(second); }
};
}  // namespace consolidators
}  // namespace data
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SEQUENTIAL_CONSOLIDATOR_H_
