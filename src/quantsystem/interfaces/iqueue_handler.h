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

#ifndef QUANTSYSTEM_INTERFACES_IQUEUE_HANDLER_H_
#define QUANTSYSTEM_INTERFACES_IQUEUE_HANDLER_H_

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include "quantsystem/common/global.h"
#include "quantsystem/common/data/market/tick.h"
#include "quantsystem/common/packets/algorithm_node_packet.h"

namespace quantsystem {
using data::market::Tick;
using packets::AlgorithmNodePacket;
namespace interfaces {
/**
 * Task requestor interface with cloud system
 * @ingroup Interfaces
 */
class IQueueHandler {
 public:
  /**
   * Initialize the task handler.
   */
  virtual void Initialize(bool live_mode) = 0;

  /**
   * Request the next task to run through the engine.
   * @param[out] algorithm path
   * @return AlgorithmNodePacket to process
   */
  virtual AlgorithmNodePacket* NextJob(string* algorithm_path) = 0;

  /**
   * Signal task complete.
   * @param job Work to do.
   */
  virtual void AcknowledgeJob(const AlgorithmNodePacket& job) = 0;

  /**
   * Get the next ticks from the live trading data queue
   * @return Vector of ticks since the last update
   */
  virtual vector<Tick> NextTicks() = 0;

  /**
   * Adds the specified symbols to the subscription.
   * @param symbols The symbols to be added keyed by SecurityType
   */
  virtual void Subscribe(
      const map<SecurityType::Enum, vector<string> >& symbols) = 0;

  /**
   * Removes the specified symbols to the subscription.
   * @param symbols The symbols to be removed keyed by SecurityType
   */
  virtual void Unsubscribe(
      const map<SecurityType::Enum, vector<string> >& symbols) = 0;
};

}  // namespace interfaces
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INTERFACES_IQUEUE_HANDLER_H_
