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
 * @file sink.hpp
 * @author Gaina Stefan
 * @date 17.11.2024
 * @brief This header defines the sink class.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_LOG_INTERNAL_SINK_HPP_
#define HOB_LOG_INTERNAL_SINK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <string>
#include <cstdint>

#include "details/visibility.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob::log
{

/** ***************************************************************************************************
 * @brief Interface that all the sinks shall implement, because it is the way the logger can redirect
 * messages.
 *****************************************************************************************************/
class HOB_LOG_LOCAL sink
{
public:
	/** ***********************************************************************************************
	 * @brief Makes a copy of the name.
	 * @param name: The name of the sink.
	 * @throws std::invalid_argument: If the name is invalid (empty string).
	 * @throws std::bad_alloc: If making the copy of the name fails.
	 *************************************************************************************************/
	sink(std::string_view name) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Virtual destructor to avoid polymorphically delete undefined behavior.
	 * @param void
	 * @throws N/A.
	 *************************************************************************************************/
	virtual ~sink(void) noexcept = default;

	/** ***********************************************************************************************
	 * @brief Pure virtual method allowing children to log the message based on their type.
	 * @param severity_bit: Bit indicating the type of message that is being logged (see
	 * hob::log::severity_level).
	 * @param tag: Tag indicating the type of message.
	 * @param file_path: The path of the file where the log function is being called.
	 * @param function_name: The name of the function where this call is made.
	 * @param line: The line where the log function is being called.
	 * @param message: The message to be logged.
	 * @returns void
	 * @throws N/A.
	 *************************************************************************************************/
	virtual void log(std::uint8_t	  severity_bit,
					 std::string_view tag,
					 std::string_view file_path,
					 std::string_view function_name,
					 std::int32_t	  line,
					 std::string_view message) noexcept = 0;

	/** ***********************************************************************************************
	 * @brief Gets the name of the sink. It is thread-safe.
	 * @param void
	 * @returns The name of the sink (non-empty).
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] std::string_view get_name(void) const noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Copy of the assigned name to be able to get identified.
	 *************************************************************************************************/
	const std::string name;
};

} /*< namespace hob::log */

#endif /*< HOB_LOG_INTERNAL_SINK_HPP_ */
