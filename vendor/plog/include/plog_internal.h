/******************************************************************************************************
 * @file plog_internal.h                                                                              *
 * @date:      @author:                   Reason for change:                                          *
 * 22.06.2023  Gaina Stefan               Initial version.                                            *
 * 29.06.2023  Gaina Stefan               Added function macro.                                       *
 * @details This file defines macros and interfaces of Plog that are meant to be internal.            *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief This macro is not meant to be invoked outside plog macros.
 * @param[uint8_t] severity_bit: The message will not be logged if the severity bit is not set in
 * severity level mask.
 * @param[const char*] severity_tag: The tag that will be attached between time and the actual message
 * (indicating the severity of the message).
 * @param __VA_ARGS__: The message passed in a printf style.
*/
#define plog_internal(severity_bit, severity_tag, ...)                                                                        \
	do                                                                                                                        \
	{                                                                                                                         \
		if (severity_bit == (severity_bit & plog_get_severity_level()) && NULL != plog_internal_get_file())                   \
		{                                                                                                                     \
			(void)fprintf(plog_internal_get_file(), "[%s] [%s] [%s] ", plog_internal_get_time(), __FUNCTION__, severity_tag); \
			(void)fprintf(plog_internal_get_file(), __VA_ARGS__);                                                             \
			(void)fprintf(plog_internal_get_file(), "\n");                                                                    \
		}                                                                                                                     \
	}                                                                                                                         \
	while (false)

/******************************************************************************************************
 * FUNCTION PROTOTYPES                                                                                *
 *****************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief This function is not meant to be called outside plog macros.
 * @param void
 * @return The file where the logs are written.
*/
extern FILE* plog_internal_get_file(void);

/**
 * @brief This function is not meant to be called outside plog macros.
 * @param void
 * @return The current severity level.
*/
extern uint8_t plog_internal_get_severity_level(void);

/**
 * @brief This function is not meant to be called outside plog macros.
 * @param void
 * @return A string representing the current time in a "mmm dd hh:mm:ss yyyy" format.
*/
extern const char* plog_internal_get_time(void);

#ifdef __cplusplus
}
#endif
