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
 * @file worker_test.cpp
 * @author Gaina Stefan
 * @date 07.12.2024
 * @brief This file unit-tests hob-log/worker.cpp.
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

#include "worker.hpp"

/******************************************************************************************************
 * FUNCTION DEFINITIONS
 *****************************************************************************************************/

static bool log_function(const std::uint8_t severity_bit, std::string&& message) noexcept
{
	return true;
}

/******************************************************************************************************
 * replace_placeholder
 *****************************************************************************************************/

TEST(worker_test, replace_placeholder_not_found)
{
	std::atomic<std::uint64_t> lost_logs = 0UL;
	hob::log::worker worker = { log_function, lost_logs };
}
