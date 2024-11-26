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
 * @file worker.hpp
 * @author Gaina Stefan
 * @date 17.11.2024
 * @brief This header defines the worker class.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_LOG_INTERNAL_WORKER_HPP_
#define HOB_LOG_INTERNAL_WORKER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <string>
#include <thread>

#include "message_queue.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob::log
{

/** ***************************************************************************************************
 * @brief This class provides an asynchronous logging mechanism.
 * @details The worker class accepts log messages from the caller thread, queues them, and processes
 * them on a separate worker thread, ensuring that the caller thread is not blocked while waiting for
 * the logging operation to complete.
 *****************************************************************************************************/
class HOB_LOG_LOCAL worker final
{
public:
	/** ***********************************************************************************************
	 * @brief Type alias for a callback function used to handle log messages.
	 * @param severity_bit The severity level of the log message.
	 * @param message The log message to be processed.
	 * @returns true - the message has been logged successfully.
	 * @returns false - the log has been lost.
	 * @throws N/A.
	 *************************************************************************************************/
	using callback = std::function<bool(std::uint8_t, std::string&&)>;

	/** ***********************************************************************************************
	 * @brief Creates the worker thread that waits for messages to be inserted into the queue.
	 * @param callback: The function that will be called to handle the logging of the message on the
	 * working thread.
	 * @param lost_logs_count: Reference to the counter of lost logs due to unrecoverable errors.
	 * @throws N/A.
	 *************************************************************************************************/
	worker(callback&& callback, std::atomic<std::uint64_t>& lost_logs_count) noexcept;

	/** ***********************************************************************************************
	 * @brief Logs the buffered messages and joins the working thread.
	 * @param void
	 * @throws N/A.
	 *************************************************************************************************/
	~worker(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Logs the message through the given callback on a separate thread. It is thread-safe.
	 * @param severity_bit: Bit indicating the type of message that is being logged (see
	 * hob::log::severity_level).
	 * @param message: The message to be logged.
	 * @returns true - the message has been logged successfully.
	 * @returns false - the log has been lost.
	 *************************************************************************************************/
	[[nodiscard]] bool log(std::uint8_t severity_bit, std::string&& message) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Logs the message from the queue through the given callback. It is **not** thread-safe.
	 * @param void
	 * @returns void
	 * @throws N/A.
	 *************************************************************************************************/
	void log_messages(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Logs a message from the queue and waits if the queue is empty until a message is being
	 * inserted. It is **not** thread-safe.
	 * @param void
	 * @returns void
	 * @throws N/A.
	 *************************************************************************************************/
	void log_message(void) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief The function that will be called when a message is being consumed from the queue.
	 *************************************************************************************************/
	callback log_function;

	/** ***********************************************************************************************
	 * @brief How many logs have been lost due to unrecoverable errors.
	 *************************************************************************************************/
	std::atomic<std::uint64_t>& lost_logs_count;

	/** ***********************************************************************************************
	 * @brief The thread-safe queue that holds the pending message to be logged.
	 *************************************************************************************************/
	message_queue queue;

	/** ***********************************************************************************************
	 * @brief The flag indicating if the worker thread should keep running.
	 *************************************************************************************************/
	bool is_working;

	/** ***********************************************************************************************
	 * @brief The worker thread on which the message are being logged.
	 *************************************************************************************************/
	std::thread thread;
};

} /*< namespace hob::log */

#endif /*< HOB_LOG_INTERNAL_WORKER_HPP_ */
