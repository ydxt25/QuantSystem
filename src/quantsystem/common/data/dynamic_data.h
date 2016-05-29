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

#ifndef QUANTSYSTEM_COMMON_DYNAMIC_DATA_H_
#define QUANTSYSTEM_COMMON_DYNAMIC_DATA_H_
#include <string>
using std::string;
#include <map>
using std::map;

#include "quantsystem/common/data/base_data.h"
#include "quantsystem/common/global.h"
#include "quantsystem/common/strings/stringpiece.h"

namespace quantsystem {

namespace data {
/**
 * Dynamic Data Class
 * @ingroup CommonBaseData
 * 
 * Accept flexible data, adapting to the columns provided by source.
 * Intended for use with Quandl class.
 */
class DynamicData : public BaseData {
 public:
  /**
   * Standard constructor.
   */
  DynamicData();

  /**
   * Standard destructor.
   */
  virtual ~DynamicData();

  /**
   * Set the core properties of basedata object.
   *
   * @param name Property name.
   * @param value Object property value.
   * @return True if set successfully.
   */
  bool SetProperty(const StringPiece& name, const StringPiece& value);

  /**
   * Get the core properties of basedata object.
   *
   * @param name Property name.
   * @return Object value of basedata, if not found, empty boost::any object.
   */
  string GetProperty(const StringPiece& name) const;

 private:
  typedef map<string, string> StorageMap;
  StorageMap storage_;
};

}  // namespace data
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_DYNAMIC_DATA_H_
