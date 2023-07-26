/******************************************************************************************************
 * @file hobServer_Version.hpp                                                                        *
 * @date:      @author:                   Reason for change:                                          *
 * 26.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file defines the version of the HOB-Server.                                          *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
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

/**
 * @brief The compiled major version of the HOB-Server.
*/
static constexpr const uint8_t VERSION_MAJOR = 0U;

/**
 * @brief The compiled minor version of the HOB-Server.
*/
static constexpr const uint8_t VERSION_MINOR = 0U;

/**
 * @brief The compiled patch version of the HOB-Server.
*/
static constexpr const uint8_t VERSION_PATCH = 0U;

/**
 * @brief Encapsulates the version.
*/
class Version final
{
public:
	/**
	 * @brief Initializes with the linked version of HOB-Server.
	 * @param void
	*/
	Version(void) noexcept;

	/**
	 * @brief Querries the major version of HOB-Server.
	 * @param void
	 * @return The linked major version.
	*/
	uint8_t getMajor(void) const noexcept;

	/**
	 * @brief Querries the minor version of HOB-Server.
	 * @param void
	 * @return The linked minor version.
	*/
	uint8_t getMinor(void) const noexcept;

	/**
	 * @brief Querries the patch version of HOB-Server.
	 * @param void
	 * @return The linked patch version.
	*/
	uint8_t getPatch(void) const noexcept;

private:
	/**
	 * @brief The linked major version of the HOB-Server.
	*/
	uint8_t m_major;

	/**
	 * @brief The linked minor version of the HOB-Server.
	*/
	uint8_t m_minor;

	/**
	 * @brief The linked patch version of the HOB-Server.
	*/
	uint8_t m_patch;
};

} /*< namespace hobServer */

#endif /*< HOB_SERVER_VERSION_HPP_ */
