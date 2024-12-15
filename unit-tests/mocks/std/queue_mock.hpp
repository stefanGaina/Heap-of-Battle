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

#ifndef QUEUE_MOCK_HPP_
#define QUEUE_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>

#include "queue_begin.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

using queue_mocked_type = std::uint64_t;

namespace std
{

template<typename TYPE>
class queue
{
public:
	bool empty(void);
	void push(const TYPE& __x) noexcept(false);
	template<typename... args>
	decltype(auto) emplace(args&&... arguments);
	void emplace();
	TYPE front(void) noexcept;
	void pop(void) noexcept;
};

// class StlQueueDummy
// {
// public:
// 	virtual ~StlQueueDummy(void) = default;

// 	virtual bool			empty(void)						 = 0;
// 	virtual void			push(const QueueMockedType& __x) = 0;
// 	virtual QueueMockedType front(void)						 = 0;
// 	virtual void			pop(void)						 = 0;
// };

class queue_mock
{
public:
	queue_mock(void)
	{
		queue_mock_obj = this;
	}

	virtual ~queue_mock(void)
	{
		queue_mock_obj = nullptr;
	}

	MOCK_METHOD0(empty, bool(void));
	MOCK_METHOD1(push, void(const queue_mocked_type&));
	MOCK_METHOD0(emplace, queue_mocked_type&(void));
	MOCK_METHOD0(front, queue_mocked_type(void));
	MOCK_METHOD0(pop, void(void));

public:
	static queue_mock* queue_mock_obj;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

queue_mock* queue_mock::queue_mock_obj = nullptr;

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

template<typename TYPE>
bool queue<TYPE>::empty(void)
{
	if (nullptr == queue_mock::queue_mock_obj)
	{
		ADD_FAILURE() << "empty(): nullptr == queue_mock::queue_mock_obj";
	}
	return queue_mock::queue_mock_obj->empty();
}

template<typename TYPE>
void queue<TYPE>::push(const TYPE& __x) noexcept(false)
{
	if (nullptr == queue_mock::queue_mock_obj)
	{
		ADD_FAILURE() << "push(): nullptr == queue_mock::queue_mock_obj";
		return;
	}
	queue_mock::queue_mock_obj->push(__x);
}

template<typename TYPE>
template<typename... args>
decltype(auto) queue<TYPE>::emplace(args&&... arguments)
{
	if (nullptr == queue_mock::queue_mock_obj)
	{
		ADD_FAILURE() << "emplace(): nullptr == queue_mock::queue_mock_obj";
	}
	return queue_mock::queue_mock_obj->emplace();
}

template<typename TYPE>
TYPE queue<TYPE>::front(void) noexcept
{
	if (nullptr == queue_mock::queue_mock_obj)
	{
		ADD_FAILURE() << "front(): nullptr == queue_mock::queue_mock_obj";
	}
	return queue_mock::queue_mock_obj->front();
}

template<typename TYPE>
void queue<TYPE>::pop(void) noexcept
{
	if (nullptr == queue_mock::queue_mock_obj)
	{
		ADD_FAILURE() << "pop(): nullptr == queue_mock::queue_mock_obj";
		return;
	}
	queue_mock::queue_mock_obj->pop();
}

} /*< namespace std */

#include "queue_end.hpp"

#endif /*< QUEUE_MOCK_HPP_ */
