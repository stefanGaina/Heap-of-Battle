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

#ifndef HOB_LOG_LOGGER_HPP_
#define HOB_LOG_LOGGER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <string_view>

#include "details/internal.hpp"
#include "details/strip.hpp"

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

#ifndef HOB_LOG_STRIP_FATAL

/** ***************************************************************************************************
 * @brief Logs a fatal error message (system is unusable or application is crashing).
 * @param sink_name: The name of the sink that the log will be redirected to (does nothing if it is
 * incorrect).
 * @param format: String that contains the text to be written.
 * @param VA_ARGS: Arguments to be formatted (optional).
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_FATAL(sink_name, format, ...) HOB_LOG_DETAILS_FATAL(sink_name, format, ##__VA_ARGS__)

#endif /*< HOB_LOG_STRIP_FATAL */

#ifndef HOB_LOG_STRIP_ERROR

/** ***************************************************************************************************
 * @brief Logs a non-fatal error message (system or application is still usable).
 * @param sink_name: The name of the sink that the log will be redirected to (does nothing if it is
 * incorrect).
 * @param format: String that contains the text to be written.
 * @param VA_ARGS: Arguments to be formatted (optional).
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_ERROR(sink_name, format, ...) HOB_LOG_DETAILS_ERROR(sink_name, format, ##__VA_ARGS__)

#endif /*< HOB_LOG_STRIP_ERROR */

#ifndef HOB_LOG_STRIP_WARN

/** ***************************************************************************************************
 * @brief Logs a warning message (something unusual that might require attention).
 * @param sink_name: The name of the sink that the log will be redirected to (does nothing if it is
 * incorrect).
 * @param format: String that contains the text to be written.
 * @param VA_ARGS: Arguments to be formatted (optional).
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_WARN(sink_name, format, ...) HOB_LOG_DETAILS_WARN(sink_name, format, ##__VA_ARGS__)

#endif /*< HOB_LOG_STRIP_WARN */

#ifndef HOB_LOG_STRIP_INFO

/** ***************************************************************************************************
 * @brief Logs an information message.
 * @param sink_name: The name of the sink that the log will be redirected to (does nothing if it is
 * incorrect).
 * @param format: String that contains the text to be written.
 * @param VA_ARGS: Arguments to be formatted (optional).
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_INFO(sink_name, format, ...) HOB_LOG_DETAILS_INFO(sink_name, format, ##__VA_ARGS__)

#endif /*< HOB_LOG_STRIP_INFO */

#ifndef HOB_LOG_STRIP_DEBUG

/** ***************************************************************************************************
 * @brief Logs a message for debugging purposes.
 * @param sink_name: The name of the sink that the log will be redirected to (does nothing if it is
 * incorrect).
 * @param format: String that contains the text to be written.
 * @param VA_ARGS: Arguments to be formatted (optional).
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_DEBUG(sink_name, format, ...) HOB_LOG_DETAILS_DEBUG(sink_name, format, ##__VA_ARGS__)

#endif /*< HOB_LOG_STRIP_DEBUG */

#ifndef HOB_LOG_STRIP_TRACE

/** ***************************************************************************************************
 * @brief Logs a message to show the path of the execution.
 * @param sink_name: The name of the sink that the log will be redirected to (does nothing if it is
 * incorrect).
 * @param format: String that contains the text to be written.
 * @param VA_ARGS: Arguments to be formatted (optional).
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_TRACE(sink_name, format, ...) HOB_LOG_DETAILS_TRACE(sink_name, format, ##__VA_ARGS__)

#endif /*< HOB_LOG_STRIP_TRACE */

/******************************************************************************************************
 * FUNCTION PROTOTYPES
 *****************************************************************************************************/

namespace hob::log
{

/** ***************************************************************************************************
 * @brief Initializes the logger from a configuration file. This is necessary in order to call logging
 * macros or functions. It is **not** thread-safe. The file's format is JSON and shall contain: TODO
 * @param configuration_file: The path to the JSON configuration file from which the logger will be
 * initialized.
 * @returns void
 * @throws TODO
 *****************************************************************************************************/
HOB_LOG_API void initialize(std::string_view configuration_file) noexcept(false);

} /*< namespace hob::log */

#endif /*< HOB_LOG_LOGGER_HPP_ */
