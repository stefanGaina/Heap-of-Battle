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
 * @file serializer.hpp
 * @author Gaina Stefan
 * @date 12.12.2024
 * @brief This header defines the serializer class.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_LOG_INTERNAL_SERIALIZER_HPP_
#define HOB_LOG_INTERNAL_SERIALIZER_HPP_

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
 * @brief Serializer for configuration files in CBOR format (and JSON in debug mode).
 *****************************************************************************************************/
class HOB_LOG_LOCAL serializer final
{
public:
	/** ***********************************************************************************************
	 * @brief Writes the configuration to the file.
	 * @param configuration_file_path: The path to the configuration file to be deserialized (CBOR
	 * format and JSON in debug mode supported formats).
	 * @param sinks: The sinks to be written.
	 * @param default_sink_name: The default sink name to be written.
	 * @returns void
	 * @throws std::ios_base::failure: If the configuration file failed to be opened.
	 * @throws std::bad_alloc: If allocating memory for the writer's buffer fails.
	 *************************************************************************************************/
	static void serialize(const std::filesystem::path&				configuration_file_path,
						  const std::vector<std::shared_ptr<sink>>& sinks,
						  std::string_view							default_sink_name) noexcept(false);

private:
	/** ***********************************************************************************************
	 * @brief Writes the buffered configuration data to a file.
	 * @param writer: The writer which collected the configuration.
	 * @param configuration_file_path: The path to the file where the configuration will be written to.
	 * @returns void
	 * @throws std::ios_base::failure: If the configuration file failed to be opened.
	 *************************************************************************************************/
	static void write_to_file(const nlohmann::json& writer, const std::filesystem::path& configuration_file_path) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Puts the sink's configuration into writer's buffer.
	 * @param writer: The writer which collects the configuration before writing to the file.
	 * @param sink: The sink to be written.
	 * @returns void
	 * @throws std::bad_alloc: If allocating memory for the writer's buffer fails.
	 *************************************************************************************************/
	static void write_sink(nlohmann::json& writer, const std::shared_ptr<sink>& sink) noexcept(false);
};

} /*< namespace hob::log */

#endif /*< HOB_LOG_INTERNAL_SERIALIZER_HPP_ */
