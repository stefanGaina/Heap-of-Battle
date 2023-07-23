/******************************************************************************************************
 * @file plog_version.h                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 29.06.2023  Gaina Stefan               Initial version.                                            *
 * @details This file defines the type definitions and function prototype of getting the version of   *
 * Plog.                                                                                              *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef PLOG_VERSION_H_
#define PLOG_VERSION_H_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <inttypes.h>

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief The compiled major version.
*/
#define PLOG_VERSION_MAJOR 1

/**
 * @brief The compiled minor version.
*/
#define PLOG_VERSION_MINOR 0

/**
 * @brief The compiled patch version.
*/
#define PLOG_VERSION_PATCH 0

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

/**
 * @brief A structure that contains information about the version of Plog in use.
*/
typedef struct s_plog_Version_t
{
	uint8_t major; /**< Increments with massive changes, additions, and enhancement.        */
	uint8_t minor; /**< Increments with backwards-compatible changes to the major revision. */
	uint8_t patch; /**< Increments with fixes to the minor revision.                        */
} plog_Version_t;

/******************************************************************************************************
 * FUNCTION PROTOTYPES                                                                                *
 *****************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the version of Plog that is linked.
 * @param void
 * @return Version information.
*/
extern plog_Version_t plog_get_version(void);

#ifdef __cplusplus
}
#endif

#endif /*< PLOG_VERSION_H_ */
