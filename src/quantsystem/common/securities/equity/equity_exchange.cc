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

#include "quantsystem/common/securities/equity/equity_exchange.h"
namespace quantsystem {
namespace securities {
namespace equity {
EquityExchange::EquityExchange() {
}

EquityExchange::~EquityExchange() {
}

bool EquityExchange::DateTimeIsOpen(const DateTime& datetime) const {
}

DateTime EquityExchange::TimeOfDayOpen(const DateTime& time) {
}

DateTime EquityExchange::TimeOfDayClosed(const DateTime& time) {
}

bool EquityExchange::DateIsOpen(const DateTime& date) const {
}

bool EquityExchange::DateTimeIsExtendedOpen(const DateTime& time) const {
}

}  // namespace equity
}  // namespace securities
}  // namespace quantsystem
