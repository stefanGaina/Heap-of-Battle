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
 * @file configuration.hpp
 * @author Gaina Stefan
 * @date 17.11.2024
 * @brief This header defines compile-time configuration.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_LOG_CONFIGURATION_HPP_
#define HOB_LOG_CONFIGURATION_HPP_

#ifndef HOB_LOG_STRIP_ALL

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <string_view>

/******************************************************************************************************
 * CONSTANTS
 *****************************************************************************************************/

namespace hob::log
{

/** ***************************************************************************************************
 * @brief The tag that is attached to fatal logs to be identified.
 *****************************************************************************************************/
inline constexpr std::string_view LOG_TAG_FATAL = "fatal";

/** ***************************************************************************************************
 * @brief The tag that is attached to error logs to be identified.
 *****************************************************************************************************/
inline constexpr std::string_view LOG_TAG_ERROR = "error";

/** ***************************************************************************************************
 * @brief The tag that is attached to warn logs to be identified.
 *****************************************************************************************************/
inline constexpr std::string_view LOG_TAG_WARN = "warn";

/** ***************************************************************************************************
 * @brief The tag that is attached to info logs to be identified.
 *****************************************************************************************************/
inline constexpr std::string_view LOG_TAG_INFO = "info";

/** ***************************************************************************************************
 * @brief The tag that is attached to debug logs to be identified.
 *****************************************************************************************************/
inline constexpr std::string_view LOG_TAG_DEBUG = "debug";

/** ***************************************************************************************************
 * @brief The tag that is attached to trace logs to be identified.
 *****************************************************************************************************/
inline constexpr std::string_view LOG_TAG_TRACE = "trace";

/** ***************************************************************************************************
 * @brief The tag that is attached to expect logs to be identified.
 *****************************************************************************************************/
inline constexpr std::string_view LOG_TAG_EXPECT = "expect";

/** ***************************************************************************************************
 * @brief The tag that is attached to assert logs to be identified.
 *****************************************************************************************************/
inline constexpr std::string_view LOG_TAG_ASSERT = "assert";

} /*< namespace hob::log */

#endif /*< HOB_LOG_STRIP_ALL */

#endif /*< HOB_LOG_CONFIGURATION_HPP_ */
