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
 * @file deserializer.hpp
 * @author Gaina Stefan
 * @date 12.12.2024
 * @brief This header defines the deserializer class.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_LOG_INTERNAL_DESERIALIZER_HPP_
#define HOB_LOG_INTERNAL_DESERIALIZER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <string_view>
#include <vector>
#include <filesystem>
#include <memory>
#include <nlohmann/json.hpp>

#include "details/visibility.hpp"

/******************************************************************************************************
 * FORWARD DECLARATIONS
 *****************************************************************************************************/

namespace hob::log
{

class sink;

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Deserializer for configuration files in CBOR format (and JSON in debug mode).
 *****************************************************************************************************/
class HOB_LOG_LOCAL deserializer final
{
public:
	/** ***********************************************************************************************
	 * @brief Deserialized data type alias containing the sinks and the default sink name.
	 *************************************************************************************************/
	using data = std::pair<std::vector<std::shared_ptr<sink>>, std::string>;

	/** ***********************************************************************************************
	 * @brief Reads the configuration file and parse it for the configuration.
	 * @param configuration_file_path: The path to the configuration file to be deserialized (CBOR
	 * format and JSON in debug mode supported formats).
	 * @returns Deserialized log configuration containing the sinks and the default sink name.
	 * @throws std::invalid_argument If a required property of a sink configuration is missing or
	 * invalid.
	 * @throws std::ios_base::failure: If the configuration file failed to be opened.
	 * @throws std::bad_alloc: If memory allocation for sinks or sink name fails.
	 * @throws nlohmann::json::parse_error: If the data can not be parsed.
	 * @throws nlohmann::json::type_error: If the structure does not match expected types.
	 *************************************************************************************************/
	[[nodiscard]] static data deserialize(const std::filesystem::path& configuration_file_path) noexcept(false);

private:
	/** ***********************************************************************************************
	 * @brief Creates a parser for the configuration file.
	 * @param configuration_file_path: The path to the configuration file to be deserialized
	 * @returns Parser with the configuration file loaded.
	 * @throws std::ios_base::failure: If the configuration file failed to be opened.
	 * @throws nlohmann::json::parse_error: If the data can not be parsed.
	 *************************************************************************************************/
	[[nodiscard]] static nlohmann::json create_parser(const std::filesystem::path& configuration_file_path) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Processes key-value pairs in the configuration file to update sinks and the default
	 * sink name.
	 * @param sinks: The sinks where the newly configured sink is to be added.
	 * @param default_sink_name: The name of of the default sink to be updated.
	 * @param key: The key of the JSON property being parsed.
	 * @param value: The JSON value corresponding to the key.
	 * @returns void
	 * @throws std::invalid_argument: If the key or value is invalid or missing required properties.
	 * @throws std::bad_alloc: If memory allocation for sinks or sink name fails.
	 * @throws nlohmann::json::type_error: If the value has an unexpected type.
	 *************************************************************************************************/
	static void parse_property(std::vector<std::shared_ptr<sink>>& sinks,
							   std::string&						   default_sink_name,
							   const std::string_view			   key,
							   const nlohmann::json&			   value) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Parses and creates a sink from the JSON configuration.
	 * @param sink_name The name of the sink to be parsed.
	 * @param sink_configuration The JSON object containing the sink configuration.
	 * @returns The newly created sink.
	 * @throws std::invalid_argument: If the sink type is unsupported or configuration is invalid.
	 * @throws std::bad_alloc: If memory allocation fails during sink creation.
	 * @throws nlohmann::json::type_error: If the sink configuration is missing required properties
	 * or has incorrect types.
	 *************************************************************************************************/
	[[nodiscard]] static std::shared_ptr<sink> parse_sink(const std::string_view sink_name, const nlohmann::json& sink_configuration) noexcept(false);
};

} /*< namespace hob::log */

#endif /*< HOB_LOG_INTERNAL_DESERIALIZER_HPP_ */
