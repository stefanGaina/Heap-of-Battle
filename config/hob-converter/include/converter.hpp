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
 * @file converter.hpp
 * @author Gaina Stefan
 * @date 14.12.2024
 * @brief This header defines the converter class.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_CONVERTER_CONVERTER_HPP_
#define HOB_CONVERTER_CONVERTER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <filesystem>

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

/** ***************************************************************************************************
 * @brief Converter class for JSON and CBOR files.
 *****************************************************************************************************/
class converter final
{
public:
	/** ***********************************************************************************************
	 * @brief Converts a file from JSON to CBOR or from CBOR to JSON.
	 * @param source_file_path: The path to the source file to be converted.
	 * @param destination_file_path: The path to the destination file where the converted content will
	 * be written.
	 * @returns void
	 * @throws std::invalid_argument: If the file extensions do not match the expected types (i.e.
	 * JSON → CBOR or CBOR → JSON).
	 * @throws std::ios_base::failure If a file cannot be read or written.
	 * @throws std::bad_alloc If memory allocation for buffers fail.
	 *************************************************************************************************/
	static void convert_files(const std::filesystem::path& source_file_path, const std::filesystem::path& destination_file_path) noexcept(false);

private:
	/** ***********************************************************************************************
	 * @brief Converts a JSON file to CBOR format.
	 * @param source_json_file_path: The path to the JSON source file to be converted.
	 * @param destination_cbor_file_path: The path to the CBOR destination file where the converted
	 * content will be written.
	 * @returns void
	 * @throws std::ios_base::failure If a file cannot be read or written.
	 * @throws std::bad_alloc If memory allocation for buffers fail.
	 *************************************************************************************************/
	static void json_to_cbor(const std::filesystem::path& source_json_file_path, const std::filesystem::path& destination_cbor_file_path) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Converts a CBOR file to JSON format.
	 * @param source_cbor_file_path: The path to the CBOR source file to be converted.
	 * @param destination_json_file_path: The path to the JSON destination file where the converted
	 * content will be written.
	 * @returns void
	 * @throws std::ios_base::failure If a file cannot be read or written.
	 * @throws std::bad_alloc If memory allocation for buffers fail.
	 *************************************************************************************************/
	static void cbor_to_json(const std::filesystem::path& source_cbor_file_path, const std::filesystem::path& destination_json_file_path) noexcept(false);
};

} /*< namespace hob */

#endif /*< HOB_CONVERTER_CONVERTER_HPP_ */
