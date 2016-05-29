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
#include "quantsystem/common/strings/split.h"
#include "quantsystem/common/strings/numbers.h"
#include "quantsystem/common/data/market/tradebar.h"

namespace quantsystem {
namespace data {
namespace market {
TradeBar::TradeBar()
    : volume_(0),
      open_(0),
      high_(0),
      low_(0) {
  set_data_type(MarketDataType::kTradeBar);
}

TradeBar::TradeBar(const TradeBar& original) {
  set_time(original.time());
  set_symbol(original.symbol());
  set_value(original.value());
  set_data_type(original.data_type());
  volume_ = original.volume_;
  open_ = original.open_;
  high_ = original.high_;
  low_ = original.low_;
}

TradeBar::TradeBar(const SubscriptionDataConfig& config, const StringPiece& line,
         const DateTime& base_date, DataFeedEndpoint::Enum datafeed) {
  vector<StringPiece> parts = strings::Split(line, ",");
  const double kScaleFactor = 10000;
  set_symbol(config.symbol);
  double temp;
  switch (config.security) {
    case SecurityType::kEquity:
      // Equity file data format:
      int32 milliseconds;
      if (!SimpleAtoi(parts[0].as_string(), &milliseconds)) {
        LOG(ERROR) << "Invalid milliseconds=" << parts[0].as_string();
      }
      set_time(base_date + TimeSpan::FromMilliseconds(milliseconds));
      ConvertStringToDouble(parts[1].as_string(), &temp);
      open_ = (temp / kScaleFactor) * config.price_scale_factor;
      ConvertStringToDouble(parts[2].as_string(), &temp);
      high_ = (temp / kScaleFactor) * config.price_scale_factor;
      ConvertStringToDouble(parts[3].as_string(), &temp);
      low_ = (temp / kScaleFactor) * config.price_scale_factor;
      ConvertStringToDouble(parts[4].as_string(), &temp);
      set_close((temp / kScaleFactor) * config.price_scale_factor);
      if (!SimpleAtoi(parts[5].as_string(), &volume_)) {
        LOG(ERROR) << "Invalid volume=" << parts[5].as_string();
      }
      break;
    case SecurityType::kForex:
      // FOREX has a different data file format:
      set_time(DateTime(parts[0].as_string()));
      ConvertStringToDouble(parts[1].as_string(), &open_);
      ConvertStringToDouble(parts[2].as_string(), &high_);
      ConvertStringToDouble(parts[3].as_string(), &low_);
      ConvertStringToDouble(parts[4].as_string(), &temp);
      set_close(temp);
      break;
    default:
      LOG(ERROR) << "Invalid security type=" << config.security;
      break;
  }
}

TradeBar::TradeBar(const DateTime& time, const string& symbol, const double& open,
         const double& high, const double& low, const double& close,
         const int64& volume) {
  set_time(time);
  set_symbol(symbol);
  open_ = open;
  high_ = high;
  low_ = low;
  set_close(close);
  volume_ = volume;
}

TradeBar::~TradeBar() {
}

BaseData* TradeBar::Reader(const SubscriptionDataConfig& config,
                           const StringPiece& line, const DateTime& date,
                           DataFeedEndpoint::Enum datafeed) {
  if (line.empty()) {
    return NULL;
  }
  BaseData* trade_bar;
  // Select the URL source of the data depending on where the system is trading.
  switch (datafeed) {
    case DataFeedEndpoint::kBacktesting:
      // Amazon S3 Backtesting Data:
      trade_bar = new TradeBar(config, line, date, datafeed);
      break;
    case DataFeedEndpoint::kFileSystem:
      // Localhost data source
      trade_bar = new TradeBar(config, line, date, datafeed);
      break;
    case DataFeedEndpoint::kLiveTrading:
      // Live Tick system
      trade_bar = NULL;
      break;
    default:
      trade_bar = NULL;
      LOG(ERROR) << "Invalid datafeed type=" << datafeed;
      break;
  }
  return trade_bar;
}

string TradeBar::GetSource(const SubscriptionDataConfig& config,
                           const DateTime& date,
                           DataFeedEndpoint::Enum data_feed) {
  string source = "";
  switch (data_feed) {
    case DataFeedEndpoint::kBacktesting:
      // Source location for backtesting. Commonly a dropbox or FTP link
      // E.g.:
      // source = "https://www.dropbox.com/";
      break;
    case DataFeedEndpoint::kFileSystem:
      // Source location for local testing
      break;
    case DataFeedEndpoint::kLiveTrading:
      // Source location for live trading
      break;
    default:
      LOG(ERROR) << "Invalid security type=" << config.security;
      break;
  }
  return source;
}

void TradeBar::Update(const double& last_trade, const double &bid_price,
                      const double& ask_price, const double& volume) {
  if (open_ == 0) {
    open_ = last_trade;
  }
  if (last_trade > high_) {
    high_ = last_trade;
  }
  if (last_trade < low_) {
    low_ = last_trade;
  }
  volume_ += static_cast<int32>(volume);
  set_close(last_trade);
  set_value(last_trade);
}

void TradeBar::ConvertStringToDouble(const string& str, double* value) {
  if (!safe_strtod(str, value)) {
    LOG(ERROR) << "Invalid string value=" << str;
  }
}

}  // namespace market
}  // namespace data
}  // namespace quantsystem
