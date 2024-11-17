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

#ifndef HOB_LOG_DETAILS_INTERNAL_HPP_
#define HOB_LOG_DETAILS_INTERNAL_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <format>

#include "../types.hpp"
#include "../configuration.hpp"

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

#ifndef HOB_LOG_STRIP_ALL

// TOOD: documentation
#define HOB_LOG_DETAILS(sink_name, severity_bit, tag, format, ...)                                                                                                 \
	hob::log::details::log(sink_name, severity_bit, tag, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)

#endif /*< HOB_LOG_STRIP_ALL */

#ifndef HOB_LOG_STRIP_FATAL

/** ***************************************************************************************************
 * @brief This macro is not meant to be called outside hob-log macros.
 * @param sink_name: The name of the name the message will be sent to.
 * @param format: String that contains the text to be written.
 * @param VA_ARGS: Arguments to be formatted (optional).
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_DETAILS_FATAL(sink_name, format, ...) HOB_LOG_DETAILS(sink_name, hob::log::severity_level::FATAL, hob::log::LOG_TAG_FATAL, format, ##__VA_ARGS__)

#endif /*< HOB_LOG_STRIP_FATAL */

#ifndef HOB_LOG_STRIP_ERROR

/** ***************************************************************************************************
 * @brief This macro is not meant to be called outside hob-log macros.
 * @param sink_name: The name of the name the message will be sent to.
 * @param format: String that contains the text to be written.
 * @param VA_ARGS: Arguments to be formatted (optional).
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_DETAILS_ERROR(sink_name, format, ...) HOB_LOG_DETAILS(sink_name, hob::log::severity_level::ERROR, hob::log::LOG_TAG_ERROR, format, ##__VA_ARGS__)

#endif /*< HOB_LOG_STRIP_ERROR */

#ifndef HOB_LOG_STRIP_WARN

/** ***************************************************************************************************
 * @brief This macro is not meant to be called outside hob-log macros.
 * @param sink_name: The name of the name the message will be sent to.
 * @param format: String that contains the text to be written.
 * @param VA_ARGS: Arguments to be formatted (optional).
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_DETAILS_WARN(sink_name, format, ...) HOB_LOG_DETAILS(sink_name, hob::log::severity_level::WARN, hob::log::LOG_TAG_WARN, format, ##__VA_ARGS__)

#endif /*< HOB_LOG_STRIP_WARN */

#ifndef HOB_LOG_STRIP_INFO

/** ***************************************************************************************************
 * @brief This macro is not meant to be called outside hob-log macros.
 * @param sink_name: The name of the name the message will be sent to.
 * @param format: String that contains the text to be written.
 * @param VA_ARGS: Arguments to be formatted (optional).
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_DETAILS_INFO(sink_name, format, ...) HOB_LOG_DETAILS(sink_name, hob::log::severity_level::INFO, hob::log::LOG_TAG_INFO, format, ##__VA_ARGS__)

#endif /*< HOB_LOG_STRIP_INFO */

#ifndef HOB_LOG_STRIP_DEBUG

/** ***************************************************************************************************
 * @brief This macro is not meant to be called outside hob-log macros.
 * @param sink_name: The name of the name the message will be sent to.
 * @param format: String that contains the text to be written.
 * @param VA_ARGS: Arguments to be formatted (optional).
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_DETAILS_DEBUG(sink_name, format, ...) HOB_LOG_DETAILS(sink_name, hob::log::severity_level::DEBUG, hob::log::LOG_TAG_DEBUG, format, ##__VA_ARGS__)

#endif /*< HOB_LOG_STRIP_DEBUG */

#ifndef HOB_LOG_STRIP_TRACE

/** ***************************************************************************************************
 * @brief This macro is not meant to be called outside hob-log macros.
 * @param sink_name: The name of the name the message will be sent to.
 * @param format: String that contains the text to be written.
 * @param VA_ARGS: Arguments to be formatted (optional).
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_DETAILS_TRACE(sink_name, format, ...) HOB_LOG_DETAILS(sink_name, hob::log::severity_level::TRACE, hob::log::LOG_TAG_TRACE, format, ##__VA_ARGS__)

#endif /*< HOB_LOG_STRIP_TRACE */

/******************************************************************************************************
 * FUNCTION PROTOTYPES
 *****************************************************************************************************/

#ifndef HOB_LOG_STRIP_ALL

namespace hob::log::details
{

/** ***************************************************************************************************
 * @brief This function is not meant to be called outside hob-log macros.
 * @tparam: Variadic parameters to format.
 * @param sink_name: The name of the name the message will be sent to.
 * @param severity_bit: Bit indicating the type of message that is being logged (see
 * hob::log::severity_level).
 * @param tag: Tag indicating the type of message.
 * @param file_path: The path of the file where the log function is being called.
 * @param function_name: The name of the function where this call is made.
 * @param line: The line where the log function is being called.
 * @param format: String that contains the text to be written.
 * @param args: Arguments to be formatted.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
template<typename... args>
HOB_LOG_API extern void
log(std::string_view sink_name,
	std::uint8_t	 severity_bit,
	std::string_view tag,
	std::string_view file_path,
	std::string_view function_name,
	std::int32_t	 line,
	std::string_view format,
	args&&... arguments) noexcept;

/** ***********************************************************************************************
 * @brief Sends a message to the appropiate sink for it to handle.
 * @param sink_name: The name of the name the message will be sent to.
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
HOB_LOG_API extern void
log(std::string_view   sink_name,
	std::uint8_t	   severity_bit,
	std::string_view   tag,
	std::string_view   file_path,
	std::string_view   function_name,
	std::int32_t	   line,
	const std::string& message) noexcept;

/******************************************************************************************************
 * FUNCTION DEFINITIONS
 *****************************************************************************************************/

template<typename... args>
void log(std::string_view		sink_name,
		 const std::uint8_t		severity_bit,
		 const std::string_view tag,
		 const std::string_view file_path,
		 const std::string_view function_name,
		 const std::int32_t		line,
		 const std::string_view format,
		 args&&... arguments) noexcept
{
	try
	{
		log(sink_name, severity_bit, tag, file_path, function_name, line, std::vformat(format, std::make_format_args(std::forward<args>(arguments)...)));
	}
	catch (const std::exception& exception)
	{
	}
}

} /*< namespace hob::log::details */

#endif /*< HOB_LOG_STRIP_ALL */

#endif /*< HOB_LOG_DETAILS_INTERNAL_HPP_ */
