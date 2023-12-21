/******************************************************************************************************
 * Heap of Battle Copyright (C) 2024                                                                  *
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
 * @file hobServer_Version.cpp                                                                        *
 * @date:      @author:                   Reason for change:                                          *
 * 26.07.2023  Gaina Stefan               Initial version.                                            *
 * 26.08.2023  Gaina Stefan               Improved logs.                                              *
 * 21.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file implements the class defined in hobServer_Version.hpp.                          *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <cinttypes>
#include <plog.h>

#include "hobServer_Version.hpp"
#include "hobServer_Common.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hobServer
{

Version::Version(void) noexcept
	: major { VERSION_MAJOR }
	, minor { VERSION_MINOR }
	, patch { VERSION_PATCH }
{
	plog_verbose(LOG_PREFIX "Version is being constructed! (%" PRIu8 ".%" PRIu8 ".%" PRIu8 ")", major, minor, patch);
}

Version::Version(const uint8_t major, const uint8_t minor, const uint8_t patch) noexcept
	: major { major }
	, minor { minor }
	, patch { patch }
{
	plog_verbose(LOG_PREFIX "Version is being constructed with values! (%" PRIu8 ".%" PRIu8 ".%" PRIu8 ")", major, minor, patch);
}

uint8_t Version::getMajor(void) const noexcept
{
	plog_verbose(LOG_PREFIX "Major version is being got.");
	return major;
}

uint8_t Version::getMinor(void) const noexcept
{
	plog_verbose(LOG_PREFIX "Minor version is being got.");
	return minor;
}

uint8_t Version::getPatch(void) const noexcept
{
	plog_verbose(LOG_PREFIX "Patch version is being got.");
	return patch;
}

} /*< namespace hobServer */
