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

#ifndef QUANTSYSTEM_BROKERAGES_PAPER_PAPER_BROKERAGE_H_
#define QUANTSYSTEM_BROKERAGES_PAPER_PAPER_BROKERAGE_H_

#include <string>
using std::string;
#include "quantsystem/common/base/callback.h"
#include "quantsystem/brokerages/brokerage.h"

namespace quantsystem {
namespace brokerages {
/**
 * Paper Trading Brokerage
 * @ingroup BrokeragesLayer
 */
class PaperBrokerage : public Brokerage {
 public:
  /**
   * Standard constructor.
   */
  PaperBrokerage();

  /**
   * Standard destructor.
   */
  virtual ~PaperBrokerage();

  /**
   * Add an error handler for the specific brokerage error.
   * @param key String error name
   * @param callback Action call back
   */
  virtual void AddErrorHander(const string& key, Closure* callback) {
    // No error handlers from paper trading brokerage
  }

  /**
   * Refresh brokerage login session where applicable.
   */
  virtual bool RefreshSession() {
    // No need to refresh session for paper brokerage.
    return true;
  }
};

}  // namespace brokerages
}  // namespace quantsystem
#endif  // QUANTSYSTEM_BROKERAGES_PAPER_PAPER_BROKERAGE_H_
