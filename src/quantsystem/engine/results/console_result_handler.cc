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

#include <utility>
using std::make_pair;
#include <thread>
#include <chrono>
#include "quantsystem/common/packets/log_packet.h"
#include "quantsystem/common/packets/debug_packet.h"
#include "quantsystem/common/util/stl_util.h"
#include "quantsystem/engine/results/console_result_handler.h"

namespace quantsystem {
using packets::LogPacket;
using packets::DebugPacket;
namespace engine {
namespace results {
ConsoleResultHandler::ConsoleResultHandler(
    AlgorithmNodePacket* packet)
    : exit_triggered_(false) {
  LOG(INFO) << "Launching Console Result Handler";
  is_active_ = true;
  if (dynamic_cast<BacktestNodePacket*>(packet)) {
    BacktestNodePacket* backtest = dynamic_cast<BacktestNodePacket*>(packet);
    algorithm_node_.reset(new BacktestConsoleStatusHandler(backtest));
  } else {
    LiveNodePacket *live = dynamic_cast<LiveNodePacket*>(packet);
    if (live == NULL) {
      LOG(FATAL) << "Unexpected AlgorithmNodeType";
    }
    algorithm_node_.reset(new LiveConsoleStatusHandler(live));
  }
  resample_period_ = algorithm_node_->ComputeSampleEquityPeriod();
  // Notification Period for pushes
  notification_period_ = TimeSpan::FromSeconds(5);
  update_time_ = DateTime();
  last_sampleed_timed_ = DateTime(1990, 01, 01);
  LOG(INFO) << "Launching Console Result Handler finish";
}

void ConsoleResultHandler::Run() {
  LOG(INFO) << "ConsoleResultHandler: Starting Thread.";
  while (!exit_triggered_ || messages().size() > 0) {
    while (messages().size() > 0) {
      Packet* packet = messages().front();
      messages().pop();
      if (!packet) {
        continue;
      }
      switch (packet->type) {
        case packets::kLog:
          {
            LogPacket* log = dynamic_cast<LogPacket*>(packet);
            if (log) {
              LOG(INFO) << "Log Message:" << log->message;
            }
            break;
          }
        case packets::kDebug:
          {
            DebugPacket* debug = dynamic_cast<DebugPacket*>(packet);
            if (debug) {
              LOG(INFO) << "Debug Message:" << debug->message;
            }
            break;
          }
      }
    }
    std::this_thread::sleep_for(std::chrono::seconds(100));
    DateTime now = DateTime();
    if (now > update_time_) {
      update_time_ = now + TimeSpan::FromSeconds(5);
      algorithm_node_->LogAlgorithmStatus(last_sampleed_timed_);
    }
  }
  LOG(INFO) << "ConsoleResultHandler: Ending Thread.";
  is_active_ = false;
}

void ConsoleResultHandler::Sample(const string& chart_name,
                                  ChartType::Enum chart_type,
                                  const string& series_name,
                                  SeriesType::Enum series_type,
                                  const DateTime& time,
                                  double value) {
  if (charts_.find(chart_name) == charts_.end()) {
    charts_.insert(make_pair(chart_name,
                                            new Chart(chart_name, chart_type)));
  }
  Chart::SeriesMap& series_map = charts_[chart_name]->series_map;
  if (series_map.find(series_name) == series_map.end()) {
    series_map.insert(make_pair(
        series_name, Series(series_name, series_type)));
  }
  series_map[series_name].values.push_back(ChartPoint(time, value));
}

void ConsoleResultHandler::SampleRange(const vector<Chart>& samples) {
  for (vector<Chart>::const_iterator it = samples.begin();
       it != samples.end(); ++it) {
    if (charts_.find(it->name) == charts_.end()) {
      charts_.insert(make_pair(
          it->name, new Chart(it->name, it->chart_type)));
    }
    for (Chart::SeriesMap::const_iterator it_s = it->series_map.begin();
         it_s != it->series_map.end(); ++it_s) {
      Chart::SeriesMap& series_map = charts_[it->name]->series_map;
      if (series_map.find(it_s->second.name) == series_map.end()) {
        series_map.insert(make_pair(
            it_s->second.name, Series(it_s->second.name,
                                      it_s->second.series_type)));
      }
      vector<ChartPoint>& values = charts_[it->name]->series_map[it_s->second.name].values;
      values.insert(values.end(), it_s->second.values.begin(), it_s->second.values.end());
    }
  }
}

void ConsoleResultHandler::SendFinalResult(
    AlgorithmNodePacket* job,
    const securities::OrderMap& orders,
    const map<DateTime, double>& profit_loss,
    const map<string, Holding>& holdings,
    const map<string, string>& statistics,
    const map<string, string>& banner) {
  for (map<string, string>::const_iterator it = statistics.begin();
       it != statistics.end(); ++it) {
    LOG(INFO) << "Statistics:" << it->first << it->second;
  }
}

void ConsoleResultHandler::UnsafePurgeQueue() {
  STLDeleteMapElements(&messages_);
}
}  // namespace results
}  // namespace engine
}  // namespace quantsystem
