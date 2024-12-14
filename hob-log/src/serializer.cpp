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
 * @file serialzier.cpp
 * @author Gaina Stefan
 * @date 12.12.2024
 * @brief This file implements the class defined in serializer.hpp.
 * @todo Add support for composed sink.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <fstream>
#include <cassert>

#include "serializer.hpp"
#include "sink_terminal.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob::log
{

void serializer::serialize(const std::filesystem::path&				 configuration_file_path,
						   const std::vector<std::shared_ptr<sink>>& sinks,
						   std::string_view							 default_sink_name) noexcept(false)
{
	nlohmann::json writer = {};

	writer["default"] = default_sink_name;

	for (const std::shared_ptr<sink>& sink : sinks)
	{
		write_sink(writer, sink);
	}

	write_to_file(writer, configuration_file_path);
}

void serializer::write_to_file(const nlohmann::json& writer, const std::filesystem::path& configuration_file_path) noexcept(false)
{
	std::ofstream					configuration_file = {};
	const std::vector<std::uint8_t> cbor			   = nlohmann::json::to_cbor(writer);

	assert(false == configuration_file_path.empty());
	configuration_file.exceptions(configuration_file.exceptions() | std::ios::failbit | std::ios::badbit);

#ifndef NDEBUG

	if (".json" == configuration_file_path.extension())
	{
		configuration_file.open(configuration_file_path);
		configuration_file << writer.dump(4);
		return;
	}

#endif /*< NDEBUG */

	assert(".cbor" == configuration_file_path.extension());

	configuration_file.open(configuration_file_path);
	configuration_file.write(reinterpret_cast<const char*>(cbor.data()), cbor.size());
}

void serializer::write_sink(nlohmann::json& writer, const std::shared_ptr<sink>& sink) noexcept(false)
{
	const std::shared_ptr<sink_terminal> terminal_sink = std::dynamic_pointer_cast<sink_terminal>(sink);

	assert(nullptr != sink);

	if (nullptr != terminal_sink)
	{
		writer[static_cast<std::string>(terminal_sink->get_name())] = {
			{ "type", "terminal" },
			{ "format", terminal_sink->get_format() },
			{ "time_format", terminal_sink->get_time_format() },
			{ "severity_level", terminal_sink->get_severity_level() },
			{ "async_mode", terminal_sink->get_async_mode() },
			{ "stream", stdout == terminal_sink->get_stream() ? "stdout" : "stderr" },
			{ "color", terminal_sink->get_color() }
		};

		assert(stdout == terminal_sink->get_stream() || stderr == terminal_sink->get_stream());
		return;
	}
}

} /*< namespace hob::log */
