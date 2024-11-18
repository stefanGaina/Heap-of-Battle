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
 * @file utility.cpp
 * @author Gaina Stefan
 * @date 17.11.2024
 * @brief This file implements the functions defined in utility.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "utility.hpp"

/******************************************************************************************************
 * FUNCTION DEFINITIONS
 *****************************************************************************************************/

namespace hob::log
{

void utility::replace_placeholder(std::string& destination, const std::string_view placeholder, const std::string_view replacement) noexcept(false)
{
	std::size_t position = 0UL;

	while (std::string::npos != (position = destination.find(placeholder, position)))
	{
		destination.replace(position, placeholder.length(), replacement);
		position += replacement.length();
	}
}

std::pair<std::tm*, std::int64_t> utility::get_time(void) noexcept
{
	std::chrono::time_point<std::chrono::system_clock> now		  = std::chrono::system_clock::now();
	std::time_t										   now_time	  = std::chrono::system_clock::to_time_t(now);
	std::tm* const									   local_time = std::localtime(&now_time);

	return { local_time, std::chrono::milliseconds{ std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000 }.count() };
}

} /*< namespace hob::log */
