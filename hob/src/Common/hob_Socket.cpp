/******************************************************************************************************
 * @file hob_Socket.cpp                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 25.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file implements the class defined in hob_Socket.hpp.                                 *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <exception>
#include <WS2tcpip.h>
#include <plog.h>

#include "hob_Socket.hpp"
#include "hob_Version.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief 
*/
static constexpr uint16_t PORT = 8887U;

Socket& Socket::getInstance(void) noexcept
{
	static Socket socketInstance = {};

	plog_verbose("Socket instance is being got.");

	return socketInstance;
}

Socket::Socket(void) noexcept
	: m_socket{ INVALID_SOCKET }
{
	WORD    versionRequested = MAKEWORD(2, 2);
	WSADATA wsaData          = {};
	int32_t errorCode        = ERROR_SUCCESS;

	plog_debug("Socket is being constructed.");

	errorCode = WSAStartup(versionRequested, &wsaData);
	if (ERROR_SUCCESS != errorCode)
	{
		plog_error("WSA failed to be started! (error code: %" PRId32 ")", WSAGetLastError());
	}

	if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
	{
		plog_error("Could not find a usable version of Winsock.dll!");
	}
}

Socket::~Socket(void) noexcept
{
	int32_t errorCode = ERROR_SUCCESS;

	plog_debug("Socket is being deconstructed.");
	close();

	errorCode = WSACleanup();
	if (ERROR_SUCCESS != errorCode)
	{
		plog_error("WSA failed to be cleaned! (error code: %" PRId32 ")", errorCode);
	}
}

void Socket::create(std::string ipAddress) noexcept(false)
{
	static constexpr uint32_t BLOCKING = 0UL;

	sockaddr_in        server         = {};
	int32_t            errorCode      = ERROR_SUCCESS;
	u_long             socketMode     = BLOCKING;
	hobServer::Message versionMessage = {};

	plog_debug("Client socket is being created. (IP address: %s)", ipAddress.c_str());
	if (INVALID_SOCKET != m_socket)
	{
		plog_error("Socket is already created!");
		return;
	}

	if ("" == ipAddress)
	{
		plog_warn("Invalid IP address! (IP address: %s)", ipAddress.c_str());
		throw std::exception();
	}

	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (0ULL == m_socket)
	{
		plog_error("Client socket failed to be created! (error code: %" PRId32 ")", WSAGetLastError());
		throw std::exception();
	}

	errorCode = ioctlsocket(m_socket, FIONBIO, &socketMode);
	if (ERROR_SUCCESS != errorCode)
	{
		plog_error("Failed to set socket to blocking mode! (error code: %" PRId32 ")", errorCode);
		goto CLOSE;
	}

	errorCode = InetPton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr); /*< TODO: Change address. */
	if (1L != errorCode)
	{
		plog_error("Failed to convert ip address to binary! (error code: % " PRId32 ")", WSAGetLastError());
		goto CLOSE;
	}

	server.sin_family = AF_INET;
	server.sin_port   = htons(PORT);

	errorCode = connect(m_socket, (sockaddr*)&server, sizeof(server));
	if (ERROR_SUCCESS > errorCode)
	{
		plog_error("Client failed to connect to server! (error code: %" PRId32 ")", errorCode);
		goto CLOSE;
	}

	versionMessage.type            = hobServer::MessageType::VERSION;
	versionMessage.payload.version = { VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH };
	sendUpdate(versionMessage);

	return;
	
CLOSE:

	close();

	throw std::exception();
}

void Socket::close(void) noexcept
{
	int32_t errorCode = ERROR_SUCCESS;

	plog_trace("Client socket is being closed.");
	if (INVALID_SOCKET != m_socket)
	{
		errorCode = closesocket(m_socket);
		if (ERROR_SUCCESS != errorCode)
		{
			plog_error("Client socket failed to be closed! (error code: %" PRId32 ")", errorCode);
		}
		m_socket = INVALID_SOCKET;
	}
	else
	{
		plog_warn("Client socket is already closed.");
	}
}

void Socket::sendUpdate(const hobServer::Message& updateMessage) const noexcept
{
	plog_trace("Update is being sent. (type: %" PRId32 ")", static_cast<int32_t>(updateMessage.type));
	if (INVALID_SOCKET == m_socket)
	{
		plog_fatal("Connection is not established!");
		return;
	}
	send(m_socket, reinterpret_cast<const char*>(&updateMessage), sizeof(hobServer::Message), 0L);
}

void Socket::receiveUpdate(hobServer::Message& updateMessage) const noexcept
{
	int32_t receivedBytes = 0L;

	plog_verbose("Querrying for updates.");
	if (INVALID_SOCKET == m_socket)
	{
		plog_fatal("Connection is not established");
		return;
	}
	plog_debug("Waiting for updates to arrive.");

	receivedBytes = recv(m_socket, reinterpret_cast<char*>(&updateMessage), sizeof(hobServer::Message), 0L);
	if (0L == receivedBytes)
	{
		plog_info("Connection was lost!");
		updateMessage.type = hobServer::MessageType::END_COMMUNICATION;
	}
	else if (0L > receivedBytes)
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
