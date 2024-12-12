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
 * @file deserializer_cbor.hpp
 * @author Gaina Stefan
 * @date 12.12.2024
 * @brief This header defines the deserializer_cbor class.
 * @todo Implement this.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_LOG_INTERNAL_DESERIALIZER_CBOR_HPP_
#define HOB_LOG_INTERNAL_DESERIALIZER_CBOR_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <filesystem>

#include "deserializer.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob::log
{

/** ***************************************************************************************************
 * @brief Deserializer for configuration files in CBOR format.
 *****************************************************************************************************/
class HOB_LOG_LOCAL deserializer_cbor final : public deserializer
{
public:
	/** ***********************************************************************************************
	 * @brief Opens the provided configuration file path for reading.
	 * @param configuration_file_path:
	 * @throws std::ios_base::failure: If the configuration file failed to be opened.
	 *************************************************************************************************/
	deserializer_cbor(const std::filesystem::path& configuration_file_path) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Parses the CBOR file for the logging configuration.
	 * @param void
	 * @returns Deserialized log configuration containing the sinks and the default sink name.
	 * @throws std::exception: This is not yet implemented.
	 *************************************************************************************************/
	[[nodiscard]] deserializer::data deserialize(void) noexcept(false) override;
};

} /*< namespace hob::log */

#endif /*< HOB_LOG_INTERNAL_DESERIALIZER_CBOR_HPP_ */
