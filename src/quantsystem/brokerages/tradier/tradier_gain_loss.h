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

#ifndef QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_GAIN_LOSS_H_
#define QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_GAIN_LOSS_H_

#include <string>
using std::string;
#include <vector>
using std::vector;
#include "quantsystem/common/time/date_time.h"

namespace quantsystem {
namespace brokerages {
class TradierGainLoss;

/**
 * Gain loss class 
 * @ingroup BrokeragesLayer
 */
class TradierGainLossClosed {
 public:
  vector<TradierGainLoss> closed_positions;
};

/**
 * Gain loss parent class for deserialization.
 * @ingroup BrokeragesLayer
 */
class TradierGainLossContainer {
 public:
  TradierGainLossClosed gain_loss_closed;
};

/**
 * Account only settings for a tradier user.
 * @ingroup BrokeragesLayer
 */
class TradierGainLoss {
 public:
  DateTime close_date;  // Date the position was closed
  DateTime open_date;  // Date the position was opened
  double cost;  //  Total cost of the order
  double gain_loss;  // Gain or loss on the position
  double gain_loss_percentage;  // Percentage of gain or loss on the position
  double proceeds;  // Total amount received for the order
  double quantity;  // Number of shares/contracts
  string symbol;
  double term;  //  Number of shares/contracts

  /**
   * Standard constructor.
   */
  TradierGainLoss();

  /**
   * Standard destructor.
   */
  virtual ~TradierGainLoss();
};

}  // namespace brokerages
}  // namespace quantsystem
#endif  // QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_GAIN_LOSS_H_
