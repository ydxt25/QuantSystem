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

#include "quantsystem/engine/subscription_stream_reader.h"
namespace quantsystem {
namespace engine {
SubscriptionStreamReader::SubscriptionStreamReader(
    const string& source,
    DataFeedEndpoint::Enum data_feed)
    : data_feed_(data_feed) {
  /*if (data_feed == DataFeedEndpoint::kBacktesting ||
      data_feed == DataFeedEndpoint::kFileSystem) {
    is_.reset(new ifstream(source, ifstream::in));
  }*/
}

SubscriptionStreamReader::SubscriptionStreamReader(
    istream* is, DataFeedEndpoint::Enum data_feed)
    : data_feed_(data_feed) {
  is_.reset(is);
}

bool SubscriptionStreamReader::EndOfStream() const {
  bool eos = false;
  switch (data_feed_) {
    case DataFeedEndpoint::kBacktesting:
    case DataFeedEndpoint::kFileSystem:
      eos = is_->eof();
      break;
    case DataFeedEndpoint::kLiveTrading:
      eos = false;
      break;
  }
  return eos;
}

string SubscriptionStreamReader::ReadLine() {
  string line = "";
  switch (data_feed_) {
    case DataFeedEndpoint::kBacktesting:
    case DataFeedEndpoint::kFileSystem:
      if (!getline(*is_, line)) {
        line = "";
      }
      break;
    case DataFeedEndpoint::kLiveTrading:
      // TODO(SHI)
      line = "";
      break;
  }
  return line;
}

}  // namespace engine
}  // namespace quantsystem
