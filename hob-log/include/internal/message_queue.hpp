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

#ifndef HOB_LOG_INTERNAL_MESSAGE_QUEUE_HPP_
#define HOB_LOG_INTERNAL_MESSAGE_QUEUE_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

#include "details/visibility.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob::log
{

/** ***************************************************************************************************
 * @brief Thread safe STL queue for one consumer thread and one supplier thread. It is used for sending
 * messages to the thread that does the logging.
 * @details In the case of multiple consumer threads one might empty the queue after the other checked
 * it is not empty. This case is accepted as for the moment is not used this way.
 *****************************************************************************************************/
class HOB_LOG_LOCAL message_queue final
{
public:
	/** ***********************************************************************************************
	 * @brief The data type of the log that is being stored inside the queue.
	 *************************************************************************************************/
	using payload = std::pair<std::uint8_t, std::string>;

	/** ***********************************************************************************************
	 * @brief Checks if the queue has any message stored in it.
	 * @param void
	 * @returns true - queue is empty.
	 * @returns false - queue has at least 1 message.
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] bool is_empty(void) const noexcept;

	/** ***********************************************************************************************
	 * @brief Emplaces a log at the end of the queue.
	 * @param severity_bit: Bit indicating the type of message that is being logged (see
	 * log1cxx::severity_level).
	 * @param message: The message of the log.
	 * @returns true - the log has been emplaced successfully.
	 * @returns false - the log has been lost.
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] bool emplace(std::uint8_t severity_bit, std::string&& message) noexcept;

	/** ***********************************************************************************************
	 * @brief Gets the message at the beginning of the list and removes it. If the queue is empty waits
	 * until a message is being emplaced.
	 * @param void
	 * @returns The first message stored.
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] std::optional<payload> pop(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Guarantees that the consumer thread is not stuck waiting in a pop() call.
	 * @param void
	 * @returns void
	 * @throws N/A.
	 *************************************************************************************************/
	void interrupt_wait(void) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief The queue where the messages are being placed.
	 *************************************************************************************************/
	std::queue<payload> queue;

	/** ***********************************************************************************************
	 * @brief The mutex protecting the queue from multiple threads access.
	 *************************************************************************************************/
	mutable std::mutex mutex;

	/** ***********************************************************************************************
	 * @brief The variable that controls the consumer and the supplier thread.
	 *************************************************************************************************/
	std::condition_variable condition_notifier;
};

} /*< namespace hob::log */

#endif /*< HOB_LOG_INTERNAL_MESSAGE_QUEUE_HPP_ */
