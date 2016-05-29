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

#include <thread>
#include <chrono>
#include <functional>
#include "quantsystem/common/util/stl_util.h"
#include "quantsystem/common/securities/security.h"
#include "quantsystem/engine/real_time/backtesting_real_time_handler.h"
namespace quantsystem {
using securities::Security;
namespace engine {
namespace realtime {
BacktestingRealTimeHandler::BacktestingRealTimeHandler(
    IAlgorithm* algorithm,
    AlgorithmNodePacket* job)
    : exit_triggered_(false),
      algorithm_(algorithm),
      job_(job) {
  is_active_ = true;
}

BacktestingRealTimeHandler::~BacktestingRealTimeHandler() {
  STLDeleteElements(&events_);
}

void RealTimeEventHelper(IAlgorithm* algorithm, const Security* security) {
  algorithm->OnEndOfDay();
  algorithm->OnEndOfDay(security->symbol());
}

void BacktestingRealTimeHandler::SetupEvents(const DateTime& date) {
  ClearEvents();
  vector<const Security*> securities;
  algorithm_->securities()->Values(&securities);
  for (int i = 0; i < securities.size(); ++i) {
    const Security* security = securities[i];
    RealTimeEvent::CallBackType* func = new RealTimeEvent::CallBackType(
        std::bind(RealTimeEventHelper, algorithm_, security));
    AddEvent(new RealTimeEvent(security->exchange()->market_close() -
                               TimeSpan::FromMinutes(10), func));
  }
}

void BacktestingRealTimeHandler::Run() {
  is_active_ = true;
  while (!exit_triggered_) {
    std::this_thread::sleep_for(std::chrono::seconds(50));
  }
  is_active_ = false;
}

void BacktestingRealTimeHandler::AddEvent(RealTimeEvent* new_event) {
  events_.push_back(new_event);
}

void BacktestingRealTimeHandler::ScanEvents() {
  for (int i = 0; i < events_.size(); ++i) {
    events_[i]->Scan(time_);
  }
}

void BacktestingRealTimeHandler::ResetEvents() {
  for (int i = 0; i < events_.size(); ++i) {
    events_[i]->Reset();
  }
}

void BacktestingRealTimeHandler::ClearEvents() {
  STLDeleteElements(&events_);
}

void BacktestingRealTimeHandler::SetTime(const DateTime& time) {
  if (time_ != time) {
    SetupEvents(time);
    ResetEvents();
  }
  time_ = time;
  ScanEvents();
}

void BacktestingRealTimeHandler::Exit() {
  exit_triggered_ = true;
}

}  // namespace realtime
}  // namespace engine
}  // namespace quantsystem
