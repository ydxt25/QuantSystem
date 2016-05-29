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

#include "quantsystem/engine/stream_store.h"
namespace quantsystem {
namespace engine {
StreamStore::StreamStore(const SubscriptionDataConfig* config) {
}

void StreamStore::Update(const BaseData* data) {
}

void StreamStore::Update(const Tick* tick) {
}

void StreamStore::TriggerArchive(bool fill_forward, bool is_qs_data) {
}

DateTime StreamStore::ComputeBarStartTime(const BaseData* data) {
}

}  // namespace engine
}  // namespace quantsystem
