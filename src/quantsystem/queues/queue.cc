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

#include <glog/logging.h>
#include "quantsystem/queues/queue.h"
#include "quantsystem/common/packets/live_node_packet.h"
#include "quantsystem/common/packets/backtest_node_packet.h"

namespace quantsystem {
using packets::LiveNodePacket;
using packets::BacktestNodePacket;
namespace queues {
Queue::Queue()
    : live_mode_(false) {
}

Queue::~Queue() {
}

AlgorithmNodePacket* Queue::NextJob(string* algorithm_path) {
  *algorithm_path = AlgorithmLocation();
  if (!BacktestingMode()) {
    AlgorithmNodePacket* live_job = new LiveNodePacket();
    live_job->result_endpoint = ResultHandlerEndpoint::kLiveTrading;
    live_job->setup_endpoint = SetupHandlerEndpoint::kPaperTrading;
    live_job->data_endpoint = DataFeedEndpoint::kLiveTrading;
    live_job->transaction_endpoint = TransactionHandlerEndpoint::kBacktesting;
    live_job->real_time_endpoint = RealTimeEndpoint::kLiveTrading;
    live_job->type = packets::kLiveNode;
    return live_job;
  }
  AlgorithmNodePacket* backtest_job = new BacktestNodePacket();
  backtest_job->result_endpoint = ResultHandlerEndpoint::kConsole;
  backtest_job->setup_endpoint = SetupHandlerEndpoint::kConsole;
  backtest_job->data_endpoint = DataFeedEndpoint::kFileSystem;
  backtest_job->transaction_endpoint = TransactionHandlerEndpoint::kBacktesting;
  backtest_job->real_time_endpoint = RealTimeEndpoint::kBacktesting;
  backtest_job->type = packets::kBacktestNode;
  return backtest_job;
}

string Queue::AlgorithmLocation() const {
  return "";
}

vector<Tick> Queue::NextTicks() {
  LOG(ERROR) << "Queue has not implemented live data.";
}

void Queue::Subscribe(const map<SecurityType::Enum,
                      vector<string> >& symbols) {
  LOG(ERROR) << "Queue has not implemented live data.";
}

void Queue::Unsubscribe(const map<SecurityType::Enum,
                        vector<string> >& symbols) {
  LOG(ERROR) << "Queue has not implemented live data.";
}
}  // namespace queues
}  // namespace quantsystem
