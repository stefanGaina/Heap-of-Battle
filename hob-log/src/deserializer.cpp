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
 * @file deserializer.cpp
 * @author Gaina Stefan
 * @date 12.12.2024
 * @brief This file implements the class defined in deserializer.hpp.
 * @todo Add support for composed sink.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <fstream>
#include <cassert>

#include "deserializer.hpp"
#include "sink_terminal.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob::log
{

deserializer::data deserializer::deserialize(const std::filesystem::path& configuration_file_path) noexcept(false)
{
	std::vector<std::shared_ptr<sink>> sinks			 = {};
	std::string						   default_sink_name = "";
	nlohmann::json					   parser			 = create_parser(configuration_file_path);

	for (const auto& item : parser.items())
	{
		if ("default" == item.key())
		{
			default_sink_name = item.value().get<std::string>();
			continue;
		}

		sinks.push_back(parse_sink(item.key(), item.value()));
	}

	return { sinks, default_sink_name };
}

nlohmann::json deserializer::create_parser(const std::filesystem::path& configuration_file_path) noexcept(false)
{
	std::ifstream configuration_file = {};

	assert(false == configuration_file_path.empty());
	configuration_file.exceptions(configuration_file.exceptions() | std::ios::failbit | std::ios::badbit);

#ifndef NDEBUG

	if (".json" == configuration_file_path.extension())
	{
		configuration_file.open(configuration_file_path);
		return nlohmann::json::parse(configuration_file);
	}

#endif /*< NDEBUG */

	if (".cbor" != configuration_file_path.extension())
	{
		throw std::invalid_argument{ "The extension of the configuration file is not \".cbor\"!" };
	}

	configuration_file.open(configuration_file_path, std::ios::binary);
	return nlohmann::json::from_cbor(std::vector<std::uint8_t>{ std::istreambuf_iterator<char>(configuration_file), std::istreambuf_iterator<char>() });
}

std::shared_ptr<sink> deserializer::parse_sink(const std::string_view sink_name, const nlohmann::json& sink_configuration) noexcept(false)
{
	if ("terminal" == sink_configuration["type"])
	{
		return std::make_shared<sink_terminal>(
			sink_name,
			sink_terminal_configuration{
				{ sink_configuration["format"].get<std::string>(), sink_configuration["time_format"].get<std::string>(), sink_configuration["severity_level"],
				  sink_configuration["async_mode"] },
				"stdout" == sink_configuration["stream"] ? stdout
				: "stderr" == sink_configuration["stream"]
					? stderr
					: throw std::invalid_argument{ std::format("\"{}\" stream is invalid!)", sink_configuration["stream"].get<std::string>()) },
				sink_configuration["color"] });
	}

	throw std::invalid_argument{ std::format("Invalid sink type! (type: \"{}\")", sink_configuration["type"].get<std::string>()) };
}

} /*< namespace hob::log */
