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

#include <glog/logging.h>
#include "quantsystem/common/util/curl_processor.h"
namespace quantsystem {
CurlProcessor::CurlProcessor()
    : curl_(NULL) {
}

CurlProcessor::~CurlProcessor() {
  if (curl_) {
    curl_easy_cleanup(curl_);
  }
}

bool CurlProcessor::Download(const string& url, const string& path) {
  bool status = PrepareRequestOptions(url);
  if (!status) {
    LOG(ERROR) << "PrepareRequestOptions fail:" << url;
    return false;
  }
  FILE* fp = fopen(path.c_str(), "wb");
  curl_easy_setopt(curl_, CURLOPT_WRITEDATA, fp);
  CURLcode code = curl_easy_perform(curl_);
  fclose(fp);
  if (code != CURLE_OK) {
    LOG(ERROR) << "curl_easy_perform fail:" << curl_easy_strerror(code);
    return false;
  }
  return true;
}

bool CurlProcessor::DownloadFollowUrl(const string& url, const string& path) {
  bool status = PrepareRequestOptions(url);
  if (!status) {
    LOG(ERROR) << "PrepareRequestOptions fail:" << url;
    return false;
  }
  curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, 1L);
  FILE* fp = fopen(path.c_str(), "wb");
  curl_easy_setopt(curl_, CURLOPT_WRITEDATA, fp);
  CURLcode code = curl_easy_perform(curl_);
  fclose(fp);
  if (code != CURLE_OK) {
    LOG(ERROR) << "curl_easy_perform fail:" << curl_easy_strerror(code);
    return false;
  }
  return true;
}

bool CurlProcessor::LazyInitCurl() {
  if (!curl_) {
    curl_ = curl_easy_init();
    if (!curl_) {
      LOG(ERROR) << "Could not initialize curl";
      return false;
    }
    bool status = InitStandardOptions();
    if (!status) {
      curl_easy_cleanup(curl_);
      curl_ = NULL;
      return false;
    }
  }
  return true;
}

bool CurlProcessor::InitStandardOptions() {
  bool ok = true;
  ok = ok && !curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION,
                                ResultBodyCallback);
  if (!ok) {
    LOG(ERROR) << "Unexpected error setting up basic IO helpers";
    return false;
  }
  return true;
}

size_t CurlProcessor::ResultBodyCallback(
    void* data, size_t size, size_t nmemb, void* instance) {
  FILE* stream = static_cast<FILE*>(instance);
  size_t written = fwrite(data, size, nmemb, stream);
  return written;
}

bool CurlProcessor::PrepareRequestOptions(
    const string& url) {
  bool status = LazyInitCurl();
  if (!status) {
    return status;
  }
  curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
  return true;
}

}  // namespace quantsystem
