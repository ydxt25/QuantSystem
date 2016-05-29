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
 * @defgroup CommonGeneric Common - Generic Components
 *
 * The common for the quantsystem platform.
 */
#ifndef QUANTSYSTEM_COMMON_GLOBAL_H_
#define QUANTSYSTEM_COMMON_GLOBAL_H_

#include <string>
using std::string;
#include <map>
using std::map;
#include <vector>
using std::vector;
#include "quantsystem/common/time/date_time.h"

namespace quantsystem {
/**
 * @ingroup CommonGeneric
 *
 * Shortcut data format strings.
 */
class DataFormat {
 public:
  // Year-Month-Date 6 Character Date Representation
  static const string kSixCharacter;
  // YYYY-MM-DD Eight Character Date Representation
  static const string kEightCharacter;
  // JSON Format Date Representation
  static const string kJsonFormat;
  // MySQL Format Date Representation
  static const string kDB;
  // Quantsystem UX Date Representation
  static const string kUI;
  // EXT Web Date Representation
  static const string kEXT;
};

/**
 * Processing runmode of the backtest.
 */
enum RunMode {
  // Automatically detect the runmode of the algorithm:
  // series for minute data, parallel for second-tick
  kAutomatic,
  // Series runmode for the algorithm
  kSeries,
  // Parallel runmode for the algorithm
  kParallel
};

/**
 * Multilanguage support enum: which language is this project.
 */
enum Language {
  // C++ language project
  kCPlusPlus,
  // Python language project
  kPython
};

/**
 * User subscription level.
 */
enum UserPlan {
  kFree,  // Free user
  kHobbyist  // Hobbyist user
};

/**
 * Type of tradable security / underlying asset
 */
namespace SecurityType {
enum Enum {
  // Base class for all security types
  kBase,
  // Equity security
  kEquity,
  // Option security type
  kOption,
  // Commondity security type
  kCommodity,
  // FOREX securtiy
  kForex,
  // Future Security Type
  kFuture
};

#define CASE(type) case SecurityType::type:  return string(#type).substr(1)
static string SecurityTypeToString(Enum type) {
  switch (type) {
    CASE(kBase);
    CASE(kEquity);
    CASE(kOption);
    CASE(kCommodity);
    CASE(kForex);
    CASE(kFuture);
    default:
      return "";
  }
}
#undef CASE
};  // namespace SecurityType

/**
 * Market data style: is the market data a summary
 * (OHLC style) bar, or is it a time-price value.
*/
namespace MarketDataType {
enum Enum {
  // Bse market data type
  kBase,
  // Tradebar market data type (OHLC summary bar)
  kTradeBar,
  // Tick market data type (price-time pair)
  kTick
};
};

/**
 * Datafeed enum options for selecting the source of the datafeed.
 */
namespace DataFeedEndpoint {
enum Enum {
  kBacktesting,  // Backtesting datafeed endpoint
  kFileSystem,  // Loading files off the local system
  kLiveTrading,  // Getting datafeed from a QC-Live-Cloud
  kTest  // Test live data feed
};
};

/**
 * Realtime events handler options for handling
 * realtime events in the algorithm.
 */
namespace RealTimeEndpoint {
enum Enum {
  kBacktesting,  // Backtesting facked realtime events
  kLiveTrading  // Live trading realtime events
};
};

/**
 * Result events handler options for processing algorithm messages.
 */
namespace ResultHandlerEndpoint {
enum Enum {
  kBacktesting,  // Send results to the backtesting web application
  kConsole,  // Send results to the local console
  kLiveTrading  // Send results to the live web application
};
};

/**
 * Setup handler options for setting up algorithm state
 * and the livetrading/backtest requirements.
 */
namespace SetupHandlerEndpoint {
enum Enum {
  kBacktesting,  // Configure algorithm+job for backtesting
  kConsole,  // Configure algorithm+job for the console
  kPaperTrading,  // Paper trading alogrithm++job internal state configuration
  kTradier  // Tradier setup handler
};
};

/**
 * Transaction handler options for selecting who processes the transactions.
 */
namespace TransactionHandlerEndpoint {
enum Enum {
  kBacktesting,  // Use backtesting models to process transactions
  kTradier,  // Use Tradier to process transactions
  // kInteractiveBrokers,  // Use Interactive Brokers to process transactions
  // kFXCM,  // Use FXCM to process transactions
};
};

/**
 *  Cloud storage permission options.
 */
enum StoragePermissions {
  kPublic,  // Public storage permissions
  kAuthenticated  // Authenticated read storage permissions
};

/**
 * Types of tick data - trades or quote ticks.
 */
enum TickType {
  kTrade,  // Trade type tick object
  kQuote  // Quote type tick object
};

#define CASE(choice) case choice:  return string(#choice).substr(1)
static string TickTypeToString(TickType type) {
  switch (type) {
    CASE(kTrade);
    CASE(kQuote);
    default:
      return "";
  }
}
#undef CASE

/**
 * Resolution of data requested.
 *
 * Always sort the enum from the smallest to largest resolution
 */
namespace Resolution {
enum Enum {
  kTick,  //  Tick resolution (1)
  kSecond,  // Second resolution (2)
  kMinute,  // Minute resolution (3)
  kHour,  // Hour resolution (4)
  kDaily  // Daily resolution (5)
};

#define CASE(type) case Resolution::type:  return string(#type).substr(1)
static string ResolutionToString(Resolution::Enum type) {
  switch (type) {
    CASE(kTick);
    CASE(kSecond);
    CASE(kMinute);
    CASE(kHour);
    CASE(kDaily);
    default:
      return "";
  }
#undef CASE
}
};  // namespace Resolution

/**
 * States of a live deployment.
 */
namespace AlgorithmStatus {
enum Enum {
  kQuit = 0,  // User initiated a quit request
  kDeployError,  // Error compiing algorithm
  kInQueue,  // Waiting for a server
  kRunning,  // Running the algorithm
  kStopped,  // Stopped algorithm or exited with runtime errors
  kLiquidated,  // Liquidated algorithm
  kDeleted,  // Algorithm has been deleted
  kCompleted,  // Algorithm completed runnig
  kRuntimeError,  // Runtime error stopped the algorithm
  kInvalid  // Error
};

#define CASE(choice) case choice:  return string(#choice).substr(1)
static string AlgorithmStatusToString(Enum type) {
  switch (type) {
    CASE(kQuit);
    CASE(kDeployError);
    CASE(kInQueue);
    CASE(kRunning);
    CASE(kStopped);
    CASE(kLiquidated);
    CASE(kDeleted);
    CASE(kCompleted);
    CASE(kRuntimeError);
    CASE(kInvalid);
    default:
      return "";
  }
}
#undef CASE
};  // namespace AlgorithmStatus

/**
 * Enum of all the analysis periods, AS integers.
 * Reference "Period" Array to access the values.
 */
enum Period {
  kTenSeconds = 10,
  kThirtySeconds = 30,
  kOneMinute = 60,
  kTwoMinutes = 120,
  kThreeMinutes = 180,
  kFiveMinutes = 300,
  kTenMinutes = 600,
  kFifteenMinutes = 900,
  kTwentyMinutes = 1200,
  kThirtyMinutes = 1800,
  kOneHour = 3600,
  kTwoHours = 7200,
  kFourHours = 14400,
  kSixHours = 21600
};

/**
 * @ingroup CommonGeneric
 * Global Market Short Codes and their full versions: (used in tick objects)
 */
class MarketCodes {
 public:
  static const map<string, string> kUS;
  static const map<string, string> kCanada;
};

/**
 * @ingroup CommonGeneric
 * US public holidays.
 */
class USHoliday {
 public:
  // Public Holidays
  static const vector<DateTime> kDates;
};

}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_GLOBAL_H_
