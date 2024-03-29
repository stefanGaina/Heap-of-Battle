/******************************************************************************************************
 * Heap of Battle Copyright (C) 2024
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
 * @file hobServerInstance_Version.hpp
 * @author Gaina Stefan
 * @date 26.07.2023
 * @brief This file defines the version of the Heap-of-Battle server instance.
 * @todo Update version on release.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_SERVER_INSTANCE_VERSION_HPP_
#define HOB_SERVER_INSTANCE_VERSION_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <cinttypes>

/******************************************************************************************************
 * CONSTANTS
 *****************************************************************************************************/

namespace hobServerInstance
{

/** ***************************************************************************************************
 * @brief The compiled major version of the server instance.
 *****************************************************************************************************/
inline constexpr uint8_t VERSION_MAJOR = 0U;

/** ***************************************************************************************************
 * @brief The compiled minor version of the server instance.
 *****************************************************************************************************/
inline constexpr uint8_t VERSION_MINOR = 0U;

/** ***************************************************************************************************
 * @brief The compiled patch version of the server instance.
 *****************************************************************************************************/
inline constexpr uint8_t VERSION_PATCH = 0U;

} /*< namespace hobServerInstance */

#endif /*< HOB_SERVER_INSTANCE_VERSION_HPP_ */
