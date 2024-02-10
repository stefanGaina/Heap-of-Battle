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
 * @file hobServer_Server.hpp
 * @author Gaina Stefan
 * @date 26.07.2023
 * @brief This file defines the class and method prototypes of the server.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_SERVER_SERVER_HPP_
#define HOB_SERVER_SERVER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <atomic>

#include "hobServer_Socket.hpp"
#include "hobServer_Timer.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hobServer
{

/** ***************************************************************************************************
 * @brief This class offers a way to run the server for matches.
 * @details It either runs on a different machine either one of the players runs this on a separte
 * thread.
 *****************************************************************************************************/
class Server final : public Timer
{
public:
	/** ***********************************************************************************************
	 * @brief Stops the server.
	 * @param void
	 *************************************************************************************************/
	~Server(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Runs the server asynchronically.
	 * @param port: Port on which the server socket will be opened.
	 * @param timeout: Maximum amount of time (milliseconds) allowed to wait until the server socket
	 * is ready to accept connections from client socket
	 * @return void
	 * @throws std::exception If the timeout is exceeded or if a spurious wake up happends.
	 *************************************************************************************************/
	void runAsync(uint16_t port, uint16_t timeout) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Stops the server.
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void stop(void) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Sends an update message with how much time is left in the turn.
	 * @param timeLeft: How many seconds are left in the turn.
	 * @return void
	 *************************************************************************************************/
	void onTimeUpdate(uint16_t timeLeft) noexcept override;

	/** ***********************************************************************************************
	 * @brief Sends an update message that the turn has ended due to time.
	 * @param[out] timeLeft: The time allowed for the next turn.
	 * @return void
	 *************************************************************************************************/
	void onTimesUp(uint16_t& timeLeft) const noexcept override;

	/** ***********************************************************************************************
	 * @brief Runs the server synchronically.
	 * @param port: Port on which the server socket will be opened.
	 * @return void
	 *************************************************************************************************/
	void runSync(uint16_t port) noexcept;

	/** ***********************************************************************************************
	 * @brief Wakes up the caller's waiting thread.
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void onSocketReady(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Receives updates from a player and sends them to the other.
	 * @param clientType: Which player the updates come from.
	 * @return void
	 *************************************************************************************************/
	void receivePlayerUpdates(ClientType clientType) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief It is static because it is used in a lambda function.
	 *************************************************************************************************/
	static bool isSocketReady;

	/** ***********************************************************************************************
	 * @brief Server socket for sending and receiving messages for the players.
	 *************************************************************************************************/
	Socket socket;

	/** ***********************************************************************************************
	 * @brief The thread that the server is ran on.
	 *************************************************************************************************/
	std::thread runThread;

	/** ***********************************************************************************************
	 * @brief Flag indicating the server is still running after the connections are closed/lost.
	 *************************************************************************************************/
	std::atomic<bool> createAgain;

	/** ***********************************************************************************************
	 * @brief The variable signaled when the socket is ready (to avoid premature connection).
	 *************************************************************************************************/
	std::condition_variable waitSocket;

	/** ***********************************************************************************************
	 * @brief Mutex protecting isSocketReady.
	 *************************************************************************************************/
	std::mutex mutex;
};

} /*< namespace hobServer */

#endif /*< HOB_SERVER_SERVER_HPP_ */
