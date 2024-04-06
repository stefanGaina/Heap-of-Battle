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

#ifndef STL_QUEUE_MOCK_HPP_
#define STL_QUEUE_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>

#include "stl_queue_begin.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

using QueueMockedType = uint64_t;

namespace std
{

template<typename TYPE>
class queue
{
public:
	bool empty(void);
	void push(const TYPE& __x) noexcept(false);
	TYPE front(void) noexcept;
	void pop(void) noexcept;
};

} /*< namespace std */

class StlQueueDummy
{
public:
	virtual ~StlQueueDummy(void) = default;

	virtual bool			empty(void)						 = 0;
	virtual void			push(const QueueMockedType& __x) = 0;
	virtual QueueMockedType front(void)						 = 0;
	virtual void			pop(void)						 = 0;
};

class StlQueueMock : public StlQueueDummy
{
public:
	StlQueueMock(void)
	{
		stlQueueMock = this;
	}

	virtual ~StlQueueMock(void)
	{
		stlQueueMock = nullptr;
	}

	MOCK_METHOD0(empty, bool(void));
	MOCK_METHOD1(push, void(const QueueMockedType&));
	MOCK_METHOD0(front, QueueMockedType(void));
	MOCK_METHOD0(pop, void(void));

public:
	static StlQueueMock* stlQueueMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

StlQueueMock* StlQueueMock::stlQueueMock = nullptr;

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace std
{

template<typename TYPE>
bool queue<TYPE>::empty(void)
{
	// ASSERT_NE(nullptr, StlQueueMock::stlQueueMock) << "empty(): nullptr == StlQueueMock::stlQueueMock";
	if (nullptr == StlQueueMock::stlQueueMock)
	{
		ADD_FAILURE() << "empty(): nullptr == StlQueueMock::stlQueueMock";
	}
	return StlQueueMock::stlQueueMock->empty();
}

template<typename TYPE>
void queue<TYPE>::push(const TYPE& __x) noexcept(false)
{
	if (nullptr == StlQueueMock::stlQueueMock)
	{
		ADD_FAILURE() << "push(): nullptr == StlQueueMock::stlQueueMock";
		return;
	}
	StlQueueMock::stlQueueMock->push(__x);
}

template<typename TYPE>
TYPE queue<TYPE>::front(void) noexcept
{
	// ASSERT_NE(nullptr, StlQueueMock::stlQueueMock) << "front(): nullptr == StlQueueMock::stlQueueMock";
	if (nullptr == StlQueueMock::stlQueueMock)
	{
		ADD_FAILURE() << "front(): nullptr == StlQueueMock::stlQueueMock";
	}
	return StlQueueMock::stlQueueMock->front();
}

template<typename TYPE>
void queue<TYPE>::pop(void) noexcept
{
	if (nullptr == StlQueueMock::stlQueueMock)
	{
		ADD_FAILURE() << "pop(): nullptr == StlQueueMock::stlQueueMock";
		return;
	}
	StlQueueMock::stlQueueMock->pop();
}

} /*< namespace std */

#include "stl_queue_end.hpp"

#endif /*< STL_QUEUE_MOCK_HPP_ */
