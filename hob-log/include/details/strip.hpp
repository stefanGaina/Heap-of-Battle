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
 * @brief Strips hob_log_fatal() and hob_log_default_fatal() calls from compilation.
 *****************************************************************************************************/
#define HOB_LOG_STRIP_FATAL

/** ***************************************************************************************************
 * @brief Strips hob_log_error() and hob_log_default_error() calls from compilation.
 *****************************************************************************************************/
#define HOB_LOG_STRIP_ERROR

/** ***************************************************************************************************
 * @brief Strips hob_log_warn() and hob_log_default_warn() calls from compilation.
 *****************************************************************************************************/
#define HOB_LOG_STRIP_WARN

/** ***************************************************************************************************
 * @brief Strips hob_log_info() and hob_log_default_info() calls from compilation.
 *****************************************************************************************************/
#define HOB_LOG_STRIP_INFO

/** ***************************************************************************************************
 * @brief Strips hob_log_debug() and hob_log_default_debug() calls from compilation.
 *****************************************************************************************************/
#define HOB_LOG_STRIP_DEBUG

/** ***************************************************************************************************
 * @brief Strips hob_log_trace() and hob_log_default_trace() calls from compilation.
 *****************************************************************************************************/
#define HOB_LOG_STRIP_TRACE

/** ***************************************************************************************************
 * @brief Strips hob_log_expect() and hob_log_default_expect() calls from compilation.
 *****************************************************************************************************/
#define HOB_LOG_STRIP_EXPECT

/** ***************************************************************************************************
 * @brief Strips hob_log_assert(), hob_log_default_assert(), hob_log_abort() and
 * hob_log_default_abort() calls from compilation.
 *****************************************************************************************************/
#define HOB_LOG_STRIP_ASSERT

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
#define hob_log_fatal(sink_name, format, ...) (void)0

/** ***************************************************************************************************
 * @brief Fatal error messages are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define hob_log_default_fatal(format, ...) (void)0

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
#define hob_log_error(sink_name, format, ...) (void)0

/** ***************************************************************************************************
 * @brief Error messages are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define hob_log_default_error(format, ...) (void)0

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
#define hob_log_warn(sink_name, format, ...) (void)0

/** ***************************************************************************************************
 * @brief Warning messages are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define hob_log_default_warn(format, ...) (void)0

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
#define hob_log_info(sink_name, format, ...) (void)0

/** ***************************************************************************************************
 * @brief Information messages are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define hob_log_default_info(format, ...) (void)0

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
#define hob_log_debug(sink_name, format, ...) (void)0

/** ***************************************************************************************************
 * @brief Debug messages are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define hob_log_default_debug(format, ...) (void)0

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
#define hob_log_trace(sink_name, format, ...) (void)0

/** ***************************************************************************************************
 * @brief Trace messages are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define hob_log_default_trace(format, ...) (void)0

#endif /*< HOB_LOG_STRIP_TRACE */

#ifdef HOB_LOG_STRIP_EXPECT

/** ***************************************************************************************************
 * @brief Expectations are stripped from compilation.
 * @param sink_name: Does not matter.
 * @param condition: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define hob_log_expect(sink_name, condition) (void)0

/** ***************************************************************************************************
 * @brief Expectations are stripped from compilation.
 * @param condition: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define hob_log_default_expect(condition) (void)0

#endif /*< HOB_LOG_STRIP_EXPECT */

#ifdef HOB_LOG_STRIP_ASSERT

/** ***************************************************************************************************
 * @brief Assertions are stripped from compilation.
 * @param sink_name: Does not matter.
 * @param condition: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define hob_log_assert(sink_name, condition) (void)0

/** ***************************************************************************************************
 * @brief Assertions are stripped from compilation.
 * @param condition: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define hob_log_default_assert(condition) (void)0

/** ***************************************************************************************************
 * @brief Assertions are stripped from compilation.
 * @param sink_name: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define hob_log_abort(sink_name) (void)0

/** ***************************************************************************************************
 * @brief Assertions are stripped from compilation.
 * @param void
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define hob_log_default_abort() (void)0

#endif /*< HOB_LOG_STRIP_ASSERT */

#endif /*< HOB_LOG_DETAILS_STRIP_HPP_ */
