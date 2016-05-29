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

#include <vector>
using std::vector;
#include "quantsystem/common/strings/numbers.h"
#include "quantsystem/common/base/integral_types.h"
#include "quantsystem/common/strings/split.h"
#include "quantsystem/common/data/market/tick.h"

namespace quantsystem {
namespace data {
namespace market {
Tick::Tick()
    : tick_type_(kTrade),
      quantity_(0),
      exchange_(0),
      sale_condition_(""),
      suspicious_(false),
      bid_price_(0.0),
      ask_price_(0.0) {
  set_data_type(MarketDataType::kTick);
}

Tick::Tick(const Tick& original)
    : tick_type_(original.tick_type_),
      quantity_(original.quantity_),
      exchange_(original.exchange_),
      sale_condition_(original.sale_condition_),
      suspicious_(original.suspicious_),
      bid_price_(original.bid_price_),
      ask_price_(original.ask_price_) {
  set_data_type(original.data_type());
  set_symbol(original.symbol());
  set_value(original.value());
  set_time(original.time());
}

Tick::Tick(const DateTime& time, const string& symbol, const double& bid,
           const double& ask)
    : tick_type_(kQuote),
      quantity_(0),
      exchange_(0),
      sale_condition_(""),
      suspicious_(false),
      bid_price_(bid),
      ask_price_(ask) {
  set_data_type(MarketDataType::kTick);
  set_time(time);
  set_symbol(symbol);
  set_value(bid + (ask + bid) / 2);
}

Tick::Tick(const DateTime& time, const string& symbol, const double& last,
           const double& bid, const double& ask)
    : tick_type_(kQuote),
      quantity_(0),
      exchange_(0),
      sale_condition_(""),
      suspicious_(false),
      bid_price_(bid),
      ask_price_(ask) {
  set_data_type(MarketDataType::kTick);
  set_time(time);
  set_symbol(symbol);
  set_value(last);
}

Tick::Tick(const string& symbol, const StringPiece& line)
    : tick_type_(kQuote),
      quantity_(0),
      exchange_(0),
      sale_condition_(""),
      suspicious_(false) {
  vector<StringPiece> parts = strings::Split(line, ".");
  set_data_type(MarketDataType::kTick);
  set_symbol(symbol);
  set_time(DateTime(parts[0].as_string()));
  set_value(bid_price_ + (ask_price_ + bid_price_) / 2);
  if (!safe_strtod(parts[1].as_string(), &bid_price_)) {
    LOG(ERROR) << "invalid input bid_price=" << parts[1].as_string();
  }
  if (!safe_strtod(parts[2].as_string(), &ask_price_)) {
    LOG(ERROR) << "invalid input ask_price=" << parts[2].as_string();
  }
}

Tick::Tick(const SubscriptionDataConfig& config, const StringPiece& line,
          const DateTime& date, DataFeedEndpoint::Enum datafeed)
    : quantity_(0),
      exchange_(0),
      sale_condition_(""),
      suspicious_(false) {
  vector<StringPiece>  parts = strings::Split(line, ",");
  switch (config.security) {
    case SecurityType::kEquity:
      set_symbol(config.symbol);
      int32 milliseconds;
      if (!SimpleAtoi(parts[0].as_string(), &milliseconds)) {
        LOG(ERROR) << "invalid milliseconds=" << parts[0].as_string();
      }
      set_time(date +  TimeSpan::FromMilliseconds(milliseconds));
      double d;
      if (!safe_strtod(parts[1].as_string(), &d)) {
        LOG(ERROR) << "invalid input value=" << parts[1].as_string();
      }
      set_value((d / 10000) * config.price_scale_factor);
      set_data_type(MarketDataType::kTick);
      tick_type_ = kTrade;
      if (!SimpleAtoi(parts[2].as_string(), &quantity_)) {
        LOG(ERROR) << "invalid input quantity=" << parts[2].as_string();
      }
      if (parts.size() > 3) {
        exchange_ = parts[3].as_string();
        sale_condition_ = parts[4].as_string();
        suspicious_ = (parts[5] == "1");
      }
      break;
    case SecurityType::kForex:
      set_symbol(config.symbol);
      tick_type_= kQuote;
      set_time(DateTime(parts[0].as_string()));
      if (!safe_strtod(parts[1].as_string(), &bid_price_)) {
        LOG(ERROR) << "invalid input bid_price=" << parts[1].as_string();
      }
      if (!safe_strtod(parts[2].as_string(), &ask_price_)) {
        LOG(ERROR) << "invalid input ask_price=" << parts[2].as_string();
      }
      set_value(bid_price_ + (ask_price_ + bid_price_) / 2);
      break;
    default:
      LOG(FATAL) << "Invalid input security type  = " << config.security;
      break;
  }
}

BaseData* Tick::Reader(const SubscriptionDataConfig &config,
                       const StringPiece& line, const DateTime& date,
                       DataFeedEndpoint::Enum datafeed) {
  BaseData* tick = NULL;
  switch (datafeed) {
    case DataFeedEndpoint::kFileSystem:
    case DataFeedEndpoint::kBacktesting:
      tick = new Tick(config, line, date, datafeed);
      break;
    case DataFeedEndpoint::kLiveTrading:
      tick = new Tick();
      break;
    default:
      tick = new Tick();
      break;
  }
  return tick;
}

string Tick::GetSource(const SubscriptionDataConfig& config,
                       const DateTime& date,
                       DataFeedEndpoint::Enum data_feed) {
  string source = "";
  switch (data_feed) {
    case DataFeedEndpoint::kBacktesting:
      // Source location for backtesting. Commonly a dropbox or FTP link
      break;
    case DataFeedEndpoint::kFileSystem:
      // Source location for local testing
      break;
    case DataFeedEndpoint::kLiveTrading:
      // Source location for live trading
      break;
  }
  return source;
}

void Tick::Update(const double& last_trade, const double &bid_price,
                  const double& ask_price, const double& volume) {
  set_value(last_trade);
  bid_price_ = bid_price;
  ask_price_ = ask_price;
  quantity_ = static_cast<int>(volume);
}

}  // namespace market
}  // namespace data
}  // namespace quantsystem
