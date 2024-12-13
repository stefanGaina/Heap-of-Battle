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

HOB_APITEST(fatal, sink_name, message)
{
	hob_log_fatal(sink_name, message);
}

HOB_APITEST(default_fatal, message)
{
	hob_log_default_fatal(message);
}

HOB_APITEST(error, sink_name, message)
{
	hob_log_error(sink_name, message);
}

HOB_APITEST(default_error, message)
{
	hob_log_default_error(message);
}

HOB_APITEST(warn, sink_name, message)
{
	hob_log_warn(sink_name, message);
}

HOB_APITEST(default_warn, message)
{
	hob_log_default_warn(message);
}

HOB_APITEST(info, sink_name, message)
{
	hob_log_info(sink_name, message);
}

HOB_APITEST(default_info, message)
{
	hob_log_default_info(message);
}

HOB_APITEST(debug, sink_name, message)
{
	hob_log_debug(sink_name, message);
}

HOB_APITEST(default_debug, message)
{
	hob_log_default_debug(message);
}

HOB_APITEST(trace, sink_name, message)
{
	hob_log_trace(sink_name, message);
}

HOB_APITEST(default_trace, message)
{
	hob_log_default_trace(message);
}

HOB_APITEST(expect, sink_name, condition)
{
	hob_log_expect(sink_name, true == condition);
}

HOB_APITEST(default_expect, condition)
{
	hob_log_default_expect(true == condition);
}

HOB_APITEST(assert, sink_name, condition)
{
	hob_log_assert(sink_name, true == condition);
}

HOB_APITEST(default_assert, condition)
{
	hob_log_default_assert(true == condition);
}

HOB_APITEST(abort, sink_name)
{
	hob_log_abort(sink_name);
}

HOB_APITEST(default_abort)
{
	hob_log_default_abort();
}

HOB_APITEST(is_initialized)
{
	std::println("The logger is {}initialized!", true == hob::log::is_initialized() ? "" : "NOT ");
}

HOB_APITEST(initialize, configuration_file_path)
{
	hob::log::initialize(configuration_file_path);
	std::println("The logger has been initialized successfully!");
}

HOB_APITEST(deinitialize)
{
	hob::log::deinitialize();
	std::println("The logger has been deinitialized successfully!");
}

HOB_APITEST(add_sink_terminal, sink_name, format, time_format, severity_level, async_mode, stream, color)
{
	hob::log::add_sink(sink_name, hob::log::sink_terminal_configuration{ { format, time_format, severity_level, async_mode }, stream, color });
	std::println("\"{}\" has been added successfully!", sink_name);
}

HOB_APITEST(remove_sink, sink_name)
{
	hob::log::remove_sink(sink_name);
	std::println("\"{}\" has been removed successfully!", sink_name);
}

HOB_APITEST(is_sink_valid, sink_name)
{
	std::println("\"{}\" is {}valid", sink_name, true == hob::log::is_sink_valid(sink_name) ? "" : "NOT ");
}

HOB_APITEST(set_default_sink_name, sink_name)
{
	hob::log::set_default_sink_name(sink_name);
	std::println("\"{}\" has been set as default successfully!", sink_name);
}

HOB_APITEST(get_default_sink_name)
{
	std::println("The default sink name is: \"{}\"", hob::log::get_default_sink_name());
}
