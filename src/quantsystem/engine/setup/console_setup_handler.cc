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

#include <limits>
#include "quantsystem/brokerages/brokerage.h"
#include "quantsystem/algorithm/basic_template_algorithm.h"
#include "quantsystem/common/packets/backtest_node_packet.h"
#include "quantsystem/engine/setup/console_setup_handler.h"

namespace quantsystem {
using algorithm::BasicTemplateAlgorithm;
using brokerages::Brokerage;
using packets::BacktestNodePacket;
namespace engine {
namespace setup {
ConsoleSetupHandler::ConsoleSetupHandler() {
  max_orders_ = numeric_limits<int32>::max();
  starting_capital_ = 0;
  starting_date_ = DateTime(1998, 1, 1);
  maximum_runtime_ = TimeSpan::FromDays(10 * 365);
}

IAlgorithm* ConsoleSetupHandler::CreateAlgorithmInstance(
    const string& assembly_path) {
  // TODO(SHI): dynamic load
  IAlgorithm* algorithm = new BasicTemplateAlgorithm();
  return algorithm;
}

bool ConsoleSetupHandler::Setup(IAlgorithm* algorithm,
                                AlgorithmNodePacket* job,
                                IBrokerage* brokerage) {
  bool initialize_complete = false;
  if (!brokerage) {
    brokerage = new Brokerage();
  }
  if (job->type == packets::kBacktestNode) {
    BacktestNodePacket* backtest_job =
        dynamic_cast<BacktestNodePacket*>(job);
    if (!backtest_job) {
      return initialize_complete;
    }
    algorithm->Initialize();

    // Job packets
    backtest_job->period_start = algorithm->start_date();
    backtest_job->period_finish = algorithm->end_date();
    backtest_job->backtest_id = "LOCALHOST";
    backtest_job->user_id = 1001;
    // Endpoints
    backtest_job->transaction_endpoint =
        TransactionHandlerEndpoint::kBacktesting;
    backtest_job->result_endpoint = ResultHandlerEndpoint::kConsole;
    backtest_job->data_endpoint = DataFeedEndpoint::kFileSystem;
    backtest_job->real_time_endpoint = RealTimeEndpoint::kBacktesting;
    backtest_job->setup_endpoint = SetupHandlerEndpoint::kConsole;
    // Specific parameters
    starting_capital_ = algorithm->portfolio()->cash();
    starting_date_ = backtest_job->period_start;
  } else {
    // TODO(SHI): live
  }
  if (errors().size() == 0) {
    initialize_complete = true;
  }
  return initialize_complete;
}

}  // namespace setup
}  // namespace engine
}  // namespace quantsystem
