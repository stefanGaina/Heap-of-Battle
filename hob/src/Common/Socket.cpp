#include <string.h>
#include <WS2tcpip.h>
#include <plog.h>

#include "Socket.hpp"

namespace Utility
{

/**
 * @brief 
*/
static constexpr uint16_t PORT = 8887U;

/**
 * @brief 
*/
static constexpr uint32_t BLOCKING = 0UL;

Socket& Socket::getInstance(void) noexcept
{
	static Socket socketInstance = {};

	plog_verbose("Socket instance is being got.");

	return socketInstance;
}

Socket::Socket(void) noexcept
	: m_serverSocket        { INVALID_SOCKET }
	, m_clientSocket        { INVALID_SOCKET }
	, m_waitConnectionThread{}
{
	WORD    versionRequested = MAKEWORD(2, 2);
	WSADATA wsaData          = {};
	int32_t errorCode        = NO_ERROR;

	plog_debug("Socket is being constructed.");

	errorCode = WSAStartup(versionRequested, &wsaData);
	if (NO_ERROR != errorCode)
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
	int32_t errorCode = NO_ERROR;

	plog_debug("Socket is being destructed.");
	clean();

	errorCode = WSACleanup();
	if (NO_ERROR != errorCode)
	{
		plog_error("WSA failed to be cleaned! (error code: %" PRId32 ")", errorCode);
	}
}

void Socket::waitConnectionFunction(Callback callback) noexcept
{
	int32_t     errorCode      = NO_ERROR;
	sockaddr_in client         = {};
	int32_t     addressLength  = sizeof(sockaddr_in);
	Message     versionMessage = {};

	plog_info("Waiting for incoming connections!");

	errorCode = listen(m_serverSocket, 0L);
	if (NO_ERROR != errorCode)
	{
		plog_error("Server failed to open for connections! (error code: %" PRId32 ")", errorCode);
	}

WAIT_FOR_CONNECTION:

	m_clientSocket = accept(m_serverSocket, reinterpret_cast<sockaddr*>(&client), &addressLength);
	if (0ULL >= m_clientSocket)
	{
		plog_error("Connection failed to be accepted! (error code: %" PRId32 ")", WSAGetLastError());
		goto WAIT_FOR_CONNECTION;
	}

	if (INVALID_SOCKET == m_serverSocket)
	{
		plog_warn("Server socket was closed!");
		return;
	}

	plog_info("Connection accepted successfully!");

	receiveUpdates(versionMessage);
	if (MessageType::VERSION != versionMessage.type)
	{
		plog_error("First message received is not checking to match versions! (message type: %" PRId32 ")", static_cast<int32_t>(versionMessage.type));
		goto ABORT_CONNECTION;
	}
	else
	{
		plog_info("Version message received! (opponent version: %s)", versionMessage.payload.version);
		if (0L != strcmp(VERSION_STRING, versionMessage.payload.version))
		{
			plog_error("Versions are not matching! (opponent version: %s)", versionMessage.payload.version);
			goto ABORT_CONNECTION;
		}
	}

	if (NULL == callback)
	{
		plog_warn("Callback is invalid!");
		return;
	}
	(*callback)();
	return;

ABORT_CONNECTION:

	versionMessage.type = MessageType::END_COMMUNICATION;
	sendUpdate(versionMessage);

	closeClient();

	goto WAIT_FOR_CONNECTION;
}

void Socket::clean(void) noexcept
{
	plog_debug("Socket is being cleaned.");
	closeServer();
	closeClient();

	if (true == m_waitConnectionThread.joinable())
	{
		plog_trace("Wait connection thread is joining.");
		m_waitConnectionThread.join();
	}
}

bool Socket::createServer(Callback callback) noexcept
{
	sockaddr_in server     = {};
	int32_t     errorCode  = NO_ERROR;
	u_long      socketMode = BLOCKING;

	plog_debug("Creating server socket.");
	if (NULL == callback)
	{
		plog_error("Callback is invalid!");
		return false;
	}

	if (INVALID_SOCKET != m_serverSocket || INVALID_SOCKET != m_clientSocket)
	{
		plog_error("Socket is already created!");
		return false;
	}

	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (0ULL > m_serverSocket)
	{
		plog_error("Server socket failed to be created! (error code: %" PRId32 ")", WSAGetLastError());
		return false;
	}

	errorCode = ioctlsocket(m_serverSocket, FIONBIO, &socketMode);
	if (NO_ERROR != errorCode)
	{
		plog_error("Failed to set socket to blocking mode! error code: %" PRId32 ")", errorCode);
		goto CLEAN_SOCKET;
	}

	server.sin_family      = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port        = htons(PORT);

	errorCode = ::bind(m_serverSocket, reinterpret_cast<sockaddr*>(&server), sizeof(server));
	if (SOCKET_ERROR == errorCode)
	{
		plog_error("Bind failed to be done! (error code: %" PRId32 ")", WSAGetLastError());
		goto CLEAN_SOCKET;
	}

	if (true == m_waitConnectionThread.joinable())
	{
		plog_warn("Wait connection thread joining!");
		m_waitConnectionThread.join();
	}
	m_waitConnectionThread = std::thread{ std::bind(&Socket::waitConnectionFunction, this, callback) };

	return true;

CLEAN_SOCKET:

	closeServer();

	return false;
}

bool Socket::createClient(std::string ipAddress) noexcept
{
	sockaddr_in server         = {};
	int32_t     errorCode      = NO_ERROR;
	u_long      socketMode     = BLOCKING;
	Message     versionMessage = {};

	plog_debug("Client socket is being created.");
	if (INVALID_SOCKET != m_serverSocket || INVALID_SOCKET != m_clientSocket)
	{
		plog_error("Socket is already created!");
		return false;
	}

	if ("" == ipAddress)
	{
		plog_warn("Invalid address!");
		ipAddress = "127.0.0.1";
	}

	m_clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (0ULL > m_clientSocket)
	{
		plog_error("Client socket failed to be created! (error code: %" PRId32 ")", WSAGetLastError());
		return false;
	}

	errorCode = ioctlsocket(m_clientSocket, FIONBIO, &socketMode);
	if (NO_ERROR != errorCode)
	{
		plog_error("Failed to set socket to blocking mode! (error code: %" PRId32 ")", errorCode);
		return false;
	}

	errorCode = InetPton(AF_INET, L"127.0.0.1", &server.sin_addr.s_addr); /*< TODO: Change address. */
	if (1L != errorCode)
	{
		plog_error("Failed to convert ip address to binary! (error code: % " PRId32 ")", WSAGetLastError());
		goto CLEAN_SOCKET;
	}

	server.sin_family = AF_INET;
	server.sin_port   = htons(PORT);

	errorCode = connect(m_clientSocket, (sockaddr*)&server, sizeof(server));
	if (NO_ERROR > errorCode)
	{
		plog_error("Client failed to connect to server! (error code: %" PRId32 ")", errorCode);
		goto CLEAN_SOCKET;
	}

	versionMessage.type = MessageType::VERSION;
	errorCode           = strcpy_s(versionMessage.payload.version, sizeof(versionMessage.payload.version), VERSION_STRING);
	if (0L != errorCode)
	{
		plog_warn("Failed to copy version into payload! (error code: %" PRId32 ")", errorCode);
	}
	sendUpdate(versionMessage);

	return true;

CLEAN_SOCKET:

	closeClient();

	return false;
}

void Socket::sendUpdate(const Message& updateMessage) const noexcept
{
	plog_trace("Update is being sent.");
	if (INVALID_SOCKET == m_clientSocket)
	{
		plog_fatal("Connection is not established!");
		return;
	}
	send(m_clientSocket, reinterpret_cast<const char*>(&updateMessage), sizeof(Message), 0L);
}

void Socket::closeClient(void) noexcept
{
	int32_t errorCode = NO_ERROR;

	plog_trace("Client socket is being closed.");
	if (INVALID_SOCKET != m_clientSocket)
	{
		errorCode = closesocket(m_clientSocket);
		if (NO_ERROR != errorCode)
		{
			plog_error("Client socket failed to be closed! (error code: %" PRId32 ")", errorCode);
		}
		m_clientSocket = INVALID_SOCKET;
	}
	else
	{
		plog_warn("Client socket is already closed.");
	}
}

} /*< namespace Utility */
