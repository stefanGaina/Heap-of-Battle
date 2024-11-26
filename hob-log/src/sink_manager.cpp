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
 * @file sink_manager.cpp
 * @author Gaina Stefan
 * @date 18.11.2024
 * @brief This file implements the class defined in sink_manager.hpp.
 * @todo Read the logger configuration from file and update it in case of runtime changes.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "sink_manager.hpp"
#include "sink_terminal.hpp"
#include "sink_composed.hpp"

/******************************************************************************************************
 * CONSTANTS
 *****************************************************************************************************/

namespace hob::log
{

/** ***************************************************************************************************
 * @brief The message that is attached to the exception thrown when a sink is not found by its name.
 *****************************************************************************************************/
static constexpr const char* INVALID_SINK_MESSAGE = "Invalid sink name or the sink has not been added successfully!";

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

sink_manager::sink_manager(const std::string_view configuration_file_path) noexcept(false)
	: configuration_file_path{ configuration_file_path }
	, default_sink_name{ "" }
	, sinks{}
{
	if (true == configuration_file_path.empty())
	{
		return;
	}

	// TODO: read from file
}

sink_manager::~sink_manager(void) noexcept
{
	if (true == configuration_file_path.empty())
	{
		return;
	}

	// TODO: write to file
}

void sink_manager::add_sink(const std::string_view sink_name, const sink_terminal_configuration& configuration) noexcept(false)
{
	assert(nullptr != this);

	throw_if_sink_name_invalid(sink_name);
	(void)sinks.emplace_back(std::make_shared<sink_terminal>(sink_name, configuration));
}

void sink_manager::add_sink(const std::string_view sink_name, const std::list<std::string>& sink_names) noexcept(false)
{
	std::list<std::shared_ptr<sink>> sinks = {};

	assert(nullptr != this);
	throw_if_sink_name_invalid(sink_name);

	for (const auto& sink_to_compose : sink_names)
	{
		sinks.push_back(get_sink(sink_to_compose));
	}

	(void)this->sinks.emplace_back(std::make_shared<sink_composed>(sink_name, std::move(sinks)));
}

void sink_manager::remove_sink(const std::string_view sink_name) noexcept
{
	assert(nullptr != this);
	(void)sinks.erase(std::remove_if(sinks.begin(), sinks.end(), [sink_name](const std::shared_ptr<sink>& sink) { return sink_name == sink->get_name(); }),
					  sinks.end());
}

bool sink_manager::is_sink_valid(const std::string_view sink_name) const noexcept
{
	assert(nullptr != this);

	try
	{
		(void)get_sink(sink_name);
		return true;
	}
	catch (const std::exception& exception)
	{
		return false;
	}
}

void sink_manager::set_default_sink_name(const std::string_view sink_name) noexcept(false)
{
	assert(nullptr != this);
	default_sink_name = sink_name;
}

std::string_view sink_manager::get_default_sink_name(void) const noexcept
{
	assert(nullptr != this);
	return default_sink_name;
}

void sink_manager::throw_if_sink_name_invalid(const std::string_view sink_name) const noexcept(false)
{
	assert(nullptr != this);

	if (true == is_sink_valid(sink_name))
	{
		throw std::logic_error{ std::format("\"{}\" sink has already been added!", sink_name) };
	}
}

std::shared_ptr<sink>& sink_manager::get_sink(const std::string_view sink_name) noexcept(false)
{
	auto iterator = std::find_if(sinks.begin(), sinks.end(), [sink_name](std::shared_ptr<sink>& sink) { return sink_name == sink->get_name(); });

	assert(nullptr != this);
	return iterator != sinks.end() ? *iterator : throw std::invalid_argument{ INVALID_SINK_MESSAGE };
}

const std::shared_ptr<sink>& sink_manager::get_sink(const std::string_view sink_name) const noexcept(false)
{
	auto iterator = std::find_if(sinks.begin(), sinks.end(), [sink_name](const std::shared_ptr<sink>& sink) { return sink_name == sink->get_name(); });

	assert(nullptr != this);
	return iterator != sinks.end() ? *iterator : throw std::invalid_argument{ INVALID_SINK_MESSAGE };
}

} /*< namespace hob::log */
