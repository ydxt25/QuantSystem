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

#include <string>
using std::to_string;
#include <functional>
using std::bind;
#include "quantsystem/indicators/functional_indicator.h"
#include "quantsystem/indicators/aroon_oscillator.h"
namespace quantsystem {
namespace indicators {
AroonOscillator::AroonOscillator(int up_period, int down_period)
    : TradeBarIndicator("AROON(" + to_string(up_period) + "},{" +
                        to_string(down_period) + "})") {
  string name = "AROON(" + to_string(up_period) + "},{" +
      to_string(down_period) + "})";
  InitAroonOscillator(name, up_period, down_period);
}

AroonOscillator::AroonOscillator(const string& name,
                                 int up_period, int down_period)
    : TradeBarIndicator(name) {
  InitAroonOscillator(name, up_period, down_period);
}

void AroonOscillator::InitAroonOscillator(const string& name,
                                     int up_period, int down_period) {
  scoped_ptr<Maximum> max(new Maximum(name + "_Max", up_period));
 // typedef std::function<bool()> ReadyHandler;
 //s typedef std::function<double(IndicatorDataPoint)> ComputeNewHandler;  //NOLINT
  /*FunctionalIndicator<IndicatorDataPoint>::ComputeNewHandler AroonUpHandler = bind(AroonOscillator::ComputeAroonUp, up_period,
                                   max.get(), std::placeholders::_1);
  FunctionalIndicator<IndicatorDataPoint>::ReadyHandler ReadyUpHandler = &max->is_ready;
  aroon_up_.reset(new FunctionalIndicator<IndicatorDataPoint>(
      name + "_AroonUp", AroonUpHandler, ReadyUpHandler));
  scoped_ptr<Minimum> min(new Minimum(name + "_Min", down_period));
  FunctionalIndicator<IndicatorDataPoint>::ComputeNewHandler AroonDownHandler = bind(AroonOscillator::ComputeAroonDown, down_period,
                                            min.get(), std::placeholders::_1);
  FunctionalIndicator<IndicatorDataPoint>::ReadyHandler ReadyDownHandler = &min->is_ready;
  aroon_down_.reset(new FunctionalIndicator<IndicatorDataPoint>(
      name + "_AroonDown", AroonDownHandler, ReadyDownHandler)); */
}

double AroonOscillator::ComputeNextValue(const TradeBar& input) {
  IndicatorDataPoint data_point_up(input.time(), input.high());
  aroon_up_->Update(data_point_up);
  IndicatorDataPoint data_point_down(input.time(), input.low());
  aroon_down_->Update(data_point_down);
  return aroon_up_->value() - aroon_down_->value();
}

double AroonOscillator::ComputeAroonUp(
    int up_period,
    Maximum* max,
    const IndicatorDataPoint& input) {
  max->Update(input);
  return 100 * (up_period - max->periods_since_maximum()) / up_period;
}

double AroonOscillator::ComputeAroonDown(
    int down_period, Minimum* min,
    const IndicatorDataPoint& input) {
  min->Update(input);
  return 100 * (down_period - min->periods_since_minimum()) / down_period;
}

}  // namespace indicators
}  // namespace quantsystem
