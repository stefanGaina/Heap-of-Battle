/******************************************************************************************************
 * Plog Copyright (C) 2024
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the
 * authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
 *    original software. If you use this software in a product, an acknowledgment in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being
 *    the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @file plog_version.h
 * @author Gaina Stefan
 * @date 29.06.2023
 * @brief This file defines the type definitions and function prototype of getting the version of
 * Plog.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef PLOG_VERSION_H_
#define PLOG_VERSION_H_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#ifndef PLOG_STRIP_ALL

#include <glib.h>

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief The compiled major version.
*/
#define PLOG_VERSION_MAJOR (guint8)2U

/** ***************************************************************************************************
 * @brief The compiled minor version.
 *****************************************************************************************************/
#define PLOG_VERSION_MINOR (guint8)1U

/** ***************************************************************************************************
 * @brief The compiled patch version.
 *****************************************************************************************************/
#define PLOG_VERSION_PATCH (guint8)0U

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief A structure that contains information about the version of Plog in use.
 *****************************************************************************************************/
typedef struct s_plog_Version_t
{
	guint8 major; /**< Increments with massive changes, additions, and enhancement.		   */
	guint8 minor; /**< Increments with backwards-compatible changes to the major revision. */
	guint8 patch; /**< Increments with fixes to the minor revision.						   */
} plog_Version_t;

/******************************************************************************************************
 * FUNCTION PROTOTYPES
 *****************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/** ***************************************************************************************************
 * @brief Get the version of Plog that is linked.
 * @param void
 * @return Version information.
 *****************************************************************************************************/
extern plog_Version_t plog_get_version(void);

#ifdef __cplusplus
}
#endif

#endif /*< PLOG_STRIP_ALL */

#endif /*< PLOG_VERSION_H_ */
