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

#include "quantsystem/common/global.h"
#include "quantsystem/common/util/stl_util.h"

namespace quantsystem {
const string DataFormat::kSixCharacter = "yyMMdd";
const string DataFormat::kEightCharacter = "yyyyMMdd";
const string DataFormat::kJsonFormat = "yyyy-MM-ddThh:mm:ss";
const string DataFormat::kDB = "yyyy-MM-dd HH:mm:ss";
const string DataFormat::kUI = "yyyyMMdd HH:mm:ss";
const string DataFormat::kEXT = "yyyy-MM-dd HH:mm:ss";

const map<string, string> MarketCodes::kUS = {
  {"A", "American Stock Exchange"},
  {"B", "Boston Stock Exchange"},
  {"C", "National Stock Exchange"},
  {"D", "FINRA ADF"},
  {"I", "International Securities Exchange"},
  {"J", "Direct Edge A"},
  {"K", "Direct Edge X"},
  {"M", "Chicago Stock Exchange"},
  {"N", "New York Stock Exchange"},
  {"P", "Nyse Arca Exchange"},
  {"Q", "NASDAQ OMX"},
  {"T", "NASDAQ OMX"},
  {"U", "OTC Bulletin Board"},
  {"u", "Over-the-Counter trade in Non-NASDAQ issue"},
  {"W", "Chicago Board Options Exchange"},
  {"X", "Philadelphia Stock Exchange"},
  {"Y", "BATS Y-Exchange, Inc"},
  {"Z", "BATS Exchange, Inc"}};

const map<string, string> MarketCodes::kCanada = {
  {"T", "Toronto"},
  {"V", "Venture"}};

const vector<DateTime> USHoliday::kDates = {
  /* Years Day */
  DateTime(1998, 1, 1),
  DateTime(1999, 1, 1),
  DateTime(2001, 1, 1),
  DateTime(2002, 1, 1),
  DateTime(2003, 1, 1),
  DateTime(2004, 1, 1),
  DateTime(2006, 1, 2),
  DateTime(2007, 1, 1),
  DateTime(2008, 1, 1),
  DateTime(2009, 1, 1),
  DateTime(2010, 1, 1),
  DateTime(2011, 1, 1),
  DateTime(2012, 1, 2),
  DateTime(2013, 1, 1),
  DateTime(2014, 1, 1),
  DateTime(2015, 1, 1),
  DateTime(2016, 1, 1),
  /* Day of Mouring */
  DateTime(2007, 1, 2),
  /* World Trade Center */
  DateTime(2001, 9, 11),
  DateTime(2001, 9, 12),
  DateTime(2001, 9, 13),
  DateTime(2001, 9, 14),
  /* Regan Funeral */
  DateTime(2004, 06, 11),
  /* Hurricane Sandy */
  DateTime(2012, 10, 29),
  DateTime(2012, 10, 30),
  /* Martin Luther King Jnr Day*/
  DateTime(1998, 01, 19),
  DateTime(1999, 01, 18),
  DateTime(2000, 01, 17),
  DateTime(2001, 01, 15),
  DateTime(2002, 01, 21),
  DateTime(2003, 01, 20),
  DateTime(2004, 01, 19),
  DateTime(2005, 01, 17),
  DateTime(2006, 01, 16),
  DateTime(2007, 01, 15),
  DateTime(2008, 01, 21),
  DateTime(2009, 01, 19),
  DateTime(2010, 01, 18),
  DateTime(2011, 01, 17),
  DateTime(2012, 01, 16),
  DateTime(2013, 01, 21),
  DateTime(2014, 01, 20),
  DateTime(2015, 01, 19),
  DateTime(2016, 01, 18),
  /* Washington / Presidents Day */
  DateTime(1998, 02, 16),
  DateTime(1999, 02, 15),
  DateTime(2000, 02, 21),
  DateTime(2001, 02, 19),
  DateTime(2002, 02, 18),
  DateTime(2003, 02, 17),
  DateTime(2004, 02, 16),
  DateTime(2005, 02, 21),
  DateTime(2006, 02, 20),
  DateTime(2007, 02, 19),
  DateTime(2008, 02, 18),
  DateTime(2009, 02, 16),
  DateTime(2010, 02, 15),
  DateTime(2011, 02, 21),
  DateTime(2012, 02, 20),
  DateTime(2013, 02, 18),
  DateTime(2014, 02, 17),
  DateTime(2015, 02, 16),
  DateTime(2016, 02, 15),
  /* Good Friday */
  DateTime(1998, 04, 10),
  DateTime(1999, 04, 02),
  DateTime(2000, 04, 21),
  DateTime(2001, 04, 13),
  DateTime(2002, 03, 29),
  DateTime(2003, 04, 18),
  DateTime(2004, 04, 9),
  DateTime(2005, 03, 25),
  DateTime(2006, 04, 14),
  DateTime(2007, 04, 06),
  DateTime(2008, 03, 21),
  DateTime(2009, 04, 10),
  DateTime(2010, 04, 02),
  DateTime(2011, 04, 22),
  DateTime(2012, 04, 06),
  DateTime(2013, 03, 29),
  DateTime(2014, 04, 18),
  DateTime(2015, 04, 03),
  DateTime(2016, 03, 25),
  /* Memorial Day */
  DateTime(1998, 05, 25),
  DateTime(1999, 05, 31),
  DateTime(2000, 05, 29),
  DateTime(2001, 05, 28),
  DateTime(2002, 05, 27),
  DateTime(2003, 05, 26),
  DateTime(2004, 05, 31),
  DateTime(2005, 05, 30),
  DateTime(2006, 05, 29),
  DateTime(2007, 05, 28),
  DateTime(2008, 05, 26),
  DateTime(2009, 05, 25),
  DateTime(2010, 05, 31),
  DateTime(2011, 05, 30),
  DateTime(2012, 05, 28),
  DateTime(2013, 05, 27),
  DateTime(2014, 05, 26),
  DateTime(2015, 05, 25),
  DateTime(2016, 05, 30),
  /* Independence Day */
  DateTime(1998, 07, 03),
  DateTime(1999, 07, 05),
  DateTime(2000, 07, 04),
  DateTime(2001, 07, 04),
  DateTime(2002, 07, 04),
  DateTime(2003, 07, 04),
  DateTime(2004, 07, 05),
  DateTime(2005, 07, 04),
  DateTime(2006, 07, 04),
  DateTime(2007, 07, 04),
  DateTime(2008, 07, 04),
  DateTime(2009, 07, 03),
  DateTime(2010, 07, 05),
  DateTime(2011, 07, 04),
  DateTime(2012, 07, 04),
  DateTime(2013, 07, 04),
  DateTime(2014, 07, 04),
  DateTime(2014, 07, 04),
  DateTime(2015, 07, 03),
  DateTime(2016, 07, 04),
  /* Labour Day */
  DateTime(1998, 9, 07),
  DateTime(1999, 9, 06),
  DateTime(2000, 9, 04),
  DateTime(2001, 9, 03),
  DateTime(2002, 9, 02),
  DateTime(2003, 9, 01),
  DateTime(2004, 9, 06),
  DateTime(2005, 9, 05),
  DateTime(2006, 9, 04),
  DateTime(2007, 9, 03),
  DateTime(2008, 9, 01),
  DateTime(2009, 9, 07),
  DateTime(2010, 9, 06),
  DateTime(2011, 9, 05),
  DateTime(2012, 9, 03),
  DateTime(2013, 9, 02),
  DateTime(2014, 9, 01),
  DateTime(2015, 9, 07),
  DateTime(2016, 9, 05),
  /* Thanksgiving Day */
  DateTime(1998, 11, 26),
  DateTime(1999, 11, 25),
  DateTime(2000, 11, 23),
  DateTime(2001, 11, 22),
  DateTime(2002, 11, 28),
  DateTime(2003, 11, 27),
  DateTime(2004, 11, 25),
  DateTime(2005, 11, 24),
  DateTime(2006, 11, 23),
  DateTime(2007, 11, 22),
  DateTime(2008, 11, 27),
  DateTime(2009, 11, 26),
  DateTime(2010, 11, 25),
  DateTime(2011, 11, 24),
  DateTime(2012, 11, 22),
  DateTime(2013, 11, 28),
  DateTime(2014, 11, 27),
  DateTime(2015, 11, 26),
  DateTime(2016, 11, 24),
  /* Christmas 1998-2014 */
  DateTime(1998, 12, 25),
  DateTime(1999, 12, 24),
  DateTime(2000, 12, 25),
  DateTime(2001, 12, 25),
  DateTime(2002, 12, 25),
  DateTime(2003, 12, 25),
  DateTime(2004, 12, 24),
  DateTime(2005, 12, 26),
  DateTime(2006, 12, 25),
  DateTime(2007, 12, 25),
  DateTime(2008, 12, 25),
  DateTime(2009, 12, 25),
  DateTime(2010, 12, 24),
  DateTime(2011, 12, 26),
  DateTime(2012, 12, 25),
  DateTime(2013, 12, 25),
  DateTime(2014, 12, 25),
  DateTime(2015, 12, 25),
  DateTime(2016, 12, 25)
};

}  // namespace quantsystem

