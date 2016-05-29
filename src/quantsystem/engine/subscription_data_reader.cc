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
#include "quantsystem/configuration/configuration.h"
#include "quantsystem/common/data/market/tick.h"
#include "quantsystem/common/data/market/tradebar.h"
#include "quantsystem/common/data/custom/quandl.h"
#include "quantsystem/common/strings/case.h"
#include "quantsystem/common/strings/strcat.h"
#include "quantsystem/common/util/file.h"
#include "quantsystem/common/util/curl_processor.h"
#include "quantsystem/compression/compression.h"
#include "quantsystem/engine/subscription_data_reader.h"
namespace quantsystem {
using configuration::Config;
using data::market::Tick;
using data::market::TradeBar;
using data::custom::Quandl;
namespace engine {
SubscriptionDataReader::SubscriptionDataReader(
    SubscriptionDataConfig* config,
    Security* security,
    DataFeedEndpoint::Enum feed,
    const DateTime& period_start,
    const DateTime& period_finish,
    IResultHandler* result_handler)
    : period_start_(period_start),
      period_finish_(period_finish),
      end_of_stream_(false),
      is_fill_forward_(true),
      price_factor_(0.0),
      result_handler_(result_handler),
      config_(config),
      security_(security) {
  is_fill_forward_ = config->fill_data_forward;
  is_qs_data_ = security->is_quant_system_data();
  is_qs_equity_ = (security->type() == SecurityType::kEquity) && is_qs_data_;
  is_qs_tick_ = ((config->type_name == typeid(Tick).name()) && is_qs_data_);
  is_qs_tradebar_ = ((config->type_name == typeid(TradeBar).name()) &&
                     is_qs_data_);
  feed_endpoint_ = feed;
  if (is_qs_equity_) {
    SubscriptionAdjustment::GetFactorTable(config->symbol, &price_factors_);
    SubscriptionAdjustment::GetMapTable(config->symbol, &symbol_map_);
  }
  data_factory_.reset(GetDataFactory(config->type_name));
}

SubscriptionDataReader::~SubscriptionDataReader() {
}

bool SubscriptionDataReader::MoveNext() {
  shared_ptr<BaseData> instance;
  bool instance_market_open = false;
  if (end_of_stream_ || reader_ == NULL || reader_->EndOfStream()) {
    if (reader_ == NULL) {
      current_.reset();
    } else {
      last_bar_of_stream_ = current_;
    }
    end_of_stream_ = true;
    return false;
  }
  // Keep looking until output an instance
  while (instance == NULL && !reader_->EndOfStream()) {
    string line = reader_->ReadLine();
    instance.reset(data_factory_->Reader(*config_, line,
                                         date_, feed_endpoint_));
    if (instance != NULL) {
      instance_market_open = security_->exchange()->DateTimeIsOpen(
          instance->time());
      // Apply custom user data filters
      if (!security_->data_filter()->Filter(*security_, *instance)) {
        instance.reset();
        continue;
      }
      if (instance == NULL) {
        LOG(INFO) << "Instance is NULL, continuing..";
        continue;
      }
      if (!is_qs_data_) {
        if (instance->time() < period_start_) {
          last_bar_outside_market_hours_ = instance;
          instance.reset();
          continue;
        }
        if (instance->time() > period_finish_) {
          instance.reset();
          continue;
        }
      }
      // Save bar for extended market hours (fill forward)
      if (!instance_market_open) {
        last_bar_outside_market_hours_ = instance;
      }
      // However, if we only want market hours data,
      // don't return yet: Discard and continue looping.
      if (!config_->extended_market_hours && !instance_market_open) {
        instance.reset();
      }
    }
  }  // while
  // Handle edge conditions: First Bar Read:
  // Use previous bar from yesterday if available
  if (current_ == NULL) {
    if (last_bar_of_stream_ == NULL) {
      last_bar_of_stream_ = last_bar_outside_market_hours_?
                            last_bar_outside_market_hours_ : instance;
    }
    // If current not set yet, set Previous to yesterday/last bar read.
    previous_ = last_bar_of_stream_;
  } else {
    previous_ = current_;
  }
  current_ = instance;
  // End of Stream: rewind reader to last
  if (reader_->EndOfStream() && instance == NULL) {
    end_of_stream_ = true;
    if (is_fill_forward_ && previous_ == NULL) {
      current_.reset(previous_->Clone());
      current_->set_time(
          security_->exchange()->TimeOfDayClosed(previous_->time()));
      last_bar_of_stream_ = previous_;
    }
    return false;
  }
  return true;
}

void SubscriptionDataReader::UpdateScaleFactors(const DateTime& date) {
  mapped_symbol_ = SubscriptionAdjustment::GetMappedSymbol(symbol_map_, date);
  price_factor_ = SubscriptionAdjustment::GetTimePriceFactor(price_factors_,
                                                             date);
  config_->set_price_scale_factor(price_factor_);
  config_->set_mapped_symbol(mapped_symbol_);
}

bool SubscriptionDataReader::MarketOpen(const DateTime& time) const {
  return security_->exchange()->DateTimeIsOpen(time);
}

bool SubscriptionDataReader::ExtendedMarketOpen(const DateTime& time) const {
  return security_->exchange()->DateTimeIsExtendedOpen(time);
}

bool SubscriptionDataReader::RefreshSource(const DateTime& date) {
  date_ = date;
  string new_source = "";
  if (is_qs_equity_ && (feed_endpoint_ == DataFeedEndpoint::kBacktesting ||
                        feed_endpoint_ == DataFeedEndpoint::kFileSystem)) {
    UpdateScaleFactors(date);
  }
  // Make sure this particular security is trading today
  if (!security_->exchange()->DateIsOpen(date)) {
    end_of_stream_ = true;
    return false;
  }
  if (is_qs_data_) {
    new_source = GetQuantSystemSource(date);
  } else {
    // If its not a QS bar, load the source from the user function
    new_source = GetSource(date);
  }
  if (new_source == "") {
    end_of_stream_ = true;
    return false;
  }
  if (source_ != new_source && new_source != "") {
    // If a new file, reset the EOS flag:
    end_of_stream_ = false;
    // Set the new source.
    source_ = new_source;
    // Close out the last source file.
    Dispose();
    reader_.reset(GetReader(source_, (is_qs_data_ &&
                                      Config::GetBool("local"))));
    if (reader_ == NULL) {
      LOG(ERROR) << "Failed to get StreamReader for data source(" + source_
          + "), symbol(" + mapped_symbol_ + "). Skipping date(" +
          date.ToString() + "). Reader is null.";
      return false;
    }
    MoveNext();
  }
  return true;
}

void SubscriptionDataReader::Dispose() {
  if (reader_ != NULL) {
    reader_->Close();
    reader_->Dispose();
  }
}

string SubscriptionDataReader::GetSource(const DateTime& date) {
  string new_source = "";
  new_source = data_factory_->GetSource(*config_, date, feed_endpoint_);
  return new_source;
}

string SubscriptionDataReader::GetQuantSystemSource(const DateTime& date) {
  string source = "";
  TickType data_type = kTrade;
  switch (feed_endpoint_) {
    case DataFeedEndpoint::kBacktesting:
    case DataFeedEndpoint::kFileSystem:
      source = StrCat("./data/",
                      strings::ToLower(SecurityType::SecurityTypeToString(
          config_->security)));
      source += StrCat("/", strings::ToLower(
          Resolution::ResolutionToString(config_->resolution)),
                       "/", strings::ToLower(config_->symbol));
      source += StrCat("/", date.ToShortString(),
                       "_", strings::ToLower(TickTypeToString(data_type)),
                       ".zip");
      break;
    case DataFeedEndpoint::kLiveTrading:
      source = "";
      break;
  }
  return source;
}

SubscriptionStreamReader* SubscriptionDataReader::GetReader(
    const string& source,
    bool qs_file) {
  const string kCache = "./cache/data";
  SubscriptionStreamReader* reader = NULL;
  if (!File::Exists(kCache)) {
    common::util::Status status =
        File::RecursivelyCreateDirWithPermissions(kCache, S_IRWXU);
    if (!status.ok()) {
      LOG(FATAL) << "Could not create " << kCache;
      return NULL;
    }
  }
  string extension = GetExtension(source);
  string filename = config_->symbol + extension;
  string location = kCache + "/" + filename;
  switch (feed_endpoint_) {
    case DataFeedEndpoint::kFileSystem:
    case DataFeedEndpoint::kBacktesting:
      if (qs_file) {
        if (!File::Exists(source)) {
          LOG(INFO) << "Could not find QS Data, skipped: " << source;
          result_handler_->SamplePerformance(date_, 0);
          return NULL;
        }
        // Data source is also location of raw file; root /data directory.
        location = source;
      } else {
        CurlProcessor curl_processor;
        bool status = curl_processor.Download(source, location);
        if (!status) {
          result_handler_->ErrorMessage(
              "Error downloading custom data source file, skipped: " + source);
          result_handler_->SamplePerformance(date_, 0);
        }
      }
      if (File::Exists(location)) {
        if (extension == ".zip") {
          istream *is = compression::Unzip(location);
          if (is == NULL) {
            LOG(ERROR) << "Fail to unzip the file: " << location;
            return NULL;
          }
          reader = new SubscriptionStreamReader(is, feed_endpoint_);
        } else {
          // Custom file stream: open from disk
          reader = new SubscriptionStreamReader(location, feed_endpoint_);
        }
      }
      break;
    case DataFeedEndpoint::kLiveTrading:
      reader = new SubscriptionStreamReader(location, feed_endpoint_);
      break;
  }
  return reader;
}

BaseData* SubscriptionDataReader::GetDataFactory(const string& type_name) {
  BaseData* data_factory = NULL;
  if (type_name == typeid(Tick).name()) {
    data_factory = new Tick();
  } else if (type_name == typeid(TradeBar).name()) {
    data_factory = new TradeBar();
  } else if (type_name == typeid(Quandl).name()) {
    data_factory = new Quandl();
  } else {
    LOG(FATAL) << "There is no base type:" << type_name;
  }
  return data_factory;
}

string SubscriptionDataReader::GetExtension(const string& str) {
  const vector<string> allowed_ext = {".zip", ".csv", ".json"};
  for (int i = 0; i < allowed_ext.size(); ++i) {
    if (str.find(allowed_ext[i]) != string::npos) {
      return allowed_ext[i];
    }
  }
  return ".custom";
}

}  // namespace engine
}  // namespace quantsystem
