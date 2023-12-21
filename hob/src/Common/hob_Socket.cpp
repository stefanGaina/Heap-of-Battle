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
 * @file hob_Socket.cpp                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 25.07.2023  Gaina Stefan               Initial version.                                            *
 * 27.07.2023  Gaina Stefan               Removed WSA.                                                *
 * 26.08.2023  Gaina Stefan               Improved logs.                                              *
 * 27.08.2023  Gaina Stefan               Simplified recv() error case.                               *
 * 29.08.2023  Gaina Stefan               Solved todo.                                                *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file implements the class defined in hob_Socket.hpp.                                 *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <exception>
#include <functional>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <plog.h>

#include "hob_Socket.hpp"
#include "hob_Version.hpp"

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

/**
 * @brief The value indicating a socket error/ the socket is closed or in an invalid state.
*/
static constexpr const int32_t SOCKET_INVALID = -1;

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Socket::Socket(void) noexcept
	: socket{ SOCKET_INVALID }
{
	plog_trace("Socket is being constructed.");
}

Socket::~Socket(void) noexcept
{
	plog_trace("Socket is being destructed.");
	close();
}

void Socket::create(const std::string ipAddress) noexcept(false)
{
	sockaddr_in        server         = {};
	hobServer::Message versionMessage = {};

	plog_debug("Client socket is being created. (IP address: %s)", ipAddress.c_str());
	if (SOCKET_INVALID != socket)
	{
		plog_error("Socket is already created!");
		return;
	}

	socket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_INVALID == socket)
	{
		plog_error("Client socket failed to be created! (error message: %s)", strerror(errno));
		throw std::exception();
	}

	server.sin_family      = AF_INET;
	server.sin_addr.s_addr = inet_addr(ipAddress.c_str());
	server.sin_port        = htons(8787U);

	if (0 != connect(socket, (sockaddr*)&server, sizeof(server)))
	{
		plog_error("Failed to connect to server! (error message: %s)", strerror(errno));
		close();

		throw std::exception();
	}

	versionMessage.type            = hobServer::MessageType::VERSION;
	versionMessage.payload.version = hobServer::Version{ VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH };
	sendUpdate(versionMessage);
}

void Socket::close(void) noexcept
{
	plog_trace("Client socket is being closed.");
	if (SOCKET_INVALID == socket)
	{
		plog_warn("Client socket is already closed.");
		return;
	}

	if (0 != shutdown(socket, SHUT_RDWR))
	{
		plog_error("Client socket failed to be closed! (error message: %s)", strerror(errno));
	}
	socket = SOCKET_INVALID;
}

void Socket::sendUpdate(const hobServer::Message& updateMessage) const noexcept
{
	plog_trace("Update is being sent. (type: %" PRId32 ")", static_cast<int32_t>(updateMessage.type));
	if (SOCKET_INVALID == socket)
	{
		plog_fatal("Connection is not established!");
		return;
	}

	if (-1 == send(socket, reinterpret_cast<const char*>(&updateMessage), sizeof(hobServer::Message), 0))
	{
		plog_error("Message failed to be sent! (type: %" PRId32 ")", static_cast<int32_t>(updateMessage.type));
	}
}

void Socket::receiveUpdate(hobServer::Message& updateMessage) const noexcept
{
	int32_t receivedBytes = 0;

	plog_verbose("Querrying for updates.");
	if (SOCKET_INVALID == socket)
	{
		plog_fatal("Connection is not established!");
		return;
	}
	plog_debug("Waiting for updates to arrive.");

	receivedBytes = recv(socket, reinterpret_cast<char*>(&updateMessage), sizeof(hobServer::Message), 0);
	if (0 >= receivedBytes)
	{
		plog_fatal("Invalid number of bytes received! (bytes: %" PRId32 ")", receivedBytes);
		updateMessage.type = hobServer::MessageType::END_COMMUNICATION;
	}
	else
	{
		plog_debug("Received an updated! (bytes: %" PRId32 ")", receivedBytes);
	}
}

} /*< namespace hob */
