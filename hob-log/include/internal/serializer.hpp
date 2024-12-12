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
 * @brief This header defines the serializer abstract class.
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
#include <fstream>
#include <filesystem>
#include <memory>

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
 * @brief This serves as an abstract base for serializing log configuration data to a file.
 *****************************************************************************************************/
class HOB_LOG_LOCAL serializer
{
public:
	/** ***********************************************************************************************
	 * @brief Opens the provided configuration file path for writing.
	 * @param configuration_file_path: The path to the configuration file to be serialized.
	 * @throws std::ios_base::failure: If the configuration file failed to be opened.
	 *************************************************************************************************/
	serializer(const std::filesystem::path& configuration_file_path) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Virtual destructor to avoid polymorphically delete undefined behavior.
	 * @param void
	 * @throws N/A.
	 *************************************************************************************************/
	virtual ~serializer(void) noexcept;

	/** ***********************************************************************************************
	 * @brief This method should write the configuration file depending on its format.
	 * @param sinks: The sinks to be written.
	 * @param default_sink_name: The default sink name to be written.
	 * @returns void
	 * @throws other: Exceptions defined by class implementing this in case of failure.
	 *************************************************************************************************/
	virtual void serialize(const std::vector<std::shared_ptr<sink>>& sinks, std::string_view default_sink_name) noexcept(false) = 0;

protected:
	/** ***********************************************************************************************
	 * @brief The output file stream used to write the configuration file.
	 *************************************************************************************************/
	std::ifstream configuration_file;
};

} /*< namespace hob::log */

#endif /*< HOB_LOG_INTERNAL_SERIALIZER_HPP_ */
