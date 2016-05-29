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

#ifndef QUANTSYSTEM_ENGINE_STREAM_STORE_H_
#define QUANTSYSTEM_ENGINE_STREAM_STORE_H_

#include <string>
using std::string;
#include <vector>
using std::vector;
#include "quantsystem/common/time/time_span.h"
#include "quantsystem/common/data/market/tick.h"
#include "quantsystem/common/data/base_data.h"
#include "quantsystem/common/base/scoped_ptr.h"
#include "quantsystem/common/data/subscription_data_config.h"

namespace quantsystem {
using data::BaseData;
using data::market::Tick;
using data::SubscriptionDataConfig;
namespace engine {
/**
 * StreamStore manages the creation of data objects for live streams;
 * including managing a fillforward data stream request.
 * Streams data is pushed into update where it is appended to the data object
 * to be consolidated. Once required time has lapsed for the bar the data
 * is piped into a queue.
 * @ingroup EngineLayer
 */
class StreamStore {
 public:
  typedef vector<BaseData*> DataQueue;
  /**
   * Create a new self updating, thread safe data updater.
   * @param config Configuration for subscription
   */
  explicit StreamStore(const SubscriptionDataConfig* config);

  /**
   * For custom data streams just manually set the data,
   * it doesn't need to be compiled over time into a bar.
   * @param data New data
   */
  void Update(const BaseData* data);

  /**
   * Trade causing an update to the current tradebar object.
   * @param tick New tick data
   */
  void Update(const Tick* tick);

  /**
   * A time period has lapsed, trigger a save/queue of the current
   * value of data.
   * @param fill_forward Data stream is a fillforward type
   * @param is_qs_data The data stream is a QSManaged stream
   */
  void TriggerArchive(bool fill_forward, bool is_qs_data);

  /**
   * Symbol for the given stream.
   */
  string Symbol() const {
    return config_->symbol;
  }

  /**
   * Queue for temporary storage for generated data.
   */
  DataQueue queue() { return queue_; }
  void set_queue(DataQueue& queue) {
    queue_  = queue;
  }

  /**
   * Timespan increment for this resolution data
   */
  TimeSpan increment() const { return increment_; }

  /**
   * Public access to the data object we're dynamically generating.
   */
  BaseData* data() const { return data_.get(); }

 private:
  scoped_ptr<BaseData> data_;
  scoped_ptr<BaseData> previous_data_;
  string type_;
  SubscriptionDataConfig* config_;
  TimeSpan increment_;
  DataQueue queue_;

  /**
   * Computes the start time of the bar this data belongs in
   * @param data The Data
   */
  DateTime ComputeBarStartTime(const BaseData* data);
};

}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_STREAM_STORE_H_
