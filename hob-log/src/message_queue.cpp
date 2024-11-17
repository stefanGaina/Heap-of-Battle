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
 * @file message_queue.cpp
 * @author Gaina Stefan
 * @date 17.11.2024
 * @brief This file implements the class defined in message_queue.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "message_queue.hpp"
#include "utility.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob::log
{

bool message_queue::is_empty(void) const noexcept
{
	std::lock_guard<std::mutex> lock = std::lock_guard{ mutex };

	assert(nullptr != this);
	return queue.empty();
}

bool message_queue::emplace(const std::uint8_t severity_bit, std::string&& message) noexcept
{
	std::lock_guard<std::mutex> lock = std::lock_guard{ mutex };

	assert(nullptr != this);

	try
	{
		(void)queue.emplace(severity_bit, std::move(message));
		condition_notifier.notify_one();

		return true;
	}
	catch (const std::bad_alloc& exception)
	{
		DEBUG_PRINT("Caught std::bad_alloc while emplacing message into queue! (error message: \"{}\")", exception.what());
		return false;
	}
}

std::optional<message_queue::payload> message_queue::pop(void) noexcept
{
	payload						 message = { 0U, "" };
	std::unique_lock<std::mutex> lock	 = std::unique_lock{ mutex };

	assert(nullptr != this);

	if (true == queue.empty())
	{
		condition_notifier.wait(lock);
		if (true == queue.empty())
		{
			return std::nullopt;
		}
	}

	message = queue.front();
	queue.pop();

	return std::optional<payload>{ std::move(message) };
}

void message_queue::interrupt_wait(void) noexcept
{
	std::lock_guard<std::mutex> lock = std::lock_guard{ mutex };

	assert(nullptr != this);
	condition_notifier.notify_one();
}

} /*< namespace hob::log */
