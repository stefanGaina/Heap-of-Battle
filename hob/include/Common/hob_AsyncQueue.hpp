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
 * @file hob_AsyncQueue.hpp
 * @author Gaina Stefan
 * @date 27.08.2023
 * @brief This file defines the class and method prototypes of the queue.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_ASYNC_QUEUE_HPP_
#define HOB_ASYNC_QUEUE_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <queue>
#include <mutex>

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

/** ***************************************************************************************************
 * @brief Thread safe STL queue for one consumer thread and one supplier thread.
 * @details It is used for updates that are being processed on other threads than the main one. In the
 * case of multiple consumer threads one might empty the queue after the other checked it is not empty.
 * This case is accepted as for the moment is not used this way.
 *****************************************************************************************************/
template<typename TYPE>
class AsyncQueue final
{
public:
	/** ***********************************************************************************************
	 * @brief Checks if the queue has any elements stored in it.
	 * @param void
	 * @return true - queue is empty.
	 * @return false - queue has at least 1 element.
	 *************************************************************************************************/
	bool isEmpty(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Inserts an element at the end of the queue.
	 * @param element: The element to be inserted.
	 * @return void
	 *************************************************************************************************/
	void push(TYPE element) noexcept;

	/** ***********************************************************************************************
	 * @brief Gets the element at the beginning of the list and removes it. If the queue is empty
	 * (which should not be a valid case) the game will abort() in case of debug builds and crash in
	 * the production builds.
	 * @param void
	 * @return The element.
	 *************************************************************************************************/
	TYPE pop(void) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief The queue where the elements are being placed.
	 *************************************************************************************************/
	std::queue<TYPE> queue;

	/** ***********************************************************************************************
	 * @brief The mutex protecting the queue from multiple threads access.
	 *************************************************************************************************/
	std::mutex mutex;
};

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

template<typename TYPE>
bool AsyncQueue<TYPE>::isEmpty(void) noexcept
{
	std::unique_lock<std::mutex> lock(mutex);
	return queue.empty();
}

template<typename TYPE>
void AsyncQueue<TYPE>::push(TYPE element) noexcept
{
	std::unique_lock<std::mutex> lock(mutex);

	plog_verbose("Element is being pushed into asynchronically queue.");
	try
	{
		queue.push(element);
	}
	catch (...)
	{
		plog_error("Failed to push element to queue! (bytes: %" PRIu64 ")", sizeof(element));
	}
}

template<typename TYPE>
TYPE AsyncQueue<TYPE>::pop(void) noexcept
{
	TYPE element;

	plog_verbose("Element is being popped from asynchronically queue.");
	plog_assert(false == isEmpty());

	mutex.lock();
	element = queue.front();
	queue.pop();
	mutex.unlock();

	return element;
}

} /*< namespace hob */

#endif /*< HOB_ASYNC_QUEUE_HPP_ */
