/******************************************************************************************************
 * Heap of Battle Copyright (C) 2024                                                                  *
 *                                                                                                    *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the   *
 * authors be held liable for any damages arising from the use of this software.                      *
 *                                                                                                    *
 * Permission is granted to anyone to use this software for any purpose, including commercial         *
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:   *
 *                                                                                                    *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the   *
 *    original software. If you use this software in a product, an acknowledgment in the product      *
 *    documentation would be appreciated but is not required.                                         *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being *
 *    the original software.                                                                          *
 * 3. This notice may not be removed or altered from any source distribution.                         *
******************************************************************************************************/

/******************************************************************************************************
 * @file hob_AsyncQueue.hpp                                                                           *
 * @date:      @author:                   Reason for change:                                          *
 * 27.08.2023  Gaina Stefan               Initial version.                                            *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file defines the class and method prototypes of the queue.                           *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_ASYNC_QUEUE_HPP_
#define HOB_ASYNC_QUEUE_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <queue>
#include <mutex>

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Thread safe STL queue for one consumer thread and one supplier thread. In the case of multiple
 * consumer threads one might empty the queue after the other checked it is not empty.
*/
template<typename TYPE>
class AsyncQueue final
{
public:
	/**
	 * @brief Default constructor.
	 * @param void
	*/
	AsyncQueue(void) noexcept;

	/**
	 * @brief Default destructor.
	 * @param void
	*/
	~AsyncQueue(void) = default;

	/**
	 * @brief Checks if the queue has any elements stored in it.
	 * @param void
	 * @return true - queue is empty | false - otherwise.
	*/
	bool isEmpty(void) noexcept;

	/**
	 * @brief Inserts an element at the end of the queue.
	 * @param element: The element to be inserted.
	 * @return void
	*/
	void put(TYPE element) noexcept;

	/**
	 * @brief Gets the element at the beginning of the list and removes it. If the queue is empty
	 * (which should not be a valid case) the element will be a default constructed one.
	 * @param void
	 * @return The element.
	*/
	TYPE get(void) noexcept;

private:
	/**
	 * @brief The queue where the elements are being placed.
	*/
	std::queue<TYPE> queue;

	/**
	 * @brief The mutex protecting the queue from multiple threads access.
	*/
	std::mutex mutex;
};

/***********************************************************************************************************************
 * METHOD DEFINITIONS                                                                                                  *
 **********************************************************************************************************************/

template<typename TYPE>
AsyncQueue<TYPE>::AsyncQueue(void) noexcept
	: queue{}
	, mutex{}
{
	plog_trace("Async queue is being constructed.");
}

template<typename TYPE>
bool AsyncQueue<TYPE>::isEmpty(void) noexcept
{
	std::unique_lock<std::mutex> lock(mutex);
	return queue.empty();
}

template<typename TYPE>
void AsyncQueue<TYPE>::put(TYPE element) noexcept
{
	std::unique_lock<std::mutex> lock(mutex);

	plog_verbose("Element is being pushed into asynchronically queue.");
	try
	{
		queue.push(element);
	}
	catch (const std::bad_alloc& exception)
	{
		plog_error("Failed to push element to queue! (bytes: %" PRIu64 ")", sizeof(element));
	}
}

template<typename TYPE>
TYPE AsyncQueue<TYPE>::get(void) noexcept
{
	TYPE element;

	plog_verbose("Element is being popped from asynchronically queue.");
	if (true == isEmpty())
	{
		plog_error("Queue is empty!");
		return (TYPE){};
	}

	mutex.lock();
	element = queue.front();
	queue.pop();
	mutex.unlock();

	return element;
}

} /*< namespace hob */

#endif /*< HOB_ASYNC_QUEUE_HPP_ */
