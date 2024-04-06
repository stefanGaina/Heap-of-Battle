/******************************************************************************************************
 * Heap of Battle Copyright (C) 2024
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the
 * authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
 *    original software. If you use this software in a product, an acknowledgment in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being
 *    the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @file hob_AsyncQueue_test.cpp
 * @author Gaina Stefan
 * @date 04.04.2024
 * @brief This file unit-tests hob_AsyncQueue.hpp.
 * @details Current coverage report:
 * <ul>
 * <li> Line coverage: 100.0% (14/14) </li>
 * <li> Functions:     100.0% (3/3)   </li>
 * <li> Branches:      100.0% (2/2)   </li>
 * </ul>
 * @todo Usually the mocks that do return something are checked for null using ASSERT_NE(), but in the
 * case of templates it seems to not be working (the lines are commented).
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "stl_queue_mock.hpp"
#include "stl_queue_begin.hpp"
#include "hob_AsyncQueue.hpp"
#include "stl_queue_end.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Using hob::AsyncQueue only with the the std::queue's mocked type.
 *****************************************************************************************************/
using hobAsyncQueue = hob::AsyncQueue<QueueMockedType>;

/******************************************************************************************************
 * TEST CLASS
 *****************************************************************************************************/

class AsyncQueueTest : public testing::Test
{
public:
	AsyncQueueTest(void)
		: stlQueueMock{}
	{
	}

public:
	StlQueueMock stlQueueMock;
};

/******************************************************************************************************
 * isEmpty
 *****************************************************************************************************/

TEST_F(AsyncQueueTest, isEmpty_false)
{
	static constexpr bool RESULT = false;

	hobAsyncQueue asyncQueue = {};

	EXPECT_CALL(stlQueueMock, empty()) /**/
		.WillOnce(testing::Return(RESULT));

	EXPECT_EQ(RESULT, asyncQueue.isEmpty());
}

TEST_F(AsyncQueueTest, isEmpty_true)
{
	static constexpr bool RESULT = true;

	hobAsyncQueue asyncQueue = {};

	EXPECT_CALL(stlQueueMock, empty()) /**/
		.WillOnce(testing::Return(RESULT));

	EXPECT_EQ(RESULT, asyncQueue.isEmpty());
}

/******************************************************************************************************
 * push
 *****************************************************************************************************/

TEST_F(AsyncQueueTest, push_success)
{
	hobAsyncQueue asyncQueue = {};

	EXPECT_CALL(stlQueueMock, push(0UL));

	asyncQueue.push(0UL);
}

TEST_F(AsyncQueueTest, push_fail)
{
	hobAsyncQueue asyncQueue = {};

	EXPECT_CALL(stlQueueMock, push(0UL)) /**/
		.WillOnce(testing::Throw(std::bad_alloc()));

	asyncQueue.push(0UL);
}

/******************************************************************************************************
 * pop
 *****************************************************************************************************/

TEST_F(AsyncQueueTest, pop_success)
{
	static constexpr QueueMockedType RESULT = 0UL;

	hobAsyncQueue asyncQueue = {};

	EXPECT_CALL(stlQueueMock, front()) /**/
		.WillOnce(testing::Return(RESULT));
	EXPECT_CALL(stlQueueMock, pop());

	EXPECT_EQ(RESULT, asyncQueue.pop());
}
