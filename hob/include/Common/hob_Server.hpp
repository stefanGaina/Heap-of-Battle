/******************************************************************************************************
 * @file hob_Server.hpp                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 29.08.2023  Gaina Stefan               Initial version.                                            *
 * @details This file defines the class and method prototypes of the server.                          *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_SERVER_HPP_
#define HOB_SERVER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <memory>

#include "hobServer_Server.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Local server for host in case of LAN games.
*/
class Server final
{
public:
	/**
	 * @brief Singleton way to get access to the server object.
	 * @param void
	 * @return Reference to the server instance.
	*/
	static Server& getInstance(void) noexcept;

	/**
	 * @brief Creates the server.
	 * @param void
	 * @return void
	*/
	void create(void) noexcept(false);

	/**
	 * @brief Closes the server.
	 * @param void
	 * @return void
	*/
	void close(void) noexcept;

	/**
	 * @brief Prevents the creation of another object.
	 * @param otherServer: Instance to be copied.
	*/
	Server(Server& otherServer) = delete;

	/**
	 * @brief Prevents the creation of another object.
	 * @param server: Instance to be copied.
	*/
	void operator =(const Server& server) = delete;

private:
	/**
	 * @brief Does not create the server implicitly.
	 * @param void
	*/
	Server(void) noexcept;

	/**
	 * @brief Closes the server if it was not already.
	 * @param void
	*/
	~Server(void) noexcept;

private:
	/**
	 * @brief The server.
	*/
	std::unique_ptr<hobServer::Server> m_server;
};

} /*< namespace hob */

#endif /*< HOB_SERVER_HPP_ */
