/******************************************************************************************************
 * @file hobServer_Version.cpp                                                                        *
 * @date:      @author:                   Reason for change:                                          *
 * 26.07.2023  Gaina Stefan               Initial version.                                            *
 * 26.08.2023  Gaina Stefan               Improved logs.                                              *
 * @details This file implements the class defined in hobServer_Version.hpp.                          *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hobServer_Version.hpp"
#include "hobServer_Common.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hobServer
{

Version::Version(void) noexcept
	: m_major { VERSION_MAJOR }
	, m_minor { VERSION_MINOR }
	, m_patch { VERSION_PATCH }
{
	plog_verbose(LOG_PREFIX "Version is being constructed! (version: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ") (size: %" PRIu64 ") "
		"(1: %" PRIu64 ") (2: %" PRIu64 ") (3: %" PRIu64 ")", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, sizeof(*this),
		sizeof(m_major), sizeof(m_minor), sizeof(m_patch));
}

uint8_t Version::getMajor(void) const noexcept
{
	plog_verbose(LOG_PREFIX "Major version is being got.");
	return m_major;
}

uint8_t Version::getMinor(void) const noexcept
{
	plog_verbose(LOG_PREFIX "Minor version is being got.");
	return m_minor;
}

uint8_t Version::getPatch(void) const noexcept
{
	plog_verbose(LOG_PREFIX "Patch version is being got.");
	return m_patch;
}

} /*< namespace hobServer */
