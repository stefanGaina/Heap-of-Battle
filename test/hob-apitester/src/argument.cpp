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
 * @file argument.cpp
 * @author Gaina Stefan
 * @date 26.11.2024
 * @brief This file implements the interface defined in details/argument.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <stdexcept>
#include <cstring>
#include <cassert>

#include "argument.hpp"
#include "invalid_argument.hpp"
#include "out_of_range.hpp"

/******************************************************************************************************
 * CONSTANTS
 *****************************************************************************************************/

namespace hob::apitester::details
{

/** ***************************************************************************************************
 * @brief Message where only the type of the thrown exception matters, as it will be caught and
 * rethrown with a more appropiate message.
 *****************************************************************************************************/
static constexpr const char* EMPTY_EXCEPTION_MESSAGE = "This message should've been overridden!";

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

argument::argument(void) noexcept
	: text{ "" }
{
}

argument::argument(const std::string& text) noexcept(false)
	: text{ text }
{
	assert(false == text.empty());
}

argument::argument(std::string&& text) noexcept
	: text{ std::move(text) }
{
}

argument& argument::operator=(const argument& other) noexcept(false)
{
	assert(nullptr != this);
	assert(false == other.text.empty());

	if (&other != this)
	{
		this->text = other.text;
	}

	return *this;
}

bool argument::operator==(const argument& other) const noexcept
{
	assert(nullptr != this);
	return text == other.text;
}

bool argument::operator==(const std::string& string) const noexcept
{
	assert(nullptr != this);
	return string == text;
}

bool argument::operator==(const char* const string) const noexcept
{
	assert(nullptr != this);
	return 0 == strcmp(string, text.c_str());
}

argument::operator bool(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	return "true" == text ? true : "false" == text ? false : throw invalid_argument{ std::format("\"{}\" needs to be of boolean type (true or false)!", text) };
}

argument::operator std::int8_t(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return static_cast<std::int8_t>(get_signed_integer(INT8_MIN, INT8_MAX));
	}
	catch (const std::invalid_argument& exception)
	{
		throw invalid_argument{ std::format("\"{}\" needs to be of 1 byte signed integer type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		throw out_of_range{ std::format("\"{}\" needs to be in the 1 byte signed integer [-128, 127] interval!", text) };
	}
}

argument::operator std::uint8_t(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return static_cast<std::uint8_t>(get_unsigned_integer(UINT8_MAX));
	}
	catch (const std::invalid_argument& exception)
	{
		throw invalid_argument{ std::format("\"{}\" needs to be of 1 byte unsigned integer type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		throw out_of_range{ std::format("\"{}\" needs to be in the 1 byte unsigned integer [0, 255] interval!", text) };
	}
}

argument::operator std::int16_t(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return static_cast<std::int16_t>(get_signed_integer(INT16_MIN, INT16_MAX));
	}
	catch (const std::invalid_argument& exception)
	{
		throw invalid_argument{ std::format("\"{}\" needs to be of 2 byte signed integer type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		throw out_of_range{ std::format("\"{}\" needs to be in the 2 byte signed integer [-32768, 32767] interval!", text) };
	}
}

argument::operator std::uint16_t(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return static_cast<std::uint16_t>(get_unsigned_integer(UINT16_MAX));
	}
	catch (const std::invalid_argument& exception)
	{
		throw invalid_argument{ std::format("\"{}\" needs to be of 2 byte unsigned integer type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		throw out_of_range{ std::format("\"{}\" needs to be in the 2 byte unsigned integer [0, 65535] interval!", text) };
	}
}

argument::operator std::int32_t(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return static_cast<std::int32_t>(get_signed_integer(INT32_MIN, INT32_MAX));
	}
	catch (const std::invalid_argument& exception)
	{
		throw invalid_argument{ std::format("\"{}\" needs to be of 4 byte signed integer type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		throw out_of_range{ std::format("\"{}\" needs to be in the 4 byte signed integer [-2147483648, 2147483647] interval!", text) };
	}
}

argument::operator std::uint32_t(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return static_cast<std::uint32_t>(get_unsigned_integer(UINT32_MAX));
	}
	catch (const std::invalid_argument& exception)
	{
		throw invalid_argument{ std::format("\"{}\" needs to be of 4 byte unsigned integer type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		throw out_of_range{ std::format("\"{}\" needs to be in the 4 byte unsigned integer [0, 4294967295] interval!", text) };
	}
}

argument::operator std::int64_t(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return get_signed_integer(INT64_MIN, INT64_MAX);
	}
	catch (const std::invalid_argument& exception)
	{
		throw invalid_argument{ std::format("\"{}\" needs to be of 8 byte signed integer type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		throw out_of_range{ std::format("\"{}\" needs to be in the 8 byte signed integer [-9223372036854775808, 9223372036854775807] interval!", text) };
	}
}

argument::operator std::uint64_t(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return get_unsigned_integer(UINT64_MAX);
	}
	catch (const std::invalid_argument& exception)
	{
		throw invalid_argument{ std::format("\"{}\" needs to be of 8 byte unsigned integer type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		throw out_of_range{ std::format("\"{}\" needs to be in the 8 byte unsigned integer [0, 18446744073709551615] interval!", text) };
	}
}

argument::operator float(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return get_float();
	}
	catch (const std::invalid_argument& exception)
	{
		throw invalid_argument{ std::format("\"{}\" needs to be of 4 byte floating point type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		throw out_of_range{ std::format("\"{}\" needs to be in the 4 byte floating point number [1.175494e-38, 3.402823e+38] interval!", text) };
	}
}

argument::operator double(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return get_double();
	}
	catch (const std::invalid_argument& exception)
	{
		throw invalid_argument{ std::format("\"{}\" needs to be of 8 byte floating point type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		throw out_of_range{ std::format("\"{}\" needs to be in the 8 byte floating point number [2.225074e-308, 1.797693e+308] interval!", text) };
	}
}

argument::operator const char*(void) const noexcept
{
	assert(nullptr != this);
	assert(false == text.empty());

	return text.c_str();
}

argument::operator const std::string&(void) const noexcept
{
	assert(nullptr != this);
	assert(false == text.empty());

	return text;
}

argument::operator std::string_view(void) const noexcept
{
	assert(nullptr != this);
	assert(false == text.empty());

	return text;
}

argument::operator FILE*(void) const noexcept(false)
{
	FILE* const stream = "stdout" == text ? stdout : "stderr" == text ? stderr : "stdin" == text ? stdin : nullptr;
	return nullptr == stream && "nullptr" != text
			   ? throw invalid_argument{ std::format("\"{}\" needs to be of stream type (stdout, stderr, stdin or nullptr)", text) }
			   : stream;
}

std::int64_t argument::get_signed_integer(const std::int64_t minimum, const std::int64_t maximum) const noexcept(false)
{
	std::size_t		   position = 0UL;
	const std::int64_t result	= std::stol(text, &position, 0);

	assert(nullptr != this);
	assert(false == text.empty());

	throw_if_trailing_characters(position);

	if (result < minimum || result > maximum)
	{
		throw std::out_of_range{ EMPTY_EXCEPTION_MESSAGE };
	}

	return result;
}

std::uint64_t argument::get_unsigned_integer(const std::uint64_t maximum) const noexcept(false)
{
	std::size_t			position = 0UL;
	const std::uint64_t result	 = std::stoul(text, &position, 0);

	assert(nullptr != this);
	assert(false == text.empty());

	throw_if_trailing_characters(position);

	if (result > maximum)
	{
		throw std::out_of_range{ EMPTY_EXCEPTION_MESSAGE };
	}

	return result;
}

float argument::get_float(void) const noexcept(false)
{
	std::size_t position = 0UL;
	const float result	 = std::stof(text, &position);

	assert(nullptr != this);
	assert(false == text.empty());

	throw_if_trailing_characters(position);
	return result;
}

double argument::get_double(void) const noexcept(false)
{
	std::size_t	 position = 0UL;
	const double result	  = std::stod(text, &position);

	assert(nullptr != this);
	assert(false == text.empty());

	throw_if_trailing_characters(position);
	return result;
}

void argument::throw_if_trailing_characters(const std::size_t position) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	if (position != text.length())
	{
		throw std::invalid_argument{ EMPTY_EXCEPTION_MESSAGE };
	}
}

bool operator==(const std::string& string, const argument& argument) noexcept
{
	return argument == string;
}

bool operator==(const char* const string, const argument& argument) noexcept
{
	return argument == string;
}

std::ostream& operator<<(std::ostream& ostream, const argument& argument) noexcept(false)
{
	ostream << static_cast<const std::string&>(argument);
	return ostream;
}

} /*< namespace hob::apitester::details */
