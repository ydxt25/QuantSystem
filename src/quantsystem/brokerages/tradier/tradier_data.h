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

#ifndef QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_DATA_H_
#define QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_DATA_H_

#include <string>
using std::string
#include <vector>
using std::vector;
#include "quantsystem/common/base/integral_types.h"
#include "quantsystem/brokerages/tradier/tradier_common.h"
#include "quantsystem/common/time/date_time.h"

namespace quantsystem {
namespace brokerages {
class TradierTimeSeries;
/**
 * Container for timeseries array.
 * @ingroup BrokeragesLayer
 */
class TradierTimeSeriesContainer {
 public:
  vector<TradierTimeSeries> time_series;
};

/**
 * One bar of historical Tradier data.
 * @ingroup BrokeragesLayer
 */
class TradierTimeSeries{
 public:
  DateTime time;  // Time of price sample
  double price;  // Tick data requests
  double open;  // Bar requests: open
  double high;  // Bar requests: high
  double low;  // Bar requests: low
  double close;  // Bar requests: close
  double volume;  // Bar requests: volume
};

class TradierQuote;
/**
 * Container for quotes.
 * @ingroup BrokeragesLayer
 */
class TradierQuoteContainer {
 public:
  vector<TradierQuote> quotes;
};

class TradierQuote {
 public:
  string symbol;
  string description;
  string exchange;
  string type;
  double last;
  double change;
  double percentage_change;
  double volume;
  double average_volume;
  double last_volume;
  int64 trade_date_unix;
  double open;
  double high;
  double low;
  double close;
  double previous_close;
  double week52_high;
  double week52_low;
  double bid;
  double bid_size;
  string big_exchange;
  int64 bid_date_unix;
  double ask;
  double ask_size;
  string ask_exchange;
  int64 ask_date_unix;
  int64 options_open_interest;
  string options_underlying_asset;
  double options_strike;
  int options_contract_size;
  int64 options_expiration_date;
  TradierOptionExpirationType options_expiration_type;
  TradierOptionType options_option_type;
};

class TradierHistoryBar;
/**
 * Container for deserializing history classes
 * @ingroup BrokeragesLayer
 */
class TradierHistoryDataContainer {
 public:
  vector<TradierHistoryBar> data;
};

/**
 * "Bar" for a history unit.
 * @ingroup BrokeragesLayer
 */
class TradierHistoryBar {
 public:
  DateTime time;
  double open;
  double high;
  double low;
  double close;
  double volume;
};

/**
 * Current market status description.
 * @ingroup BrokeragesLayer
 */
class TradierMarketStatus {
 public:
  DateTime time;
  string description;
  string next_change;
  string state;
  int64 time_stamp;
};

class TradierCalendarDayContainer;
/**
 * Calendar status.
 * @ingroup BrokeragesLayer
 */
class TradierCalendarStatus {
 public:
  TradierCalendarDayContainer days;
  int month;
  int year;
};

class TradierCalenderDay;
/**
 * Container for the days array.
 * @ingroup BrokeragesLayer
 */
class TradierCalendarDayContainer {
 public:
  vector<TradierCalenderDay> days;
};

class TradierCalendarDayMarketHours;
/**
 * Single days properties from the calendar.
 * @ingroup BrokeragesLayer
 */
class TradierCalenderDay {
 public:
  DateTime date;
  string status;
  string description;
  TradierCalendarDayMarketHours permarket;
  TradierCalendarDayMarketHours open;
  TradierCalendarDayMarketHours postmarket;
};

/**
 * Start and finish time of market hours for this market.
 * @ingroup BrokeragesLayer
 */
class TradierCalendarDayMarketHours {
 public:
  DateTime start;
  DateTime end;
};

class TradierSearchResult;
/**
 * Tradier Search Container for Deserialization.
 * @ingroup BrokeragesLayer 
 */
class TradierSearchContainer {
 public:
  vector<TradierSearchResult> results;
};

/**
 * One search result from API.
 * @ingroup BrokeragesLayer
 */
class TradierSearchResult {
 public:
  string symbol;
  string exchange;
  string type;
  string description;
};

/**
 * Create a new stream session.
 * @ingroup BrokeragesLayer
 */
class TradierStreamSession {
 public:
  string session_id;
  string url;
};

/**
 * One data packet from a tradier stream:
 * @ingroup BrokeragesLayer
 */
class TradierStreamData {
 public:
  string type;
  string symbol;
  double summary_open;
  double summary_high;
  double summary_low;
  double summary_close;
  double bid_price;
  int bid_size;
  string bid_exchange;
  int64 bid_date_unix;
  double trade_price;
  double trade_size;
  string trade_exchange;
  int64 trade_date_unix;
  int64 trade_vol;
  double ask_price;
  int ask_size;
  string ask_exchange;
  int64 ask_date_unix;
}

}  // namespace brokerages
}  // namespace quantsystem
#endif  // QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_DATA_H_
