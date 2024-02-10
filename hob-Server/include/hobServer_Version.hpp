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
 * @file hobServer_Version.hpp
 * @author Gaina Stefan
 * @date 26.07.2023
 * @brief This file defines the version of the HOB_Server.
 * @todo Update version on release.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_SERVER_VERSION_HPP_
#define HOB_SERVER_VERSION_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <cstdint>

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hobServer
{

/** ***************************************************************************************************
 * @brief The compiled major version of the HOB-Server.
 *****************************************************************************************************/
static constexpr const uint8_t VERSION_MAJOR = 0U;

/** ***************************************************************************************************
 * @brief The compiled minor version of the HOB-Server.
 *****************************************************************************************************/
static constexpr const uint8_t VERSION_MINOR = 0U;

/** ***************************************************************************************************
 * @brief The compiled patch version of the HOB-Server.
 *****************************************************************************************************/
static constexpr const uint8_t VERSION_PATCH = 0U;

/** ***************************************************************************************************
 * @brief Encapsulates the version.
 *****************************************************************************************************/
class Version final
{
public:
	/** ***********************************************************************************************
	 * @brief Initializes with the linked version of HOB-Server.
	 * @param void
	 *************************************************************************************************/
	Version(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Initializes with the current version of the game.
	 * @param void
	 *************************************************************************************************/
	Version(uint8_t major, uint8_t minor, uint8_t patch) noexcept;

	/** ***********************************************************************************************
	 * @brief Querries the major version of HOB-Server.
	 * @param void
	 * @return The linked major version.
	 *************************************************************************************************/
	uint8_t getMajor(void) const noexcept;

	/** ***********************************************************************************************
	 * @brief Querries the minor version of HOB-Server.
	 * @param void
	 * @return The linked minor version.
	 *************************************************************************************************/
	uint8_t getMinor(void) const noexcept;

	/** ***********************************************************************************************
	 * @brief Querries the patch version of HOB-Server.
	 * @param void
	 * @return The linked patch version.
	 *************************************************************************************************/
	uint8_t getPatch(void) const noexcept;

private:
	/** ***********************************************************************************************
	 * @brief The linked major version of the HOB-Server.
	 *************************************************************************************************/
	uint8_t major;

	/** ***********************************************************************************************
	 * @brief The linked minor version of the HOB-Server.
	 *************************************************************************************************/
	uint8_t minor;

	/** ***********************************************************************************************
	 * @brief The linked patch version of the HOB-Server.
	 *************************************************************************************************/
	uint8_t patch;
};

} /*< namespace hobServer */

#endif /*< HOB_SERVER_VERSION_HPP_ */
