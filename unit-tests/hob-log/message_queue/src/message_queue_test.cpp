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
 * @file message_queue_test.cpp
 * @author Gaina Stefan
 * @date 19.11.2024
 * @brief This file unit-tests hob-log/message_queue.cpp.
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

#include "std/queue_mock.hpp"
#include "std/queue_begin.hpp"
#include "message_queue.cpp"
#include "std/queue_end.hpp"

/******************************************************************************************************
 * TEST CLASS
 *****************************************************************************************************/

class message_queue_test : public testing::Test
{
public:
	message_queue_test(void)
		: queue_mock{}
	{
	}

public:
	std::queue_mock queue_mock;
};

/******************************************************************************************************
 * replace_placeholder
 *****************************************************************************************************/

TEST_F(message_queue_test, replace_placeholder_not_found)
{
}
