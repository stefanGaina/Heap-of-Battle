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

#ifndef HOB_LOG_INTERNAL_SINK_TERMINAL_HPP_
#define HOB_LOG_INTERNAL_SINK_TERMINAL_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "sink_base.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob::log
{

/** ***************************************************************************************************
 * @brief This class provides the unique (only 1 instance is allowed) terminal sink.
 *****************************************************************************************************/
class HOB_LOG_LOCAL sink_terminal final : public sink_base
{
public:
	/** ***********************************************************************************************
	 * @brief Configures the terminal specific sink parameters.
	 * @param name: The name of the sink.
	 * @param configuration: The parameters that will be configured with.
	 * @throws std::invalid_argument: If the stream is **not** stdout or stderr, severity level is not
	 * in the [0, 63] interval or the format does not contain the specifier for the log message.
	 * @throws std::bad_alloc: If making the copy of the name, time or time format fails.
	 *************************************************************************************************/
	sink_terminal(std::string_view name, const sink_terminal_configuration& configuration) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Sets a new stream. It is **not** thread-safe.
	 * @param stream: The stream to be set.
	 * @returns void
	 * @throws std::invalid_argument: If stream is **not** stdout or stderr.
	 *************************************************************************************************/
	void set_stream(FILE* stream) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Gets the current stream. It is thread-safe.
	 * @param void
	 * @returns The current stream.
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] FILE* get_stream(void) const noexcept;

	/** ***********************************************************************************************
	 * @brief Sets a new configuration of the terminal color. It is **not** thread-safe.
	 * @param color: The color configuration to be set.
	 * @returns void
	 * @throws N/A.
	 *************************************************************************************************/
	void set_color(bool color) noexcept;

	/** ***********************************************************************************************
	 * @brief Gets the current configuration of the terminal color. It is thread-safe.
	 * @param void
	 * @returns true - the color in the terminal is enabled.
	 * @returns false - the color in the terminal is disabled.
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] bool get_color(void) const noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Prints the message to the terminal. It is **not** thread-safe.
	 * @param severity_bit: Bit indicating the type of message that is being logged (see
	 * log1cxx::severity_level).
	 * @param message: The message to be logged.
	 * @returns true - the message has been logged successfully.
	 * @returns false - the log has been lost.
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] bool log(std::uint8_t severity_bit, std::string_view message) noexcept override;

	/** ***********************************************************************************************
	 * @brief Changes the color of the terminal output depending on the severity level of the log. (0
	 * will restore the color to its default).
	 * @param severity_bit: Bit indicating the type of message that is being logged (see
	 * log1cxx::severity_level).
	 * @returns void
	 * @throws N/A.
	 *************************************************************************************************/
	void change_color(std::uint8_t severity_bit = 0U) const noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Stream which the messages will be printed to (only stdout and stderr is supported).
	 *************************************************************************************************/
	FILE* stream;

	/** ***********************************************************************************************
	 * @brief Flag indicating if the messages are colored based on severity level.
	 *************************************************************************************************/
	bool color_enabled;
};

/** ***************************************************************************************************
 * @brief Changes the terminal text color based on the severity of the log in a RAII manner.
 *****************************************************************************************************/
class HOB_LOG_LOCAL color final
{
public:
	/** ***********************************************************************************************
	 * @brief Changes the terminal text color based on the severity of the log.
	 * @param color_enabled: Flag indicating if the terminal text color needs to be changed.
	 * @param severity_bit: Bit indicating the type of message that is being logged (see
	 * hob::log::severity_level).
	 * @throws N/A.
	 *************************************************************************************************/
	color(bool color_enabled, std::uint8_t severity_bit) noexcept;

	/** ***********************************************************************************************
	 * @brief Restores the color to the default one (only if it was changed).
	 * @param void
	 * @throws N/A.
	 *************************************************************************************************/
	~color(void) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Stored flag to not restore color in destructor if it was not changed.
	 *************************************************************************************************/
	const bool color_enabled;
};

} /*< namespace hob::log */

#endif /*< HOB_LOG_INTERNAL_SINK_TERMINAL_HPP_ */
