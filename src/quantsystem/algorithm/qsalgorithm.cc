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

#include <cstdlib>
#include <utility>
using std::make_pair;
#include <thread>
#include <chrono>
#include "quantsystem/common/strings/case.h"
#include "quantsystem/common/orders/order.h"
#include "quantsystem/algorithm/qsalgorithm.h"
namespace quantsystem {
namespace algorithm {
QSAlgorithm::QSAlgorithm()
    : locked_(false),
      quit_(false),
      sent_no_data_error_(false) {
  run_mode_ = kSeries;
  live_mode_ = false;
  start_date_ = DateTime(1998, 01, 01);
  end_date_ = DateTime() - TimeSpan::FromDays(1);
  securities_.reset(new SecurityManager());
  transactions_.reset(new SecurityTransactionManager(securities_.get()));
  portfolio_.reset(new SecurityPortfolioManager(securities_.get(),
                                                transactions_.get()));
  subscription_manager_.reset(new SubscriptionManager());
}

QSAlgorithm::~QSAlgorithm() {
}

void QSAlgorithm::Debug(const string& message) {
  if (!live_mode_ && (message == "" || previous_debug_message_ == message)) {
    return;
  }
  error_messages_.push_back(message);
  previous_debug_message_ = message;
}

void QSAlgorithm::Log(const string& message) {
  if (message == "") {
    return;
  }
  log_messages_.push_back(message);
}

void QSAlgorithm::Error(const string& message) {
  if (message == "" || previous_error_message_ == message) {
    return;
  }
  error_messages_.push_back(message);
  previous_error_message_ = message;
}

void QSAlgorithm::SetStartDate(const DateTime& start) {
  if (start > end_date_) {
    LOG(ERROR) << "Please select start date less than end date.";
  }
  if (!locked_) {
    start_date_ = start;
  } else {
    LOG(ERROR) << "Cannot change start date after algorithm initialized.";
  }
}

void QSAlgorithm::SetEndDate(const DateTime& end) {
  DateTime last_day = DateTime() - TimeSpan::FromDays(1);
  DateTime end_tmp = end;
  if (end_tmp > last_day) {
    end_tmp = last_day;
  }
  if (end_tmp < start_date_) {
    LOG(ERROR) << "Please select end date greater than start date.";
  }
  if (!locked_) {
    end_date_ = end_tmp;
  } else {
    LOG(ERROR) << "Cannot change end date after algorithm initialized.";
  }
}

void QSAlgorithm::AddSecurity(SecurityType::Enum security_type,
                              const string& symbol,
                              Resolution::Enum resolution,
                              bool fill_data_forward,
                              double leverage,
                              bool extended_market_hours) {
  if (!locked_) {
    if (leverage <= 0) {
      switch (security_type) {
        case SecurityType::kEquity:
          leverage = 2;  // //Cash Ac. = 1, RegT Std = 2 or PDT = 4.
          break;
        case SecurityType::kForex:
          leverage = 50;
          break;
      }
    }
    // Add the symbol to Data Manager -- generate unified data streams
    // for algorithm events
    subscription_manager_->Add(security_type, symbol, resolution,
                               fill_data_forward, extended_market_hours);
    // Add the symbol to Securities Manager -- manage collection of
    // portfolio entities for easy access.
    securities_->Add(symbol, security_type, resolution, fill_data_forward,
                     leverage, extended_market_hours, true);
  } else {
    LOG(ERROR) << "Cannot change add another security"
        "after algorithm initialized.";
  }
}

void QSAlgorithm::SetCash(double starting_cash) {
  if (!locked_) {
    portfolio_->set_cash(starting_cash);
  } else {
    LOG(ERROR) << "Cannot change cash after algorithm initialized.";
  }
}

AverageTrueRange* QSAlgorithm::ATR(
    const string& symbol, int period,
    Resolution::Enum resolution,
    indicators::MovingAverageType type) {
}

ExponentialMovingAverage* QSAlgorithm::EMA(const string& symbol, int period,
                              Resolution::Enum resolution) {
}

SimpleMovingAverage* QSAlgorithm::SMA(const string& symbol, int period,
                         Resolution::Enum resolution) {
}

MovingAverageConvergenceDivergence* QSAlgorithm::MACD(
    const string& symbol,
    int fast_period, int slow_period,
    int signal_period,
    Resolution::Enum resolution,
    indicators::MovingAverageType type) {
}

Maximum* QSAlgorithm::MAX(const string& symbol,
                          int period, Resolution::Enum resolution) {
}

Minimum* QSAlgorithm::MIN(const string& symbol,
                          int period, Resolution::Enum resolution) {
}

AroonOscillator* QSAlgorithm::AROON(const string& symbol,
                                    int period, Resolution::Enum resolution) {
}

AroonOscillator* QSAlgorithm::AROON(const string& symbol,
                                    int up_period, int down_period,
                                    Resolution::Enum resolution) {
}

Momentum* QSAlgorithm::MOM(const string& symbol,
                           int period, Resolution::Enum resolution) {
}

MomentumPercent* QSAlgorithm::MOMP(const string& symbol, int period,
                                   Resolution::Enum resolution) {
}

RelativeStrengthIndex* QSAlgorithm::RSI(
    const string& symbol,
    int period,
    Resolution::Enum resolution,
    indicators::MovingAverageType moving_average_type) {
}

void QSAlgorithm::RegisterIndicator(
    const string& symbol,
    IndicatorBase<IndicatorDataPoint>* indicator,
    DataConsolidator* consolidator,
    const std::function<double(BaseData*)>* selector) {
}

///////////////// Plotting  /////////////////////////////////
void QSAlgorithm::AddChart(Chart* chart) {
  if (charts_.find(chart->name) == charts_.end()) {
    charts_.insert(make_pair(chart->name, chart));
  }
}

void QSAlgorithm::GetChartUpdates(vector<Chart>* charts) {
  for (ChartsMap::const_iterator it = charts_.begin();
       it != charts_.end(); ++it) {
    charts->push_back(it->second->GetUpdates());
  }
}

///////////////// Trading  /////////////////////////////////
int QSAlgorithm::SendOrder(const string& symbol,
                           int quantity,
                           OrderType type,
                           bool asynchronous,
                           const string& tag) {
  int order_id = -1;
  double price = 0;
  if (symbol == "" || quantity == 0) {
    return -1;
  }
  string symbol_up = strings::ToUpper(symbol);
  if (!securities_->ContainsKey(symbol_up) && !sent_no_data_error_) {
    sent_no_data_error_ = true;
    Error("You haven't requested " + symbol +
          " data. Add this with AddSecurity() in the Initialize() Method.");
    return -1;
  }
  price = (*securities_)[symbol_up]->Price();
  if (price == 0) {
    Error("Asset price is $0."
          "If using custom data make sure you've set the 'Value' property.");
    return -1;
  }
  // Check the exchange is open before sending a market order
  if (type == orders::kMarket &&
      !(*securities_)[symbol_up]->exchange()->ExchangeOpen()) {
    Error("Market order and exchange not open");
    return -3;
  }
  // Add the order and create a new order Id
  order_id = transactions_->AddOrder(new Order(symbol, quantity, type, time(),
                                               price, tag));
  // Wait for the order event to process
  if (!asynchronous && type == orders::kMarket) {
    // Wait for the market order to fill
    const securities::OrderMap& orders = transactions_->orders();
    securities::OrderMap::const_iterator it;
    while ((it = orders.find(order_id)) == orders.end() ||
           (it->second->status != orders::kFilled &&
            it->second->status != orders::kInvalid &&
            it->second->status != orders::kCanceled)
           || processing_order_) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }
  return order_id;
}

void QSAlgorithm::Liquidate(vector<int>* order_list,
                            const string& symbol_to_liquidate) {
  if (symbol_to_liquidate == "") {
    return;
  }
  string symbol_to = strings::ToUpper(symbol_to_liquidate);
  vector<string> symbols;
  securities_->Keys(&symbols);
  for (int i = 0; i < symbols.size(); ++i) {
    const string& symbol = symbols[i];
    if (!(*portfolio_)[symbol]->HoldStock() || symbol != symbol_to) {
      continue;
    }
    int quantity = 0;
    quantity = -(*portfolio_)[symbol]->quantity();
    // Liquidate at market price
    order_list->push_back(SendOrder(symbol, quantity, orders::kMarket));
  }
}

void QSAlgorithm::SetHoldings(const string& symbol,
                              double percentage,
                              bool liquidate_existing_holdings,
                              const string& tag) {
  if (!portfolio_->ContainsKey(symbol)) {
    Debug(symbol +
          " not found in portfolio. Request this data"
          "when initializing the algorithm.");
    return;
  }
  // Range check values:
  if (percentage > 1) percentage = 1;
  if (percentage < -1) percentage = -1;
  // If they triggered a liquidate
  if (liquidate_existing_holdings) {
    vector<string> holding_symbols;
    portfolio_->Keys(&holding_symbols);
    for (int i = 0; i < holding_symbols.size(); ++i) {
      const string& holding_symbol = holding_symbols[i];
      if (holding_symbol != symbol &&
          (*portfolio_)[holding_symbol]->AbsoluteQuantity() > 0) {
        // Go through all existing holdings [synchronously],
        // market order the inverse quantity
        SendOrder(holding_symbol, -(*portfolio_)[holding_symbol]->quantity());
      }
    }
  }
  // the whole: Cash * Leverage for remaining buying power
  double total = portfolio_->TotalHoldingsValue() + portfolio_->cash() *
      (*securities_)[symbol]->leverage();
  // Difference between our target % and our current holdings:
  // (relative +- number).
  double delta_value = (total * percentage) -
      (*portfolio_)[symbol]->HoldingsValue();
  int delta_quantity = 0;
  if (abs((*securities_)[symbol]->Price()) > 0) {
    delta_quantity = delta_value / (*securities_)[symbol]->Price();
  }
  if (abs(delta_quantity) > 0) {
    SendOrder(symbol, delta_quantity, orders::kMarket, false, tag);
  }
}

DataConsolidator* QSAlgorithm::ResolveConsolidator(
    const string& symbol,
    Resolution::Enum resolution) {
}

string QSAlgorithm::CreateIndicatorName(
    const string& symbol,
    const string& type,
    Resolution::Enum resolution) {
}

}  // namespace algorithm
}  // namespace quantsystem
