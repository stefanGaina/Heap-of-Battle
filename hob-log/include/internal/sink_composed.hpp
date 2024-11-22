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
 * @file sink_composed.hpp
 * @author Gaina Stefan
 * @date 22.11.2024
 * @brief This file defines the sink_composed class.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_LOG_INTERNAL_SINK_COMPOSED_HPP_
#define HOB_LOG_INTERNAL_SINK_COMPOSED_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <list>
#include <memory>

#include "sink.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob::log
{

/** ***************************************************************************************************
 * @brief This class provides the composed sink.
 * @details It does not provide a new logging implementation, but instead bundles other sinks so they
 * can be invoked through only 1 call.
 *****************************************************************************************************/
class HOB_LOG_LOCAL sink_composed final : public sink
{
public:
	/** ***********************************************************************************************
	 * @brief Configures the composed specific sink parameters.
	 * @param name: The name of the sink.
	 * @param sinks: The sinks that will get bundled (can **not** be empty).
	 * @throws std::invalid_argument: If the name is invalid.
	 * @throws std::bad_alloc: If making the copy of the name fails.
	 *************************************************************************************************/
	sink_composed(std::string_view name, std::list<std::shared_ptr<sink>>&& sinks) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Sends a message to the appropiate sinks for them to handle. It is **not** thread-safe.
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
	void log(std::uint8_t	  severity_bit,
			 std::string_view tag,
			 std::string_view file_path,
			 std::string_view function_name,
			 std::int32_t	  line,
			 std::string_view message) noexcept override;

private:
	/** ***********************************************************************************************
	 * @brief The sinks that the messages will be handed to (can **not** be empty).
	 *************************************************************************************************/
	const std::list<std::shared_ptr<sink>> sinks;
};

} /*< namespace hob::log */

#endif /*< HOB_LOG_INTERNAL_SINK_COMPOSED_HPP_ */
