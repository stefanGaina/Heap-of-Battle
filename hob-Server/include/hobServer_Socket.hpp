/******************************************************************************************************
 * @file hobServer_Socket.hpp                                                                         *
 * @date:      @author:                   Reason for change:                                          *
 * 26.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Made waitConnectionFunction throwable.                      *
 * @details This file defines the class and method prototypes of the socket.                          *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_SERVER_SOCKET_HPP_
#define HOB_SERVER_SOCKET_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#define WIN32_LEAN_AND_MEAN  /*< For winsock to not have linkage issues.  */
#include <string>
#include <memory>
#include <thread>
#include <functional>
#include <winsock2.h>

#include "hobServer_Types.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hobServer
{

/**
 * @brief The client that the request is meant to.
*/
enum class ClientType
{
	PLAYER_1 = 0, /**< The first player that connected to the server.  */
	PLAYER_2 = 1  /**< The second player that connected to the server. */
};

/**
 * @brief Server socket that supports connections from 2 clients.
*/
class Socket final
{
public:
	/**
	 * @brief Function prototype of the callback when the connections are done.
	*/
	using CallbackFunction = std::function<void(bool)>;

	/**
	 * @brief Pointer to the callback when the connections are done
	*/
	using Callback = std::shared_ptr<CallbackFunction>;

	/**
	 * @brief Does not create the socket implicitly.
	 * @param void
	*/
	Socket(void) noexcept;

	/**
	 * @brief Closes the sockets if they were not already.
	 * @param void
	*/
	~Socket(void) noexcept;

	/**
	 * @brief Create a server socket and waits connections from 2 clients.
	 * @param port: The port that the server socket will be opened to connections.
	 * @param[in] callback: Function that will be called asynchronically after the connection is done
	 * with both clients. This is optional, otherwise the waiting will be done synchronically.
	 * @return void
	*/
	void create(uint16_t port, Callback callback = nullptr) noexcept(false);

	/**
	 * @brief Closes the server socket and the 2 client sockets interrupting the waiting of
	 * connections if they were not already done.
	 * @param void
	 * @return void
	*/
	void close(void) noexcept;

	/**
	 * @brief Waits until an update message is available from a client.
	 * @param[out] updateMessage: The update message received.
	 * @param clientType: Which client the update message is received from.
	 * @return void
	*/
	void receiveUpdate(Message& updateMessage, ClientType clientType) const noexcept;

	/**
	 * @brief Sends an update message to a client.
	 * @param[in] updateMessage: The message update to be sent.
	 * @param clientType: Which client the update message will be sent to.
	 * @return void
	*/
	void sendUpdate(const Message& updateMessage, ClientType clientType) const noexcept;

private:
	/**
	 * @brief Waits connections to server from 2 clients. Throws exceptions only when not called with a callback.
	 * @param[in] callback: Function that will be called at the end if on another thread (null - otherwise).
	 * Parameter is true if the connection has been established successfully and false otherwise.
	 * @return void
	*/
	void waitConnectionFunction(Callback callback = nullptr) noexcept(false);

	/**
	 * @brief Closes the client socket.
	 * @param clientType: Which client.
	 * @return void
	*/
	void closeClient(ClientType clientType) noexcept;

private:
	/**
	 * @brief The server socket.
	*/
	SOCKET m_serverSocket;

	/**
	 * @brief The client sockets.
	*/
	SOCKET m_clientSockets[2];

	/**
	 * @brief The thread that will be created if the waiting of connections is be done asynchronically.
	*/
	std::thread m_waitConnectionThread;
};

} /*< hobServer */

#endif /*< HOB_SERVER_SOCKET_HPP_ */
