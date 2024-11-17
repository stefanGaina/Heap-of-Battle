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
 * @file worker.cpp
 * @author Gaina Stefan
 * @date 17.11.2024
 * @brief This file implements the class defined in worker.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <functional>

#include "worker.hpp"
#include "utility.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob::log
{

worker::worker(callback&& callback, std::atomic<std::uint64_t>& lost_logs_count) noexcept
	: log_function{ std::move(callback) }
	, lost_logs_count{ lost_logs_count }
	, queue{}
	, is_working{ true }
	, thread{ std::bind(&worker::log_messages, this) }
{
}

worker::~worker(void) noexcept
{
	is_working = false;
	queue.interrupt_wait();

	if (true == thread.joinable())
	{
		thread.join();
	}
}

bool worker::log(const std::uint8_t severity_bit, std::string&& message) noexcept
{
	assert(nullptr != this);
	assert(true == is_working);

	return queue.emplace(severity_bit, std::move(message));
}

void worker::log_messages(void) noexcept
{
	std::optional<message_queue::payload> message = std::nullopt;

	assert(nullptr != this);
	assert(true == is_working);

	while (true == is_working || false == queue.is_empty())
	{
		message = queue.pop();
		if (false == message.has_value())
		{
			continue;
		}

		lost_logs_count += false == log_function(message->first, std::move(message->second)) ? UINT64_MAX > lost_logs_count ? 1UL : 0UL : 0UL;
	}
}

} /*< namespace hob::log */
