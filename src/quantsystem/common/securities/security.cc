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

#include <glog/logging.h>
#include "quantsystem/common/securities/security.h"
#include "quantsystem/common/securities/security_transaction_model.h"
#include "quantsystem/common/securities/security_data_filter.h"
#include "quantsystem/common/securities/equity/equity_transaction_model.h"
#include "quantsystem/common/securities/equity/equity_data_filter.h"
#include "quantsystem/common/securities/forex/forex_transaction_model.h"
#include "quantsystem/common/securities/forex/forex_data_filter.h"


namespace quantsystem {
namespace securities {
Security::Security(const string& symbol, SecurityType::Enum type,
                   Resolution::Enum resolution, bool fill_data_forward,
                   const double& leverage, bool extended_market_hours,
                   bool use_quant_system_data)
    : symbol_(symbol),
      type_(type),
      resolution_(resolution),
      is_fill_data_forward_(fill_data_forward),
      leverage_(leverage),
      is_extended_market_hours_(extended_market_hours),
      is_quant_system_data_(use_quant_system_data) {
  switch (type) {
    case SecurityType::kEquity:
      model_.reset(new equity::EquityTransactionModel());
      data_filter_.reset(new equity::EquityDataFilter());
      break;
    case SecurityType::kForex:
      model_.reset(new forex::ForexTransactionModel());
      data_filter_.reset(new forex::ForexDataFilter());
      break;
    case SecurityType::kBase:
      model_.reset(new SecurityTransactionModel());
      data_filter_.reset(new SecurityDataFilter());
      break;
    default:
      LOG(ERROR) << "Invalid Security Type=" << type;
      break;
  }
  cache_.reset(new SecurityCache());
  holdings_.reset(new SecurityHolding(symbol, model_.get()));
  exchange_.reset(new SecurityExchange());
}

Security::~Security() {
}

void Security::Update(const DateTime& frontier, BaseData* data) {
  // Update the exhange/timer
  exchange_->SetDataTimeFrontier(frontier);
  if (data == NULL) {
    return;
  }
  cache_->AddData(data);
  holdings_->UpdatePrice(data->value());
}

}  // namespace securities
}  // namespace quantsystem
