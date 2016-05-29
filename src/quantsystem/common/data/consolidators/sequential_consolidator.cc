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

#include "quantsystem/common/data/consolidators/sequential_consolidator.h"

namespace quantsystem {
namespace data {
namespace consolidators {

SequentialConsolidator::SequentialConsolidator(
    DataConsolidator *first,
    DataConsolidator *second)
    : first_(first), second_(second) {
  // wire up the second one to get data from the first
  first_->DataConsolidated.Bind<DataConsolidator,
                               &DataConsolidator::Update>(second);
  // wire up the second one's events to also fire this
  // consolidator's event so consumers can attach
  second_->DataConsolidated.Bind<DataConsolidator,
                                &DataConsolidator::Update>(this);
}

SequentialConsolidator::~SequentialConsolidator() {
}

void SequentialConsolidator::Update(BaseData* data) {
  first_->Update(data);
}

void SequentialConsolidator::OnDataConsolidated(BaseData* consolidated) {
  DataConsolidated(consolidated);
}
}  // namespace consolidators
}  // namespace data
}  // namespace quantsystem
