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

#ifndef QUANTSYSTEM_COMMON_SECURITIES_SECURITY_CACHE_H_
#define QUANTSYSTEM_COMMON_SECURITIES_SECURITY_CACHE_H_

#include "quantsystem/common/data/base_data.h"
namespace quantsystem {
using data::BaseData;
namespace securities {
/**
 * Base class caching caching spot for security data and
 * any other temporary properties.
 * 
 * @ingroup CommonBaseSecurities
 */
class SecurityCache {
 public:
  /**
   * Standard constructor.
   */
  SecurityCache();

  /**
   * Standard destructor.
   */
  virtual ~SecurityCache();

  /**
   * Add a new market data point to the local security cache for the
   * current market price.
   */
  virtual void AddData(BaseData* data) {
    if (data) {
      last_data_ = data;
    }
  }

  /**
   * Get the last data packet received for the security.
   * @return BaseData type of the security.
   */
  virtual BaseData* GetData() const {
    return last_data_;
  }

  /**
   * Reset cache storage and free memory.
   */
  virtual void Reset() {
    last_data_ = NULL;
  }

 private:
  BaseData* last_data_;  // Last data for this security
};

}  // namespace securities
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_SECURITIES_SECURITY_CACHE_H_
