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

#include "quantsystem/common/statistics/statistics.h"
namespace quantsystem {
namespace statistics {
Statistics::Statistics() {
}

Statistics::~Statistics() {
}

Statistics::SortBenchmarkMap Statistics::Benchmark() {
}

void Statistics::Generate(
      const ChartPointVector& points_equity,
      const SortBenchmarkMap& profit_loss,
      const ChartPointVector& points_performance, double starting_cash,
      map<string, string>* statistics,
      double trading_days_per_year) {
}
  
double Statistics::ProfitLossRatio(
    double average_win, double average_loss) {
}

double Statistics::DrawDown(
    SortBenchmarkMap equity_over_time, int rounding) {
}

double Statistics::CompoundingAnnualPerformance(double starting_capital,
                                                double final_capital,
                                                double years) {
}

double Statistics::AnnualPerformance(const vector<double> performance,
                                     double trading_days_per_year) {
}

double Statistics::AnnualVariance(const vector<double>& performance,
                                  double trading_days_per_year) {
}

double Statistics::AnnualStandardDeviation(
    const vector<double>& performance,
    double trading_days_per_year) {
}

double Statistics::Beta(const vector<double>& algo_performance,
                        const vector<double>& benchmark_performance) {
}

double Statistics::Alpha(const vector<double>& algo_performance,
                         const vector<double>& benchmark_performance,
                         double risk_free_rate) {
}

double Statistics::TrackingError(
    const vector<double>& algo_performance,
    const vector<double>& benchmark_performance) {
}

double Statistics::InformationRatio(
    const vector<double>& algo_performance,
    const vector<double>& benchmark_performance) {
}

double Statistics::SharpeRatio(
    const vector<double>& algo_performance,
    double risk_free_rate) {
}

double Statistics::TreynorRatio(
    const vector<double>& algo_performance,
    const vector<double>& benchmark_performance,
    double risk_free_rate) {
}

Statistics::SortBenchmarkMap Statistics::ChartPointToMap(
    vector<ChartPoint> points) {
}

}  // namespace statistics
}  // namespace quantsystem
