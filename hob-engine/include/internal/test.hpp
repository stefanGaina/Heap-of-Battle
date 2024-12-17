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
 * @file test.hpp
 * @author Gaina Stefan
 * @date 15.12.2024
 * @brief This header defines the test class.
 * @todo Add commands for keys and mouse.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_ENGINE_INTERNAL_TEST_HPP_
#define HOB_ENGINE_INTERNAL_TEST_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#ifndef NDEBUG

#include <fstream>
#include <thread>
#include <mutex>
#include <queue>
#include <filesystem>
#include <SFML/Graphics.hpp>

#include "details/visibility.hpp"

#endif /*< NDEBUG */

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

#ifdef NDEBUG

/** ***************************************************************************************************
 * @brief Polls the event without injection.
 * @param window: The window of which the event is being polled.
 * @param event: The event to be returned.
 * @returns true - if an event was returned.
 * @returns false - if the event queue was empty.
 * @throws N/A.
 *****************************************************************************************************/
#define hob_engine_poll_event(window, event) window.pollEvent(event)

#else

/** ***************************************************************************************************
 * @brief Polls the event with the possibility of test events being injected.
 * @param window: The window of which the event is being polled.
 * @param event: The event to be returned.
 * @returns true - if an event was returned.
 * @returns false - false if both event queue were empty.
 * @throws N/A.
 *****************************************************************************************************/
#define hob_engine_poll_event(window, event) hob::engine::test::poll_event(window, event)

#endif /*< NDEBUG */

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

#ifndef NDEBUG

namespace hob::engine
{

/** ***************************************************************************************************
 * @brief Class allowing event injection in debug mode.
 * @details This is useful for automation testing. The following commands are supported:
 * - wait <milliseconds>: Pauses the execution for the specified number of milliseconds.
 * - quit: Simulates the closure of the window by injecting an sf::Event::Closed event.
 *****************************************************************************************************/
class HOB_LOG_LOCAL test final
{
public:
	/** ***********************************************************************************************
	 * @brief Initializes the testing mechanism, without this the polling of events will behave as
	 * normal. This is the only method meant to be called directly.
	 * @param file_path: The path to the file containing the commands.
	 * @returns void
	 * @throws std::ios_base:: If the file fails to be opened.
	 * @throws std::bad_alloc If memory allocation for the testing object fails.
	 *************************************************************************************************/
	static void initialize(const std::filesystem::path& file_path) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Polls the event with the possibility of test events being injected.
	 * @param window: The window of which the event is being polled.
	 * @param event: The event to be returned.
	 * @returns true - if an event was returned.
	 * @returns false - false if both event queue were empty.
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] static bool poll_event(sf::Window& window, sf::Event& event) noexcept;

	/** ***********************************************************************************************
	 * @brief Opens the test command file and starts a parsing thread.
	 * @param file_path: The path to the file containing the commands.
	 * @throws std::ios_base:: If the file fails to be opened.
	 * @throws std::bad_alloc If memory allocation fails.
	 *************************************************************************************************/
	test(const std::filesystem::path& file_path) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Joins the thread on which the commands are being parsed. If it has not been finished it
	 * will wait.
	 * @param void
	 * @throws N/A.
	 *************************************************************************************************/
	~test(void) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Polls events from the test event queue.
	 * @param event: The event to be returned.
	 * @returns true - if an event was returned.
	 * @returns false - if the test event queue was empty.
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] bool poll_event(sf::Event& event) noexcept;

	/** ***********************************************************************************************
	 * @brief Parses the test command file and processes each command.
	 * @param void
	 * @returns void
	 * @throws N/A.
	 *************************************************************************************************/
	void parse_commands(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Parses and executes a single command from the test command file.
	 * @param line: The command line to parse and execute.
	 * @returns void
	 * @throws std::invalid_argument: If the command is not recognized or malformed.
	 *************************************************************************************************/
	void parse_command(const std::string& line) noexcept(false);

private:
	/** ***********************************************************************************************
	 * @brief The input file stream used to read the test command file.
	 *************************************************************************************************/
	std::ifstream file;

	/** ***********************************************************************************************
	 * @brief The thread used to parse the test commands asynchronously.
	 *************************************************************************************************/
	std::thread thread;

	/** ***********************************************************************************************
	 * @brief Mutex used to ensure thread-safe access to the event queue.
	 *************************************************************************************************/
	std::mutex mutex;

	/** ***********************************************************************************************
	 * @brief The event queue that stores events injected from the test commands.
	 *************************************************************************************************/
	std::queue<sf::Event> queue;
};

} /*< namespace hob::engine */

#endif /*< NDEBUG */

#endif /*< HOB_ENGINE_INTERNAL_TEST_HPP_ */
