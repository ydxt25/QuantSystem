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

/**
 * @defgroup MessagingLayer Messaging Layer
 *
 * Messaging Layer.
 */

#ifndef QUANTSYSTEM_MESSAGIN_MESSAGING_H_
#define QUANTSYSTEM_MESSAGIN_MESSAGING_H_

#include <string>
using std::string;
#include "quantsystem/common/packets/packet.h"
#include "quantsystem/common/packets/security_types_packet.h"
#include "quantsystem/common/packets/backtest_result_packet.h"
#include "quantsystem/common/packets/live_result_packet.h"
#include "quantsystem/interfaces/imessaging_handler.h"

namespace quantsystem {
using packets::Packet;
using packets::SecurityTypesPacket;
using packets::BacktestResultPacket;
using packets::LiveResultPacket;
using interfaces::IMessagingHandler;
namespace messaging {
/**
 * Local/desktop implementation of messaging system for Quantsystem Engine.
 * @ingroup MessagingLayer
 */
class Messaging: public IMessagingHandler {
 public:
  /**
   * Standard constructor.
   */
  Messaging();

  /**
   * Standard destructor.
   */
  virtual ~Messaging();

  /**
   * Initialize the Messaging System Plugin.
   */
  virtual void Initialize() {
  }

  /**
   * Set the user communication channel.
   * @param channel_id Unique channel id for the communication
   */
  virtual void SetChannel(const string& channel_id) {
  }

  /**
   * Send any message with a base type of Packet.
   * @param packet Packet of data to send via the messaging system plugin
   */
  virtual void Send(const Packet& packet) {
  }

  /**
   * Send a string debug message to the user.
   * @param line String message data to send
   * @param project_id Project id associated with this message
   * @param algorithm_id Algorithm id assocaited with this message
   * @param compile_id Compile id associated with this message
   */
  virtual void DebugMessage(const string& line,
                            int project_id,
                            const string& algorithm = "",
                            const string& compile_id = "") {
  }

  /**
   * Send a security types packet: what securities are being
   * used in this algorithm? What markets are we trading?
   * @param types List of security types to be passed to the GUI
   */
  virtual void SecurityTypes(const SecurityTypesPacket& type) {
  }

  /**
   * Send a log message to the final user interface via
   * messaging system plugin.
   * @param algorithm_id Algorithm id associated with this log message
   * @param message String log message to be saved and passed to user interface
   */
  virtual void LogMessage(const string& algorithm_id,
                          const string& message) {
  }

  /**
   * Runtime error handler. Triggered when the user algorithm
   * has an unhandled error while the algorithm was running.
   * @param algorithm_id Algorithm id associated with this backtest
   * @param error String error message captured from the unhandled error event
   * @param stacktrace String stack trace of the runtime error
   */
  virtual void RuntimeError(const string& algorithm_id,
                            const string& error,
                            const string& stacktrace = "") {
  }

  /**
   * Algorithm status change signal from the Engine triggering GUI updates.
   * @param algorithm_id Algorithm id associated with this backtest
   * @param status State(enum) status message
   * @param message Additional string message information
   */
  virtual void AlgorithmStatus(const string& algorithm_id,
                               AlgorithmStatus::Enum status,
                               const string& message) {
  }

  /**
   * Send a backtest result message via the messaging plugin system.
   * @param packet Backtest result packet containing
   * updated chart and progress information
   * @param final_packet This is the final packet.
   * Backtests can return before 100% if they have failed or
   * the data does not contain the expected number of days
   */
  virtual void BacktestResult(const BacktestResultPacket* packet,
                              bool final_packet = false) {
  }

  /**
   * Send live trading result packet to the user interface
   * via the messaging plugin system.
   * @param packet Live result packet containing live result
   * information to update the GUI
   */
  virtual void LiveTradingResult(const LiveResultPacket& packet) {
  }
};

}  // namespace messaging
}  // namespace quantsystem
#endif  // QUANTSYSTEM_MESSAGIN_MESSAGING_H_
