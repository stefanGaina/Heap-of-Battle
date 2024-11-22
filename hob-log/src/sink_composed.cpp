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
 * @file sink_composed.cpp
 * @author Gaina Stefan
 * @date 22.11.2024
 * @brief This file implements the class defined in sink_composed.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "sink_composed.hpp"
#include "utility.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob::log
{

sink_composed::sink_composed(const std::string_view name, std::list<std::shared_ptr<sink>>&& sinks) noexcept(false)
	: sink{ name }
	, sinks{ std::move(sinks) }
{
	assert(false == sinks.empty());
}

void sink_composed::log(const std::uint8_t	   severity_bit,
						const std::string_view tag,
						const std::string_view file_path,
						const std::string_view function_name,
						const std::int32_t	   line,
						const std::string_view message) noexcept
{
	assert(false == sinks.empty());

	for (const std::shared_ptr<sink>& sink : sinks)
	{
		sink->log(severity_bit, tag, file_path, function_name, line, message);
	}
}

} /*< namespace hob::log */
