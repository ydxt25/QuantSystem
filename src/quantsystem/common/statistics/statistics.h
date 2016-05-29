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
 * @defgroup CommonBaseStatistics Common - Base Statistics Components
 *
 * The Base statistic components of Quantsystem.
 */
#ifndef QUANTSYSTEM_COMMON_STATISTICS_STATISTICS_H_
#define QUANTSYSTEM_COMMON_STATISTICS_STATISTICS_H_

#include <map>
using std::map;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include "quantsystem/common/time/date_time.h"
#include "quantsystem/common/util/charting.h"

namespace quantsystem {
namespace statistics {
/**
 * Calculate all the statistics required from the backtest,
 * based on the equity curve and the profit loss statement.
 * @ingroup CommonBaseStatistics
 */
class Statistics {
 public:
  typedef map<DateTime, double> SortBenchmarkMap;
  typedef vector<ChartPoint> ChartPointVector;
  /**
   * Standard constructor.
   */
  Statistics();

  /**
   * Standard destructor.
   */
  virtual ~Statistics();

  /**
   * Retrieve a static S-P500 Benchmark for the statistics calculations.
   * Update the benchmark once per day.
   */
  static SortBenchmarkMap Benchmark();

  /**
   * Run a full set of orders and return a Map of statistics.
   * @param points_equity Equity value over time
   * @param points_performance Daily performance
   * @param porfit_loss Profit loss from trades
   * @param starting_cash Amount of starting cash in USD
   * @param statistics[out] the statistics results
   * @param trading_days_per_year Number of trading days per year
   
   * @return Statistics array, broken into annual periods.
   */
  static void Generate(
      const ChartPointVector& points_equity,
      const SortBenchmarkMap& profit_loss,
      const ChartPointVector& points_performance, double starting_cash,
      map<string, string>* statistics,
      double trading_days_per_year = 252);

  /**
   * Return profit loss ratio safely avoiding divide by zero errors.
   */
  static double ProfitLossRatio(double average_win, double average_loss);

  /**
   * Get the drawdown dtatistic for this period from the equity curve.
   * @param equity_over_time Array of portfolio value over time
   * @param rounding Round the drawdown statistics
   * @return Draw down percentage over period
   */
  static double DrawDown(SortBenchmarkMap equity_over_time, int rouding = 2);

  /**
   * Annual compounded returns statistic based on the final-starting
   * capital and years.
   * @param starting_capital Algorithm starting capital
   * @param final_capital Algorithm final capital
   * @param years Years trading
   * @return Double fraction for annual compounding performance
   */
  static double CompoundingAnnualPerformance(double starting_capital,
                                             double final_capital,
                                             double years);

  /**
   * Annualized return statistic calculated as an average of daily trading
   * performance multiplied by the number of trading days per year.
   * May be unaccurate for forex algorithms with more trading days in a year.
   * @param performance Collection of double performance values
   * @param trading_days_per_year Trading days per year for
   * the assets in portfolio
   * @return Double annual performance percentage
   */
  static double AnnualPerformance(const vector<double> performance,
                                  double trading_days_per_year = 252);

  /**
   * Annualized variance statistic calculation using the daily
   * performance variance and trading days per year.
   * @param performance Collection of double performance values
   * @param trading_days_per_year Trading days per year for the assets
   * @return Annual variance value
   */
  static double AnnualVariance(const vector<double>& performance,
                               double trading_days_per_year = 252);

  /**
   * Annualized standard deviation
   * @param performance Collection of double performance values
   * @param trading_days_per_year Trading days per year for the assets
   * @return Value for annual standard deviation
   */
  static double AnnualStandardDeviation(
      const vector<double>& performance,
      double trading_days_per_year = 252);

  /**
   * Algorithm "beta" statistic - the covariance between the algorithm
   * and benchmark performance, divided by benchmark's variance.
   * @param algo_performance Collection of values for algorithm
   * daily performance
   * @param benchmark_performance Collection of benchmark daily
   * performance values
   * @return Value for beta
   */
  static double Beta(const vector<double>& algo_performance,
                     const vector<double>& benchmark_performance);

  /**
   * Algorithm "Alpha" statistic - abnormal returns over the risk
   * free rate and the relationshio (beta) with the benchmark returns.
   * @param algo_performance Collection of values for algorithm
   * daily performance
   * @param benchmark_performance Collection of benchmark daily
   * performance values
   * @param risk_free_rate Risk free rate of return for the T-Bonds
   * @return Value for alpha
   */
  static double Alpha(const vector<double>& algo_performance,
                      const vector<double>& benchmark_performance,
                      double risk_free_rate);

  /**
   * Tracking error volatility (TEV) statistic - a measure of how closely
   * a portfolio follows the index to which it is benchmarked.
   * If algo = benchmark, TEV = 0.
   * @param algo_performance Collection of values for algorithm
   * daily performance
   * @param benchmark_performance Collection of benchmark daily
   * performance values
   * @return Value for tracking error
   */
  static double TrackingError(
      const vector<double>& algo_performance,
      const vector<double>& benchmark_performance);

  /**
   * Information ratio - risk adjusted return.
   * (risk = tracking error volatility, a volatility measures that considers
   * the volatility of both algo and benchmark),
   * @param algo_performance Collection of values for algorithm
   * daily performance
   * @param benchmark_performance Collection of benchmark daily
   * performance values
   * @return Value for information ratio
   */
  static double InformationRatio(
      const vector<double>& algo_performance,
      const vector<double>& benchmark_performance);

  /**
   * Sharpe ratio with respect to risk free rate: measures excess of
   * return per unit of risk.
   * With risk defined as the algorithm's volatility.
   * @param algo_performance Collection of values for algorithm
   * daily performance
   * @param risk_free_rate Risk free rate of return for the T-Bonds
   * @return Value for sharpe ratio
   */
  static double SharpeRatio(
      const vector<double>& algo_performance,
      double risk_free_rate);

  /**
   * Treynor ratio statistic is a measurement of the returns earned in
   * excess of that which could have been earned on an investment
   * that has no diversifiable risk.
   * @param algo_performance Collection of values for algorithm
   * daily performance
   * @param benchmark_performance Collection of benchmark daily
   * performance values
   * @param risk_free_rate Risk free rate of return for the T-Bonds
   * @return Double Treynor ratio
   */
  static double TreynorRatio(
      const vector<double>& algo_performance,
      const vector<double>& benchmark_performance,
      double risk_free_rate);

 private:
  DateTime benchmark_age_;
  SortBenchmarkMap benchmark_;

  /**
   * Convert the charting data into an equity array.
   * This is required to convert the equity plot into a usable form
   * for the statistics calculation,
   * @param points ChartPoints vector
   * @return Sorted map of the equity double values ordered in time.
   */
  static SortBenchmarkMap ChartPointToMap(vector<ChartPoint> points);
};

}  // namespace statistics
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_STATISTICS_STATISTICS_H_
