/******************************************************************************************************
 * Copyright (C) 2024 Gaina Stefan
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
 * OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @file utility_test.cpp
 * @author Gaina Stefan
 * @date 19.11.2024
 * @brief This file unit-tests hob-log/utility.cpp.
 * @details Current coverage report:
 * <ul>
 * <li> Line coverage: 100.0% (11/11) </li>
 * <li> Functions:     100.0% (2/2)   </li>
 * <li> Branches:      100.0% (2/2)   </li>
 * </ul>
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "utility.cpp"

/******************************************************************************************************
 * replace_placeholder
 *****************************************************************************************************/

TEST(utility_test, replace_placeholder_not_found)
{
	std::string destination = "not found";

	hob::log::utility::replace_placeholder(destination, "{TEST}", "test");
	EXPECT_EQ("not found", destination);
}

TEST(utility_test, replace_placeholder_found)
{
	std::string destination = "found {TEST}";

	hob::log::utility::replace_placeholder(destination, "{TEST}", "test");
	EXPECT_EQ("found test", destination);
}

/******************************************************************************************************
 * get_time
 *****************************************************************************************************/

TEST(utility_test, get_time)
{
	std::pair<std::tm*, std::int64_t> time = hob::log::utility::get_time();

	EXPECT_TRUE(124 <= time.first->tm_year) << "Year has invalid value: " << time.first->tm_year;
	EXPECT_TRUE(0 <= time.first->tm_mon && 12 > time.first->tm_mon) << "Month has invalid value: " << time.first->tm_mon;
	EXPECT_TRUE(0 <= time.first->tm_yday && 366 > time.first->tm_yday) << "Year day has invalid value: " << time.first->tm_yday;
	EXPECT_TRUE(0 <= time.first->tm_wday && 7 > time.first->tm_wday) << "Week day has invalid value: " << time.first->tm_wday;
	EXPECT_TRUE(0 <= time.first->tm_hour && 24 > time.first->tm_hour) << "Hour has invalid value: " << time.first->tm_hour;
	EXPECT_TRUE(0 <= time.first->tm_min && 60 > time.first->tm_min) << "Minute has invalid value: " << time.first->tm_min;
	EXPECT_TRUE(0 <= time.first->tm_sec && 60 > time.first->tm_sec) << "Second has invalid value: " << time.first->tm_sec;
	EXPECT_TRUE(0L <= time.second && 1000L > time.second) << "Millisecond has invalid value: " << time.second;
}
