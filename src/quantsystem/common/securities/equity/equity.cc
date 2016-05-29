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

#include "quantsystem/common/securities/equity/equity.h"
namespace quantsystem {
namespace securities {
namespace equity {
Equity::Equity(const string& symbol, Resolution::Enum resolution,
               bool fill_data_forward, double leverage,
               bool extended_market_hours,
               bool use_quant_system_data)
    : Security(symbol, SecurityType::kEquity, resolution, fill_data_forward,
               leverage, extended_market_hours, use_quant_system_data) {
}

Equity::~Equity() {
}

}  // namespace equity 
}  // namespace securities
}  // namespace quantsystem
