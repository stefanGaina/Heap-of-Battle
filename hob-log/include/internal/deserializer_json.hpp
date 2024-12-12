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
 * @file deserializer_json.hpp
 * @author Gaina Stefan
 * @date 12.12.2024
 * @brief This header defines the deserializer_json class.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_LOG_INTERNAL_DESERIALIZER_JSON_HPP_
#define HOB_LOG_INTERNAL_DESERIALIZER_JSON_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <nlohmann/json.hpp>

#include "deserializer.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob::log
{

/** ***************************************************************************************************
 * @brief Deserializer for configuration files in JSON format.
 *****************************************************************************************************/
class HOB_LOG_LOCAL deserializer_json final : public deserializer
{
public:
	/** ***********************************************************************************************
	 * @brief Opens the provided configuration file path for reading.
	 * @param configuration_file_path: The path to the JSON configuration file.
	 * @throws std::ios_base::failure: If the configuration file failed to be opened.
	 * @throws std::bad_alloc: If memory allocation for object fails.
	 *************************************************************************************************/
	deserializer_json(const std::filesystem::path& configuration_file_path) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Parses the JSON file for the logging configuration.
	 * @param void
	 * @returns Deserialized log configuration containing the sinks and the default sink name.
	 * @throws std::invalid_argument If a required property of a sink configuration is missing or
	 * invalid.
	 * @throws std::bad_alloc: If memory allocation for sinks or sink name fails.
	 * @throws nlohmann::json::parse_error: If the JSON data cannot be parsed.
	 * @throws nlohmann::json::type_error: If the JSON structure does not match expected types.
	 *************************************************************************************************/
	[[nodiscard]] deserializer::data deserialize(void) noexcept(false) override;

private:
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
	void parse_property(std::vector<std::shared_ptr<sink>>& sinks,
						std::string&						default_sink_name,
						const std::string_view				key,
						const nlohmann::json&				value) noexcept(false);

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
	std::shared_ptr<sink> parse_sink(const std::string_view sink_name, const nlohmann::json& sink_configuration) noexcept(false);

private:
	/** ***********************************************************************************************
	 * @brief The JSON parser object holding the parsed configuration.
	 *************************************************************************************************/
	nlohmann::json parser;
};

} /*< namespace hob::log */

#endif /*< HOB_LOG_INTERNAL_DESERIALIZER_JSON_HPP_ */
