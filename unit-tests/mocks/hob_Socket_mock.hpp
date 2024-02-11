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

#ifndef HOB_SOCKET_MOCK_HPP_
#define HOB_SOCKET_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>

#include "hob_Socket.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

class SocketDummy
{
public:
	virtual ~SocketDummy(void) = default;

	virtual void create(std::string ipAddress) = 0;
	virtual void close(void) = 0;
	virtual void receiveUpdate(hobServer::Message& updateMessage) = 0;
	virtual void sendUpdate(const hobServer::Message& updateMessage) = 0;
};

class SocketMock : public SocketDummy
{
public:
	SocketMock(void)
	{
		socketMock = this;
	}

	virtual ~SocketMock(void)
	{
		socketMock = nullptr;
	}

	MOCK_METHOD1(create, void(std::string));
	MOCK_METHOD0(close, void(void));
	MOCK_METHOD1(receiveUpdate, void(hobServer::Message&));
	MOCK_METHOD1(sendUpdate, void(const hobServer::Message&));

public:
	static SocketMock* socketMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

SocketMock* SocketMock::socketMock = nullptr;

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

Socket::Socket(void) noexcept
{
}

Socket::~Socket(void) noexcept
{
}

void Socket::create(const std::string ipAddress) noexcept(false)
{
	ASSERT_NE(nullptr, SocketMock::socketMock) << "create(): nullptr == SocketMock::socketMock";
	SocketMock::socketMock->create(ipAddress);
}

void Socket::close(void) noexcept
{
	ASSERT_NE(nullptr, SocketMock::socketMock) << "close(): nullptr == SocketMock::socketMock";
	SocketMock::socketMock->close();
}

void Socket::sendUpdate(const hobServer::Message& updateMessage) const noexcept
{
	ASSERT_NE(nullptr, SocketMock::socketMock) << "sendUpdate(): nullptr == SocketMock::socketMock";
	SocketMock::socketMock->sendUpdate(updateMessage);
}

} /*< namespace hob */

#endif /*< HOB_SOCKET_MOCK_HPP_ */
