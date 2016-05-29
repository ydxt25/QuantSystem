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
#include "quantsystem/common/util/file.h"
#include "quantsystem/common/util/status.h"
#include "quantsystem/common/strings/case.h"

namespace quantsystem {
namespace {
const string kDefaultAlgoritmType_ = "BasicTemplateAlgorithm";
const string kDefaultEngineLocal_ = "true";
const string kDefaultEngineLivemode_ = "false";
const string kDefaultEngineMessagingHandler_ =
    "quantsystem.messaging.Messaging";
const string kDefualtEngineQueueHandler_ = "quantsystem.queues.Queues";
const string kDefaultEngineApiHander_ = "quantsystem.api,Api";
}  // anonymous namespace

namespace configuration {
const string Config::kAlgorithmType("algorithm-type-name");
const string Config::kEngineLocal("local");
const string Config::kEngineLivemode("livemode");
const string Config::kEngineMessagingHandler("messaging-handler");
const string Config::kEngineQueueHandler("queue-handler");
const string Config::kEngineApiHandler("api-handler");
bool Config::loaded_(false);
const string Config::config_("config.json");
Json::Value  Config::settings_;

void Config::InitConfigSetting() {
  settings_[kAlgorithmType] = kDefaultAlgoritmType_;
  settings_[kEngineLocal] = kDefaultEngineLocal_;
  settings_[kEngineLivemode] = kDefaultEngineLivemode_;
  settings_[kEngineMessagingHandler] = kDefaultEngineMessagingHandler_;
  settings_[kEngineQueueHandler] = kDefualtEngineQueueHandler_;
  settings_[kEngineApiHandler] = kDefaultEngineApiHander_;
}

Config::~Config() {
}

string Config::Get(const StringPiece& key,
                   const string& default_value) {
  Initialize();
  return settings_.get(key.data(), default_value).asString();
}

bool Config::GetBool(const StringPiece& key,
                     const bool& default_value) {
  return GetValue(key, default_value);
}

int Config::GetInt(const StringPiece& key, const int& default_value) {
  return GetValue(key, default_value);
}

double Config::GetDouble(const StringPiece& key,
                         const double& default_value) {
  return GetValue(key, default_value);
}

void Config::Initialize() {
  if (loaded_) {
    return;
  }
  InitConfigSetting();
  if (File::Exists(config_)) {
    string json;
    common::util::Status status = File::ReadPath(config_, &json);
    if (status.ok()) {
      Json::Reader reader;
      std::istringstream stream(json);
      if (!reader.parse(stream, settings_)) {
        common::util::Status status(common::util::error::INVALID_ARGUMENT,
                                    "Invalid JSON");
        LOG(ERROR) << status.error_message();
	LOG(ERROR)  << reader.getFormatedErrorMessages();
      }
      LOG(INFO) << "Config.Initialize(): Located Config.";
    }
  }
  loaded_ = true;
}

bool Config::StringToBool(const string& str) {
  if (StringCaseEqual("true", str)) {
    return true;
  }
  return false;
}

}  // namespace configuration
}  // namespace quantsystem
