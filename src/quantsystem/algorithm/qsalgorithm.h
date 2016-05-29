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
 * @defgroup AlgorithmLayer Algorithm Layer
 *
 * The QuantSystem Algorithm layer.
 */
#ifndef QUANTSYSTEM_ALGORITYM_QSALGORITHM_H_
#define QUANTSYSTEM_ALGORITYM_QSALGORITHM_H_

#include <glog/logging.h>
#include <typeinfo>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include "quantsystem/interfaces/ialgorithm.h"
#include "quantsystem/common/global.h"
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/util/charting.h"
#include "quantsystem/common/orders/order.h"
#include "quantsystem/common/orders/order_event.h"
#include "quantsystem/common/data/subscription_manager.h"
#include "quantsystem/common/data/market/ticks.h"
#include "quantsystem/common/data/market/tradebars.h"
#include "quantsystem/common/data/consolidators/data_consolidator.h"
#include "quantsystem/common/securities/security_manager.h"
#include "quantsystem/common/securities/security_portfolio_manager.h"
#include "quantsystem/common/securities/security_transaction_manager.h"
#include "quantsystem/indicators/indicator_base.h"
#include "quantsystem/indicators/indicator_data_point.h"
#include "quantsystem/indicators/average_true_range.h"
#include "quantsystem/indicators/moving_average_type.h"
#include "quantsystem/indicators/exponential_indicator.h"
#include "quantsystem/indicators/simple_moving_average.h"
#include "quantsystem/indicators/moving_average_converagence_divergence.h"
#include "quantsystem/indicators/maximum.h"
#include "quantsystem/indicators/minimum.h"
#include "quantsystem/indicators/aroon_oscillator.h"
#include "quantsystem/indicators/momentum.h"
#include "quantsystem/indicators/momentum_percent.h"
#include "quantsystem/indicators/relative_strength_index.h"
namespace quantsystem {
using interfaces::IAlgorithm;
using orders::Order;
using orders::OrderEvent;
using orders::OrderType;
using data::SubscriptionManager;
using data::market::Ticks;
using data::market::TradeBars;
using data::consolidators::DataConsolidator;
using securities::SecurityManager;
using securities::SecurityPortfolioManager;
using securities::SecurityTransactionManager;
using indicators::AverageTrueRange;
using indicators::ExponentialMovingAverage;
using indicators::SimpleMovingAverage;
using indicators::MovingAverageConvergenceDivergence;
using indicators::Maximum;
using indicators::Minimum;
using indicators::AroonOscillator;
using indicators::Momentum;
using indicators::MomentumPercent;
using indicators::RelativeStrengthIndex;
using indicators::IndicatorBase;
using indicators::IndicatorDataPoint;
namespace algorithm {
/**
 * QS Algorithm Base Class - Handle the basic requirements of a
 * trading algorithm, allowing user to focus on event methods.
 * The QSAlgorithm class implements Portfolio, Securities, Transactions and
 * Data Subscription Management.
 * @ingroup AlgorithmLayer
 */
class QSAlgorithm : public IAlgorithm {
 public:
  /**
   * QSAlgorithm Base Class Constructor - Initialize the underlying
   * QSAlgorithm components.
   * QSAlgorithm manages the transactions, portfolio, charting and
   * security subscriptions for the users algorithms.
   */
  QSAlgorithm();

  /**
   * Standard destructor.
   */
  virtual ~QSAlgorithm();

  /**
   * Initialise the Algorithm and Prepare Required Data.
   */
  virtual void Initialize() {
    LOG(FATAL) << "Please override the Intitialize() method";
  }

  /**
   * Event handler for general data subscriptions.
   * @param data List of base data.
   */
  virtual void OnData(const BaseData* data) {
  }

  /**
   * Event handler for TradeBar data subscriptions packets.
   * @param data List of trade bar data.
   */
  virtual void OnData(const TradeBars* data) {
  }

  /**
   * Event handler for Tick data subscriptions.
   * @param data List of Tick data.
   */
  virtual void OnData(const Ticks* data) {
  }

  /**
   * Send debug message.
   * @param message Debug message
   */
  virtual void Debug(const string& message);

  /**
   * Save entry to the Log.
   * @param message Log message
   */
  virtual void Log(const string& message);

  /**
   * Send an error message for the algorithm
   * @param message Error message
   */
  virtual void Error(const string& message);

  /**
   * Call this method at the end of each day of data.
   */
  virtual void OnEndOfDay() {
  }

  /**
   * Call this method at the end of each day of data.
   */
  virtual void OnEndOfDay(const string& symbol) {
  }

  /**
   * Call this event at the end of the algorithm running.
   */
  virtual void OnEndOfAlgorithm() {
  }

  /**
   *  New order event handler: on order status changes
   * (filled, partially filled, cancelled etc).
   * @param new_event Event information
   */
  virtual void OnOrderEvent(const OrderEvent* new_event) {
  }

  /**
   * Set the DateTime Frontier: This is the master time.
   */
  virtual void SetDateTime(const DateTime& time) {
    time_ = time;
  }

  /**
   * Set the start date of the backtest period.
   * This must be within available data.
   */
  virtual void SetStartDate(int year, int month, int day) {
    SetStartDate(DateTime(year, month, day));
  }

  /**
   * Alias for SetStartDate() which accepts DateTime Class
   */
  virtual void SetStartDate(const DateTime& start);

  /**
   * Set the end Backtest date for the algorithm.
   * This must be within available data.
   */
  virtual void SetEndDate(int year, int month, int day) {
    SetEndDate(DateTime(year, month, day));
  }

  /**
   * Alias for SetStartDate() which accepts DateTime Object.
   */
  virtual void SetEndDate(const DateTime& end);

  /* Set the algorithm Id for this backtest or live run.
   * This can be used to identify the order and equity records.
   * @param algorithm_id Unique 32 character identifier
   * for backtest or live server
   */
  virtual void SetAlgorithmId(const string& algorithm_id) {
    algorithm_id_ = algorithm_id;
  }

  /**
   * Set the algorithm as initialized and locked.
   * No more cash or security changes.
   */
  virtual void SetLocked() {
    locked_ = true;
  }

  /**
   * Add specified data to our data subscriptions.
   * @param security_type Enum: Equity, Commodity, FOREX or Future
   * @param symbol Symbol Representation of the MarketType, e.g. AAPL
   * @param resolution Resolution of the MarketType required:
   * MarketData, Second or Minute
   * @param fill_data_forward If true, returns the last available
   * data even if none in that timeslice.
   * @param extended_market_hours Send in data from 4am-8pm, not used for FOREX
   */
  void AddSecurity(SecurityType::Enum security_type,
                   const string& symbol,
                   Resolution::Enum resolution = Resolution::kMinute,
                   bool fill_data_forward = true,
                   bool extended_market_hours = false) {
    AddSecurity(security_type, symbol, resolution, fill_data_forward, 0,
                extended_market_hours);
  }

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
                           bool extended_market_hours);

  /**
   * AddData-typeparam name="T"- a new user defined data source,
   * requiring only the minimum config options.
   * @param symbol Key/Symbol for data
   * @param resolution Resolution of the data
   */
  template <typename T>
  void AddData(const string& symbol,
                       Resolution::Enum resolution = Resolution::kSecond) {
    if (locked_) {
      return;
    }
    // Add this to the data-feed subscriptions
    subscription_manager_->Add(typeid(T).name(), SecurityType::kBase,
                               symbol, resolution, false, true);
    // Add this new generic data as a tradeable security:
    // Defaults:extended market hours" = true because we want events 24 hours,
    //          fillforward = false because only want to trigger
    //          when there's new custom data.
    //          leverage = 1 because no leverage on nonmarket data
    securities_->Add(symbol, SecurityType::kBase, resolution,
                     false, 1, true, false);
  }

  /**
   * Set the starting capital for the strategy.
   * @param starting_cash Starting capital, default $100,000
   */
  virtual void SetCash(double starting_cash);

  /**
   * Terminate the algorithm on exiting the current event processor.
   * If have holdings at the end of the algorithm/day they will be
   * liquidated at market prices. If running a series analysis this command
   * skips the current day (and doesn't liquidate).
   * @param message Exit message
   */
  virtual void Quit(const string& message = "") {
    Debug("Quit():" + message);
    quit_ = true;
  }

  /**
   * Set the quit flag true / false.
   * @param quit When true quits the algorithm event loop for this day
   */
  virtual void SetQuit(bool quit) { quit_ = quit; }

  /**
   * Enable Algorithm Live Mode.
   * @param live Live state
   */
  virtual void SetLiveMode(bool live) {
    if (!locked_) {
      live_mode_ = live;
    }
  }

  /**
   * Get the quit flag state.
   * @return Boolean quit flag
   */
  virtual bool GetQuit() { return quit_; }

  ///////////////// Indicators /////////////////////////////////
  /**
   * Creates a new AverageTrueRange indicator for the symbol.
   * The indicator will be automatically updated on the given resolution.
   *
   * @param symbol The symbol whose ATR we want
   * @param period The smoothing period used to smooth the computed
   * TrueRange values
   * @param resolution The resolution
   * @param type The type of smoothing to use
   * @return A new AverageTrueRange indicator with the specified
   * smoothing type and period
   */
  AverageTrueRange* ATR(
      const string& symbol, int period,
      Resolution::Enum resolution,
      indicators::MovingAverageType type = indicators::kSimple);

  /**
   * Creates an ExponentialMovingAverage indicator for the symbol.
   * The indicator will be automatically updated on the given resolution.
   *
   * @param symbol The symbol whose EMA we want
   * @param period The period of the EMA
   * @param resolution The resolution
   * @return The ExponentialMovingAverage for the given parameters
   */
  ExponentialMovingAverage* EMA(const string& symbol, int period,
                               Resolution::Enum resolution);

  /**
   * Creates an SimpleMovingAverage indicator for the symbol.
   * The indicator will be automatically updated on the given resolution.
   *
   * @param symbol The symbol whose SMA we want
   * @param period The period of the SMA
   * @param resolution The resolution
   * @return The SimpleMovingAverage for the given parameters
   */
  SimpleMovingAverage* SMA(const string& symbol, int period,
                           Resolution::Enum resolution);

  /**
   * Creates a MACD indicator for the symbol. The indicator will be
   * automatically updated on the given resolution.
   *
   * @param symbol The symbol whose MACD we want
   * @param fast_period The period for the fast moving average
   * @param slow_period The period for the slow moving average
   * @param signal_period The period for the signal moving average
   * @param resolution The resolution
   * @param type The type of moving average to use for the MACD
   * @return The moving average convergence divergence
   * between the fast and slow averages
   */
  MovingAverageConvergenceDivergence* MACD(
      const string& symbol,
      int fast_period, int slow_period,
      int signal_period,
      Resolution::Enum resolution,
      indicators::MovingAverageType type = indicators::kSimple);

  /**
   * Creates a new Maximum indicator to compute the maximum value.
   *
   * @param symbol The symbol whose max we want
   * @param period The look back period over which to compute the max value
   * @param resolution The resolution
   * @return A Maximum indicator that compute the max value
   * and the periods since the max value
   */
  Maximum* MAX(const string& symbol, int period, Resolution::Enum resolution);

  /**
   * Creates a new Minimum indicator to compute the minimum value.
   *
   * @param symbol The symbol whose min we want
   * @param period The look back period over which to compute the min value
   * @param resolution The resolution
   * @return A Minimum indicator that compute the in value
   * and the periods since the min value
   */
  Minimum* MIN(const string& symbol, int period, Resolution::Enum resolution);

  /**
   * Creates a new AroonOscillator indicator which will compute
   * the AroonUp and AroonDown (as well as the delta).
   *
   * @param symbol The symbol whose Aroon we seek
   * @param period The look back period for computing number of periods
   * since maximum and minimum
   * @param resolution The resolution
   * @return An AroonOscillator configured with the specied periods
   */
  AroonOscillator* AROON(const string& symbol,
                         int period, Resolution::Enum resolution);

  /**
   * Creates a new AroonOscillator indicator which will compute the
   * AroonUp and AroonDown (as well as the delta).
   *
   * @param symbol The symbol whose Aroon we seek
   * @param up_period The look back period for computing number of
   * periods since maximum
   * @param down_period The look back period for computing number of
   * periods since minimum
   * @param resolution The resolution
   * @return An AroonOscillator configured with the specied periods
   */
  AroonOscillator* AROON(const string& symbol,
                         int up_period, int down_period,
                         Resolution::Enum resolution);

  /**
   * Creates a new Momentum indicator. This will compute the absolute
   * n-period change in the security. The indicator will be automatically
   * updated on the given resolution.
   *
   * @param symbol The symbol whose momentumwe want
   * @param period The period over which to compute the momentum
   * @param resolution The resolution
   * @return The momentum indicator for the requested symbol over
   * the specified period
   */
  Momentum* MOM(const string& symbol, int period, Resolution::Enum resolution);

  /**
   * Creates a new MomentumPercent indicator. This will compute the
   * n-period percent change in the security.
   *
   * @param symbol The symbol whose momentum we want
   * @param period The period over which to compute the momentum
   * @param resolution The resolution
   * @return The momentum indicator for the requested symbol
   * over the specified period
   */
  MomentumPercent* MOMP(const string& symbol, int period,
                        Resolution::Enum resolution);

  /**
   * Creates a new RelativeStrengthIndex indicator. This will produce
   * an oscillator that ranges from 0 to 100 based on the ratio of
   * average gains to average losses over the specified period.
   *
   * @param symbol The symbol whose RSI we want
   * @param period The period over which to compute the RSI
   * @param resolution The resolution
   * @param moving_average_type The type of moving average to use
   * in computing the average gain/loss values
   * @return The RelativeStrengthIndex indicator for the requested
   * symbol over the speified period
   */
  RelativeStrengthIndex* RSI(const string& symbol, int period,
                             Resolution::Enum resolution,
                             indicators::MovingAverageType moving_average_type = indicators::kSimple);

  /**
   * Creates and registers a new consolidator to receive automatic at
   * the specified resolution as well as configures the indicator to
   * receive updates from the consolidator.
   *
   * @param symbol The symbol to register against
   * @param resolution The resolution at which to send data to the indicator
   * @param indicator[out] The indicator to receive data from the consolidator
   * @param selector Selects a value from the BaseData to send into the
   * indicator, if null defaults to the Value property of BaseData
   * (x => x.Value)
   */
  void RegisterIndicator(
      const string& symbol,
      Resolution::Enum resolution,
      IndicatorBase<IndicatorDataPoint>* indicator,
      const std::function<double(BaseData*)>* selector = NULL) {
    RegisterIndicator(symbol,  indicator,
                      ResolveConsolidator(symbol, resolution), selector);
  }

  /**
   * Registers the consolidator to receive automatic updates as well as
   * configures the indicator to receive updates from the consolidator.
   *
   * @param symbol The symbol to register against
   * @param indicator[out] The indicator to receive data from the consolidator
   * @param consolidator[out] The consolidator to receive raw subscription data
   * @param selector Selects a value from the BaseData to send into the
   * indicator, if null defaults to the Value property of BaseData
   * (x => x.Value)
   */
  void RegisterIndicator(const string& symbol,
                         IndicatorBase<IndicatorDataPoint>* indicator,
                         DataConsolidator* consolidator,
                         const std::function<double(BaseData*)>* selector= NULL);

  ///////////////// Plotting  /////////////////////////////////
  /**
   * Add a chart to the internal algorithm list.
   * @param chart Chart object to add
   */
  virtual void AddChart(Chart* chart);

  /**
   * Get the chart updates since the last request:
   * @param charts[out] Vector of Chart Updates
   */
  virtual void GetChartUpdates(vector<Chart>* charts);

  ///////////////// Trading  /////////////////////////////////
  virtual map<int, Order> Orders() const {
  }

  /**
   * Buy stock.
   *
   * @param symbol Symbol of the asset to trade
   * @param quantity Quantity of the asset to trade
   */
  int Buy(const string& symbol, int quantity) {
    return SendOrder(symbol, quantity);
  }

  /**
   * Sell stock.
   * @param symbol Symbol of the asset to trade
   * @param quantity Quantity of the asset to trade
   */
  int Sell(const string& symbol, int quantity) {
    return SendOrder(symbol, quantity);
  }

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
                        const string& tag = "");

  /**
   * Liquidate your portfolio holdings.
   * @param symbol_to_liquidate Specific asset to liquidate, defaults to all.
   * @param order_list[out] Vector of order
   */
  virtual void Liquidate(vector<int>* order_list, const string& symbol_to_liquidate = "");

  /**
   * Automatically place an order which will set the holdings to
   * between 100% or -100% of *Buying Power*.
   * E.g. SetHoldings("AAPL", 0.1); SetHoldings("IBM", -0.2);
   * -> Sets portfolio as long 10% APPL and short 20% IBM
   *
   * @param symbol Symbol we want to purchase
   * @param percentage Fraction of portfolio to set stock
   * @param liquidate_existing_holdings Bool flag to clean all existing
   * holdings before setting new faction
   * @param tage Tag the order with a short string
   */
  void SetHoldings(const string& symbol,
                   double percentage,
                   bool liquidate_existing_holdings = false,
                   const string& tag = "");

 protected:
  bool locked_;
  bool quit_;

  // Error tracking to avoid message flooding
  string previous_debug_message_;
  string previous_error_message_;
  bool sent_no_data_error_;

  // plotting
  typedef map<string, Chart*> ChartsMap;
  ChartsMap charts_;

  /**
   * Gets the default consolidator for the specified symbol and resolution
   *
   * @param symbol The symbol whose data is to be consolidated
   * @param resolution The resolution for the consolidator
   * @return The new consolidator
   */
  DataConsolidator* ResolveConsolidator(const string& symbol,
                                         Resolution::Enum resolution);

  /**
   * Creates a new name for an indicator created with the convenience
   * functions (SMA, EMA, ect...).
   * @param symbol symbol The symbol this indicator is register to
   * @param type The indicator type
   * @param resolution The resolution requested
   * @return A unique for the given parameters
   */
  static string CreateIndicatorName(const string& symbol,
                                    const string& type,
                                    Resolution::Enum resolution);
};

}  // namespace algorithm
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ALGORITYM_QSALGORITHM_H_
