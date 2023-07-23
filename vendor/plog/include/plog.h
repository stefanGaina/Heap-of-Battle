/******************************************************************************************************
 * @file plog.h                                                                                       *
 * @date:      @author:                   Reason for change:                                          *
 * 22.06.2023  Gaina Stefan               Initial version.                                            *
 * 22.06.2023  Gaina Stefan               Add plog_get_version.                                       *
 * 22.06.2023  Gaina Stefan               Fixed the stripping of logging from compilation.            *
 * 29.06.2023  Gaina Stefan               Moved version to plog_version.h.                            *
 * @details This file defines the type definitions and public interface of Plog.                      *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef PLOG_H_
#define PLOG_H_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "plog_version.h"
#include "plog_internal.h"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief The name of the file to be opened if any other is not passed at initialization.
*/
#define PLOG_DEFAULT_FILE_NAME "messages"

/**
 * @brief The name of the file that is opened to read the persistent severity level (one will be created
 * if not already).
*/
#define PLOG_LEVEL_FILE_NAME "plog_level"

#ifdef PLOG_STRIP_ALL

/**
 * @brief Strips plog_fatal calls from compilation.
*/
#define PLOG_STRIP_FATAL

/**
 * @brief Strips plog_error calls from compilation.
*/
#define PLOG_STRIP_ERROR

/**
 * @brief Strips plog_warn calls from compilation.
*/
#define PLOG_STRIP_WARN

/**
 * @brief Strips plog_info calls from compilation.
*/
#define PLOG_STRIP_INFO

/**
 * @brief Strips plog_debug calls from compilation.
*/
#define PLOG_STRIP_DEBUG

/**
 * @brief Strips plog_trace calls from compilation.
*/
#define PLOG_STRIP_TRACE

/**
 * @brief Strips plog_verbose calls from compilation.
*/
#define PLOG_STRIP_VERBOSE

#endif /*< PLOG_STRIP_ALL */

#ifndef PLOG_STRIP_FATAL

/**
 * @brief Logs a fatal error message (system is unusable).
 * @param __VA_ARGS__: The message passed in a printf style.
*/
#define plog_fatal(...) plog_internal(E_PLOG_SEVERITY_LEVEL_FATAL, "fatal", __VA_ARGS__)

#else

/**
 * @brief Fatal error messages are stripped from compilation.
 * @param __VA_ARGS__: Do not matter.
*/
#define plog_fatal(...)

#endif /*< PLOG_STRIP_FATAL */

#ifndef PLOG_STRIP_ERROR

/**
 * @brief Logs a non-fatal error message (system is still usable).
 * @param __VA_ARGS__: The message passed in a printf style.
*/
#define plog_error(...) plog_internal(E_PLOG_SEVERITY_LEVEL_ERROR, "error", __VA_ARGS__)

#else

/**
 * @brief Error messages are stripped from compilation.
 * @param __VA_ARGS__: Do not matter.
*/
#define plog_error(...)

#endif /*< PLOG_STRIP_ERROR */

#ifndef PLOG_STRIP_WARN

/**
 * @brief Logs a warning message (something unusual that might require attention).
 * @param __VA_ARGS__: The message passed in a printf style.
*/
#define plog_warn(...) plog_internal(E_PLOG_SEVERITY_LEVEL_WARN, "warn", __VA_ARGS__)

#else

/**
 * @brief Warning messages are stripped from compilation.
 * @param __VA_ARGS__: Do not matter.
*/
#define plog_warn(...)

#endif /*< PLOG_STRIP_WARN */

#ifndef PLOG_STRIP_INFO

/**
 * @brief Logs an information message.
 * @param __VA_ARGS__: The message passed in a printf style.
*/
#define plog_info(...) plog_internal(E_PLOG_SEVERITY_LEVEL_INFO, "info", __VA_ARGS__)

#else

/**
 * @brief Information messages are stripped from compilation.
 * @param __VA_ARGS__: Do not matter.
*/
#define plog_info(...)

#endif /*< PLOG_STRIP_INFO */

#ifndef PLOG_STRIP_DEBUG

/**
 * @brief Logs a message for debugging purposes.
 * @param __VA_ARGS__: The message passed in a printf style.
*/
#define plog_debug(...) plog_internal(E_PLOG_SEVERITY_LEVEL_DEBUG, "debug", __VA_ARGS__)

#else

/**
 * @brief Debug messages are stripped from compilation.
 * @param __VA_ARGS__: Do not matter.
*/
#define plog_debug(...)

#endif /*< PLOG_STRIP_DEBUG */

#ifndef PLOG_STRIP_TRACE

/**
 * @brief Logs a message to show the path of the execution.
 * @param __VA_ARGS__: The message passed in a printf style.
*/
#define plog_trace(...) plog_internal(E_PLOG_SEVERITY_LEVEL_TRACE, "trace", __VA_ARGS__)

#else

/**
 * @brief Trace messages are stripped from compilation.
 * @param __VA_ARGS__: Do not matter.
*/
#define plog_trace(...)

#endif /*< PLOG_STRIP_TRACE */

#ifndef PLOG_STRIP_VERBOSE

/**
 * @brief Logs a message for verbose details.
 * @param __VA_ARGS__: The message passed in a printf style.
*/
#define plog_verbose(...) plog_internal(E_PLOG_SEVERITY_LEVEL_VERBOSE, "verbose", __VA_ARGS__)

#else

/**
 * @brief Verbose messages are stripped from compilation.
 * @param __VA_ARGS__: Do not matter.
*/
#define plog_verbose(...)

#endif /*< PLOG_STRIP_VERBOSE */

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

/**
 * @brief Enumerates the bits representing if the log severity level is enabled.
*/
typedef enum e_plog_SeverityLevel_t
{
	E_PLOG_SEVERITY_LEVEL_FATAL   = (1 << 0), /**< If bit is set fatal logs are enabled.   */
	E_PLOG_SEVERITY_LEVEL_ERROR   = (1 << 1), /**< If bit is set error logs are enabled.   */
	E_PLOG_SEVERITY_LEVEL_WARN    = (1 << 2), /**< If bit is set warn logs are enabled.    */
	E_PLOG_SEVERITY_LEVEL_INFO    = (1 << 3), /**< If bit is set info logs are enabled.    */
	E_PLOG_SEVERITY_LEVEL_DEBUG   = (1 << 4), /**< If bit is set debug logs are enabled.   */
	E_PLOG_SEVERITY_LEVEL_TRACE   = (1 << 5), /**< If bit is set trace logs are enabled.   */
	E_PLOG_SEVERITY_LEVEL_VERBOSE = (1 << 6)  /**< If bit is set verbose logs are enabled. */
} plog_SeverityLevel_t;

/******************************************************************************************************
 * FUNCTION PROTOTYPES                                                                                *
 *****************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the plog library, opening the file where the logs will be written. Logging before
 * calling this will not have any effect.
 * @param file_name: Name/path of the existing/to be created file.
 * @return void
*/
extern void plog_init(const char* file_name);

/**
 * @brief Deinitializes the plog library, closing the file where the logs were written. Logging after
 * calling this will not have any effect.
 * @param void
 * @return void
*/
extern void plog_deinit(void);

/**
 * @brief Sets a new severity level.
 * @param severity_level_mask: Bitmask for severity level according to plog_SeverityLevel_t.
 * @return void
*/
extern void plog_set_severity_level(uint8_t severity_level_mask);

/**
 * @brief Querries the severiry level.
 * @param void
 * @return The current severity level.
*/
extern uint8_t plog_get_severity_level(void);

#ifdef __cplusplus
}
#endif

#endif /*< PLOG_H_ */
