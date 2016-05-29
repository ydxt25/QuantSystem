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
 * @defgroup Interfaces Quantsystem interfaces
 *
 * The interfaces for Quantsystem.
 */

#ifndef QUANTSYSTEM_INTERFACES_IALGORITHM_H_
#define QUANTSYSTEM_INTERFACES_IALGORITHM_H_

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include "quantsystem/common/base/scoped_ptr.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/orders/order.h"
#include "quantsystem/common/orders/order_event.h"
#include "quantsystem/common/global.h"
#include "quantsystem/common/util/charting.h"
#include "quantsystem/common/data/subscription_manager.h"
#include "quantsystem/common/data/market/tradebars.h"
#include "quantsystem/common/data/market/ticks.h"
#include "quantsystem/common/securities/security_manager.h"
#include "quantsystem/common/securities/security_portfolio_manager.h"
#include "quantsystem/common/securities/security_transaction_manager.h"

namespace quantsystem {
using orders::Order;
using orders::OrderEvent;
using orders::OrderType;
using data::SubscriptionManager;
using data::market::Ticks;
using data::market::TradeBars;
using securities::SecurityManager;
using securities::SecurityPortfolioManager;
using securities::SecurityTransactionManager;

namespace interfaces {
/**
 * Interface for QuantSystem algorithm implementations.
 * All algorithms must implement these 
 * basic members to allow interaction with the Backtesting Engine.
 * @ingroup Interfaces
 */
class IAlgorithm {
 public:
  IAlgorithm() { }

  virtual ~IAlgorithm() { }

  /**
   * Initialise the Algorithm and Prepare Required Data.
   */
  virtual void Initialize() = 0;

  /**
   * Event handler for general data subscriptions.
   * @param data List of base data.
   */
  virtual void OnData(const BaseData* data) = 0;

  /**
   * Event handler for TradeBar data subscriptions packets.
   * @param data List of trade bar data.
   */
  virtual void OnData(const TradeBars* data) = 0;

  /**
   * Event handler for Tick data subscriptions.
   * @param data List of Tick data.
   */
  virtual void OnData(const Ticks* data) = 0;

  /**
   * Send debug message.
   * @param message Debug message
   */
  virtual void Debug(const string& message) = 0;

  /**
   * Save entry to the Log.
   * @param message Log message
   */
  virtual void Log(const string& message) = 0;

  /**
   * Send an error message for the algorithm
   * @param message Error message
   */
  virtual void Error(const string& message) = 0;

  /**
   * Call this method at the end of each day of data.
   */
  virtual void OnEndOfDay() = 0;

  /**
   * Call this method at the end of each day of data.
   */
  virtual void OnEndOfDay(const string& symbol) = 0;

  /**
   * Call this event at the end of the algorithm running.
   */
  virtual void OnEndOfAlgorithm() = 0;

  /**
   *  New order event handler: on order status changes
   * (filled, partially filled, cancelled etc).
   * @param new_event Event information
   */
  virtual void OnOrderEvent(const OrderEvent* new_event) = 0;

  /**
   * Set the DateTime Frontier: This is the master time.
   */
  virtual void SetDateTime(const DateTime& time) = 0;

  /**
   * Set the start date of the backtest period.
   * This must be within available data.
   */
  virtual void SetStartDate(int year, int month, int day) = 0;

  /**
   * Alias for SetStartDate() which accepts DateTime Class
   */
  virtual void SetStartDate(const DateTime& start) = 0;

  /**
   * Set the end Backtest date for the algorithm.
   * This must be within available data.
   */
  virtual void SetEndDate(int year, int month, int day) = 0;

  /**
   * Alias for SetStartDate() which accepts DateTime Object.
   */
  virtual void SetEndDate(const DateTime& end) = 0;

  /* Set the algorithm Id for this backtest or live run.
   * This can be used to identify the order and equity records.
   * @param algorithm_id Unique 32 character identifier
   * for backtest or live server
   */
  virtual void SetAlgorithmId(const string& algorithm_id) = 0;

  /**
   * Set the algorithm as initialized and locked.
   * No more cash or security changes.
   */
  virtual void SetLocked() = 0;

  /**
   * Get the chart updates since the last request:
   * @param charts[out] Vector of Chart Updates
   */
  virtual void GetChartUpdates(vector<Chart>* charts) = 0;

  /**
   * Add a chart to the internal algorithm list.
   * @param chart Chart object to add
   */
  virtual void AddChart(Chart* chart) = 0;

  /**
   * Set a required SecurityType-symbol and resolution for algorithm.
   * @param security_type Enum: Equity, Commodity, FOREX or Future
   * @param symbol Symbol Representation of the MarketType, e.g. AAPL
   * @param resolution Resolution of the MarketType required:
   * MarketData, Second or Minute
   * @param fill_data_forward If true, returns the last available
   * data even if none in that timeslice.
   * @param leverage Leverage for this security
   * @param extended_market_hours Send in data from 4am-8pm, not used for FOREX
   */
  virtual void AddSecurity(SecurityType::Enum security_type,
                           const string& symbol,
                           Resolution::Enum resolution,
                           bool fill_data_forward,
                           double leverage,
                           bool extended_market_hours) = 0;

  /**
   * Set the starting capital for the strategy.
   * @param starting_cash Starting capital, default $100,000
   */
  virtual void SetCash(double starting_cash) = 0;

  /**
   * Send an order to the transaction manager.
   * @param symbol Symbol we want to purchase
   * @param quantity Quantity to buy, + long, - short
   * @param type Market, Limit or Stop Order
   * @param asynchronous Don't wait for the response,
   * just submit order and move on.
   * @param tag Custom data for this order
   * @return Integer Order ID
   */
  virtual int SendOrder(const string& symbol,
                    int quantity,
                    OrderType type = orders::kMarket,
                    bool asynchronous = false,
                    const string& tag = "") {
    }

  /**
   * Liquidate your portfolio holdings.
   * @param symbol_to_liquidate Specific asset to liquidate, defaults to all.
   * @param order_list[out] Vector of order
   */
  virtual void Liquidate(vector<int>* order_list, const string& symbol_to_liquidate = "") {
  }

  /**
   * Terminate the algorithm on exiting the current event processor.
   * If have holdings at the end of the algorithm/day they will be
   * liquidated at market prices. If running a series analysis this command
   * skips the current day (and doesn't liquidate).
   * @param message Exit message
   */
  virtual void Quit(const string& message = "") = 0;

  /**
   * Set the quit flag true / false.
   * @param quit When true quits the algorithm event loop for this day
   */
  virtual void SetQuit(bool quit) = 0;

  /**
   * Enable Algorithm Live Mode.
   * @param live Live state
   */
  virtual void SetLiveMode(bool live) = 0;

  /**
   * Set a runtime statistic for your algorithm- these are displayed
   * on the IDE during live runmode.
   * @param name Key name for the statistic
   * @param value String value for statistic
   */
  virtual void SetRuntimeStatistic(const string& name,
                                   const string& value) {
  }

  /**
   * Get the quit flag state.
   * @return Boolean quit flag
   */
  virtual bool GetQuit() = 0;

  virtual map<int, Order> Orders() const = 0;

  SubscriptionManager* subscription_manager() {
    return subscription_manager_.get();
  }
  void set_subscription_manager(
      SubscriptionManager* subscription_manager) {
    subscription_manager_ .reset(subscription_manager);
  }

  SecurityManager* securities() {
    return securities_.get();
  }
  void set_securites(SecurityManager* securities) {
    securities_.reset(securities);
  }

  SecurityPortfolioManager* portfolio() { return portfolio_.get(); }
  void set_portfolio(SecurityPortfolioManager* portfolio) {
    portfolio_.reset(portfolio);
  }

  SecurityTransactionManager* transactions() { return transactions_.get(); }
  const SecurityTransactionManager* transactions() const { return transactions_.get(); }
  void set_transactions(SecurityTransactionManager* transactions) {
    transactions_.reset(transactions);
  }

  string name() const { return name_; }
  void set_name(const string& name) {
    name_ = name;
  }

  bool processing_order() const { return processing_order_; }
  void set_processing_order(bool processing_order) {
    processing_order_ = processing_order;
  }

  DateTime time() const { return time_; }

  DateTime start_date() const { return start_date_; }

  DateTime end_date() const { return end_date_; }

  string algorithm_id() const { return algorithm_id_; }

  RunMode run_mode() const { return run_mode_; }

  bool live_mode() const { return live_mode_; }

  vector<string>& debug_messages() { return debug_messages_; }
  void set_debug_messages(const vector<string>& debug_messages) {
    debug_messages_ = debug_messages;
  }

  vector<string>& error_messages() { return error_messages_;}
  void set_error_messages(const vector<string> &error_messages) {
    error_messages_ = error_messages;
  }

  vector<string>& log_messages() { return log_messages_; }
  void set_log_messages(const vector<string>& log_messages) {
    log_messages_.clear();
    for (vector<string>::const_iterator it = log_messages.begin();
         it != log_messages.end(); ++it) {
      log_messages_.push_back(*it);
    }
  }

  map<string, string>& runtime_statistics() { return runtime_statistics_; }

 protected:
  // Data subscription manager controls the information and subscriptions
  // the algorithms recieves. Subscription configurations can be
  // added through the Subscription Manager.
  scoped_ptr<SubscriptionManager> subscription_manager_;

  // Security object collection class stores an array of objects
  // representing representing each security/asset we have a subscription for.
  scoped_ptr<SecurityManager> securities_;

  // Security portfolio management class provides wrapper and
  // helper methods for the Security.Holdings class such as
  // IsLong, IsShort, TotalProfit.
  scoped_ptr<SecurityPortfolioManager> portfolio_;

  // Security transaction manager class controls the store and
  // processing of orders.
  // The orders and their associated events are accessible here.
  // When a new OrderEvent is recieved the algorithm portfolio is updated.
  scoped_ptr<SecurityTransactionManager> transactions_;

  // Public name for the algorithm.
  string name_;

  // Property indicating the transaction handler is currently processing
  // an order and the algorithm should wait (syncrhonous order processing).
  bool processing_order_;

  // Current date/time.
  DateTime time_;

  // Algorithm start date for backtesting, set by the SetStartDate methods.
  DateTime start_date_;

  // Requested Backtest End Date.
  DateTime end_date_;

  // AlgorithmId for the backtest
  string algorithm_id_;

  // Run Backtest Mode for the algorithm: Automatic, Parallel or Series.
  RunMode run_mode_;

  // Algorithm is running on a live server.
  bool live_mode_;

  // Debug messages from the strategy
  vector<string> debug_messages_;

  // Error messages from the strategy
  vector<string> error_messages_;

  // Log messages from the strategy
  vector<string> log_messages_;

  // Customizable dynamic statistics displayed during live trading:
  map<string, string> runtime_statistics_;
};

}  // namespace interfaces
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INTERFACES_IALGORITHM_H_
