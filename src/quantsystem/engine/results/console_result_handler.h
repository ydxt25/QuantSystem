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

#ifndef QUANTSYSTEM_ENGINE_RESULTS_CONSOLE_RESULT_HANDLER_H_
#define QUANTSYSTEM_ENGINE_RESULTS_CONSOLE_RESULT_HANDLER_H_

#include <glog/logging.h>
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <map>
using std::map;
#include "quantsystem/common/global.h"
#include "quantsystem/common/util/charting.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/packets/packet.h"
#include "quantsystem/common/base/scoped_ptr.h"
#include "quantsystem/common/orders/order.h"
#include "quantsystem/common/orders/order_event.h"
#include "quantsystem/interfaces/ialgorithm.h"
#include "quantsystem/engine/results/iresult_handler.h"
#include "quantsystem/common/packets/backtest_node_packet.h"
#include "quantsystem/common/packets/algorithm_node_packet.h"
#include "quantsystem/common/packets/live_node_packet.h"
#include "quantsystem/common/packets/debug_packet.h"
#include "quantsystem/common/packets/runtime_error_packet.h"
#include "quantsystem/common/packets/log_packet.h"
namespace quantsystem {
using interfaces::IAlgorithm;
using orders::Order;
using orders::OrderEvent;
using packets::Packet;
using packets::AlgorithmNodePacket;
using packets::BacktestNodePacket;
using packets::LiveNodePacket;
using packets::DebugPacket;
using packets::RuntimeErrorPacket;
using packets::LogPacket;
using securities::Holding;
namespace engine {
namespace results {

/**
 * Console local resulthandler passes messages back to the
 * console/local GUI display.
 * @ingroup EngineLayerResults
 */
class ConsoleResultHandler : public IResultHandler {
 public:
   /**
   * Provides an abstraction layer for live vs backtest packets to
   * provide status/sampling to the AlgorithmManager.
   * We can run both live and back test from the console.
   * @ingroup EngineLayerResults
   */
  class IConsoleStatusHandler {
   public:
    virtual void LogAlgorithmStatus(const DateTime& current) = 0;
    virtual TimeSpan ComputeSampleEquityPeriod() = 0;
  };

  /**
   * Uses a const 2 second sample equity period and does nothing for
   * logging algorithm status.
   * @ingroup EngineLayerResults
   */
  class LiveConsoleStatusHandler : public IConsoleStatusHandler {
   public:
    explicit LiveConsoleStatusHandler(const LiveNodePacket* job)
        : job_(job) {
    }

    virtual void LogAlgorithmStatus(const DateTime& current) {
    }

    virtual TimeSpan ComputeSampleEquityPeriod() {
      return TimeSpan::FromSeconds(2);
    }

   private:
    const LiveNodePacket* job_;
  };

  /**
   * Computes sample equity period from 4000 samples evenly spaced
   * over the backtest interval and logs %complete to log file
   * @ingroup EngineLayerResults
   */
  class BacktestConsoleStatusHandler : public IConsoleStatusHandler {
   public:
    explicit BacktestConsoleStatusHandler(const BacktestNodePacket* job)
        : backtest_span_in_days_(0.0),
          job_(job) {
    }

    virtual void LogAlgorithmStatus(const DateTime& current) {
      if (backtest_span_in_days_ == 0.0) {
        backtest_span_in_days_ = (job_->period_finish -
                                  job_->period_start).TotalDays();
      }
      if (backtest_span_in_days_ == 0.0) {
        LOG(INFO) << "Initializing...";
      } else {
        double days_processed = (current - job_->period_start).TotalDays();
        if (days_processed < 0) days_processed = 0;
        if (days_processed > backtest_span_in_days_)
          days_processed = backtest_span_in_days_;
        LOG(INFO) << "Progress:" << (days_processed * 100) /
            backtest_span_in_days_ << "% Processed:" << days_processed <<
            " days of total:" << static_cast<int>(backtest_span_in_days_);
      }
    }

    virtual TimeSpan ComputeSampleEquityPeriod() {
      const double kSamples = 400;
      const double kMinimumSamplePeriod = 4 * 60;
      double resample_minutes = kMinimumSamplePeriod;
      double total_minutes = (job_->period_finish -
                              job_->period_start).TotalMinutes();
      if (total_minutes > 0.0) {
        resample_minutes = (total_minutes < (kMinimumSamplePeriod * kSamples)) ?
                           kMinimumSamplePeriod : total_minutes / kSamples;
      }
      if (resample_minutes < kMinimumSamplePeriod) {
        resample_minutes = kMinimumSamplePeriod;
      }
      return TimeSpan::FromMinutes(resample_minutes);
    }

   private:
    const BacktestNodePacket* job_;
    double backtest_span_in_days_;
  };

  /**
   * Backtesting result handler constructor.
   * Setup the default sampling and notification periods based
   * on the backtest length.
   */
  explicit ConsoleResultHandler(AlgorithmNodePacket* packet);

    /**
   * Primary result thread entry point to process the result message queue
   * and send it to whatever endpoint is set.
   */
  virtual void Run();

  /**
   * Process debug messages with the preconfigured settings.
   * @param message String debug message
   */
  virtual void DebugMessage(const string& message) {
    messages_.push(new DebugPacket(message, "", "", 0));
  }

  /**
   * Send a list of security types to the browser.
   * @param types Security types list inside algorithm
   */
  virtual void SecurityType(const vector<SecurityType::Enum>& types) {
    // NOT
  }

  /**
   * Send a logging message to the log list for storage.
   * @param message Message we'd in the log
   */
  virtual void LogMessage(const string& message) {
    messages_.push(new LogPacket("", message));
  }

  /**
   * Send an error message back to the browser highlighted in red
   * with a stacktrace.
   * @param error Error message we'd like shown in console.
   * @param stacktrace Stacktrace information string
   */
  virtual void ErrorMessage(const string& error,
                            const string& stacktrace = "") {
    messages_.push(new RuntimeErrorPacket("", error, stacktrace));
  }

  /**
   * Send a runtime error message back to the browser highlighted with in red.
   * @param message Error message
   * @param stacktrace Stacktrace information string
   */
  virtual void RuntimeError(const string& message,
                            const string& stacktrace = "") {
    messages_.push(new RuntimeErrorPacket("", message, stacktrace));
  }

  /**
   * Add a sample to the chart specified by the chartName, and seriesName.
   * Sample can be used to create new charts or sample
   * equity - daily performance.
   * @param chart_name String chart name to place the sample
   * @param chart_type Type of chart we should create if it doesn't
   * already exist
   * @param series_name Series name for the chart
   * @param series_type Series type for the chart
   * @param time Time for the sample
   * @param value Value for the chart sample
   */
  virtual void Sample(const string& chart_name,
                      ChartType::Enum chart_type,
                      const string& series_name,
                      SeriesType::Enum series_type,
                      const DateTime& time,
                      double value);

  /**
   * Wrapper methond on sample to create the equity chart.
   * @param time Time of the sample
   * @param value Equity value at this moment in time
   */
  virtual void SampleEquity(const DateTime& time, double value) {
    Sample("Strategy Equity", ChartType::kStacked, "Equity",
           SeriesType::kCandle, time, value);
    last_sampleed_timed_ = time;
  }

  /**
   * Sample the current daily performance directly with a time-value pair.
   * @param time Current backtest date
   * @param value Current daily performance value
   */
  virtual void SamplePerformance(const DateTime& time, double value) {
    Sample("Strategy Equity", ChartType::kOverlay, "Daily Performance",
           SeriesType::kLine, time, value);
  }

  /**
   * Sample the asset prices to generate plots.
   * @param symbol Symbol we're sampling
   * @param time Time of sample
   * @param value Value of the asset price
   */
  virtual void SampleAssetPrices(const string& symbol,
                                 const DateTime& time,
                                 double value) {
    // Do Nothing. Don't sample asset prices in console.
  }

  /**
   * Add a range of samples from the users algorithms to the
   * end of our current list.
   * @param samples Chart updates since the last request
   */
  virtual void SampleRange(const vector<Chart>& samples);

  /**
   * Set the algorithm of the result handler after its been initialized.
   * @param algorithm Algorithm object matching IAlgorithm interface
   */
  virtual void SetAlgorithm(IAlgorithm* algorithm) {
    algorithm_ =algorithm;
  }

  /**
   * Save the snapshot of the total results to storage.
   * @param packet Packet to store
   * @param async Store the packet asyncronously to speed up the thread
   */
  virtual void StoreResult(const Packet& packet, bool async = false) {
    // Do Nothing
  }

  /**
   * Post the final result back to the controller worker if backtesting,
   * or to console if local.
   */
  virtual void SendFinalResult(AlgorithmNodePacket* job,
                          const securities::OrderMap& orders,
                          const map<DateTime, double>& profit_loss,
                          const map<string, Holding>& holdings,
                          const map<string, string>& statistics,
                          const map<string, string>& banner);

  /**
   * Send a algorithm status update to the user of the algorithms running
   * state.
   * @param algorithnm_id String Id of the algorithm
   * @param status Status enum of the algorithm
   * @param message Optional string message describing reason for status change
   */
  virtual void SendStatusUpdate(const string& algorithm_id,
                                AlgorithmStatus::Enum status,
                                const string& message = "") {
    LOG(INFO) << "SendStatusUpdate(): Algorithm status:" << AlgorithmStatus::AlgorithmStatusToString(status) <<
        ":" << message;
  }

  /**
   * Set a dynamic runtime statistic to show in the (live) algorithm header.
   * @param key Runtime headline statistic name
   * @param value Runtime headline statistic value
   */
  virtual void RuntimeStatistic(const string& key, const string& value) {
    LOG(INFO) << "RuntimeStatistic():" << key << ":" << value;
  }

  /**
   * Send a new order event.
   * @param new_event Update, processing or cancellation of an order,
   * In backtesting the order events are not sent because it would
   * generate a high load of messaging.
   */
  virtual void SendOrderEvent(const OrderEvent* new_event) {
    LOG(INFO) << "SendOrderEvent(): id:" << new_event->order_id <<
        "<< Status:" << new_event->status << "<< Fill Price:" <<
        new_event->fill_price << "<< Fill Quantity:" << new_event->fill_quantity;
  }

  /**
   * Terminate the result thread and apply any required exit proceedures.
   */
  virtual void Exit() {
    exit_triggered_ = true;
  }

  /**
   * Purge/clear any outstanding messages in message queue.
   */
  virtual void PurgeQueue() {
     VLOG(1) << "PurgeQueue";
     UnsafePurgeQueue();
  }

  /**
   * Local object access to the algorithm for the underlying Debug
   * and Error messaging.
   */
  IAlgorithm* algorithm() const { return algorithm_; }
  void set_algorithm(IAlgorithm* algorithm) {
    algorithm_ = algorithm;
  }

 private:
  bool exit_triggered_;
  scoped_ptr<IConsoleStatusHandler> algorithm_node_;
  DateTime update_time_;
  DateTime last_sampleed_timed_;
  IAlgorithm* algorithm_;
  int job_days_;

  void UnsafePurgeQueue();
};

}  // namespace results
}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_RESULTS_CONSOLE_RESULT_HANDLER_H_
