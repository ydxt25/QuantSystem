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

#include <limits>
using std::numeric_limits;
#include "quantsystem/common/base/integral_types.h"
#include "quantsystem/api/api.h"

namespace quantsystem {
namespace api {
Api::Api() {
}

Api::~Api() {
}

vector<int> Api::ReadLogAllowance(int user_id, const string& user_token) {
  vector<int> res;
  res.push_back(numeric_limits<int32>::max());
  res.push_back(numeric_limits<int32>::max());
  res.push_back(numeric_limits<int32>::max());
  return res;
}
}  // namespace api
}  // namespace quantsystem
