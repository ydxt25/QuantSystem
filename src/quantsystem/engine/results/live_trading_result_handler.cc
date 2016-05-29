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

#include "quantsystem/engine/results/live_trading_result_handler.h"
namespace quantsystem {
namespace engine {
namespace results {
LiveTradingResultHandler::LiveTradingResultHandler(const LiveNodePacket* job) {
}

void LiveTradingResultHandler::Run() {
}

void LiveTradingResultHandler::Update() {
}

void LiveTradingResultHandler::DebugMessage(const string& message) {
}

void LiveTradingResultHandler::SecurityType(
    const vector<SecurityType::Enum>& types) {
}

void LiveTradingResultHandler::LogMessage(const string& message) {
}

void LiveTradingResultHandler::ErrorMessage(const string& error,
                                            const string& stacktrace) {
}

void LiveTradingResultHandler::RuntimeError(const string& message,
                  const string& stacktrace ) {
}

void LiveTradingResultHandler::Sample(const string& chart_name,
                                      ChartType::Enum chart_type,
                                      const string& series_name,
                                      SeriesType::Enum series_type,
                                      const DateTime& time,
                                      double value) {
}

void LiveTradingResultHandler::SampleEquity(
    const DateTime& time, double value){
}

void LiveTradingResultHandler::SamplePerformance(
    const DateTime& time, double value){
}

void LiveTradingResultHandler::SampleAssetPrices(const string& symbol,
                                                 const DateTime& time,
                                                 double value){
}

void LiveTradingResultHandler::SampleRange(const vector<Chart>& samples){
}

void LiveTradingResultHandler::SetAlgorithm(IAlgorithm* algorithm) {
}


void LiveTradingResultHandler::StoreResult(
    const Packet& packet, bool async) {
}

void LiveTradingResultHandler::SendFinalResult(
    AlgorithmNodePacket* job,
    const securities::OrderMap& orders,
    const map<DateTime, double>& profit_loss,
    const map<string, Holding>& holdings,
    const map<string, string>& statistics,
    const map<string, string>& banner){
}

void LiveTradingResultHandler::StoreLog(
    const DateTime& date, const vector<string>& logs) {
}

void LiveTradingResultHandler::SendStatusUpdate(const string& algorithm_id,
                                                AlgorithmStatus::Enum status,
                                                const string& message) {
}

void LiveTradingResultHandler::RuntimeStatistic(
    const string& key, const string& value) {
}

void LiveTradingResultHandler::SendOrderEvent(const OrderEvent* new_event) {
}

void LiveTradingResultHandler::Exit() {
}

void LiveTradingResultHandler::PurgeQueue() {
}

}  // namespace results
}  // namespace engine
}  // namespace quantsystem
