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
 * @file hobServer_Socket.hpp
 * @author Gaina Stefan
 * @date 26.07.2023
 * @brief This file defines the class and method prototypes of the socket.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_SERVER_SOCKET_HPP_
#define HOB_SERVER_SOCKET_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <string>
#include <memory>
#include <thread>
#include <functional>
#include <sys/socket.h>

#include "hobServer_Types.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hobServer
{

/** ***************************************************************************************************
 * @brief The client that the request is meant to.
 *****************************************************************************************************/
enum class ClientType
{
	PLAYER_1 = 0, /**< The first player that connected to the server.  */
	PLAYER_2 = 1  /**< The second player that connected to the server. */
};

/** ***************************************************************************************************
 * @brief Server socket that supports connections from 2 clients.
 *****************************************************************************************************/
class Socket final
{
public:
	/** ***********************************************************************************************
	 * @brief Function prototype of the callback when the server is ready to make connections.
	 *************************************************************************************************/
	using Callback = std::function<void(void)>;

	/** ***********************************************************************************************
	 * @brief Does not create the socket implicitly.
	 * @param void
	 *************************************************************************************************/
	Socket(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Closes the sockets if they were not already.
	 * @param void
	 *************************************************************************************************/
	~Socket(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Create a server socket and waits connections from 2 clients.
	 * @param port: The port that the server socket will be opened to connections.
	 * @param callback: Function that will be called synchronically after the server is ready
	 * to make connections. For now this is optional.
	 * @return void
	 * @throws std::exception If the socket is already created or if the creation/binding of the socket
	 * failed.
	 *************************************************************************************************/
	void create(uint16_t port, Callback callback) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Closes the server socket and the 2 client sockets interrupting the waiting of
	 * connections if they were not already done.
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void close(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Waits until an update message is available from a client.
	 * @param[out] updateMessage: The update message received.
	 * @param clientType: Which client the update message is received from.
	 * @return void
	 *************************************************************************************************/
	void receiveUpdate(Message& updateMessage, ClientType clientType) const noexcept;

	/** ***********************************************************************************************
	 * @brief Sends an update message to a client.
	 * @param updateMessage: The message update to be sent.
	 * @param clientType: Which client the update message will be sent to.
	 * @return void
	 *************************************************************************************************/
	void sendUpdate(const Message& updateMessage, ClientType clientType) const noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Waits connections to server from 2 clients. Throws exceptions only when not called with
	 * a callback.
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void waitConnection(void) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Closes the client socket.
	 * @param clientType: Which client.
	 * @return void
	 *************************************************************************************************/
	void closeClient(ClientType clientType) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief The server socket identifier.
	 *************************************************************************************************/
	int32_t serverSocket;

	/** ***********************************************************************************************
	 * @brief The client socket identifiers.
	 *************************************************************************************************/
	int32_t clientSockets[2];
};

} /*< hobServer */

#endif /*< HOB_SERVER_SOCKET_HPP_ */
