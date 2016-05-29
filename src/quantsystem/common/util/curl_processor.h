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

#include <curl/curl.h>
#include <string>
using std::string;
#ifndef QUANTSYSTEM_COMMON_CURL_PROCESSOR_H_
#define QUANTSYSTEM_COMMON_CURL_PROCESSOR_H_

namespace quantsystem {
/**
 * The CurlProcessor is an individual stateful curl request processor.
 * If the curl processor cannot initialize, it will set the internal curl_
 * handle to NULL and fail future requests.
 * @ingroup CommonBaseUtil
 */
class CurlProcessor {
 public:
  /**
   * Standard constructor.
   */
  CurlProcessor();

  /**
   * Standard destructor.
   */
  virtual ~CurlProcessor();

  /**
   * Download the file from the link to specific path. E.g. quandl link..
   * @param url The file url
   * @param path The saving file path
   */
  bool Download(const string& url, const string& path);

  /**
   * Dowload the file from the follow url to specific path. E.g. yahoo link.
   * @param url The file url
   * @param path The saving file path
   */
  bool DownloadFollowUrl(const string& url, const string& path);

 private:
  CURL* curl_;

  bool LazyInitCurl();

  bool InitStandardOptions();

  static size_t ResultBodyCallback(
      void* data, size_t size, size_t nmemb, void* instance);

  bool PrepareRequestOptions(const string& url);
};
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_CURL_PROCESSOR_H_
