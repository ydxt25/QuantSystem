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
 * @defgroup QueuesLayer Queues Layer
 *
 * QueuesLayer Queues Layer.
 */

#ifndef QUANTSYSTEM_QUEUES_QUEUE_H_
#define QUANTSYSTEM_QUEUES_QUEUE_H_

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include "quantsystem/common/global.h"
#include "quantsystem/common/data/market/tick.h"
#include "quantsystem/common/packets/algorithm_node_packet.h"
#include "quantsystem/interfaces/iqueue_handler.h"

namespace quantsystem {
using data::market::Tick;
using packets::AlgorithmNodePacket;
using interfaces::IQueueHandler;
namespace queues {
/**
 * Implementation of local/desktop job request:
 * @ingroup QueuesLayer
 */
class Queue: public IQueueHandler {
 public:
  /**
   * Standard constructor.
   */
  Queue();

  /**
   * Standard destructor.
   */
  virtual ~Queue();

  /**
   * Initialize the task handler.
   */
  virtual void Initialize(bool live_mode) {
    live_mode_ = live_mode;
  }

  /**
   * Desktop/Local Get Next Task - Get task from the Algorithm folder.
   * @param[out] algorithm path
   * @return AlgorithmNodePacket to process
   */
  virtual AlgorithmNodePacket* NextJob(string* algorithm_path);

  /**
   * Desktop/Local acknowledge the task processed. Nothing to do.
   * @param job Work to do.
   */
  virtual void AcknowledgeJob(const AlgorithmNodePacket& job) {
    // Nothing to do.
  }

  /**
   * Desktop/Local doesn't support live data from this handler.
   * @return Vector of ticks since the last update
   */
  virtual vector<Tick> NextTicks();

  /**
   * Desktop/Local doesn't support live data from this handler.
   * @param symbols The symbols to be added keyed by SecurityType
   */
  virtual void Subscribe(
      const map<SecurityType::Enum, vector<string> >& symbols);

  /**
   * Desktop/Local doesn't support live data from this handler.
   * @param symbols The symbols to be removed keyed by SecurityType
   */
  virtual void Unsubscribe(
      const map<SecurityType::Enum, vector<string> >& symbols);

 private:
  bool live_mode_;
  /**
   * Configurations settings, runmode.
   */
  bool BacktestingMode() const {
    return !live_mode_;
  }

  /**
   * Physical location of Algorithm.
   */
  string AlgorithmLocation() const;
};

}  // namespace queues
}  // namespace quantsystem
#endif  // QUANTSYSTEM_QUEUES_QUEUE_H_
