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
 * @file hob_Test.cpp
 * @author Gaina Stefan
 * @date 08.02.2024
 * @brief This file implements the class defined in hob_Test.hpp.
 * @todo Add commands from click, hover and key presses.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <exception>
#include <chrono>
#include <SDL2/SDL.h>
#include <plog.h>

#include "hob_Test.hpp"

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

namespace hob
{

#ifdef DEVEL_BUILD

std::ifstream Test::file   = {};
std::thread   Test::thread = {};

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

void Test::init(const char* file_path) noexcept(false)
{
	plog_trace("Test is being initialized.");
	plog_assert(nullptr != file_path);
	plog_assert(false == file.is_open());
	plog_assert(false == thread.joinable());

	try
	{
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit);
		file.open(file_path);

		if (false == file.is_open())
		{
			throw std::exception();
		}
	}
	catch (const std::ifstream::failure& exception)
	{
		throw std::exception();
	}
}

void Test::deinit(void) noexcept
{
	plog_trace("Test is being deinitialized.");
	if (true == thread.joinable())
	{
		plog_debug("Test thread is being joined.");
		thread.join();
		plog_debug("Test thread has joined.");
	}
}

void Test::start(void) noexcept
{
	plog_trace("Test is being started.");
	plog_assert(false == thread.joinable());

	if (false == file.is_open())
	{
		plog_warn("Test file is not opened!");
		return;
	}

	thread = std::thread{ parseCommands };
}

void Test::parseCommands(void) noexcept
{
	std::string line = {};

	plog_info("Test commands are being parsed!");
	plog_assert(true == file.is_open());

	try
	{
		while (std::getline(file, line))
		{
			parseCommand(line);
		}
	}
	catch (const std::ifstream::failure& exception)
	{
		plog_warn("Exception caught while parsing commands!");
	}
}

void Test::parseCommand(std::string& line) noexcept
{
	SDL_Event   event    = {};
	std::string word     = {};
	size_t      argument = 0UL;

	plog_trace("Test command is being parsed.");
	try
	{
		word = "wait";
		if (0 == line.compare(0, word.size(), word))
		{
			plog_debug("Wait command received.");
			argument = std::stoul(line.substr(word.size()));
			std::this_thread::sleep_for(std::chrono::milliseconds(argument));

			return;
		}

		if ("quit" == line)
		{
			plog_debug("Quit command received.");

			event.type = SDL_QUIT;
			if (1 != SDL_PushEvent(&event))
			{
				plog_error("Failed to push quit event! (error message: %s)", SDL_GetError());
				return;
			}

			SDL_PumpEvents();
			return;
		}
	}
	catch (...)
	{
		plog_error("Exception caught while parsing command!");
		plog_assert(false);

		return;
	}

	plog_error("Invalid command! (command: %s)", line.c_str());
}

#endif /*< DEVEL_BUILD */

} /*< namespace hob */