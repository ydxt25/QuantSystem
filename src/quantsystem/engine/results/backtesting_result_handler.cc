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

#include "quantsystem/engine/results/backtesting_result_handler.h"
namespace quantsystem {
namespace engine {
namespace results {
BacktestingResultHandler::BacktestingResultHandler(
    const BacktestNodePacket* job_) {
}

void BacktestingResultHandler::Run() {
}

void BacktestingResultHandler::ProcessSeriesUpdate() {
}

void BacktestingResultHandler::DebugMessage(const string& message) {
}

void BacktestingResultHandler::SecurityType(
    const vector<SecurityType::Enum>& types) {
}

void BacktestingResultHandler::LogMessage(const string& message) {
}

void BacktestingResultHandler::ErrorMessage(const string& error,
                                           const string& stacktrace) {
}

void BacktestingResultHandler::RuntimeError(const string& message,
                                           const string& stacktrace ) {
}

void BacktestingResultHandler::Sample(const string& chart_name,
                                     ChartType::Enum chart_type,
                                     const string& series_name,
                                     SeriesType::Enum series_type,
                                     const DateTime& time,
                                     double value) {
}

void BacktestingResultHandler::SampleAssetPrices(const string& symbol,
                                                const DateTime& time,
                                                double value) {
}

void BacktestingResultHandler::SampleRange(const vector<Chart>& samples) {
}

void BacktestingResultHandler::StoreResult(
    const Packet& packet, bool async) {
}

void BacktestingResultHandler::SendFinalResult(
    AlgorithmNodePacket*,
    const securities::OrderMap& orders,
    const map<DateTime, double>& profit_loss,
    const map<string, Holding>& holdings,
    const map<string, string>& statistics,
    const map<string, string>& banner) {
}

void BacktestingResultHandler::SendStatusUpdate(const string& algorithm_id,
                                               AlgorithmStatus::Enum status,
                                               const string& message) {
}

void BacktestingResultHandler::RuntimeStatistic(
    const string& key, const string& value) {
}

void BacktestingResultHandler::SendOrderEvent(const OrderEvent* new_event) {
}

void BacktestingResultHandler::Exit() {
}

void BacktestingResultHandler::PurgeQueue() {
}

string BacktestingResultHandler::ProcessLogMessages(
    const AlgorithmNodePacket& job) {
}

}  // namespace results
}  // namespace engine
}  // namespace quantsystem
