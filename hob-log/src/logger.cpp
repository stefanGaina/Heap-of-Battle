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
 * @file logger.cpp
 * @author Gaina Stefan
 * @date 17.11.2024
 * @brief This file implements the interface defined in logger.hpp.
 * @details It serves as a facade to the sink manager and all sink types, having the API centralized
 * in C-style, not managing objects directly.
 * @todo Add configurable compile time constructor.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <vector>
#include <memory>

#include "logger.hpp"
#include "sink_manager.hpp"
#include "sink_terminal.hpp"
#include "utility.hpp"

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

namespace hob::log
{

/** ***************************************************************************************************
 * @brief This is the unique logger instance.
 * @details It is global (only in this file in contrast to a singleton) by design so the user does not
 * have manage the object and multiple loggers are not allowed anyway.
 *****************************************************************************************************/
static std::unique_ptr<sink_manager> logger = nullptr;

/******************************************************************************************************
 * LOCAL FUNCTIONS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Gets the logger, ensuring that it is valid (non nullptr). It is thread-safe.
 * @param void
 * @returns Reference to the unique logger instance.
 * @throws std::logic_error: If the logger has not been initialized successfully.
 *****************************************************************************************************/
static sink_manager& get_logger(void) noexcept(false);

/******************************************************************************************************
 * FUNCTION DEFINITIONS
 *****************************************************************************************************/

bool is_initialized(void) noexcept
{
	return nullptr != logger;
}

void initialize(const std::string_view configuration_file_path) noexcept(false)
{
	logger =
		false == is_initialized() ? std::make_unique<sink_manager>(configuration_file_path) : throw std::logic_error{ "The logger has already been initialized!" };
}

void deinitialize(void) noexcept
{
	logger = nullptr;
}

void add_sink(const std::string_view sink_name, const sink_terminal_configuration& configuration) noexcept(false)
{
	get_logger().add_sink(sink_name, configuration);
}

void add_sink(const std::string_view sink_name, const std::list<std::string>& sink_names) noexcept(false)
{
	get_logger().add_sink(sink_name, sink_names);
}

void remove_sink(const std::string_view sink_name) noexcept
{
	try
	{
		get_logger().remove_sink(sink_name);
	}
	catch (const std::logic_error& exception)
	{
		DEBUG_PRINT("Caught std::logic_error while removing sink! (error message: \"{}\")", exception.what());
	}
}

bool is_sink_valid(const std::string_view sink_name) noexcept
{
	try
	{
		return get_logger().is_sink_valid(sink_name);
	}
	catch (const std::logic_error& exception)
	{
		return false;
	}
}

void set_default_sink_name(const std::string_view sink_name) noexcept(false)
{
	get_logger().set_default_sink_name(sink_name);
}

std::string_view get_default_sink_name(void) noexcept(false)
{
	return get_logger().get_default_sink_name();
}

std::uint64_t get_lost_logs(const std::string_view sink_name) noexcept(false)
{
	return get_logger().get_sink<sink_base>(sink_name).get_lost_logs();
}

void set_format(const std::string_view sink_name, const std::string_view format) noexcept(false)
{
	get_logger().get_sink<sink_base>(sink_name).set_format(format);
}

std::string_view get_format(const std::string_view sink_name) noexcept(false)
{
	return get_logger().get_sink<sink_base>(sink_name).get_format();
}

void set_time_format(const std::string_view sink_name, const std::string_view time_format) noexcept(false)
{
	get_logger().get_sink<sink_base>(sink_name).set_time_format(time_format);
}

std::string_view get_time_format(const std::string_view sink_name) noexcept(false)
{
	return get_logger().get_sink<sink_base>(sink_name).get_time_format();
}

void set_severity_level(const std::string_view sink_name, const std::uint8_t severity_level) noexcept(false)
{
	get_logger().get_sink<sink_base>(sink_name).set_severity_level(severity_level);
}

std::uint8_t get_severity_level(const std::string_view sink_name) noexcept(false)
{
	return get_logger().get_sink<sink_base>(sink_name).get_severity_level();
}

void set_async_mode(const std::string_view sink_name, const bool async_mode) noexcept(false)
{
	get_logger().get_sink<sink_base>(sink_name).set_async_mode(async_mode);
}

bool get_async_mode(const std::string_view sink_name) noexcept(false)
{
	return get_logger().get_sink<sink_base>(sink_name).get_async_mode();
}

void set_stream(const std::string_view sink_name, FILE* const stream) noexcept(false)
{
	get_logger().get_sink<sink_terminal>(sink_name).set_stream(stream);
}

FILE* get_stream(const std::string_view sink_name) noexcept(false)
{
	return get_logger().get_sink<sink_terminal>(sink_name).get_stream();
}

void set_color(const std::string_view sink_name, const bool color) noexcept(false)
{
	get_logger().get_sink<sink_terminal>(sink_name).set_color(color);
}

bool get_color(const std::string_view sink_name) noexcept(false)
{
	return get_logger().get_sink<sink_terminal>(sink_name).get_color();
}

namespace details
{

void log(const std::string_view sink_name,
		 const std::uint8_t		severity_bit,
		 const std::string_view tag,
		 const std::string_view file_path,
		 const std::string_view function_name,
		 const std::int32_t		line,
		 const std::string_view message) noexcept
{
	try
	{
		get_logger().get_sink<sink>(sink_name).log(severity_bit, tag, file_path, function_name, line, message);
	}
	catch (const std::invalid_argument& exception)
	{
		DEBUG_PRINT("Caught std::invalid_argument sending message to a sink! (error message: \"{}\")", exception.what());
	}
	catch (const std::logic_error& exception)
	{
		DEBUG_PRINT("Caught std::logic_error while sending message to the logger! (error message: \"{}\")", exception.what());
	}
}

} /*< namespace details */

static sink_manager& get_logger(void) noexcept(false)
{
	return true == is_initialized() ? *logger : throw std::logic_error{ "The logger has NOT been initialized successfully!" };
}

} /*< namespace hob::log */
