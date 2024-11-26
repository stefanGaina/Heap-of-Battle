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

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <cstdlib>
#include <cstdint>
#include <cassert>

// #include "application.hpp"
#include "logger.hpp"

/******************************************************************************************************
 * ENTRY POINT
 *****************************************************************************************************/

std::int32_t main(const std::int32_t argument_count, char** const arguments) noexcept
{
	// std::unique_ptr<hob::engine::application> application = nullptr;

	assert(0 < argument_count);
	assert(nullptr != arguments);

	try
	{
		hob::log::initialize("");
		hob::log::add_sink(
			"terminal",
			hob::log::sink_terminal_configuration{
				{ "[{TIME}] [{FUNCTION}:{LINE}] [{TAG}] {MESSAGE}", "{YEAR}-{MONTH:numeric}-{DAY_MONTH} {HOUR:24}:{MINUTE}:{SECOND}.{MILLISECOND}", 63U, false },
				stdout,
				true });
		HOB_LOG_FATAL("terminal", "test");

		// application = std::make_unique<hob::engine::application>(1 < argument_count ? arguments[1] : "conf.json");
		// application->run();

		return EXIT_SUCCESS;
	}
	catch (const std::exception& exception)
	{
		return EXIT_FAILURE;
	}
}
