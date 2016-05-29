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

#ifndef QUANTSYSTEM_ENGINE_SETUP_BACKTESTING_SETUP_HANDLER_H_
#define QUANTSYSTEM_ENGINE_SETUP_BACKTESTING_SETUP_HANDLER_H_

#include <string>
using std::string;
#include "quantsystem/interfaces/ialgorithm.h"
#include "quantsystem/interfaces/ibrokerage.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/time/time_span.h"
#include "quantsystem/engine/setup/isetup_handler.h"
#include "quantsystem/engine/results/iresult_handler.h"
#include "quantsystem/common/packets/algorithm_node_packet.h"
namespace quantsystem {
using interfaces::IAlgorithm;
using interfaces::IBrokerage;
using engine::results::IResultHandler;
using packets::AlgorithmNodePacket;
namespace engine {
namespace setup {
/**
 * Backtesting setup handler processes the algorithm initialize
 * method and sets up the internal state of the algorithm class.
 * @ingroup EngineLayerSetup
 */
class BacktestingSetupHandler : public ISetupHandler {
 public:
  /**
   * Initialize the backtest setup handler.
   */
  BacktestingSetupHandler();

  /**
   * Create a new instance of an algorithm from a physical dll path.
   * @param assembly_path The path to the assembly's location
   * @return A new instance of IAlgorithm
   */
  virtual IAlgorithm* CreateAlgorithmInstance(const string& assembly_path);

  /**
   * Primary entry point to setup a new algorithm.
   * @param[out] algorithm Algorithm instance
   * @param[out] job Algorithm job task
   * @param[out] brokerage New brokerage output instance
   */
  virtual bool Setup(IAlgorithm* algorithm,
             AlgorithmNodePacket* job,
             IBrokerage* brokerage);

  /**
   * Setup the error handler for the brokerage errors.
   * @param results Result handler
   * @param brokerage Brokerage endpoint
   * @return True on successfully setting up the error handlers
   */
  virtual bool SetupErrorHandler(const IResultHandler* results,
                         const IBrokerage* brokerage);

 private:
  /**
   * Calculate the maximum runtime for this algorithm job.
   * @param start Start date of the algorithm
   * @param finish End date of the algorithm
   * @param subscription_count Number of data feeds the user has requested
   * @return Timespan maximum run period
   */
  TimeSpan GetMaximumRuntime(const DateTime& start,
                             const DateTime& finish,
                             int subscription_count);
};

}  // namespace setup
}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_SETUP_BACKTESTING_SETUP_HANDLER_H_
