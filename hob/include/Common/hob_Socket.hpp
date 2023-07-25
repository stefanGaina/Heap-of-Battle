/******************************************************************************************************
 * @file hob_Socket.hpp                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 25.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file defines the class and method prototypes of the client socket.                   *
 * @todo Add port to create.                                                                          *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_SOCKET_HPP_
#define HOB_SOCKET_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#define WIN32_LEAN_AND_MEAN  /*< For winsock to not have linkage issues. */
#include <string>
#include <thread>
#include <memory>
#include <functional>
#include <winsock2.h>

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
	 * @brief Singleton way to get access to the socket object.
	 * @param void
	 * @return Reference to the socket instance.
	*/
	static Socket& getInstance(void) noexcept;

	/**
	 * @brief Creates a clinet socket.
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
	 * @brief TODO
	 * @param updateMessage 
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
	void operator=(const Socket& socket) = delete;

private:
	/**
	 * @brief Initializes the Windows Socket API, but does not create the socket implicitly.
	 * @param void
	*/
	Socket(void) noexcept;

	/**
	 * @brief Deinitializes the Windows Socket API and cleans the socket if it was not already.
	 * @param void
	*/
	~Socket(void) noexcept;

private:
	/**
	 * @brief The client socket.
	*/
	SOCKET m_socket;
};

} /*< namespace hob */

#endif /*< HOB_SOCKET_HPP_ */
