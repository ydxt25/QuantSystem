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

#ifndef QUANTSYSTEM_INTERFACES_IBROKERAGE_H_
#define QUANTSYSTEM_INTERFACES_IBROKERAGE_H_

#include <string>
using std::string;
#include "quantsystem/common/base/callback.h"

namespace quantsystem {
namespace interfaces {
/**
 * Brokerage interface - store common objects and properties
 * which are common across all brokerages.
 * @ingroup Interfaces
 */
class IBrokerage {
 public:
  /**
   * Add an error handler for the specific brokerage error.
   * @param key String error name
   * @param callback Action call back
   */
  virtual void AddErrorHander(const string& key, Closure* callback) = 0;

  /**
   * Refresh brokerage login session where applicable.
   */
  virtual bool RefreshSession() = 0;

  string name() const { return name_; }
  void set_name(const string& name) { name_ = name; } 

 private:
  // Brokerage Name
  string name_;
};

}  // namespace interfaces
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INTERFACES_IBROKERAGE_H_
