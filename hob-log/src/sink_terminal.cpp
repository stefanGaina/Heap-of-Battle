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
 * @file sink_terminal.cpp
 * @author Gaina Stefan
 * @date 17.11.2024
 * @brief This file implements the class defined in sink_terminal.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <stdexcept>

#include "sink_terminal.hpp"
#include "utility.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob::log
{

sink_terminal::sink_terminal(const std::string_view name, const sink_terminal_configuration& configuration) noexcept(false)
	: sink_base{ name, configuration.base }
	, stream{ nullptr }
	, color_enabled{ false }
{
	set_stream(configuration.stream);
	set_color(configuration.color);
}

void sink_terminal::set_stream(FILE* const stream) noexcept(false)
{
	assert(nullptr != this);

	if (stdout != stream && stderr != stream)
	{
		throw std::invalid_argument{ "Stream is not stdout or stderr!" };
	}

	this->stream = stream;
}

FILE* sink_terminal::get_stream(void) const noexcept
{
	assert(nullptr != this);
	return stream;
}

void sink_terminal::set_color(const bool color) noexcept
{
	assert(nullptr != this);
	color_enabled = color;
}

bool sink_terminal::get_color(void) const noexcept
{
	assert(nullptr != this);
	return color_enabled;
}

bool sink_terminal::log(const std::uint8_t severity_bit, const std::string_view message) noexcept
{
	color color = { color_enabled, severity_bit };

	assert(nullptr != this);
	try
	{
		std::print(stream, "{}", message);
		return true;
	}
	catch (const std::exception& exception)
	{
		DEBUG_PRINT("Caught std::exception while printing to the terminal! (error message: \"{}\")", exception.what());
		return false;
	}
}

color::color(const bool color_enabled, const std::uint8_t severity_bit) noexcept
	: color_enabled{ color_enabled }
{
	if (false == color_enabled)
	{
		return;
	}

	try
	{
		switch (severity_bit)
		{
			case severity_level::FATAL:
			{
				std::print("\033[1;31m");
				break;
			}
			case severity_level::ERROR:
			{
				std::print("\033[0;91m");
				break;
			}
			case severity_level::WARN:
			{
				std::print("\033[0;93m");
				break;
			}
			case severity_level::INFO:
			{
				std::print("\033[1;32m");
				break;
			}
			case severity_level::DEBUG:
			{
				std::print("\033[1;36m");
				break;
			}
			case severity_level::TRACE:
			{
				std::print("\033[0;90m");
				break;
			}
			default:
			{
				std::print("\033[1;0m");
				break;
			}
		}
	}
	catch (const std::exception& exception)
	{
		DEBUG_PRINT("Caught std::exception while changing the terminal color! (error message: \"{}\")", exception.what());
	}
}

color::~color(void) noexcept
{
	if (false == color_enabled)
	{
		return;
	}

	try
	{
		std::print("\033[1;0m");
	}
	catch (const std::exception& exception)
	{
		DEBUG_PRINT("Caught std::exception while restoring the terminal color! (error message: \"{}\")", exception.what());
	}
}

} /*< namespace hob::log */
