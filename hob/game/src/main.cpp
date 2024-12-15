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
 * @file main.cpp
 * @author Gaina Stefan
 * @date 15.12.2024
 * @brief This file provides the entry point of the game.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <print>
#include <cassert>
#include <logger.hpp>

#include "game.hpp"

/******************************************************************************************************
 * ENTRY POINT
 *****************************************************************************************************/

std::int32_t main(const std::int32_t arguments_count, char** const arguments) noexcept
{
	assert(0 < arguments_count);
	assert(nullptr != arguments[0]);

	if (1 == arguments_count || 2 == arguments_count && ("--help" == std::string_view{ arguments[1] } || "-h" == std::string_view{ arguments[1] }))
	{
		std::println("Usage: {} <game_configuration> <logger_configuration> (optional)", arguments[0]);
		return EXIT_FAILURE;
	}

	if (3 < arguments_count)
	{
		std::println("Extra parameters will be ignored! (\"-h\" or \"--help\" for usage)");
	}

	assert(nullptr != arguments[1]);

	try
	{
		hob::game::run(arguments[1], 2 < arguments_count ? arguments[2] : "");
		return EXIT_SUCCESS;
	}
	catch (const std::exception& exception)
	{
		if (true == hob::log::is_initialized())
		{
			hob_log_fatal("Caught an exception! (error message: \"{}\")", exception.what());
			return EXIT_FAILURE;
		}

		std::println("Caught an exception! (error message: \"{}\")", exception.what());
		return EXIT_FAILURE;
	}
}
