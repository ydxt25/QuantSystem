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
 * @defgroup EngineLayerSetup  Engine Layer - Setup Components
 *
 * Setup Components in Engine Layer.
 */
#ifndef QUANTSYSTEM_ENGINE_SETUP_ISETUP_HANDLER_H_
#define QUANTSYSTEM_ENGINE_SETUP_ISETUP_HANDLER_H_

#include <vector>
using std::vector;
#include <string>
using std::string;
#include "quantsystem/interfaces/ialgorithm.h"
#include "quantsystem/interfaces/ibrokerage.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/time/time_span.h"
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
 * Interface to setup the algorithm. Pass in a raw algorithm,
 * return one with portfolio, cash, etc already preset.
 * @ingroup EngineLayerSetup
 */
class ISetupHandler {
 public:
  /**
   * Create a new instance of an algorithm from a physical dll path.
   * @param assembly_path The path to the assembly's location
   * @return A new instance of IAlgorithm
   */
  virtual IAlgorithm* CreateAlgorithmInstance(const string& assembly_path) = 0;

  /**
   * Primary entry point to setup a new algorithm.
   * @param[out] algorithm Algorithm instance
   * @param[out] job Algorithm job task
   * @param[out] brokerage New brokerage output instance
   */
  virtual bool Setup(IAlgorithm* algorithm,
             AlgorithmNodePacket* job,
             IBrokerage* brokerage) = 0;

  /**
   * Setup the error handler for the brokerage errors.
   * @param results Result handler
   * @param brokerage Brokerage endpoint
   * @return True on successfully setting up the error handlers
   */
  virtual bool SetupErrorHandler(const IResultHandler* results,
                         const IBrokerage* brokerage) = 0;

  vector<string>& errors() { return errors_; }
  void set_errors(const vector<string>& errors) {
    errors_ = errors;
  }

  TimeSpan maximum_runtime() const { return maximum_runtime_; }

  double starting_capital() const { return starting_capital_; }

  DateTime starting_date() const { return starting_date_; }

  int max_orders() const { return max_orders_; }

 protected:
  void set_maximum_runtime(const TimeSpan& maximum_runtime) {
    maximum_runtime_ = maximum_runtime;
  }

  void set_starting_capital(double starting_capital) {
    starting_capital_ = starting_capital;
  }

  void set_starting_date(const DateTime& starting_date) {
    starting_date_ = starting_date;
  }

  void set_max_orders(int max_orders) {
    max_orders_ = max_orders;
  }

 protected:
  // Any errors from the initialization stored here
  vector<string> errors_;
  // The maximum runtime for this algorithm job
  TimeSpan maximum_runtime_;
  // Algorithm starting capital for statistics calculations
  double starting_capital_;
  // Start date for analysis loops to search for data
  DateTime starting_date_;
  // Maximum number of orders for the algorithm run --
  // applicable for backtests only
  int max_orders_;
};

}  // namespace setup
}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_SETUP_ISETUP_HANDLER_H_
