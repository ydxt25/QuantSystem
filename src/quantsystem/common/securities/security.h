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
 * @defgroup CommonBaseSecurities Common - Base Securities Components
 *
 * Security object is intended to hold properties of the specific security
 * asset. These properties can include trade start-stop dates, price,
 * market hours, resolution of the security, the holdings information
 * for this security and the specific fill model.
 * Base Securities components of Quantsystem.
 */
#ifndef QUANTSYSTEM_COMMON_SECURITIES_SECURITY_H_
#define QUANTSYSTEM_COMMON_SECURITIES_SECURITY_H_

#include <string>
using std::string;
#include "quantsystem/common/global.h"
#include "quantsystem/common/base/scoped_ptr.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/data/base_data.h"
#include "quantsystem/common/data/market/tradebar.h"
#include "quantsystem/common/securities/security_cache.h"
#include "quantsystem/common/securities/security_holding.h"
#include "quantsystem/common/securities/security_exchange.h"
#include "quantsystem/common/securities/interfaces/isecurity_data_filter.h"

namespace quantsystem {
using data::market::TradeBar;
namespace securities {
class ISecurityTransactionModel;
/**
 * A base security class for providing a common interface to all assets
 * in Quantsystem.
 * @ingroup CommonBaseSecurities
 */
class Security {
 public:
  /**
   * Construct a new security based on the user options.
   */
  Security(const string& symbol, SecurityType::Enum type,
           Resolution::Enum resolution, bool fill_data_forward,
           const double& leverage, bool extended_market_hours,
           bool use_quant_system_data = false);

  /**
   * Standard destructor.
   */
  virtual ~Security();

  /**
   * String symobl for the asset.
   */
  string symbol() const { return symbol_; }

  /**
   * Type of the security.
   */
  SecurityType::Enum type() const { return type_; }

  /**
   * Resolution of data requested for this security.
   * Tick, second or minute resolution for the assets.
   */
  Resolution::Enum resolution() const { return resolution_; }

  /**
   * Indicates the data will use previous bars when there
   * was no trading in this time period. This was a configurable
   * datastream setting set in initialization.
   */
  bool is_fill_data_forward() const { return is_fill_data_forward_; }

  /**
   * Indicates the security will continue feeding data after
   * the primary market hours have closed.
   * This was a configurable setting set in initialization.
   */
  bool is_extended_market_hours() const { return is_extended_market_hours_; }

  /**
   * Data cache for the security to store previous price information.
   * 
   * @see EquityCache
   * @see ForexCache
   */
  SecurityCache* cache() const { return cache_.get(); }
  void set_cache(SecurityCache* cache) { cache_.reset(cache); }

  /**
   * Holdings class contains the portfolio, cash and processes order fills.
   * 
   * @see EquityHolding
   * @see ForexHolding
   */
  SecurityHolding* holdings() const { return holdings_.get(); }
  void set_holdings(SecurityHolding* holdings) {
    holdings_.reset(holdings);
  }

  /**
   * Exchange class.
   * @see EquityExchange
   * @see ForexExchange
   */
  SecurityExchange* exchange() const { return exchange_.get(); }
  void set_exchange(SecurityExchange* exchange) {
    exchange_.reset(exchange);
  }

  /**
   * Transaction model class
   * @see EquityTransactionModel
   * @see ForexTransactionModel
   */
  ISecurityTransactionModel* model() const { return model_.get(); }
  void set_model(ISecurityTransactionModel* model) {
    model_.reset(model);
  }

  /**
   * Customizable data filter
   * @see EquityDataFilter
   * @see ForexDataFilter
   */
  ISecurityDataFilter* data_filter() const { return data_filter_.get(); }
  void set_data_filter(ISecurityDataFilter* data_filter) {
    data_filter_.reset(data_filter);
  }

  /**
   * Check if we currently own stock in the company.
   */
  virtual bool HoldStock() const {
    return (holdings_->AbsoluteQuantity()) > 0;
  }

  /**
   * Alias for HoldStock - Do we have any of this security.
   */
  virtual bool Invested() const { return HoldStock(); }

  /**
   * Local time for this market.
   */
  virtual DateTime Time() const { exchange_->Time(); }

  /**
   * Get the current value of the security.
   */
  virtual double Price() const {
    BaseData* data = GetLastData();
    if (data) {
      data->value();
    }
    return 0;
  }

  /**
   * Leverage for this security.
   */
  virtual double leverage() const {
    return leverage_;
  }

  void set_leverage(const double& leverage) { leverage_ = leverage; }

  /**
   * Use QuantSystem data a source flag, or is the security a user
   * imported object.
   */
  virtual bool is_quant_system_data() const { return is_quant_system_data_; }

  /**
   * If this uses tradebar data, return the most recent high.
   */
  virtual double High() const {
    BaseData* data = GetLastData();
    if (!data) {
      return 0;
    }
    if (data->data_type() == MarketDataType::kTradeBar) {
      return (dynamic_cast<TradeBar*>(data))->high();
    }
    return data->value();
  }

  /**
   * If this uses tradebar data, return the most recent low.
   */
  virtual double Low() const {
    BaseData* data = GetLastData();
    if (!data) {
      return 0;
    }
    if (data->data_type() == MarketDataType::kTradeBar) {
      return (dynamic_cast<TradeBar*>(data))->low();
    }
    return data->value();
  }

  /**
   * If this uses tradebar data, return the most recent close.
   */
  virtual double Close() const {
    BaseData* data = GetLastData();
    if (!data) {
      return 0;
    }
    return data->value();
  }

  /**
   * If this uses tradebar data, return the most recent open.
   */
  virtual double Open() const {
    BaseData* data = GetLastData();
    if (!data) {
      return 0;
    }
    if (data->data_type() == MarketDataType::kTradeBar) {
      return (dynamic_cast<TradeBar*>(data))->open();
    }
    return data->value();
  }

  /**
   * Access to the volume of the equity today.
   */
  virtual int64 Volume() const {
    BaseData* data = GetLastData();
    if (!data) {
      return 0;
    }
    if (data->data_type() == MarketDataType::kTradeBar) {
      return (dynamic_cast<TradeBar*>(data))->volume();
    }
    return 0;
  }

  /**
   * Get the last price update set to the securtiy.
   * @return BaseData object for this security.
   */
  BaseData* GetLastData() const {
    return cache_->GetData();
  }

  /**
   * Update any security properties based on the lastest market data and time.
   * @param frontier Time frontier
   * @param data New data packet from Quantsystem.
   */
  void Update(const DateTime& frontier, BaseData* data);

 private:
  string symbol_;
  SecurityType::Enum type_;
  Resolution::Enum resolution_;
  bool is_fill_data_forward_;
  bool is_extended_market_hours_;
  bool is_quant_system_data_;
  double leverage_;
  // Data cache for the security to store previous price information.
  scoped_ptr<SecurityCache> cache_;
  // Holdings class contains the portfolio, cash and processes order fills.
  scoped_ptr<SecurityHolding> holdings_;
  // Exchange class contains the market opening hours,
  // along with pre-post market hours.
  scoped_ptr<SecurityExchange> exchange_;
  // Transaction model class implements the fill models for the security.
  // If the user does not define a model the default model is used for
  // this asset class.
  scoped_ptr<ISecurityTransactionModel> model_;
  // Customizable data filter to filter outlier ticks
  // before they are passed into user event handlers.
  // By default all ticks are passed into the user algorithms.
  scoped_ptr<ISecurityDataFilter> data_filter_;

  Security();
};

}  // namespace securities
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SECURITIES_SECURITY_H_
