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

#ifndef HOB_LOG_TYPES_HPP_
#define HOB_LOG_TYPES_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#ifndef HOB_LOG_STRIP_ALL

#include <string>
#include <cstdio>

#include "details/visibility.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob::log
{

/** ***************************************************************************************************
 * @brief Scoped enumeration, but with implicit conversion.
 *****************************************************************************************************/
struct HOB_LOG_API severity_level final
{
	/** ***********************************************************************************************
	 * @brief Enumerates the bits representing if the log severity level is enabled.
	 *************************************************************************************************/
	enum severity_bit : std::uint8_t
	{
		FATAL = 1 << 0, /**< If bit is set fatal logs are enabled. */
		ERROR = 1 << 1, /**< If bit is set error logs are enabled. */
		WARN  = 1 << 2, /**< If bit is set warn logs are enabled.  */
		INFO  = 1 << 3, /**< If bit is set info logs are enabled.  */
		DEBUG = 1 << 4, /**< If bit is set debug logs are enabled. */
		TRACE = 1 << 5	/**< If bit is set trace logs are enabled. */
	};
};

/** ***************************************************************************************************
 * @brief Defines the common configuration parameters for the sinks.
 *****************************************************************************************************/
struct HOB_LOG_API sink_base_configuration final
{
	std::string_view format;		 /**< The format of the log message.								*/
	std::string_view time_format;	 /**< The format of the time when the message has been logged.		*/
	std::uint8_t	 severity_level; /**< Bitmask where bits set to 0 filter messages of that severity. */
	bool			 async_mode;	 /**< The messages are being logged on a separate thread.			*/
};

/** ***************************************************************************************************
 * @brief Defines the configuration parameters for the unique terminal sink.
 *****************************************************************************************************/
struct HOB_LOG_API sink_terminal_configuration final
{
	sink_base_configuration base;	/**< Common configuration parameters.													  */
	FILE*					stream; /**< Stream which the messages will be printed to (only stdout and stderr are supported). */
	bool					color;	/**< The messages are colored based on severity level.									  */
};

} /*< namespace hob::log */

#endif /*< HOB_LOG_STRIP_ALL */

#endif /*< HOB_LOG_TYPES_HPP_ */
