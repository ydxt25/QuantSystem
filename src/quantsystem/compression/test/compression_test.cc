#include <string>
using std::string;
#include <iostream>  // NOLINT
using std::istream;
#include "quantsystem/common/strings/strcat.h"
#include "quantsystem/common/util/file.h"
#include "quantsystem/common/util/curl_processor.h"
#include "quantsystem/compression/compression.h"
#include "quantsystem/configuration/test/quantsystem_gtest.h"
#include <glog/logging.h>
#include <gtest/gtest.h>

namespace quantsystem {
TEST(Compression, TestZipAndUnziptoString) {
  const string path = StrCat(GetTestingTempDir(), "/test_zip");
  File::Delete(path);
  const string content = "This is test";
  bool status = compression::ZipFromString(path, content);
  EXPECT_TRUE(status);
  const string zip_path = path + ".zip";
  EXPECT_TRUE(File::Exists(zip_path));

  string unzip_string = compression::UnzipToString(zip_path);
  CHECK_EQ(content, unzip_string);
}

TEST(Compression, TestUnziptoStream) {
  const string path = StrCat(GetTestingTempDir(), "/test_unzip_stream");
  File::Delete(path);
  const string content = "This is test unzip to stream";
  bool status = compression::ZipFromString(path, content);
  EXPECT_TRUE(status);
  const string zip_path = path + ".zip";
  EXPECT_TRUE(File::Exists(zip_path));

  istream* is = compression::Unzip(zip_path);
  string unzip_string;
  char c;
  while(is->get(c)) {
    unzip_string.push_back(c);
  }
  CHECK_EQ(content, unzip_string);
  delete is;
}
}
