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

#ifndef QUANTSYSTEM_ENGINE_SUBSCRIPTION_STREAM_READER_H_
#define QUANTSYSTEM_ENGINE_SUBSCRIPTION_STREAM_READER_H_

#include <iostream>  // NOLINT
using std::istream;
#include <sstream>
using std::istringstream;
#include <fstream>  // NOLINT
using std::ifstream;
#include <string>
using std::string;
#include "quantsystem/common/global.h"
#include "quantsystem/common/base/scoped_ptr.h"
namespace quantsystem {
namespace engine {
/**
 * IStream Reader for enchancing the basic SR classes to include REST calls.
 * @ingroup EngineLayer
 */
class IStreamReader {
 public:
  /**
   * IStream Reader Implementation - End of Stream.
   */
  virtual bool EndOfStream() const = 0;

  /**
   * IStream Reader Implementation - Read Line.
   */
  virtual string ReadLine() = 0;

  /**
   * IStream Reader Implementation - Close Reader.
   */
  virtual void Close() = 0;

  /**
   * IStream Reader Implementation - Dispose Reader.
   */
  virtual void Dispose() = 0;
};

/**
 * Wrapper on stream reader to make it compatible with reading real files,
 * or calling live REST endpoints.
 * @ingroup EngineLayer
 */
class SubscriptionStreamReader : public IStreamReader {
 public:
  /**
   * Construct Streaming Reader.
   * @param source String location of the Endpoint
   * @param datafeed DataEndpoint
   */
  SubscriptionStreamReader(const string& source,
                           DataFeedEndpoint::Enum data_feed);

  /**
   * Construct Streaming Reader.
   * @param is Istream instance
   * @param datafeed DataEndpoint
   */
  SubscriptionStreamReader(istream* is, DataFeedEndpoint::Enum data_feed);

  /**
   * End of stream boolean flag.
   */
  virtual bool EndOfStream() const;

  /**
   * ReadLine wrapper on stream reader to read a line from the file or
   * a REST API endpoint.
   * @return String response from REST request
   */
  virtual string ReadLine();

  /**
   * Close old stream reader.
   */
  virtual void Close() {
    std::ifstream* ifs = dynamic_cast<std::ifstream*>(is_.get());
    if (ifs) {
      ifs->close();
    };
    is_.reset(NULL);
  }

  /**
   *  Dispose of old stream reader.
   */
  virtual void Dispose() {
    // Do Nothing
  }

 private:
  DataFeedEndpoint::Enum data_feed_;
  scoped_ptr<istream> is_;
};

}  // namespace engine
}  // namespace quantsystem
#endif  // QUANTSYSTEM_ENGINE_SUBSCRIPTION_STREAM_READER_H_
