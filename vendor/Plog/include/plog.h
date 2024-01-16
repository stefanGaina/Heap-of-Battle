/******************************************************************************************************
 * Plog Copyright (C) 2024                                                                            *
 *                                                                                                    *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the   *
 * authors be held liable for any damages arising from the use of this software.                      *
 *                                                                                                    *
 * Permission is granted to anyone to use this software for any purpose, including commercial         *
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:   *
 *                                                                                                    *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the   *
 *    original software. If you use this software in a product, an acknowledgment in the product      *
 *    documentation would be appreciated but is not required.                                         *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being *
 *    the original software.                                                                          *
 * 3. This notice may not be removed or altered from any source distribution.                         *
******************************************************************************************************/

/******************************************************************************************************
 * @file plog.h                                                                                       *
 * @date:      @author:                   Reason for change:                                          *
 * 22.06.2023  Gaina Stefan               Initial version.                                            *
 * 22.06.2023  Gaina Stefan               Added plog_get_version.                                     *
 * 22.06.2023  Gaina Stefan               Fixed the stripping of logging from compilation.            *
 * 29.06.2023  Gaina Stefan               Moved version to plog_version.h.                            *
 * 10.09.2023  Gaina Stefan               Added terminal mode.                                        *
 * 15.12.2023  Gaina Stefan               Added buffer size.                                          *
 * 20.12.2023  Gaina Stefan               Updated copyright.                                          *
 * 13.01.2024  Gaina Stefan               Updated doxygen.                                            *
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
 * @param format: String that contains the text to be written.
 * @param VA_ARGS: The parameters passed in a printf style (optional).
 * @return void
*/
#define plog_fatal(format, ...) plog_internal(E_PLOG_SEVERITY_LEVEL_FATAL, "fatal", __FUNCTION__, format, ##__VA_ARGS__)

#else

/**
 * @brief Fatal error messages are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @return void
*/
#define plog_fatal(format, ...)

#endif /*< PLOG_STRIP_FATAL */

#ifndef PLOG_STRIP_ERROR

/**
 * @brief Logs a non-fatal error message (system is still usable).
 * @param format: String that contains the text to be written.
 * @param VA_ARGS: The parameters passed in a printf style (optional).
 * @return void
*/
#define plog_error(format, ...) plog_internal(E_PLOG_SEVERITY_LEVEL_ERROR, "error", __FUNCTION__, format, ##__VA_ARGS__)

#else

/**
 * @brief Error messages are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @return void
*/
#define plog_error(format, ...)

#endif /*< PLOG_STRIP_ERROR */

#ifndef PLOG_STRIP_WARN

/**
 * @brief Logs a warning message (something unusual that might require attention).
 * @param format: String that contains the text to be written.
 * @param VA_ARGS: The parameters passed in a printf style (optional).
 * @return void
*/
#define plog_warn(format, ...) plog_internal(E_PLOG_SEVERITY_LEVEL_WARN, "warn", __FUNCTION__, format, ##__VA_ARGS__)

#else

/**
 * @brief Warning messages are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @return void
*/
#define plog_warn(format, ...)

#endif /*< PLOG_STRIP_WARN */

#ifndef PLOG_STRIP_INFO

/**
 * @brief Logs an information message.
 * @param format: String that contains the text to be written.
 * @param VA_ARGS: The parameters passed in a printf style (optional).
 * @return void
*/
#define plog_info(format, ...) plog_internal(E_PLOG_SEVERITY_LEVEL_INFO, "info", __FUNCTION__, format, ##__VA_ARGS__)

#else

/**
 * @brief Information messages are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @return void
*/
#define plog_info(format, ...)

#endif /*< PLOG_STRIP_INFO */

#ifndef PLOG_STRIP_DEBUG

/**
 * @brief Logs a message for debugging purposes.
 * @param format: String that contains the text to be written.
 * @param VA_ARGS: The parameters passed in a printf style (optional).
 * @return void
*/
#define plog_debug(format, ...) plog_internal(E_PLOG_SEVERITY_LEVEL_DEBUG, "debug", __FUNCTION__, format, ##__VA_ARGS__)

#else

/**
 * @brief Debug messages are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @return void
*/
#define plog_debug(format, ...)

#endif /*< PLOG_STRIP_DEBUG */

#ifndef PLOG_STRIP_TRACE

/**
 * @brief Logs a message to show the path of the execution.
 * @param format: String that contains the text to be written.
 * @param VA_ARGS: The parameters passed in a printf style (optional).
 * @return void
*/
#define plog_trace(format, ...) plog_internal(E_PLOG_SEVERITY_LEVEL_TRACE, "trace", __FUNCTION__, format, ##__VA_ARGS__)

#else

/**
 * @brief Trace messages are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @return void
*/
#define plog_trace(format, ...)

#endif /*< PLOG_STRIP_TRACE */

#ifndef PLOG_STRIP_VERBOSE

/**
 * @brief Logs a message for verbose details.
 * @param format: String that contains the text to be written.
 * @param VA_ARGS: The parameters passed in a printf style (optional).
 * @return void
*/
#define plog_verbose(format, ...) plog_internal(E_PLOG_SEVERITY_LEVEL_VERBOSE, "verbose", __FUNCTION__, format, ##__VA_ARGS__)

#else

/**
 * @brief Verbose messages are stripped from compilation.
 * @param format: Does not matter.
 * @param VA_ARGS: Does not matter.
 * @return void
*/
#define plog_verbose(format, ...)

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
}
plog_SeverityLevel_t;

/******************************************************************************************************
 * FUNCTION PROTOTYPES                                                                                *
 *****************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the plog library, opening the file where the logs will be written. Logging before
 * calling this will not have any effect.
 * @param file_name: Path to an existing file (that has write rights). If it does not exist one will be created.
 * @return TRUE - initialization has been successful.
 * @return FALSE - an error occured.
*/
extern gboolean plog_init(const gchar* file_name);

/**
 * @brief Deinitializes the plog library, closing the file where the logs were written. Logging after
 * calling this will not have any effect.
 * @param void
 * @return void
*/
extern void plog_deinit(void);

/**
 * @brief Sets a new severity level, this will filter logs at runtime.
 * @param severity_level_mask: Bitmask for severity level according to plog_SeverityLevel_t.
 * @return void
 * @see plog_SeverityLevel_t
*/
extern void plog_set_severity_level(guint8 severity_level_mask);

/**
 * @brief Querries the severiry level.
 * @param void
 * @return The current severity level.
*/
extern guint8 plog_get_severity_level(void);

/**
 * @brief Sets a new file size.
 * @param file_size: Maximum size of a log file (in bytes) before creating another (or overwriting
 * in case file count is 0).
 * @return void
*/
extern void plog_set_file_size(gsize file_size);

/**
 * @brief Querries the file size.
 * @param void
 * @return The current file size.
*/
extern gsize plog_get_file_size(void);

/**
 * @brief Sets a new file count.
 * @param file_count: The count of the additional log files created (does not have any effect if
 * file size is 0).
 * @return void
*/
extern void plog_set_file_count(guint8 file_count);

/**
 * @brief Querries the file count.
 * @param void
 * @return The current file count.
*/
extern guint8 plog_get_file_count(void);

/**
 * @brief Sets a new terminal mode.
 * @param terminal_mode: TRUE - the logs will also be printed the terminal, FALSE - the logs will
 * only be printed in the file.
 * @return void
*/
extern void plog_set_terminal_mode(gboolean terminal_mode);

/**
 * @brief Querries the terminal mode.
 * @param void
 * @return TRUE - the logs are also be printed the terminal.
 * @return FALSE - the logs are only printed in the file.
*/
extern gboolean plog_get_terminal_mode(void);

/**
 * @brief Sets a new buffer size.
 * @param buffer_size: Size of the buffer storing the log that will be printed asynchronically (0 means
 * asynchronically logging is disabled).
 * @return TRUE - the buffer size has been successfully set.
 * @return FALSE - an error occured.
*/
extern gboolean plog_set_buffer_size(gsize buffer_size);

/**
 * @brief Querries the buffer size.
 * @param void
 * @return The current buffer size.
*/
extern gsize plog_get_buffer_size(void);

#ifdef __cplusplus
}
#endif

#endif /*< PLOG_H_ */
