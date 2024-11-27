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
 * @file strip.hpp
 * @author Gaina Stefan
 * @date 17.11.2024
 * @brief This header defines empty macros for those that have been disabled.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_LOG_DETAILS_STRIP_HPP_
#define HOB_LOG_DETAILS_STRIP_HPP_

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

#ifdef HOB_LOG_STRIP_ALL

/** ***************************************************************************************************
 * @brief Strips HOB_LOG_FATAL(), HOB_LOG_DEFAULT_FATAL() and HOB_LOG_TERMINAL_FATAL() calls from
 * compilation.
 *****************************************************************************************************/
#define HOB_LOG_STRIP_FATAL

/** ***************************************************************************************************
 * @brief Strips HOB_LOG_ERROR(), HOB_LOG_DEFAULT_ERROR() and HOB_LOG_TERMINAL_ERROR() calls from
 * compilation.
 *****************************************************************************************************/
#define HOB_LOG_STRIP_ERROR

/** ***************************************************************************************************
 * @brief Strips HOB_LOG_WARN(), HOB_LOG_DEFAULT_WARN() and HOB_LOG_TERMINAL_WARN() calls from
 * compilation.
 *****************************************************************************************************/
#define HOB_LOG_STRIP_WARN

/** ***************************************************************************************************
 * @brief Strips HOB_LOG_INFO(), HOB_LOG_DEFAULT_INFO() and HOB_LOG_TERMINAL_INFO() calls from
 * compilation.
 *****************************************************************************************************/
#define HOB_LOG_STRIP_INFO

/** ***************************************************************************************************
 * @brief Strips HOB_LOG_DEBUG(), HOB_LOG_DEFAULT_DEBUG() and HOB_LOG_TERMINAL_DEBUG() calls from
 * compilation.
 *****************************************************************************************************/
#define HOB_LOG_STRIP_DEBUG

/** ***************************************************************************************************
 * @brief Strips HOB_LOG_TRACE(), HOB_LOG_DEFAULT_TRACE() and HOB_LOG_TERMINAL_TRACE() calls from
 * compilation.
 *****************************************************************************************************/
#define HOB_LOG_STRIP_TRACE

#endif /*< HOB_LOG_STRIP_ALL */

#ifdef HOB_LOG_STRIP_FATAL

/** ***************************************************************************************************
 * @brief Fatal error messages are stripped from compilation.
 * @param sink_name: Does not matter.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_FATAL(sink_name, format, ...) (void)0

/** ***************************************************************************************************
 * @brief Fatal error messages are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_DEFAULT_FATAL(format, ...) (void)0

#endif /*< HOB_LOG_STRIP_FATAL */

#ifdef HOB_LOG_STRIP_ERROR

/** ***************************************************************************************************
 * @brief Error messages are stripped from compilation.
 * @param sink_name: Does not matter.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_ERROR(sink_name, format, ...) (void)0

/** ***************************************************************************************************
 * @brief Error messages are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_DEFAULT_ERROR(format, ...) (void)0

#endif /*< HOB_LOG_STRIP_ERROR */

#ifdef HOB_LOG_STRIP_WARN

/** ***************************************************************************************************
 * @brief Warning messages are stripped from compilation.
 * @param sink_name: Does not matter.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_WARN(sink_name, format, ...) (void)0

/** ***************************************************************************************************
 * @brief Warning messages are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_DEFAULT_WARN(format, ...) (void)0

#endif /*< HOB_LOG_STRIP_WARN */

#ifdef HOB_LOG_STRIP_INFO

/** ***************************************************************************************************
 * @brief Information messages are stripped from compilation.
 * @param sink_name: Does not matter.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_INFO(sink_name, format, ...) (void)0

/** ***************************************************************************************************
 * @brief Information messages are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_DEFAULT_INFO(format, ...) (void)0

#endif /*< HOB_LOG_STRIP_INFO */

#ifdef HOB_LOG_STRIP_DEBUG

/** ***************************************************************************************************
 * @brief Debug messages are stripped from compilation.
 * @param sink_name: Does not matter.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_DEBUG(sink_name, format, ...) (void)0

/** ***************************************************************************************************
 * @brief Debug messages are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_DEFAULT_DEBUG(format, ...) (void)0

#endif /*< HOB_LOG_STRIP_DEBUG */

#ifdef HOB_LOG_STRIP_TRACE

/** ***************************************************************************************************
 * @brief Trace messages are stripped from compilation.
 * @param sink_name: Does not matter.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_TRACE(sink_name, format, ...) (void)0

/** ***************************************************************************************************
 * @brief Trace messages are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_LOG_DEFAULT_TRACE(format, ...) (void)0

#endif /*< HOB_LOG_STRIP_TRACE */

#endif /*< HOB_LOG_DETAILS_STRIP_HPP_ */
