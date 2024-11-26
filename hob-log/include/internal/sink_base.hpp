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
 * @file sink_base.hpp
 * @author Gaina Stefan
 * @date 17.11.2024
 * @brief This header defines the sink_base class.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_LOG_INTERNAL_SINK_BASE_HPP_
#define HOB_LOG_INTERNAL_SINK_BASE_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <optional>
#include <memory>
#include <atomic>

#include "types.hpp"
#include "sink.hpp"

/******************************************************************************************************
 * FORWARD DECLARATIONS
 *****************************************************************************************************/

namespace hob::log
{

class worker;

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief This class implements the common propierties of the sinks (besides composed sink).
 *****************************************************************************************************/
class HOB_LOG_LOCAL sink_base : public sink
{
public:
	/** ***********************************************************************************************
	 * @brief Configures the common sink parameters.
	 * @param name: The name of the sink.
	 * @param configuration: The parameters that will be configured with.
	 * @throws std::invalid_argument: If the name is invalid, severity level is not in the [0, 63]
	 * interval or the format does not contain the specifier for the log message.
	 * @throws std::bad_alloc: If making the copy of the name fails.
	 *************************************************************************************************/
	sink_base(std::string_view name, const sink_base_configuration& configuration) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Virtual destructor to avoid polymorphically delete undefined behavior. It is defined in
	 * the source file so that std::unique_ptr's destructor does not get inlined as well and worker
	 * can be forward declared.
	 * @param void
	 * @throws N/A.
	 *************************************************************************************************/
	virtual ~sink_base(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Processes the message and delegates it to the concrete sink.
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
			 std::string_view message) noexcept override final;

	/** ***********************************************************************************************
	 * @brief Gets how many logs have been lost due to unrecoverable errors. In case of overflow there
	 * is no way to detect that, but the value will remain to UINT64_MAX. It is thread-safe.
	 * @param void
	 * @returns How many logs have been lost due to unrecoverable errors.
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] std::uint64_t get_lost_logs(void) const noexcept;

	/** ***********************************************************************************************
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
	 * @param sink_name: The name of the sink the format will be set to.
	 * @param format: The message format to be set.
	 * @returns void
	 * @throws std::invalid_argument: If the format does not contain the specifier for the log message.
	 * @throws std::bad_alloc: If making the copy of the message format fails.
	 *************************************************************************************************/
	void set_format(std::string_view format) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Gets the current message format. It is thread-safe.
	 * @param void
	 * @returns The current message format (can not be empty).
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] std::string_view get_format(void) const noexcept;

	/** ***********************************************************************************************
	 * @brief Set a new time format. It is **not** thread-safe. The supported placeholders (all
	 * optional) are:
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
	 * @param time_format: The time format to be set. It can be empty.
	 * @returns void
	 * @throws std::bad_alloc: If making the copy of the time format fails.
	 *************************************************************************************************/
	void set_time_format(std::string_view time_format) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Gets the current time format. It is thread-safe.
	 * @param void
	 * @returns The current time format (can be empty).
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] std::string_view get_time_format(void) const noexcept;

	/** ***********************************************************************************************
	 * @brief Set a new severity level bitmask. It is **not** thread-safe.
	 * @param severity_level: The severity level bitmask to be set.
	 * @returns void
	 * @throws std::invalid_argument: If severity level is not in the [0, 63] interval.
	 *************************************************************************************************/
	void set_severity_level(std::uint8_t severity_level) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Gets the current severity level bitmask. It is thread-safe.
	 * @param void
	 * @return The current severity level bitmask (values between 0 and 63).
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] std::uint8_t get_severity_level(void) const noexcept;

	/** ***********************************************************************************************
	 * @brief Sets a new asynchronous mode. It is **not** thread-safe.
	 * @param async_mode: The asynchronous mode to be set.
	 * @returns void
	 * @throws std::bad_alloc: If the mode is enabled and the initialization fails.
	 *************************************************************************************************/
	void set_async_mode(const bool async_mode) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Gets the current asynchronous mode. It is thread-safe.
	 * @param void
	 * @returns true - the messages will be logged asynchronous.
	 * @returns false - the message will be logged synchronous.
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] bool get_async_mode(void) const noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Finds the name of the host. It is thread-safe.
	 * @param void
	 * @returns The name of the host or unkown if it could not be found.
	 * @throws std::bad_alloc: If constructing the result string fails due to memory exhaustion.
	 *************************************************************************************************/
	[[nodiscard]] static std::string get_host_name(void) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Method for concrete sinks to handle logs that have been processed.
	 * @param severity_bit: Bit indicating the type of message that is being logged (see
	 * hob::log::severity_level).
	 * @param message: The message to be logged.
	 * @returns true - the message has been logged successfully.
	 * @returns false - the log has been lost.
	 * @throws N/A.
	 *************************************************************************************************/
	virtual bool log(std::uint8_t severity_bit, std::string_view message) noexcept = 0;

	/** ***********************************************************************************************
	 * @brief Formats the message according to the format and time format. It is thread-safe.
	 * @param tag: Tag indicating the type of message.
	 * @param file_path: The path of the file where the log function is being called.
	 * @param function_name: The name of the function where this call is made.
	 * @param line: The line where the log function is being called.
	 * @param message: The message to be logged.
	 * @returns The message after being formatted.
	 * @throws std::bad_alloc: If the memory allocation for the formatted message fails.
	 *************************************************************************************************/
	[[nodiscard]] std::string
	format_message(std::string_view tag, std::string_view file_path, std::string_view function_name, std::int32_t line, std::string_view message) const
		noexcept(false);

	/** ***********************************************************************************************
	 * @brief Formats the time according to the format. It is thread-safe.
	 * @param void
	 * @returns The formatted time or a string indicating error getting the current time.
	 * @throws std::bad_alloc: If the memory alocation of the formatted time fails.
	 *************************************************************************************************/
	[[nodiscard]] std::string get_formatted_time(void) const noexcept(false);

private:
	/** ***********************************************************************************************
	 * @brief The format of the message to be logged.
	 *************************************************************************************************/
	std::string format;

	/** ***********************************************************************************************
	 * @brief The format of the time information (can be empty if time specifier is not in format).
	 *************************************************************************************************/
	std::string time_format;

	/** ***********************************************************************************************
	 * @brief Bitmask where bits set to 0 filter messages of that severity.
	 *************************************************************************************************/
	std::uint8_t severity_level;

	/** ***********************************************************************************************
	 * @brief Worker that logs the message asynchronically if this option is enabled.
	 *************************************************************************************************/
	std::unique_ptr<worker> async_worker;

	/** ***********************************************************************************************
	 * @brief How many logs have been lost due to unrecoverable errors.
	 *************************************************************************************************/
	std::atomic<std::uint64_t> lost_logs_count;
};

} /*< namespace hob::log */

#endif /*< HOB_LOG_INTERNAL_SINK_BASE_HPP_ */
