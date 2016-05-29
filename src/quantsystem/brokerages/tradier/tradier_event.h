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

#ifndef QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_EVENT_H_
#define QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_EVENT_H_

#include <string>
using std::string
#include <vector>
using std::vector;
#include "quantsystem/brokerages/tradier/tradier_common.h"
#include "quantsystem/common/time/date_time.h"

namespace quantsystem {
namespace brokerages {
class TradierEvents;
/**
 * Tradier deserialization container for history.
 * @ingroup BrokeragesLayer
 */
class TradierEventContainer {
 public:
  TradierEvents tradier_events;
};

class TradierEvent;
/**
 * Events array container.
 * @ingroup BrokeragesLayer
 */
class TradierEvents {
 public:
  vector<TradierEvent> events;
};

class TradierTradeEvent;
class TradierJournalEvent;
class TradierOptionEvent;
/**
 * Tradier event model.
 * @ingroup BrokeragesLayer
 */
class TradierEvent {
 public:
  double amount;
  DateTime date;
  TradierEventType type;
  TradierTradeEvent trade_event;
  TradierJournalEvent journal_event;
  TradierOptionEvent option_event;
  TradierOptionEvent dividend_event;
};

/**
 * Common base class for events detail information.
 * @ingroup BrokeragesLayer
 */
class TradierEventDetail {
 public:
  string description;
  double quantity;
};

/**
 * Trade event in history for tradier.
 * @ingroup BrokeragesLayer
 */
class TradierTradeEvent: public TradierEventDetail {
  double commission;
  double price;
  string symbol;
  TradierTradeType trade_type;
};

/**
 * Journal event in history.
 * @ingroup BrokeragesLayer
 */
class TradierJournalEvent : public TradierEventDetail {
};

/**
 * Dividend event in history.
 * @ingroup BrokeragesLayer
 */
class TradierDividendEvent : public TradierEventDetail {
};

/**
 * Option event record in history.
 * @ingroup BrokeragesLayer
 */
class TradierOptionEvent : public TradierEventDetail {
 public:
  TradierOptionStatus type;
};

}  // namespace brokerages
}  // namespace quantsystem
#endif  // QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_EVENT_H_
