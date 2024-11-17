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

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <vector>
#include <memory>

#include "logger.hpp"
#include "sink_terminal.hpp"
#include "utility.hpp"

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

namespace hob::log
{

/** ***************************************************************************************************
 * @brief The collection of the different type of sinks.
 *****************************************************************************************************/
static std::vector<std::shared_ptr<sink>> sinks = {};

/******************************************************************************************************
 * FUNCTION DEFINITIONS
 *****************************************************************************************************/

void initialize(const std::string_view configuration_file) noexcept(false)
{
	// TODO: Parse configuration file
	(void)configuration_file;

	(void)sinks.emplace_back(std::make_shared<sink_terminal>("terminal", sink_terminal_configuration{ { "[{TAG}] {MESSAGE}", "", 63U, false }, stdout, true }));
}

namespace details
{

void log(const std::string_view sink_name,
		 const std::uint8_t		severity_bit,
		 const std::string_view tag,
		 const std::string_view file_path,
		 const std::string_view function_name,
		 const std::int32_t		line,
		 const std::string&		message) noexcept
{
	try
	{
		sinks[0]->log(severity_bit, tag, file_path, function_name, line, message);
	}
	catch (const std::logic_error& exception)
	{
		DEBUG_PRINT("Caught std::logic_error while sending message to the logger! (error message: \"{}\")", exception.what());
	}
	catch (const std::invalid_argument& exception)
	{
		DEBUG_PRINT("Caught std::invalid_argument sending message to a sink! (error message: \"{}\")", exception.what());
	}
}

} /*< namespace details */

} /*< namespace hob::log */
