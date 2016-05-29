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

#ifndef QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_POSITIONS_H_
#define QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_POSITIONS_H_

#include <string>
using std::string;
#include <vector>
using std::vector;
#include "quantsystem/common/base/integral_types.h"
#include "quantsystem/common/time/date_time.h"

namespace quantsystem {
namespace brokerages {
class TradierPosition;
/**
 * Position array container.
 * @ingroup BrokeragesLayer
 */
class TradierPositions {
 public:
  vector<TradierPosition> positions;
};

/**
 * Empty class for deserializing positions held.
 * @ingroup BrokeragesLayer
 */
class TradierPositionsContainer {
 public:
  TradierPositions tradier_positions;
};

/**
 * Individual Tradier position model.
 * @ingroup BrokeragesLayer
 */
class TradierPosition {
 public:
  int64 id;
  DateTime date_acquired;
  int64 quantity;
  double cost_basis;
  string symbol;

  /**
   * Standard constructor.
   */
  TradierPosition();

  /**
   * Standard destructor.
   */
  virtual ~TradierPosition();
};

}  // namespace brokerages
}  // namespace quantsystem
#endif  // QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_POSITIONS_H_
