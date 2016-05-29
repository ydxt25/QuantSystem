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

#ifndef QUANTSYSTEM_ENGINE_SUBSCRIPTION_DATA_READER_H_
#define QUANTSYSTEM_ENGINE_SUBSCRIPTION_DATA_READER_H_

#include <map>
using std::map;
#include <string>
using std::string;
#include <memory>
using std::shared_ptr;
#include "quantsystem/common/global.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/data/base_data.h"
#include "quantsystem/common/base/scoped_ptr.h"
#include "quantsystem/common/securities/security.h"
#include "quantsystem/engine/subscription_stream_reader.h"
#include "quantsystem/common/data/subscription_data_config.h"
#include "quantsystem/engine/subscription_scaling.h"
#include "quantsystem/engine/results/iresult_handler.h"
namespace quantsystem {
using data::BaseData;
using securities::Security;
using data::SubscriptionDataConfig;
using engine::results::IResultHandler;
namespace engine {
/**
 * Subscription data reader is a wrapper on the stream reader class to download,
 * unpack and iterate over a data file.
 * @ingroup EngineLayer
 */
class SubscriptionDataReader {
 public:
  /**
   * Subscription data reader takes a subscription request, loads the type,
   * accepts the data source and enumerate on the results.
   * @param config Subscription configuration object
   * @param security Security asset
   * @param feed Feed type enum
   * @param period_start Start date for the data request/backtest
   * @param period_finish Finish date for the data request/backtest
   */
  SubscriptionDataReader(SubscriptionDataConfig* config,
                         Security* security,
                         DataFeedEndpoint::Enum feed,
                         const DateTime& period_start,
                         const DateTime& period_finish,
                         IResultHandler* result_handler);

  virtual  ~SubscriptionDataReader();
  /**
   * Try and create a new instance of the object and return it using
   * the MoveNext
   * enumeration pattern.
   *
   * This is a highly called method and should be kept lean as possible.
   * @return Boolean true on successful move next. Set current public property.
   */
  bool MoveNext();

  /**
   * For backwards adjusted data the price is adjusted by a scale factor
   * which is a combination of splits and dividends.
   * This backwards adjusted price
   * is used by default and fed as the current price.
   * @param date Current date of the backtest
   */
  void UpdateScaleFactors(const DateTime& date);

  /**
   * Check if this time is open for this subscription.
   * @param time Date and time we're checking to see if the market is open
   * @return Boolean true on market open
   */
  bool MarketOpen(const DateTime& time) const;

  /**
   * Check if we're still in the extended market hours.
   * @param time Time to scan
   * @return True on extended market hours
   */
  bool ExtendedMarketOpen(const DateTime& time) const;

  /**
   * Fetch and set the location of the data from the user's BaseData factory.
   * @param date Date of the source file
   * @return Boolean true on successfully retrieving the data
   */
  bool RefreshSource(const DateTime& date);

  /**
   * Dispose of the Stream Reader and close out the source
   * stream and file connections.
   */
  void Dispose();

  /**
   * Get the source URL string for this datetime from the users
   * GetSource() method in BaseData.
   * @param date DateTime we're requesting
   * @return URL string of the source file
   */
  string GetSource(const DateTime& date);

  /**
   * Get the source location of this QuantSystem data request.
   * @param date Date to retrieve
   * @return String source
   */
  string GetQuantSystemSource(const DateTime& date);

  /**
   * Source has been completed, load up next stream or stop asking for data.
   */
  bool EndOfStream() const {
    return end_of_stream_ || reader_ == NULL;
  }

  BaseData* current() const { return current_.get(); }

  BaseData* previous() const { return previous_.get(); }

  bool is_qs_tick() const { return is_qs_tick_; }

  bool is_qs_tradebar() const { return is_qs_tradebar_; }

 private:
  // Last read BaseData object from this type and source
  shared_ptr<BaseData> current_;
  // Save an instance of the previous basedata we generated
  shared_ptr<BaseData> previous_;
  // Simple flag to show if this is a QS data type
  bool is_qs_tick_;
  bool is_qs_tradebar_;
  // Source string to create memory stream
  string source_;
  // Default true to fillforward for this subscription, take the previous result
  // and continue returning it till the next time barrier
  bool is_fill_forward_;
  // Date of this source file
  DateTime date_;
  // End of stream from the reader
  bool end_of_stream_;
  // Internal stream reader for processing data line by line:
  scoped_ptr<SubscriptionStreamReader> reader_;
  // Configuration of the data-reader
  SubscriptionDataConfig* config_;
  // Subscription Securities Access
  Security* security_;
  IResultHandler* result_handler_;
  // Save security type of speed
  bool is_qs_equity_;
  // Subscription is for a QS type
  bool is_qs_data_;
  // Price factor mapping
  SubscriptionAdjustment::FactorTableType price_factors_;
  double price_factor_;
  // Symbol Mapping
  SubscriptionAdjustment::MapTableType symbol_map_;
  string mapped_symbol_;
  //  Location of the datafeed - the type of this data
  DataFeedEndpoint::Enum feed_endpoint_;
  scoped_ptr<BaseData> data_factory_;
  // Start finish times of the backtest
  DateTime period_start_;
  DateTime period_finish_;
  // Remember edge conditions as market enters/leaves open-closed.
  shared_ptr<BaseData> last_bar_of_stream_;
  shared_ptr<BaseData> last_bar_outside_market_hours_;

  void set_current(BaseData* current) {
    current_.reset(current);
  }

  void set_previous(BaseData* previous) {
    previous_ .reset(previous);
  }

  void set_is_qs_tick(bool is_qs_tick) {
    is_qs_tick_ = is_qs_tick;
  }

  void set_is_qs_tradebar(bool is_qs_tradebar) {
    is_qs_tradebar_ = is_qs_tradebar;
  }

  /**
   * Using this source URL, download it to our cache and open a local reader.
   * @param source Source URL for the data
   * @param qs_file Boolean if this is a QS managed data file,
   * if so can look in QS store
   * @return StreamReader for the data source
   */
  SubscriptionStreamReader* GetReader(const string& source,
                                      bool qs_file = false);

  /**
   * Stream the file over the net directly from its source.
   * @param source Source URL for the file
   * @return StreamReader Interface for the data source
   */
  // StreamReader* WebReader(const string& source);

  BaseData* GetDataFactory(const string& type_name);

  string GetExtension(const string& str);
};

}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_SUBSCRIPTION_DATA_READER_H_
