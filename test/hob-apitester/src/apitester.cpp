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
 * @file apitester.cpp
 * @author Gaina Stefan
 * @date 26.11.2024
 * @brief This file implements the entry point of the hob-apitester.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <print>
#include <cfloat>

#include "apitester.hpp"
#include "parser.hpp"

/******************************************************************************************************
 * ENTRY POINT
 *****************************************************************************************************/

std::int32_t main(const std::int32_t argument_count, char** const arguments) noexcept
{
	try
	{
		std::println("Usage: {} <file_path> (optional)", arguments[0]);
		hob::apitester::parser::initialize();

		if (1 < argument_count)
		{
			hob::apitester::parser::parse_from_file(arguments[1]);
			if (2 < argument_count)
			{
				std::println("Extra parameters will be ignored!");
			}
		}

		hob::apitester::parser::parse_from_terminal();
		return EXIT_SUCCESS;
	}
	catch (const std::exception& exception)
	{
		return EXIT_FAILURE;
	}
}

/******************************************************************************************************
 * FUNCTION DEFINITIONS
 *****************************************************************************************************/

namespace hob::apitester::details
{

function_registrar::function_registrar(const std::string_view name, function_prototype function, const std::string_view argument_names) noexcept(false)
{
	std::list<std::string> splitted_argument_names = {};

	assert(false == name.empty());
	assert(function);

	if (0UL != parser::get_registry().count(name.data()))
	{
		std::println(stderr, "Function with name \"{}\" has already been registered!", name);
		throw std::logic_error{ std::format("Function with name \"{}\" has already been registered!", name) };
	}

	parser::register_function(name, function, split_argument_names(argument_names));
}

std::list<std::string> function_registrar::split_argument_names(const std::string_view argument_names) noexcept(false)
{
	std::istringstream	   string_stream		   = std::istringstream{ argument_names.data() };
	std::list<std::string> splitted_argument_names = {};

	std::copy_if(std::istream_iterator<std::string>(string_stream), std::istream_iterator<std::string>(), std::back_inserter(splitted_argument_names),
				 [](const std::string& string)
				 {
					 const std::size_t start = string.find_first_not_of(" \t");
					 const std::size_t end	 = string.find_last_not_of(" \t");
					 return std::string::npos != start && std::string::npos != end && start <= end;
				 });

	for (std::string& splitted_argument_name : splitted_argument_names)
	{
		if (',' == splitted_argument_name.back())
		{
			splitted_argument_name.pop_back();
		}
	}

	return splitted_argument_names;
}

} /*< namespace hob::apitester::details */
