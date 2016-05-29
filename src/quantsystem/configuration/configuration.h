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
 * @defgroup ConfigurationLayer Configuration Layer
 *
 * Load the required external setup variables for the engine.
 * @see Engine
 */
#ifndef QUANTSYSTEM_CONFIG_H_
#define QUANTSYSTEM_CONFIG_H_

#include <map>
using std::map;
#include <string>
using std::string;
#include "quantsystem/common/base/macros.h"
#include "quantsystem/common/json/json.h"
#include "quantsystem/common/base/type_traits.h"
#include "quantsystem/common/base/strtoint.h"
#include "quantsystem/common/strings/stringpiece.h"
#include "quantsystem/common/strings/numbers.h"

namespace quantsystem {
namespace configuration {
/**
 * Configuration class.
 * @ingroup ConfigurationLayer
 */
class Config {
 public:
  // configuration key
  static const string kAlgorithmType;
  static const string kEngineLocal;
  static const string kEngineLivemode;
  static const string kEngineMessagingHandler;
  static const string kEngineQueueHandler;
  static const string kEngineApiHandler;

  Config() {
    }
  /**
   * Standard destructor.
   */
  virtual ~Config();

  /**
   * Get the value of configuration setting by the key.
   *
   * @param key key to be searched.
   * @param default_value return this value if not found in the configuration.
   * @return value of the configuartion setting.
   */
  static string Get(const StringPiece& key,
                    const string& default_value = "");

  /**
   * Get the boolean value of configuration setting by the key.
   *
   * @param key key to be searched.
   * @param default_value return this value if not found in the configuration.
   * @return boolean value of the config value.
   */
  static bool GetBool(const StringPiece& key,
                      const bool& default_value = false);

  /**
   * Get the int value of configuration setting by the key.
   *
   * @param key key to be searched.
   * @param default_value return this value if not found in the configuration.
   * @return int value of the config value.
   */
  static int GetInt(const StringPiece& key,
                    const int& default_value = 0);

  /**
   * Get the double value of configuration setting by the key.
   *
   * @param key key to be searched.
   * @param default_value return this value if not found in the configuration.
   * @return double value of the config value.
   */
  static double GetDouble(const StringPiece& key,
                   const double& default_value = 0.0);
  /**
   * Get the value of configuraiton setting by the key,
   * and converts it to the requested type.
   *
   * @param key key to be searched.
   * @param default_value return this value if not found in the configuration.
   * @return converted value of the config value.
   */
  template <typename T>
  static T GetValue(const StringPiece& key,
                    const T default_value = T()) {
    string string_value = Get(key);
    if (string_value != "") {
      if (common::base::is_same<T, bool>::value) {
        return StringToBool(string_value);
      } else if (common::base::is_same<T, int>::value) {
        return atoi32(string_value);
      } else if (common::base::is_same<T, double>::value) {
        double value;
        if (safe_strtod(string_value, &value)) {
          return value;
        }
      }
    }
    return default_value;
  }

 private:
  static const string config_;  // Configuration file
  static bool loaded_;  // has the load of the configuration file
  // configuration setting
  static Json::Value settings_;

  static void InitConfigSetting();

  /**
   * Initialize the configuration file and if it doesnt exist
   * create one with the default values above.
   */
  static void Initialize();

  /**
   * Covert string to boolean.
   * @param str input string.
   * @return bool value of the stirng value.
   */
  static bool StringToBool(const string& str);

  DISALLOW_COPY_AND_ASSIGN(Config);
};

}  // namespace configuration
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_H_
