/******************************************************************************************************
 * @file hob_AsyncQueue.hpp                                                                           *
 * @date:      @author:                   Reason for change:                                          *
 * 27.08.2023  Gaina Stefan               Initial version.                                            *
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
	std::queue<TYPE> m_queue;

	/**
	 * @brief The mutex protecting the queue from multiple threads access.
	*/
	std::mutex m_mutex;
};

/***********************************************************************************************************************
 * METHOD DEFINITIONS                                                                                                  *
 **********************************************************************************************************************/

template<typename TYPE>
AsyncQueue<TYPE>::AsyncQueue(void) noexcept
	: m_queue{}
	, m_mutex{}
{
	plog_trace("Async queue is being constructed. (size: %" PRIu64 ") (1: %" PRIu64 ") (2: %" PRIu64 ")", sizeof(*this), sizeof(m_queue), sizeof(m_mutex));
}

template<typename TYPE>
bool AsyncQueue<TYPE>::isEmpty(void) noexcept
{
	std::unique_lock<std::mutex> lock(m_mutex);
	return m_queue.empty();
}

template<typename TYPE>
void AsyncQueue<TYPE>::put(TYPE element) noexcept
{
	std::unique_lock<std::mutex> lock(m_mutex);

	plog_verbose("Element is being pushed into asynchronically queue.");
	try
	{
		m_queue.push(element);
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

	m_mutex.lock();
	element = m_queue.front();
	m_queue.pop();
	m_mutex.unlock();

	return element;
}

} /*< namespace hob */

#endif /*< HOB_ASYNC_QUEUE_HPP_ */
