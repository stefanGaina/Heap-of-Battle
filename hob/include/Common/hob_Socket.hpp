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
 * @file hob_Socket.hpp                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 25.07.2023  Gaina Stefan               Initial version.                                            *
 * 27.08.2023  Gaina Stefan               Removed unnecessary headers.                                *
 * 29.08.2023  Gaina Stefan               Fixed comment.                                              *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file defines the class and method prototypes of the client socket.                   *
 * @todo Add port to create.                                                                          *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_SOCKET_HPP_
#define HOB_SOCKET_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <string>

#include "hob_Types.hpp"
#include "hobServer_Types.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Client socket wrapper for server types.
*/
class Socket final
{
public:
	/**
	 * @brief Does not create the socket implicitly.
	 * @param void
	*/
	Socket(void) noexcept;

	/**
	 * @brief Cleans the socket if it was not already.
	 * @param void
	*/
	~Socket(void) noexcept;

	/**
	 * @brief Creates a client socket.
	 * @param ipAddress: IP address of the server.
	 * @return void
	*/
	void create(std::string ipAddress) noexcept(false);

	/**
	 * @brief Closes the client socket.
	 * @param void
	 * @return void
	*/
	void close(void) noexcept;

	/**
	 * @brief Waits until the server sends a message.
	 * @param updateMessage: Message received from the server.
	 * @return void
	*/
	void receiveUpdate(hobServer::Message& updateMessage) const noexcept;

	/**
	 * @brief Sends an update to the server.
	 * @param updateMessage: Message that will be sent to the server.
	 * @return void
	*/
	void sendUpdate(const hobServer::Message& updateMessage) const noexcept;

	/**
	 * @brief Prevents the creation of another object.
	 * @param otherSocket: Instance to be copied.
	*/
	Socket(Socket& otherSocket) = delete;

	/**
	 * @brief Prevents the creation of another object.
	 * @param socket: Instance to be copied.
	*/
	void operator =(const Socket& socket) = delete;

private:
	/**
	 * @brief The client socket.
	*/
	int32_t socket;
};

} /*< namespace hob */

#endif /*< HOB_SOCKET_HPP_ */
