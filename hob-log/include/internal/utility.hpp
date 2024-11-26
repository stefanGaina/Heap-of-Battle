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
 * @file utility.hpp
 * @author Gaina Stefan
 * @date 17.11.2024
 * @brief This header defines the utility functions/macros.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_LOG_INTERNAL_UTILITY_HPP_
#define HOB_LOG_INTERNAL_UTILITY_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <print>
#include <chrono>
#include <cassert>

#include "details/visibility.hpp"

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

#ifndef NDEBUG

/** ***************************************************************************************************
 * @brief Prints a message to the terminal. It is **not** thread safe.
 * @param format: String literal that contains the text to be written.
 * @param VA_ARGS: Arguments to be formatted (optional).
 * @returns void
 * @throws std::bad_alloc: If memory allocation fails.
 * @throws std::system_error: If writing to the stream fails.
 * @throws other: Exceptions propagated by used formatters.
 *****************************************************************************************************/
#define DEBUG_PRINT(format, ...) std::println("[hob-log] " format, ##__VA_ARGS__)

#else

/** ***************************************************************************************************
 * @brief Debug prints are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
#define DEBUG_PRINT(format, ...) (void)0

#endif /*< NDEBUG */

/******************************************************************************************************
 * FUNCTION PROTOTYPES
 *****************************************************************************************************/

namespace hob::log::utility
{

/** ***********************************************************************************************
 * @brief Replaces a placeholder inside a format string. It is thread-safe.
 * @param destination: The string to be formatted.
 * @param placeholder: The substring that will be substituted inside the format string.
 * @param replacement: The string that will replace the placeholder.
 * @returns void
 * @throws std::bad_alloc: If the replacement is larger than the placeholder and the memory
 * reallocation fails.
 *************************************************************************************************/
HOB_LOG_LOCAL extern void replace_placeholder(std::string& destination, std::string_view placeholder, std::string_view replacement) noexcept(false);

/** ***********************************************************************************************
 * @brief Gets information about the current time. It is thread-safe.
 * @param void
 * @returns Firsts in the pair is structure containing info about year, month, day, etc. (can be
 * nullptr in case of failure) and the second is the milliseconds.
 * @throws N/A.
 *************************************************************************************************/
HOB_LOG_LOCAL [[nodiscard]] extern std::pair<std::tm*, std::int64_t> get_time(void) noexcept;

} /*< namespace hob::log::utility */

#endif /*< HOB_LOG_INTERNAL_UTILITY_HPP_ */
