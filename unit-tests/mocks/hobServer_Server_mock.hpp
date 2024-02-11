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

#ifndef HOB_SERVER_SERVER_MOCK_HPP_
#define HOB_SERVER_SERVER_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>

#include "hobServer_Server.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

class ServerServerDummy
{
public:
	virtual ~ServerServerDummy(void) = default;

	virtual void runAsync(uint16_t port, uint16_t timeout) = 0;
	virtual void stop(void) = 0;
};

class ServerServerMock : public ServerServerDummy
{
public:
	ServerServerMock(void)
	{
		serverServerMock = this;
	}

	virtual ~ServerServerMock(void)
	{
		serverServerMock = nullptr;
	}

	MOCK_METHOD2(runAsync, void(uint16_t, uint16_t));
	MOCK_METHOD0(stop, void(void));

public:
	static ServerServerMock* serverServerMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

ServerServerMock* ServerServerMock::serverServerMock = nullptr;

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hobServer
{

Server::Server(void) noexcept
{
}

Server::~Server(void) noexcept
{
}

void Server::runAsync(const uint16_t port, const uint16_t timeout) noexcept(false)
{
	ASSERT_NE(nullptr, ServerServerMock::serverServerMock) << "runAsync(): nullptr == ServerServerMock::serverServerMock";
	ServerServerMock::serverServerMock->runAsync(port, timeout);
}

void Server::stop(void) noexcept
{
	ASSERT_NE(nullptr, ServerServerMock::serverServerMock) << "stop(): nullptr == ServerServerMock::serverServerMock";
	ServerServerMock::serverServerMock->stop();
}

void Server::onTimeUpdate(const uint16_t timeLeft) noexcept
{
}

void Server::onTimesUp(uint16_t& timeLeft) const noexcept
{
}

} /*< namespace hobServer */

#endif /*< HOB_SERVER_SERVER_MOCK_HPP_ */
