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

#ifndef HOB_SERVER_VERSION_MOCK_HPP_
#define HOB_SERVER_VERSION_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>

#include "hobServer_Version.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

class ServerVersionDummy
{
public:
	virtual ~ServerVersionDummy(void) = default;

	virtual uint8_t getMajor(void) = 0;
	virtual uint8_t getMinor(void) = 0;
	virtual uint8_t getPatch(void) = 0;
};

class ServerVersionMock : public ServerVersionDummy
{
public:
	ServerVersionMock(void)
	{
		serverVersionMock = this;
	}

	virtual ~ServerVersionMock(void)
	{
		serverVersionMock = nullptr;
	}

	MOCK_METHOD0(getMajor, uint8_t(void));
	MOCK_METHOD0(getMinor, uint8_t(void));
	MOCK_METHOD0(getPatch, uint8_t(void));

public:
	static ServerVersionMock* serverVersionMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

ServerVersionMock* ServerVersionMock::serverVersionMock = nullptr;

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hobServer
{

Version::Version(void) noexcept
{
}

Version::Version(const uint8_t major, const uint8_t minor, const uint8_t patch) noexcept
{
}

uint8_t Version::getMajor(void) const noexcept
{
	if (nullptr == ServerVersionMock::serverVersionMock)
	{
		ADD_FAILURE() << "getMajor(): nullptr == ServerVersionMock::serverVersionMock";
		return (uint8_t)0U;
	}
	return ServerVersionMock::serverVersionMock->getMajor();
}

uint8_t Version::getMinor(void) const noexcept
{
	if (nullptr == ServerVersionMock::serverVersionMock)
	{
		ADD_FAILURE() << "getMinor(): nullptr == ServerVersionMock::serverVersionMock";
		return (uint8_t)0U;
	}
	return ServerVersionMock::serverVersionMock->getMinor();
}

uint8_t Version::getPatch(void) const noexcept
{
	if (nullptr == ServerVersionMock::serverVersionMock)
	{
		ADD_FAILURE() << "getPatch(): nullptr == ServerVersionMock::serverVersionMock";
		return (uint8_t)0U;
	}
	return ServerVersionMock::serverVersionMock->getPatch();
}

} /*< namespace hobServer */

#endif /*< HOB_SERVER_VERSION_MOCK_HPP_ */
