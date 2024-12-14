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
 * @file converter.cpp
 * @author Gaina Stefan
 * @date 14.12.2024
 * @brief This file implements the class defined in converter.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <fstream>
#include <nlohmann/json.hpp>

#include "converter.hpp"

namespace hob
{

void converter::convert_files(const std::filesystem::path& source_path, const std::filesystem::path& destination_path) noexcept(false)
{
	if (source_path.extension() == destination_path.extension())
	{
		throw std::invalid_argument{ "The files have the same extension!" };
	}

	if (".json" == source_path.extension())
	{
		if (".cbor" != destination_path.extension())
		{
			throw std::invalid_argument{ "The destination file does not have .cbor extension!" };
		}

		json_to_cbor(source_path, destination_path);
		return;
	}

	if (".cbor" == source_path.extension())
	{
		if (".json" != destination_path.extension())
		{
			throw std::invalid_argument{ "The destination file does not have .json extension!" };
		}

		cbor_to_json(source_path, destination_path);
		return;
	}

	throw std::invalid_argument{ "The source file does not have .json or .cbor extension!" };
}

void converter::json_to_cbor(const std::filesystem::path& source_json_file_path, const std::filesystem::path& destination_cbor_file_path) noexcept(false)
{
	std::ifstream			  json_file = {};
	std::ofstream			  cbor_file = {};
	std::vector<std::uint8_t> cbor_data = {};

	assert(".json" == source_json_file_path.extension());
	assert(".cbor" == destination_cbor_file_path.extension());

	json_file.exceptions(json_file.exceptions() | std::ios::failbit | std::ios::badbit);
	json_file.open(source_json_file_path);

	cbor_file.exceptions(cbor_file.exceptions() | std::ios::failbit | std::ios::badbit);
	cbor_file.open(destination_cbor_file_path, std::ios::binary);

	cbor_data = nlohmann::json::to_cbor(nlohmann::json::parse(json_file));
	cbor_file.write(reinterpret_cast<const char*>(cbor_data.data()), cbor_data.size());
}

void converter::cbor_to_json(const std::filesystem::path& source_cbor_file_path, const std::filesystem::path& destination_json_file_path) noexcept(false)
{
	std::ifstream cbor_file = {};
	std::ofstream json_file = {};

	assert(".cbor" == source_cbor_file_path.extension());
	assert(".json" == destination_json_file_path.extension());

	cbor_file.exceptions(cbor_file.exceptions() | std::ios::failbit | std::ios::badbit);
	cbor_file.open(source_cbor_file_path, std::ios::binary);

	json_file.exceptions(json_file.exceptions() | std::ios::failbit | std::ios::badbit);
	json_file.open(destination_json_file_path);

	json_file << nlohmann::json::from_cbor(std::vector<std::uint8_t>{ std::istreambuf_iterator<char>(cbor_file), std::istreambuf_iterator<char>() }).dump(4);
}

} /*< namespace hob */
