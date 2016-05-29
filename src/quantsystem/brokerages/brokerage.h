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
 * @defgroup BrokeragesLayer Brokerages Layer
 *
 * The Brokerages Layer provides different brokerages support.
 * It includes paper and tradier brokerages.
 */

#ifndef QUANTSYSTEM_BROKERAGES_BROKERAGE_H_
#define QUANTSYSTEM_BROKERAGES_BROKERAGE_H_

#include <string>
using std::string;
#include "quantsystem/common/base/callback.h"
#include "quantsystem/interfaces/ibrokerage.h"

namespace quantsystem {
using interfaces::IBrokerage;
namespace brokerages {
/**
 * Brokerage interface - store common objects and properties
 * which are common across all brokerages.
 * @ingroup BrokeragesLayer
 */
class Brokerage: public IBrokerage {
 public:
  /**
   * Standard constructor.
   */
  Brokerage();

  /**
   * Standard destructor.
   */
  virtual ~Brokerage();

  /**
   * Add an error handler for the specific brokerage error.
   * @param key String error name
   * @param callback Action call back
   */
  virtual void AddErrorHander(const string& key, Closure* callback);

  /**
   * Refresh brokerage login session where applicable.
   */
  virtual bool RefreshSession();
};

}  // namespace brokerages
}  // namespace quantsystem
#endif  // QUANTSYSTEM_BROKERAGES_BROKERAGE_H_
