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
 * @brief 
 *****************************************************************************************************/
class HOB_LOG_LOCAL worker final
{
public:
	/**
	 * @brief 
	 *************************************************************************************************/
	using callback = std::function<bool(std::uint8_t, std::string&&)>;

	/**
	 * @brief Construct a new worker object
	 * @param callback
	 *************************************************************************************************/
	worker(callback&& callback, std::atomic<std::uint64_t>& lost_logs_count) noexcept;

	/**
	 * @brief Destroy the worker object
	 *************************************************************************************************/
	~worker(void) noexcept;

	/**
	 * @brief 
	 * @param severity_bit 
	 * @param message 
	 * @return true 
	 * @return false 
	 *************************************************************************************************/
	[[nodiscard]] bool log(std::uint8_t severity_bit, std::string&& message) noexcept;

private:
	/**
	 * @brief 
	 *************************************************************************************************/
	void log_messages(void) noexcept;

private:
	/**
	 * @brief 
	 *************************************************************************************************/
	callback log_function;

	/**
	 * @brief 
	 *************************************************************************************************/
	std::atomic<std::uint64_t>& lost_logs_count;

	/**
	 * @brief 
	 *************************************************************************************************/
	message_queue queue;

	/**
	 * @brief 
	 *************************************************************************************************/
	bool is_working;

	/** ***********************************************************************************************
	 * @brief TODO
	 *************************************************************************************************/
	std::thread thread;
};

} /*< namespace hob::log */

#endif /*< HOB_LOG_INTERNAL_WORKER_HPP_ */
