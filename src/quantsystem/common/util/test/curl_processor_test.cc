#include <string>
using std::string;
#include "quantsystem/common/strings/strcat.h"
#include "quantsystem/common/util/file.h"
#include "quantsystem/common/util/curl_processor.h"
#include "quantsystem/configuration/test/quantsystem_gtest.h"
#include <glog/logging.h>
#include <gtest/gtest.h>

namespace quantsystem {
TEST(CurlProcessor, TestDownload) {
  const string path = StrCat(GetTestingTempDir(), "/fb.csv");
  File::Delete(path);
  const string url = "https://www.quandl.com/api/v3/datasets/WIKI/FB.csv";
  CurlProcessor curl;
  curl.Download(url, path);
  EXPECT_TRUE(File::Exists(path));
  string res;
  File::ReadPath(path, &res);
  EXPECT_TRUE((res.size() > 100));
  LOG(INFO) << res.size();
}

TEST(CurlProcessor, DownloadFollowUrl) {
  const string path = StrCat(GetTestingTempDir(), "/quotes.csv");
  File::Delete(path);
  const string url =
      "http://finance.yahoo.com/d/quotes.csv?s=XOM+BBDb.TO+JNJ+MSFT&f=snd1l1yr";
  CurlProcessor curl;
  curl.DownloadFollowUrl(url, path);
  EXPECT_TRUE(File::Exists(path));
  string res;
  File::ReadPath(path, &res);
  EXPECT_TRUE((res.size() > 10));
}
}
