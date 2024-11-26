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

#include <string>
#include <list>

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
 * @brief Checks if the logger has been successfully initialized and is usable. This is useful if
 * HOB_LOG_CONSTRUCTOR_ENABLED is not set to 0 and the initialization is done before main(). It is
 * thread-safe.
 * @param void
 * @returns true - the logger has been initialized successfully.
 * @returns false - the logger failed to be initialized.
 * @throws N/A.
 *****************************************************************************************************/
HOB_LOG_API [[nodiscard]] extern bool is_initialized(void) noexcept;

/** ***************************************************************************************************
 * @brief Initializes the logger from a configuration file. This is necessary in order to call logging
 * macros or functions. It is **not** thread-safe. The file's format is JSON and shall contain: TODO
 * @param configuration_file_path: The path to the JSON configuration file from which the logger will
 * be initialized.
 * @returns void
 * @throws TODO
 *****************************************************************************************************/
HOB_LOG_API void initialize(std::string_view configuration_file_path) noexcept(false);

/** ***************************************************************************************************
 * @brief Deinitializes the the logger library (safe to call even if not initialized) and saves the
 * runtime changes to the configuration file (if one was given during initialization). Calling this
 * is optional because the clean-up is done automatically. It is **not** thread-safe.
 * @param void
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
HOB_LOG_API extern void deinitialize(void) noexcept;

/** ***************************************************************************************************
 * @brief Adds a terminal sink to the logger. It is **not** thread-safe.
 * @param sink_name: The name of the terminal sink (can **not** be empty string).
 * @param configuration: The parameters that will be configured with.
 * @returns void
 * @throws std::logic_error: If the logger has not been initialized successfully or the sink name has
 * already been added.
 * @throws std::invalid_argument: If the stream is **not** stdout or stderr or severity level is
 * not in the [0, 63] interval.
 * @throws std::bad_alloc: If the memory allocation of the sink or making the copy of the name
 * fails.
 *****************************************************************************************************/
HOB_LOG_API extern void add_sink(std::string_view sink_name, const sink_terminal_configuration& configuration) noexcept(false);

/** ***************************************************************************************************
 * @brief Adds a composed sink to the logger. This sink type can not be configured after creation. It
 * is **not** thread-safe.
 * @param sink_name: The name of the composed sink (can **not** be empty string).
 * @param arguments: The names of the sinks that will be in composition.
 * @returns void
 * @throws std::logic_error: If the logger has not been initialized successfully or the sink name has
 * already been added.
 * @throws std::invalid_argument: If a sink name is invalid.
 * @throws std::bad_alloc: If the memory allocation of the sink or making the copy of the name
 * fails.
 *****************************************************************************************************/
HOB_LOG_API extern void add_sink(std::string_view sink_name, const std::list<std::string>& sink_names) noexcept(false);

/** ***************************************************************************************************
 * @brief Removes a sink, making it not usable anymore. This function does not fail if the sink
 * has not been added. It is **not** thread-safe.
 * @param sink_name: The name of the sink to be removed.
 * @returns void
 * @throws N/A.
 *****************************************************************************************************/
HOB_LOG_API extern void remove_sink(std::string_view sink_name) noexcept;

/** ***************************************************************************************************
 * @brief Checks if the name of a sink is valid. It is thread-safe.
 * @param sink_name: The name of the sink to be checked.
 * @returns true - the sink name is valid, this can be used.
 * @returns false - the sink name is invalid, using this will result in errors.
 * @throws N/A.
 *****************************************************************************************************/
HOB_LOG_API [[nodiscard]] extern bool is_sink_valid(std::string_view sink_name) noexcept;

/** ***************************************************************************************************
 * @brief Sets the name of the default sink that will be used when logging with default macros. It
 * is **not** thread-safe.
 * @param sink_name: The name of the default sink (empty string to invalidate the logging macro
 * calls).
 * @returns void
 * @throws std::logic_error: If the logger has not been initialized successfully.
 * @throws std::bad_alloc: If making the copy of the name fails.
 *****************************************************************************************************/
HOB_LOG_API extern void set_default_sink_name(std::string_view sink_name) noexcept(false);

/** ***************************************************************************************************
 * @brief Gets the name of the sink that is used when logging with default macros. It is
 * thread-safe.
 * @param void
 * @returns The name of the default sink.
 * @throws std::logic_error: If the logger has not been initialized successfully.
 *****************************************************************************************************/
HOB_LOG_API [[nodiscard]] extern std::string_view get_default_sink_name(void) noexcept(false);

/** ***************************************************************************************************
 * @brief Gets how many logs have been lost due to unrecoverable errors. In case of overflow there
 * is no way to detect that, but the value will remain to UINT64_MAX. It is thread-safe.
 * @param sink_name: The name of the sink the lost logs count will be got from.
 * @returns How many logs have been lost due to unrecoverable errors.
 * @throws std::logic_error: If the logger has not been initialized successfully.
 * @throws std::invalid_argument: If the sink has not been successfully added or it is of unsupported
 * type.
 *****************************************************************************************************/
HOB_LOG_API [[nodiscard]] std::uint64_t get_lost_logs(std::string_view sink_name) noexcept(false);

/** ***************************************************************************************************
 * @brief Sets a new message format. It is **not** thread-safe. The supported placeholders are:
 * - {TIME}: The time when the message has been logged (@see set_time_format()).
 * - {TAG}: Tag indicating the severity level of the log.
 * - {FILE:long}: Full path to the source code file where the message has been logged.
 * - {FILE:short}: Only the name of the source code file where the message has been logged.
 * - {FUNCTION}: The name of the function where the message has been logged.
 * - {LINE}: The line in the source code file where the message has been logged.
 * - {HOST}: The name of the host on which the program is running.
 * - {PID}: The identifier of the process that logged the message.
 * - {THREAD}: The identifier of the thread that logged the message.
 * - {MESSAGE}: The message to be logged. This is mandatory!
 * @param format: The message format to be set.
 * @returns void
 * @throws std::logic_error: If the logger has not been initialized successfully.
 * @throws std::invalid_argument: If the sink has not been successfully added, it is of unsupported
 * type or the format does not contain the specifier for the log message.
 * @throws std::bad_alloc: If making the copy of the message format fails.
 *****************************************************************************************************/
HOB_LOG_API extern void set_format(std::string_view sink_name, std::string_view format) noexcept(false);

/** ***************************************************************************************************
 * @brief Gets the current message format. It is thread-safe.
 * @param void
 * @returns The current message format (can not be empty).
 * @throws std::logic_error: If the logger has not been initialized successfully.
 * @throws std::invalid_argument: If the sink has not been successfully added or it is of unsupported
 * type.
 *****************************************************************************************************/
HOB_LOG_API [[nodiscard]] extern std::string_view get_format(std::string_view sink_name) noexcept(false);

/** ***************************************************************************************************
 * @brief Set a new time format. It is **not** thread-safe. The supported placeholders (all optional)
 * are:
 * - {YEAR}: The year when the message has been logged.
 * - {MONTH:numeric}: The month (in numeric form, [1, 12]) when the message has been logged.
 * - {MONTH:long}: The month (in full name, e.g. "December") when the message has been logged.
 * - {MONTH:short}: The month (in abbreviated name, e.g. "Dec") when the message has been logged.
 * - {DAY_YEAR}: The day of the year (in numeric form, [1, 366]) when the message has been logged.
 * - {DAY_MONTH}: The day of the month (in numeric form, [1, 31]) when the message has been logged.
 * - {DAY_WEEK:numeric}: The day of the week (in numeric form, [1, 7]) when the message has been logged.
 * - {DAY_WEEK:long}: The day of the week (in full name, e.g. "Monday") when the message has been logged.
 * - {DAY_WEEK:short}: The day of the week (in abbreviated name, e.g. "Mon") when the message has been logged.
 * - {HOUR:24}: The hour in 24 hour format (in numeric form, [0, 23]) when the message has been logged.
 * - {HOUR:12}: The hour in 12 hour format (in numeric form, [1, 12]) when the message has been logged.
 * - {MERIDIEM}: The meridiem ("AM" or "PM") when the message has been logged.
 * - {MINUTE}: The minute (in numeric form, [0, 59]) when the message has been logged.
 * - {SECOND}: The second (in numeric form, [0, 59]) when the message has been logged.
 * - {MILLISECOND}: The millisecond (in numeric form, [0, 999]) when the message has been logged.
 * @param time_format: The time format to be set. It can be nullptr.
 * @returns void
 * @throws std::logic_error: If the logger has not been initialized successfully.
 * @throws std::invalid_argument: If the sink has not been successfully added or it is of unsupported
 * type.
 * @throws std::bad_alloc: If making the copy of the time format fails.
 *****************************************************************************************************/
HOB_LOG_API extern void set_time_format(std::string_view sink_name, std::string_view time_format) noexcept(false);

/** ***************************************************************************************************
 * @brief Gets the current time format. It is thread-safe.
 * @param void
 * @returns The current time format (can be empty).
 * @throws std::logic_error: If the logger has not been initialized successfully.
 * @throws std::invalid_argument: If the sink has not been successfully added or it is of unsupported
 * type.
 *****************************************************************************************************/
HOB_LOG_API [[nodiscard]] extern std::string_view get_time_format(std::string_view sink_name) noexcept(false);

/** ***************************************************************************************************
 * @brief Sets a new severity level bitmask. It is **not** thread-safe.
 * @param sink_name: The name of the sink the severity level will be set to.
 * @param severity_level: The severity level bitmask to be set.
 * @returns void
 * @throws std::logic_error: If the logger has not been initialized successfully.
 * @throws std::invalid_argument: If the sink has not been successfully added or it is of unsupported
 * type.
 *****************************************************************************************************/
HOB_LOG_API extern void set_severity_level(std::string_view sink_name, std::uint8_t severity_level) noexcept(false);

/** ***************************************************************************************************
 * @brief Gets the current severity level bitmask. It is thread-safe.
 * @param sink_name: The name of the sink the severity level will be got from.
 * @returns The current severity level bitmask.
 * @throws std::logic_error: If the logger has not been initialized successfully.
 * @throws std::invalid_argument: If the sink has not been successfully added or it is of unsupported
 * type.
 *****************************************************************************************************/
HOB_LOG_API [[nodiscard]] extern std::uint8_t get_severity_level(std::string_view sink_name) noexcept(false);

/** ***************************************************************************************************
 * @brief Sets a new asynchronous mode. It is **not** thread-safe.
 * @param sink_name: The name of the sink the asynchronous mode will be set to.
 * @param async_mode: The asynchronous mode to be set.
 * @returns void
 * @throws std::logic_error: If the logger has not been initialized successfully.
 * @throws std::invalid_argument: If the sink has not been successfully added or it is of unsupported
 * type.
 * @throws std::bad_alloc: If the mode is enabled and the initialization fails.
 *****************************************************************************************************/
HOB_LOG_API void set_async_mode(std::string_view sink_name, bool async_mode) noexcept(false);

/** ***************************************************************************************************
 * @brief Gets the current asynchronous mode. It is thread-safe.
 * @param sink_name: The name of the sink the asynchronous mode will be got from.
 * @returns true - the messages will be logged asynchronous.
 * @returns false - the message will be logged synchronous.
 * @throws std::logic_error: If the logger has not been initialized successfully.
 * @throws std::invalid_argument: If the sink has not been successfully added or it is of unsupported
 * type.
 *****************************************************************************************************/
HOB_LOG_API [[nodiscard]] bool get_async_mode(std::string_view sink_name) noexcept(false);

/** ***************************************************************************************************
 * @brief Sets a new stream. It is **not** thread-safe.
 * @param sink_name: The name of the sink the stream will be set to.
 * @param stream: The stream to be set.
 * @returns void
 * @throws std::logic_error: If the logger has not been initialized successfully.
 * @throws std::invalid_argument: If the sink has not been successfully added or it is of unsupported
 * type.
 *****************************************************************************************************/
HOB_LOG_API extern void set_stream(std::string_view sink_name, FILE* stream) noexcept(false);

/** ***************************************************************************************************
 * @brief Gets the current stream. It is thread-safe.
 * @param sink_name: The name of the sink the stream will be got from.
 * @returns The current stream.
 * @throws std::logic_error: If the logger has not been initialized successfully.
 * @throws std::invalid_argument: If the sink has not been successfully added or it is of unsupported
 * type.
 *****************************************************************************************************/
HOB_LOG_API [[nodiscard]] extern FILE* get_stream(std::string_view sink_name) noexcept(false);

/** ***************************************************************************************************
 * @brief Sets a new configuration of the terminal color. It is **not** thread-safe.
 * @param sink_name: The name of the sink the color configuration will be set to.
 * @param color: The color configuration to be set.
 * @returns void
 * @throws std::logic_error: If the logger has not been initialized successfully.
 * @throws std::invalid_argument: If the sink has not been successfully added or it is of unsupported
 * type.
 *****************************************************************************************************/
HOB_LOG_API extern void set_color(std::string_view sink_name, bool color) noexcept(false);

/** ***************************************************************************************************
 * @brief Gets the current configuration of the terminal color. It is thread-safe.
 * @param sink_name: The name of the sink the color configuration will be got from.
 * @returns true - the color in the terminal is enabled.
 * @returns false - the color in the terminal is disabled.
 * @throws std::logic_error: If the logger has not been initialized successfully.
 * @throws std::invalid_argument: If the sink has not been successfully added or it is of unsupported
 * type.
 *****************************************************************************************************/
HOB_LOG_API [[nodiscard]] extern bool get_color(std::string_view sink_name) noexcept(false);

} /*< namespace hob::log */

#endif /*< HOB_LOG_LOGGER_HPP_ */
