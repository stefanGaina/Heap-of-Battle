/******************************************************************************************************
 * @file hobServer_Server.hpp                                                                         *
 * @date:      @author:                   Reason for change:                                          *
 * 26.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file defines the class and method prototypes of the server.                          *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_SERVER_SERVER_HPP_
#define HOB_SERVER_SERVER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <thread>

#include "hobServer_Socket.hpp"
#include "hobServer_Timer.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hobServer
{

/**
 * @brief Server for matches.
*/
class Server final : public Timer
{
public:
	/**
	 * @brief Does not run the server implicitly.
	 * @param void
	*/
	Server(void) noexcept;

	/**
	 * @brief Stops the server.
	 * @param void
	*/
	~Server(void) noexcept;

	/**
	 * @brief Runs the server asynchronically.
	 * @param port: Port on which the server socket will be opened.
	 * @return void
	*/
	void runAsync(uint16_t port = 8787U) noexcept;

	/**
	 * @brief Stops the server.
	 * @param void
	 * @return void
	*/
	void stop(void) noexcept;

private:
	/**
	 * @brief Runs the server synchronically.
	 * @param port: Port on which the server socket will be opened.
	 * @return void
	*/
	void runSync(uint16_t port) noexcept;

	/**
	 * @brief Sends an update message with how much time is left in the turn.
	 * @param timeLeft: How many seconds are left in the turn.
	 * @return void
	*/
	void onTimeUpdate(uint16_t timeLeft) noexcept override;

	/**
	 * @brief Sends an update message that the turn has ended due to time.
	 * @param void
	 * @return void
	*/
	void onTimesUp(void) noexcept override;

private:
	/**
	 * @brief Server socket.
	*/
	Socket m_socket;

	/**
	 * @brief The thread that the server is ran on.
	*/
	std::thread m_runThread;

	/**
	 * @brief Flag indicating the server is still running after the connections are closed/lost.
	*/
	bool m_createAgain;
};

} /*< namespace hobServer */

#endif /*< HOB_SERVER_SERVER_HPP_ */
