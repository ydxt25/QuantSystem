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

#include "quantsystem/common/securities/equity/equity_transaction_model.h"
namespace quantsystem {
namespace securities {
namespace equity {
EquityTransactionModel::EquityTransactionModel() {
}

EquityTransactionModel::~EquityTransactionModel() {
}

OrderEvent* EquityTransactionModel::Fill(
    const Security* asset, Order* order) {
}

OrderEvent* EquityTransactionModel::MarketFill(
    const Security* asset, Order* order) {
}

OrderEvent* EquityTransactionModel::StopFill(
    const Security* asset, Order* order) {
}

OrderEvent* EquityTransactionModel::LimitFill(
    const Security* asset, Order* order) {
}

double EquityTransactionModel::GetOrderFee(
    const double& quantity, const double& price) {
}

}  // namespace equity
}  // namespace securities
}  // namespace quantsystem
