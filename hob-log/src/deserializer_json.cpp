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
 * @file deserialzied_json.cpp
 * @author Gaina Stefan
 * @date 12.12.2024
 * @brief This file implements the class defined in deserializer_json.hpp.
 * @todo Add support for sink_composed.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <stdexcept>
#include <cassert>

#include "deserializer_json.hpp"
#include "sink_terminal.hpp"

#include "utility.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob::log
{

deserializer_json::deserializer_json(const std::filesystem::path& configuration_file_path) noexcept(false)
	: deserializer{ configuration_file_path }
	, parser{}
{
	assert(true == configuration_file.is_open());
	assert(".json" == configuration_file_path.extension());
}

deserializer::data deserializer_json::deserialize(void) noexcept(false)
{
	std::vector<std::shared_ptr<sink>> sinks			 = {};
	std::string						   default_sink_name = "";

	assert(nullptr != this);
	assert(true == configuration_file.is_open());

	parser = nlohmann::json::parse(configuration_file);

	for (const auto& item : parser.items())
	{
		for (const auto& property : item.value().items())
		{
			(void)property;
			parse_property(sinks, default_sink_name, item.key(), item.value());
		}
	}

	return { sinks, default_sink_name };
}

void deserializer_json::parse_property(std::vector<std::shared_ptr<sink>>& sinks,
									   std::string&						   default_sink_name,
									   const std::string_view			   key,
									   const nlohmann::json&			   value) noexcept(false)
{
	assert(nullptr != this);

	if ("default" == key)
	{
		default_sink_name = value.get<std::string>();
		return;
	}

	sinks.push_back(parse_sink(key, value));
}

std::shared_ptr<sink> deserializer_json::parse_sink(const std::string_view sink_name, const nlohmann::json& sink_configuration) noexcept(false)
{
	assert(nullptr != this);

	if ("terminal" == sink_configuration["type"])
	{
		return std::make_shared<sink_terminal>(
			sink_name, sink_terminal_configuration{ { sink_configuration["format"].get<std::string>(), sink_configuration["time_format"].get<std::string>(),
													  sink_configuration["severity_level"].get<std::uint8_t>(), sink_configuration["async_mode"].get<bool>() },
													"stdout" == sink_configuration["stream"].get<std::string>() ? stdout : nullptr,
													sink_configuration["color"].get<bool>() });
	}

	throw std::invalid_argument{ std::format("Invalid sink type! (type: \"{}\")", sink_configuration["type"].get<std::string>()) };
}

} /*< namespace hob::log */
