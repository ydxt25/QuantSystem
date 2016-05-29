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

#include "quantsystem/common/packets/backtest_result_packet.h"
namespace quantsystem {
namespace packets {
BacktestResultPacket::BacktestResultPacket()
    : Packet(kBacktestResult){
}

BacktestResultPacket::~BacktestResultPacket() {
}

BacktestResultPacket::BacktestResultPacket(const string& jason) {
}

BacktestResultPacket::BacktestResultPacket(const BacktestNodePacket& job,
                                           const BacktestResult& in_results,
                                           double in_progress) {
  progress = in_progress;
  session_id = job.session_id;
  period_start = job.period_start;
  period_finish = job.period_finish;
  compile_id = job.compile_id;
  channel = job.channel;
  backtest_id = job.backtest_id;
  results = in_results;
  name = job.name;
  user_id = job.user_id;
  project_id = job.project_id;
  tradeable_dates = job.tradeable_dates;
}

BacktestResult::BacktestResult() {
}

BacktestResult::BacktestResult(const map<string, Chart>& in_charts,
                               const map<int, Order>& in_orders,
                               const map<DateTime, double>& in_profit_loss,
                               const map<string, string>& in_statistics) {
  charts = in_charts;
  orders = in_orders;
  profit_loss = in_profit_loss;
  statistics = in_statistics;
}

BacktestResult::~BacktestResult() {
}

}  // namespace packets
}  // namespace quantsystem
