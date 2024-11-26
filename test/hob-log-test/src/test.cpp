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

#include <print>

#include "apitester.hpp"
#include "logger.hpp"

/******************************************************************************************************
 * FUNCTION DEFINITIONS
 *****************************************************************************************************/

HOB_APITEST(FATAL, sink_name, message)
{
	HOB_LOG_FATAL(sink_name, message);
}

HOB_APITEST(initialize, configuration_file_path)
{
	hob::log::initialize(configuration_file_path);
	std::println("hob-log has been initialized successfully!");
}

HOB_APITEST(add_sink_terminal, sink_name, format, time_format, severity_level, async_mode, stream, color)
{
	hob::log::add_sink(sink_name, hob::log::sink_terminal_configuration{ { format, time_format, severity_level, async_mode }, stream, color });
	std::println("\"{}\" has been added successfully!", sink_name);
}
