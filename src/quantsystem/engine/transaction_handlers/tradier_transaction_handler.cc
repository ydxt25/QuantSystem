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

#include "quantsystem/engine/transaction_handlers/tradier_transaction_handler.h"
namespace quantsystem {
namespace engine {
namespace transaction_handlers {
TradierTransactionHandler::TradierTransactionHandler(
    const IAlgorithm* algorithm,
    const IBrokerage* brokerage,
    const IResultHandler* results,
    int account_id) {
}

void TradierTransactionHandler::Run() {
}

int TradierTransactionHandler::NewOrder(Order* order) {
}

bool TradierTransactionHandler::UpdateOrder(Order* order) {
}

bool TradierTransactionHandler::CancelOrder(Order* order) {
}

void TradierTransactionHandler::SetAlgorithm(IAlgorithm* algorithm) {
}

void TradierTransactionHandler::Exit() {
}

}  // namespace transaction_handlers
}  // namespace engine
}  // namespace quantsystem
