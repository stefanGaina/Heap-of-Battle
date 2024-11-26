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
 * @file sink_base.cpp
 * @author Gaina Stefan
 * @date 17.11.2024
 * @brief This file implements the class defined in sink_base.hpp.
 * @todo The format and time format should not be re-evaluated each time a new message is being logged.
 * This is an efficiency optimisation, so it is not high priority for now. gethostname() is being used,
 * which enforces the platform to be POSIX.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <stdexcept>
#include <functional>
#include <filesystem>
#include <cstdint>
#include <cinttypes>
#include <unistd.h>

#include "sink_base.hpp"
#include "worker.hpp"
#include "utility.hpp"

/******************************************************************************************************
 * CONSTANTS
 *****************************************************************************************************/

namespace hob::log
{

/** ***************************************************************************************************
 * @brief The mandatory substring that will be substitued for the message inside the log.
 *****************************************************************************************************/
static constexpr std::string_view FORMAT_SPECIFIER_MESSAGE = "{MESSAGE}";

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

sink_base::sink_base(const std::string_view name, const sink_base_configuration& configuration) noexcept(false)
	: sink{ name }
	, format{ "" }
	, time_format{ "" }
	, severity_level{ 0U }
	, async_worker{ nullptr }
	, lost_logs_count{ 0UL }
{
	set_format(configuration.format);
	set_time_format(configuration.time_format);
	set_severity_level(configuration.severity_level);
	set_async_mode(configuration.async_mode);
}

sink_base::~sink_base(void) noexcept = default;

void sink_base::log(const std::uint8_t	   severity_bit,
					const std::string_view tag,
					const std::string_view file_path,
					const std::string_view function_name,
					const std::int32_t	   line,
					const std::string_view message) noexcept
{
	std::string formatted_message = "";

	assert(nullptr != this);

	if (severity_bit != (severity_bit & severity_level))
	{
		return;
	}

	try
	{
		formatted_message = format_message(tag, file_path, function_name, line, message);
	}
	catch (const std::bad_alloc& exception)
	{
		DEBUG_PRINT("Caught std::bad_alloc while formatting message! (error message: \"{}\")", exception.what());
		lost_logs_count += UINT64_MAX > lost_logs_count ? 1UL : 0UL;
		return;
	}

	lost_logs_count +=
		(nullptr == async_worker ? false == log(severity_bit, formatted_message) : false == async_worker->log(severity_bit, std::move(formatted_message)))
			? UINT64_MAX > lost_logs_count ? 1UL : 0UL
			: 0UL;
}

std::uint64_t sink_base::get_lost_logs(void) const noexcept
{
	assert(nullptr != this);
	return lost_logs_count;
}

void sink_base::set_format(const std::string_view format) noexcept(false)
{
	assert(nullptr != this);

	if (std::string_view::npos == format.find(FORMAT_SPECIFIER_MESSAGE))
	{
		throw std::invalid_argument{ std::format("Format's mandatory \"{}\" field is missing!", FORMAT_SPECIFIER_MESSAGE) };
	}

	this->format = format;
}

std::string_view sink_base::get_format(void) const noexcept
{
	assert(nullptr != this);
	return format;
}

void sink_base::set_time_format(const std::string_view time_format) noexcept(false)
{
	assert(nullptr != this);
	this->time_format = time_format;
}

std::string_view sink_base::get_time_format(void) const noexcept
{
	assert(nullptr != this);
	return time_format;
}

void sink_base::set_severity_level(const std::uint8_t severity_level) noexcept(false)
{
	assert(nullptr != this);

	if (63U < severity_level)
	{
		throw std::invalid_argument{ "Severity level is not in the [0, 63] interval!" };
	}

	this->severity_level = severity_level;
}

std::uint8_t sink_base::get_severity_level(void) const noexcept
{
	assert(nullptr != this);
	return severity_level;
}

void sink_base::set_async_mode(const bool async_mode) noexcept(false)
{
	assert(nullptr != this);

	if (true == async_mode && false == get_async_mode())
	{
		async_worker = std::make_unique<worker>(
			std::bind(static_cast<bool (sink_base::*)(std::uint8_t, std::string_view)>(&sink_base::log), this, std::placeholders::_1, std::placeholders::_2),
			lost_logs_count);
		return;
	}

	if (false == async_mode && true == get_async_mode())
	{
		async_worker = nullptr;
	}
}

bool sink_base::get_async_mode(void) const noexcept
{
	assert(nullptr != this);
	return nullptr != async_worker;
}

std::string sink_base::get_host_name(void) noexcept(false)
{
	std::array<char, 256UL> hostname = {};
	return 0 == gethostname(hostname.data(), hostname.size()) ? hostname.data() : "Unknown";
}

std::string sink_base::format_message(const std::string_view tag,
									  const std::string_view file_path,
									  const std::string_view function_name,
									  const std::int32_t	 line,
									  const std::string_view message) const noexcept(false)
{
	std::string formatted_message = format;

	assert(nullptr != this);
	assert(false == tag.empty());
	assert(false == file_path.empty());
	assert(false == function_name.empty());
	assert(0 < line);

	// TODO: This should not be re-evaluated everytime if there are optional fields missing, an intermediary efficient representation is needed.
	utility::replace_placeholder(formatted_message, "{TIME}", get_formatted_time());
	utility::replace_placeholder(formatted_message, "{TAG}", tag);
	utility::replace_placeholder(formatted_message, "{FILE:long}", file_path);
	utility::replace_placeholder(formatted_message, "{FILE:short}", std::filesystem::path{ file_path }.filename().string());
	utility::replace_placeholder(formatted_message, "{FUNCTION}", function_name);
	utility::replace_placeholder(formatted_message, "{LINE}", std::to_string(line));
	utility::replace_placeholder(formatted_message, "{HOST}", get_host_name());
	utility::replace_placeholder(formatted_message, "{PID}", std::to_string(getpid()));
	utility::replace_placeholder(formatted_message, "{THREAD}", std::format("{}", std::this_thread::get_id()));
	utility::replace_placeholder(formatted_message, FORMAT_SPECIFIER_MESSAGE, message);

	return std::format("{}\n", formatted_message);
}

std::string sink_base::get_formatted_time(void) const noexcept(false)
{
	static constexpr std::size_t								MONTHS_COUNT   = 12UL;
	static constexpr std::size_t								WEEK_DAY_COUNT = 7UL;
	static constexpr std::array<std::string_view, MONTHS_COUNT> MONTHS_LONG	   = {
		   "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
	};
	static constexpr std::array<std::string_view, MONTHS_COUNT> MONTHS_SHORT = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};
	static constexpr std::array<std::string_view, WEEK_DAY_COUNT> DAY_LONG	= { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	static constexpr std::array<std::string_view, WEEK_DAY_COUNT> DAY_SHORT = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

	std::pair<std::tm*, std::int64_t> time			 = utility::get_time();
	std::string						  formatted_time = time_format;

	assert(nullptr != this);

	if (nullptr == time.first)
	{
		return "TIME_ERROR";
	}

	assert(0 <= time.first->tm_mon && MONTHS_COUNT > time.first->tm_mon);
	assert(0 <= time.first->tm_yday && 366 > time.first->tm_yday);
	assert(0 <= time.first->tm_wday && WEEK_DAY_COUNT > time.first->tm_wday);
	assert(0 <= time.first->tm_hour && 24 > time.first->tm_hour);
	assert(0 <= time.first->tm_min && 60 > time.first->tm_min);
	assert(0 <= time.first->tm_sec && 60 > time.first->tm_sec);
	assert(0 <= time.second && 1000 > time.second);

	// TODO: This should not be re-evaluated everytime if there are optional fields missing, an intermediary efficient representation is needed.
	utility::replace_placeholder(formatted_time, "{YEAR}", std::format("{:04}", time.first->tm_year + 1900));
	utility::replace_placeholder(formatted_time, "{MONTH:numeric}", std::format("{:02}", time.first->tm_mon + 1));
	utility::replace_placeholder(formatted_time, "{MONTH:long}", MONTHS_LONG[time.first->tm_mon]);
	utility::replace_placeholder(formatted_time, "{MONTH:short}", MONTHS_SHORT[time.first->tm_mon]);
	utility::replace_placeholder(formatted_time, "{DAY_YEAR}", std::format("{:03}", time.first->tm_yday + 1));
	utility::replace_placeholder(formatted_time, "{DAY_MONTH}", std::format("{:02}", time.first->tm_mday));
	utility::replace_placeholder(formatted_time, "{DAY_WEEK:numeric}", std::format("{:01}", time.first->tm_wday));
	utility::replace_placeholder(formatted_time, "{DAY_WEEK:long}", DAY_LONG[time.first->tm_wday]);
	utility::replace_placeholder(formatted_time, "{DAY_WEEK:short}", DAY_SHORT[time.first->tm_wday]);
	utility::replace_placeholder(formatted_time, "{HOUR:24}", std::format("{:02}", time.first->tm_hour));
	utility::replace_placeholder(formatted_time, "{HOUR:12}", std::format("{:02}", 0 == time.first->tm_hour ? 12 : time.first->tm_hour % 12));
	utility::replace_placeholder(formatted_time, "{MERIDIEM}", 12 > time.first->tm_hour ? "AM" : "PM");
	utility::replace_placeholder(formatted_time, "{MINUTE}", std::format("{:02}", time.first->tm_min));
	utility::replace_placeholder(formatted_time, "{SECOND}", std::format("{:02}", time.first->tm_sec));
	utility::replace_placeholder(formatted_time, "{MILLISECOND}", std::format("{:03}", time.second));

	return formatted_time;
}

} /*< namespace hob::log */
