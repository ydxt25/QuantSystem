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
 * @defgroup EngineLayer Engine Layer
 *
 * The quant engine loads new tasks, create the algorithms and threads,
 * and sends them to Algorithm Manager to be executed.
 */
#ifndef QUANTSYSTEM_ENGINE_ALGORITHM_MANAGER_H_
#define QUANTSYSTEM_ENGINE_ALGORITHM_MANAGER_H_

#include <string>
using std::string;
#include "quantsystem/common/global.h"
#include "quantsystem/interfaces/ialgorithm.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/base/scoped_ptr.h"
#include "quantsystem/engine/data_feeds/idata_feed.h"
#include "quantsystem/engine/setup/isetup_handler.h"
#include "quantsystem/engine/results/iresult_handler.h"
#include "quantsystem/engine/real_time/ireal_time_handler.h"
#include "quantsystem/common/packets/algorithm_node_packet.h"
#include "quantsystem/engine/transaction_handlers/itransaction_handler.h"

namespace quantsystem {
using interfaces::IAlgorithm;
using engine::datafeeds::IDataFeed;
using engine::setup::ISetupHandler;
using engine::results::IResultHandler;
using engine::realtime::IRealTimeHandler;
using packets::AlgorithmNodePacket;
using engine::transaction_handlers::ITransactionHandler;
namespace engine {
/**
 * Algorithm manager class executes the algorithm and generates and
 * passes through the algorithm events.
 * @ingroup EngineLayer
 */
class AlgorithmManager {
 public:
  /**
   * Launch the algorithm manager to run this strategy.
   * @param job Algorithm job
   * @param transactions Transaction manager object
   * @param setup Setup handler object
   * @param algorithm[out] Algorithm instance
   * @param feed[out] Datefeed object
   * @param results[out] Result handler object
   * @param realtime[out] Realtime processing object
   */
  static void Run(const AlgorithmNodePacket* job,
                  const ITransactionHandler* transactions,
                  const ISetupHandler* setup,
                  IAlgorithm* algorithm,
                  IDataFeed* feed,
                  IResultHandler* results,
                  IRealTimeHandler* realtime);

  /**
   * Process the user defined messaging by retrieving all the data
   * inside the algorithm and sending to result handler.
   * @param results IResultHandler object to send the results
   * @param algorithm Algorithm to extract messages from
   */
  static void ProcessMessages(IResultHandler* results,
                              IAlgorithm* algorithm);

  /**
   * Reset all variables required before next loops.
   */
  static void ResetManager();

  /**
   * Set the quit state.
   */
  static void SetStatus(AlgorithmStatus::Enum state);

  /**
   * Quit state flag for the running algorithm. When true the user
   * has requested the backtest stops through a Quit() method.
   */
  static bool QuitState() {
    return algorithm_state_ == AlgorithmStatus::kDeleted;
  }

  static DateTime frontier() { return frontier_; }

  static string algorithm_id() { return algorithm_id_; }

  static string* runtime_error() { return runtime_error_.get(); }

 private:
  static DateTime previous_time_;
  // Current time horizon of the algorithm
  static DateTime frontier_;
  static DateTime next_sample_;
  static AlgorithmStatus::Enum algorithm_state_;
  // Currently running algorithm id
  static string algorithm_id_;
  static scoped_ptr<string> runtime_error_;
};

}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_ALGORITHM_MANAGER_H_
