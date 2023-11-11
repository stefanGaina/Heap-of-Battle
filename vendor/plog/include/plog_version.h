/******************************************************************************************************
 * @file plog_version.h                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 29.06.2023  Gaina Stefan               Initial version.                                            *
 * 08.08.2023  Gaina Stefan               Added cast to macro.                                        *
 * 10.09.2023  Gaina Stefan               Updated version to 1.0.1.                                   *
 * 16.09.2023  Gaina Stefan               Updated version to 1.0.2.                                   *
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

#include <stdint.h>

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief The compiled major version.
*/
#define PLOG_VERSION_MAJOR (uint8_t)1U

/**
 * @brief The compiled minor version.
*/
#define PLOG_VERSION_MINOR (uint8_t)0U

/**
 * @brief The compiled patch version.
*/
#define PLOG_VERSION_PATCH (uint8_t)2U

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
