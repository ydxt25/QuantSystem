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

#ifndef QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_COMMON_H_
#define QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_COMMON_H_

namespace quantsystem {
namespace brokerages {
/**
 * Rate limiting categorization
 */
namespace  TradierApiRequestType {
enum Enum {
  kStandard,  // Standard rate limit
  kData,  // Data API rate limit
  kOrders  // Orders API rate limit
};
}  // namespace  TradierApiRequestType

/**
 * Tradier account type
 */
enum TradierAccountType {
  kDayTrader,  // Account Type: Trader
  kCash,  // Account Type: Cash
  kMargin  // Account Type: margin
};

/**
 * Direction of the order
 * (buy, buy_to_open, buy_to_cover, buy_to_close, sell,
 * sell_short, sell_to_open, sell_to_close)
 */
enum TradierOrderDirection {
  // Buy -- Equity -- Open Buy New Position
  kBuy,
  // Sell Short -- Equity -- Open New Short Sell
  kSellShort,
  // Sell -- Equity -- Closing Long Existing Positions
  kSell,
  // Buy to Cover -- Equity -- Closing a short equity
  kBuyToCover,
  // OPTIONS ONLY
  kSellToOpen,  // Sell to open
  kSellToClose,  // Sell to close
  kBuyToClose,  // Buy to close
  kBuyToOpen,  // Buy to Open
  kNone  // Order fail case
};

/**
 * Status of the tradier order.
 * (filled, canceled, open, expired, rejected, pending,
 * partially_filled, submitted)
 */
namespace TradierOrderStatus {
enum Enum {
  kFilled,  // Fill
  kCanceled,  // Cancelled
  kOpen,  // Open
  kExpired,  // Expired
  kRejected,  // Rejected
  kPending,  // Pending
  kPartiallyFilled,  // Partially Filled
  kSubmitted  // Submitted
};
}  // namespace TradierOrderStatus

/**
 * Length of the order offer.
 */
enum TradierOrderDuration {
  kGTC,  // Good to Cancelled
  kDay  // Day period
};

/**
 * Class of the order.
 */
namespace TradierOrderClass {
enum Enum {
  kEquity,  // Equity
  kOption,  // Option
  kMultileg,  // Multi
  kCombo  // Combo
};
}  // namespace TradierOrderClass

/**
 * Account status flag.
 */
enum TradierAccountStatus {
  kApproved,  // Approved
  kClosed  // Closed
};

/**
 * Tradier options status.
 */
namespace TradierOptionStatus {
enum Enum {
  kExercise,  // Exercise
  kExpired,  // Expired
  kAssignment  // Assignment
};
}  // namespace TradierOptionStatus

/**
 * TradeBar windows for Tradier's data histories.
 */
enum TradierTimeSeriesIntervals {
  kTick,  // Tick
  kOneMinute,  // 1min
  kFiveMinutes,  // 5min
  kFifteenMinutes  // 15min
};

/**
 * Historical data intervals for tradier requests.
 */
enum TradierHistoricalDataIntervals {
  kDaily,  // Daily
  kWeekly,  // Weekly
  kMonthly  // Monthly
};

/**
 * Tradier option type.
 */
enum TradierOptionType {
  kPut,
  kCall
};

/**
 * Tradier options expiration.
 */
namespace TradierOptionExpirationType {
enum Enum {
  kStandard,
  kWeekly
};
}  // namespace TradierOptionExpirationType

/**
 * Account classification
 */
enum TradierAccountClassification {
  kIndividual,
  kIRA,
  kRoth_Ira,
  kJoint
};

/**
 * Tradier event type.
 */
namespace TradierEventType {
enum Enum {
  kTrade,
  kJournal,
  kOption,
  kDividend
};
}  // namespace TradierEventType

/**
 * Market type of the trade.
 */
enum TradierTradeType {
  kEquity,
  kOption
};

/**
 * Tradier order type: (market, limit, stop, stop_limit or market)
 * credit, debit, even
 */
enum TradierOrderType {
  kLimit,
  kMarket,
  kStop,
  kStopLimit,
  kStopMarket,
  kCredit,
  kDebit,
  kEven
};

}  // namespace brokerages
}  // namespace quantsystem
#endif  // QUANTSYSTEM_BROKERAGES_TRADIER_TRADIER_COMMON_H_
