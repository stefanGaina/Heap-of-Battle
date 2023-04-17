/** @file plog.h
 *  @brief Global variables, logging macros and function prototypes of plog.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

#ifndef PLOG_H_
#define PLOG_H_

/****************************************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                                 *
 ***************************************************************************************************************************************/

#define WIN32_LEAN_AND_MEAN /*< Comment this if causes compiling errors related to WIN API. */
#include <windows.h>
#include <stdio.h>

/****************************************************************************************************************************************
 * GLOBAL VARIABLES                                                                                                                     *
 ***************************************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The file where the messages will be logged. To be held internally.
 */
extern FILE* log_file;

/**
 * @brief Buffer where time will be written. To be held internally.
 */
extern char time_buffer[];

/**
 * @brief Console's handle used for color changing operations. To be held internally.
 */
extern HANDLE console_handle;

#ifdef __cplusplus
}
#endif

/****************************************************************************************************************************************
 * MACROS                                                                                                                               *
 ***************************************************************************************************************************************/

/**
 * @brief Comment this for release mode.
 */
#define PLOG

/**
 * @brief Comment this to remove fatal logs.
 */
#define PLOG_FATAL

/**
 * @brief Comment this to remove fatal logs.
 */
#define PLOG_ERROR

/**
 * @brief Comment this to remove fatal logs.
 */
#define PLOG_WARN

/**
 * @brief Comment this to remove fatal logs.
 */
#define PLOG_INFO

/**
 * @brief Comment this to remove fatal logs.
 */
//#define PLOG_DEBUG

/**
 * @brief Comment this to remove fatal logs.
 */
//#define PLOG_TRACE

/**
 * @brief Comment this to remove fatal logs.
 */
//#define PLOG_VERBOSE

/**
 * @brief Tag that is attached to fatal logs.
 */
#define PLOG_STR_FATAL_TAG "fatal"

/**
 * @brief Tag that is attached to error logs.
 */
#define PLOG_STR_ERROR_TAG "error"

/**
 * @brief Tag that is attached to warn logs.
 */
#define PLOG_STR_WARN_TAG "warn"

/**
 * @brief Tag that is attached to info logs.
 */
#define PLOG_STR_INFO_TAG "info"

 /**
  * @brief Tag that is attached to debug logs.
  */
#define PLOG_STR_DEBUG_TAG "debug"

 /**
  * @brief Tag that is attached to trace logs.
  */
#define PLOG_STR_TRACE_TAG "trace"

/**
 * @brief Tag that is attached to verbose logs.
 */
#define PLOG_STR_VERBOSE_TAG "verbose"

#ifdef PLOG

/**
 * @brief To be held internally.
 */
#define plog_print_internal(log_stream, severity_tag, ...) \
	do                                                     \
	{                                                      \
		if (NULL != severity_tag)                          \
		{                                                  \
			plog_get_time();                               \
			fprintf(log_stream, "[%s] ", time_buffer);     \
		}                                                  \
		fprintf(log_stream, "[%s]", __FUNCTION__);         \
		if (NULL != severity_tag)                          \
		{                                                  \
			fprintf(log_stream, " [%s]", severity_tag);    \
		}                                                  \
		fprintf(log_stream, ": ");                         \
		fprintf(log_stream, __VA_ARGS__);                  \
		fprintf(log_stream, "\n");                         \
		fflush(log_stream);                                \
	}                                                      \
	while (0)

/**
 * @brief Prints a message to the console.
 */
#define plog_print(...)                          \
	do                                           \
	{                                            \
		fprintf(stdout, "[%s]: ", __FUNCTION__); \
		fprintf(stdout, __VA_ARGS__);            \
		fprintf(stdout, "\n");                   \
		fflush(stdout);                          \
	}                                            \
	while (0)

/**
 * @brief To be held internally.
 */
#define plog_internal(severity_tag, color, ...)                                 \
	do                                                                          \
	{                                                                           \
		if (NULL != log_file)                                                   \
		{                                                                       \
			plog_print_internal(log_file, severity_tag, __VA_ARGS__);           \
		}                                                                       \
		(void)SetConsoleTextAttribute(console_handle, color);                   \
		plog_print(__VA_ARGS__);                                                \
		(void)SetConsoleTextAttribute(console_handle, 7); /*< Default color. */ \
	}                                                                           \
	while (0)

#ifdef PLOG_FATAL

/**
 * @brief A fatal error means the system is unusable.
 */
#define plog_fatal(...) plog_internal(PLOG_STR_FATAL_TAG, 79, __VA_ARGS__)  /*< Red highlight. */

#else

/**
 * @brief Strips fatal errors from compiling.
 */
#define plog_fatal(...)

#endif

#ifdef PLOG_ERROR

/**
 * @brief A non-fatal error.
 */
#define plog_error(...) plog_internal(PLOG_STR_ERROR_TAG, 4, __VA_ARGS__) /*< Red. */

#else

/**
 * @brief Strips non-fatal errors from compiling.
 */
#define plog_error(...)

#endif

#ifdef PLOG_WARN

/**
 * @brief Warns about an unexpected behaviour.
 */
#define plog_warn(...) plog_internal(PLOG_STR_WARN_TAG, 14, __VA_ARGS__)  /*< Yellow. */

#else

/**
 * @brief Strips warnings from compiling.
 */
#define plog_warn(...)

#endif

#ifdef PLOG_INFO

/**
 * @brief Message logged by default.
 */
#define plog_info(...)  plog_internal(PLOG_STR_INFO_TAG, 2, __VA_ARGS__)  /*< Green. */

#else

/**
 * @brief Strips info messages from compiling.
 */
#define plog_info(...)

#endif

#ifdef PLOG_DEBUG

/**
 * @brief Message only meant for debugging.
 */
#define plog_debug(...) plog_internal(PLOG_STR_DEBUG_TAG, 3, __VA_ARGS__) /*< Cyan. */

#else

/**
 * @brief Strips debug messages from compiling.
 */
#define plog_debug(...)

#endif

#ifdef PLOG_TRACE

/**
 * @brief Message only meant for debugging with traces.
 */
#define plog_trace(...) plog_internal(PLOG_STR_TRACE_TAG, 7, __VA_ARGS__) /*< Default color. */

#else

/**
 * @brief Strips traces from compiling.
 */
#define plog_trace(...)

#endif

#ifdef PLOG_VERBOSE

/**
 * @brief Message only meant for debugging with verbose traces.
 */
#define plog_verbose(...) plog_internal(PLOG_STR_VERBOSE_TAG, 7, __VA_ARGS__) /*< Default color. */

#else

/**
 * @brief Strips verbose messages from compiling.
 */
#define plog_verbose(...)

#endif

#else

/**
 * @brief Strips fatal errors from compiling.
 */
#define plog_fatal(...)

/**
 * @brief Strips non-fatal errors from compiling.
 */
#define plog_error(...)

/**
 * @brief Strips warnings from compiling.
 */
#define plog_warn(...)

/**
 * @brief Strips info messages from compiling.
 */
#define plog_info(...)

/**
 * @brief Strips debug messages from compiling.
 */
#define plog_debug(...)

/**
 * @brief Strips traces from compiling.
 */
#define plog_trace(...)

/**
 * @brief Strips verbose messages from compiling.
 */
#define plog_verbose(...)

#endif /*< PLOG */

/****************************************************************************************************************************************
 * FUNCTION PROTOTYPES                                                                                                                  *
 ***************************************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes logging system. Must be called first for file logging or it will log in console.
 * @param[in] log_file_name - name of an existing file or the name of the file that will be created. Can be NULL.
 * @return void
 */
extern void plog_init(const char* log_file_name);

/**
 * @brief Deinitializes logging system. Calling this is optional.
 * @param void
 * @return void
 */
extern void plog_deinit(void);

/**
 * @brief Gets current time formated in a string.
 * @param void
 * @return void
*/
extern void plog_get_time(void);

#ifdef __cplusplus
}
#endif

#endif /*< PLOG_H_ */
