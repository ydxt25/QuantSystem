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
using std::string;

#include "quantsystem/configuration/configuration.h"
#include <glog/logging.h>
#include <gtest/gtest.h>

namespace quantsystem {

using configuration::Config;
TEST(Config, GetString) {
  EXPECT_EQ("BasicTemplateAlgorithm", Config::Get(Config::kAlgorithmType));
  EXPECT_EQ("true", Config::Get(Config::kEngineLocal));
  EXPECT_EQ("false", Config::Get("livemode"));
}

TEST(Config, GetBool) {
  EXPECT_EQ(1, Config::GetBool(Config::kEngineLocal));
  EXPECT_EQ(0, Config::GetBool("livemode"));
} 

TEST(Config, GetInt) {
  EXPECT_EQ(10, Config::GetInt("ten"));
  EXPECT_EQ(20, Config::GetInt("twenty"));
}

TEST(Config, GetDouble) {
  EXPECT_EQ(3.14, Config::GetDouble("pi"));
}

}  // hamespace quantsystem
