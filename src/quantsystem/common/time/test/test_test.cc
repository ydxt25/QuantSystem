#include <time.h>
#include <string>
using std::string;
#include <map>
using std::map;
#include <memory>
using std::shared_ptr;
#include "quantsystem/common/base/scoped_ptr.h"
#include "quantsystem/common/time/time_span.h"
#include "quantsystem/common/time/date_time.h"
#include <glog/logging.h>
#include <gtest/gtest.h>

namespace quantsystem {

class TestMore {
 public:
  TestMore(DateTime* date) {
    date_.reset(date);
  }
  void Log() {
    LOG(INFO) << "Time: " << date_->ToString();
  }
  scoped_ptr<DateTime> date_;
};

TEST(TimeSpan, TestMap) {
  DateTime *date1 = new DateTime();
  DateTime *date2 = new DateTime();
  shared_ptr<DateTime>  d1;
  shared_ptr<DateTime>  d2;
  d1.reset(date1);
  d2 = d1;
  LOG(INFO) << d1.use_count();
  LOG(INFO) << d2.use_count();
  d2.reset(date2);
  LOG(INFO) << d1->ToString();
  EXPECT_TRUE(d1->is_valid());
}

TEST(TimeSpan, TestMore) {
  scoped_ptr<DateTime> date1(new DateTime());
  TestMore t(date1.get());
  t.Log();
  EXPECT_TRUE(date1->is_valid());
}
}
