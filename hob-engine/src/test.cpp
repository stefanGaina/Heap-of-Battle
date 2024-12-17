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
 * @file test.cpp
 * @author Gaina Stefan
 * @date 15.12.2024
 * @brief This file implements the class defined in test.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef NDEBUG

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <memory>
#include <functional>
#include <cassert>
#include <logger.hpp>

#include "test.hpp"

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

namespace hob::engine
{

/******************************************************************************************************
 * @brief The unique object used for handling debug commands and inject events.
 *****************************************************************************************************/
static std::unique_ptr<test> test_object = nullptr;

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

void test::initialize(const std::filesystem::path& file_path) noexcept(false)
{
	hob_log_default_assert(nullptr == test_object);
	hob_log_default_trace("Test is being initialized. (file path: \"{}\")", file_path.string());

	test_object = std::make_unique<test>(file_path);
}

test::test(const std::filesystem::path& file_path) noexcept(false)
	: file{}
	, thread{}
	, mutex{}
	, queue{}
{
	hob_log_default_assert(false == file_path.empty());
	hob_log_default_trace("Test is being constructed. (file path: \"{}\")", file_path.string());

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit);
	file.open(file_path, std::ios::in);

	thread = std::thread{ std::bind(&test::parse_commands, this) };
}

test::~test(void) noexcept
{
	hob_log_default_trace("Test is being destructed. (this: \'{:p}\')", reinterpret_cast<void*>(this));

	if (true == thread.joinable())
	{
		hob_log_default_trace("Test thread is being joined.");
		thread.join();
		hob_log_default_trace("Test thread has joined.");
	}
}

bool test::poll_event(sf::Window& window, sf::Event& event) noexcept
{
	hob_log_default_trace("Event is being polled.");
	return true == window.pollEvent(event) || nullptr != test_object && true == test_object->poll_event(event);
}

bool test::poll_event(sf::Event& event) noexcept
{
	std::lock_guard<std::mutex> lock{ mutex };

	hob_log_default_assert(nullptr != this);
	hob_log_default_trace("Test event is being polled.");

	if (true == queue.empty())
	{
		return false;
	}

	event = queue.front();
	queue.pop();

	return true;
}

void test::parse_commands(void) noexcept
{
	std::string line = "";

	hob_log_default_assert(nullptr != this);
	hob_log_default_assert(true == file.is_open());
	hob_log_default_info("Test commands are being parsed!");

	try
	{
		while (std::getline(file, line))
		{
			parse_command(line);
		}
	}
	catch (std::exception& exception)
	{
		hob_log_default_error("Caught \'std::exception\' during parsing \"{}\"! (error message: \"{}\")", line, exception.what());
	}
}

void test::parse_command(const std::string& line) noexcept(false)
{
	std::string word  = "";
	sf::Event	event = {};

	word = "wait";
	if (0 == line.compare(0, word.size(), word))
	{
		hob_log_default_debug("Wait command received.");

		std::this_thread::sleep_for(std::chrono::milliseconds(std::stoul(line.substr(word.size()))));
		return;
	}

	if ("quit" == line)
	{
		hob_log_default_debug("Quit command received.");

		event.type = sf::Event::EventType::Closed;
		queue.push(event);
		return;
	}

	hob_log_default_error("Invalid command! (command: \"{}\")", line);
}

} /*< namespace hob::engine */

#endif /*< NDEBUG */
