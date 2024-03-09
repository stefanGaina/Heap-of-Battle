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
 * @file hobServer_Socket.cpp
 * @author Gaina Stefan
 * @date 26.07.2023
 * @brief This file implements the class defined in hobServer_Socket.hpp.
 * @todo N/A.
 * @bug -fanalyzer has been removed from compilation due to an error. The functionality seems to work
 * but something might still be wrong.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <exception>
#include <sys/socket.h>
#include <netinet/in.h>
#include <plog.h>

#include "hobServer_Socket.hpp"
#include "hobServer_Common.hpp"
#include "hob_Version.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hobServer
{

Socket::Socket(void) noexcept
	: serverSocket{ SOCKET_INVALID }
	, clientSockets{ SOCKET_INVALID, SOCKET_INVALID }
{
	plog_debug(LOG_PREFIX "Socket is being constructed.");
}

Socket::~Socket(void) noexcept
{
	plog_debug(LOG_PREFIX "Socket is being destructed.");
	close();
}

void Socket::create(const uint16_t port, Callback callback) noexcept(false)
{
	sockaddr_in server = {};
	int32_t		option = 1;

	plog_debug(LOG_PREFIX "Server socket is being created.");
	plog_assert(nullptr != this);

	if (SOCKET_INVALID != serverSocket || SOCKET_INVALID != clientSockets[0] || SOCKET_INVALID != clientSockets[1])
	{
		plog_error(LOG_PREFIX "Socket is already created!");
		throw std::exception();
	}

	serverSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_INVALID == serverSocket)
	{
		plog_error(LOG_PREFIX "Failed to create socket! (error message: %s)", strerror(errno));
		throw std::exception();
	}

	if (0 != setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)))
	{
		plog_warn(LOG_PREFIX "Failed to set socket option! (error message: %s)", strerror(errno));
	}

	server.sin_family	   = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port		   = htons(port);

	if (0 != bind(serverSocket, reinterpret_cast<sockaddr*>(&server), sizeof(server)))
	{
		plog_error(LOG_PREFIX "Failed to bind socket! (error message: %s)", strerror(errno));
		close();

		throw std::exception();
	}

	callback();
	try
	{
		waitConnection();
	}
	catch (const std::exception& exception)
	{
		plog_error(LOG_PREFIX "Server failed to establish connections!");
		throw exception;
	}
}

void Socket::close(void) noexcept
{
	plog_trace(LOG_PREFIX "Server socket is being closed.");
	plog_assert(nullptr != this);

	if (SOCKET_INVALID != serverSocket)
	{
		if (0 != shutdown(serverSocket, SHUT_RDWR))
		{
			plog_error(LOG_PREFIX "Failed to close server socket! (error message: %s)", strerror(errno));
		}
		serverSocket = SOCKET_INVALID;
	}
	else
	{
		plog_warn(LOG_PREFIX "Server socket is already closed!");
	}

	closeClient(ClientType::PLAYER_1);
	closeClient(ClientType::PLAYER_2);
}

void Socket::receiveUpdate(Message& updateMessage, const ClientType clientType) const noexcept
{
	ssize_t receivedBytes = 0L;
	size_t	index		  = 0UL;

	plog_verbose(LOG_PREFIX "Querrying for updates. (player: %" PRId32 ")", static_cast<int32_t>(clientType));
	plog_assert(nullptr != this);

	switch (clientType)
	{
		case ClientType::PLAYER_1:
		{
			index = 0UL;
			break;
		}
		case ClientType::PLAYER_2:
		{
			index = 1UL;
			break;
		}
		default:
		{
			plog_error(LOG_PREFIX "Invalid client type! (player: %" PRId32 ")", static_cast<int32_t>(clientType));
			break;
		}
	}

	if (SOCKET_INVALID == clientSockets[index])
	{
		plog_fatal(LOG_PREFIX "Connection is not established!");
		return;
	}
	plog_debug(LOG_PREFIX "Waiting for updates to arrive. (player: %" PRId32 ")", static_cast<int32_t>(clientType));

	receivedBytes = recv(clientSockets[index], reinterpret_cast<char*>(&updateMessage), sizeof(Message), 0);
	if (0L >= receivedBytes)
	{
		plog_fatal(LOG_PREFIX "Invalid number of bytes received! (bytes: %" PRId64 ") (error message: %s)", receivedBytes, strerror(errno));
		updateMessage.type = MessageType::END_COMMUNICATION;

		return;
	}

	plog_debug(LOG_PREFIX "Received an updated! (type: %" PRId32 ") (bytes: %" PRId64 ")", static_cast<int32_t>(updateMessage.type), receivedBytes);
}

void Socket::sendUpdate(const Message& updateMessage, const ClientType clientType) const noexcept
{
	size_t index = 0UL;

	plog_trace(LOG_PREFIX "Update is being sent. (type: %" PRId32 ") (player: %" PRId32 ")", static_cast<int32_t>(updateMessage.type),
			   static_cast<int32_t>(clientType));
	plog_assert(nullptr != this);

	switch (clientType)
	{
		case ClientType::PLAYER_1:
		{
			index = 0UL;
			break;
		}
		case ClientType::PLAYER_2:
		{
			index = 1UL;
			break;
		}
		default:
		{
			plog_error(LOG_PREFIX "Invalid client type! (player: %" PRId32 ")", static_cast<int32_t>(clientType));
			break;
		}
	}

	if (SOCKET_INVALID == clientSockets[index])
	{
		plog_fatal(LOG_PREFIX "Connection is not established!");
		return;
	}

	if (-1L == send(clientSockets[index], reinterpret_cast<const char*>(&updateMessage), sizeof(Message), 0))
	{
		plog_error(LOG_PREFIX "Message failed to be sent! (type: %" PRId32 ") (player: %" PRId32 ") (error message: %s)", static_cast<int32_t>(updateMessage.type),
				   static_cast<int32_t>(clientType), strerror(errno));
	}
}

void Socket::waitConnection(void) noexcept(false)
{
	size_t			 index			= 0UL;
	const ClientType clientTypes[2] = { ClientType::PLAYER_1, ClientType::PLAYER_2 };
	sockaddr_in		 client			= {};
	socklen_t		 addressLength	= sizeof(client);
	Message			 message		= { .type = MessageType::END_COMMUNICATION, .payload = {} };

	plog_info(LOG_PREFIX "Waiting for incoming connections!");
	plog_assert(nullptr != this);

	if (0 != listen(serverSocket, 2))
	{
		plog_fatal(LOG_PREFIX "Server failed to open for connections! (error message: %s)", strerror(errno));
		return;
	}

	while (true)
	{
		clientSockets[index] = accept(serverSocket, reinterpret_cast<sockaddr*>(&client), &addressLength);
		if (SOCKET_INVALID == serverSocket)
		{
			plog_warn(LOG_PREFIX "Server socket has been closed!");
			if (1UL == index)
			{
				closeClient(clientTypes[index]);
			}

			throw std::exception();
		}

		if (SOCKET_INVALID == clientSockets[index])
		{
			plog_error(LOG_PREFIX "Connection failed to be accepted! (error message: %s)", strerror(errno));
			continue;
		}
		plog_info(LOG_PREFIX "Connection accepted successfully!");

		receiveUpdate(message, clientTypes[index]);
		if (MessageType::VERSION != message.type)
		{
			plog_error(LOG_PREFIX "First message received is not checking to match versions! (type: %" PRId32 ")", static_cast<int32_t>(message.type));
			goto ABORT_CONNECTION;
		}

		plog_info(LOG_PREFIX "Version message received! (version: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ")", message.payload.version.getMajor(),
				  message.payload.version.getMinor(), message.payload.version.getPatch());
		if (hob::VERSION_MAJOR != message.payload.version.getMajor() || hob::VERSION_MINOR != message.payload.version.getMinor() ||
			hob::VERSION_PATCH != message.payload.version.getPatch())
		{
			plog_error(LOG_PREFIX "Versions are not matching!");
			goto ABORT_CONNECTION;
		}

		if (0UL == index)
		{
			++index;
			continue;
		}

		message.type = MessageType::PING;
		sendUpdate(message, ClientType::PLAYER_1);
		sendUpdate(message, ClientType::PLAYER_2);

		break;

ABORT_CONNECTION:
		message.type = MessageType::END_COMMUNICATION;
		sendUpdate(message, clientTypes[index]);
		closeClient(clientTypes[index]);
	}
}

void Socket::closeClient(const ClientType clientType) noexcept
{
	size_t index = 0UL;

	plog_debug(LOG_PREFIX "Client socket is being closed. (client type: %" PRId32 ")", static_cast<int32_t>(clientType));
	plog_assert(nullptr != this);

	switch (clientType)
	{
		case ClientType::PLAYER_1:
		{
			index = 0UL;
			break;
		}
		case ClientType::PLAYER_2:
		{
			index = 1UL;
			break;
		}
		default:
		{
			plog_error(LOG_PREFIX "Invalid client type! (%" PRId32 ")", static_cast<int32_t>(clientType));
			break;
		}
	}

	if (SOCKET_INVALID == clientSockets[index])
	{
		plog_warn(LOG_PREFIX "Client socket %" PRIu64 " is already closed!", index);
		return;
	}

	if (0 != shutdown(clientSockets[index], SHUT_RDWR))
	{
		plog_error(LOG_PREFIX "Client socket %" PRIu64 " socket failed to be closed! (error message: %s)", index, strerror(errno));
	}
	clientSockets[index] = SOCKET_INVALID;
}

} /*< namespace hobServer */
