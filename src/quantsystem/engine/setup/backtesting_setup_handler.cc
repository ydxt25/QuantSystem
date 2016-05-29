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

#include "quantsystem/engine/setup/backtesting_setup_handler.h"
namespace quantsystem {
namespace engine {
namespace setup {
BacktestingSetupHandler::BacktestingSetupHandler() {
}

IAlgorithm* BacktestingSetupHandler::CreateAlgorithmInstance(
    const string& assembly_path) {
}

bool BacktestingSetupHandler::Setup(
    IAlgorithm* algorithm,
    AlgorithmNodePacket* job,
    IBrokerage* brokerage) {
}

bool BacktestingSetupHandler::SetupErrorHandler(const IResultHandler* results,
                                                const IBrokerage* brokerage) {
}

TimeSpan BacktestingSetupHandler::GetMaximumRuntime(
    const DateTime& start,
    const DateTime& finish,
    int subscription_count) {
}

}  // namespace setup
}  // namespace engine
}  // namespace quantsystem
