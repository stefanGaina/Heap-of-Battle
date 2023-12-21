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
 * @file hobServer_Server.cpp                                                                         *
 * @date:      @author:                   Reason for change:                                          *
 * 26.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added communication to clients.                             *
 * 26.08.2023  Gaina Stefan               Improved logs.                                              *
 * 21.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file implements the class defined in hobServer_Server.hpp.                           *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hobServer_Server.hpp"
#include "hobServer_Common.hpp"
#include "hobServer_Socket.hpp"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

namespace hobServer
{

/**
 * @brief Default value for the time (seconds) allowed for every turn.
*/
static constexpr const uint16_t TIME_PER_TURN = 30U;

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

Server::Server(void) noexcept
	: socket     {}
	, runThread  {}
	, createAgain{ false }
{
	plog_trace(LOG_PREFIX "Server is being constructed.");
}

Server::~Server(void) noexcept
{
	plog_trace(LOG_PREFIX "Server is being destructed.");
	stop();
}

void Server::runAsync(const uint16_t port) noexcept
{
	plog_info(LOG_PREFIX "Server is running asynchronically (port: %" PRIu16 ")", port);
	if (true == createAgain.load())
	{
		plog_error(LOG_PREFIX "Server is already running asynchronically!");
		return;
	}

	createAgain.store(true);
	runThread = std::thread{ std::bind(&Server::runSync, this, port) };
}

void Server::stop(void) noexcept
{
	plog_debug(LOG_PREFIX "Server is being stopped.");

	createAgain.store(false);
	socket.close();

	if (true == runThread.joinable())
	{
		plog_debug(LOG_PREFIX "Run thread is being joined.");
		runThread.join();
		plog_debug(LOG_PREFIX "Run thread has joined.");
	}
}

void Server::runSync(const uint16_t port) noexcept
{
	std::thread receiveFirstPlayerThread = {};

	plog_debug(LOG_PREFIX "Server is running synchronically (port: %" PRIu16 ")", port);
	while (true)
	{
		try
		{
			socket.create(port);
		}
		catch (const std::exception& exception)
		{
			plog_fatal(LOG_PREFIX "Socket failed to be created!");
			return;
		}

		startTimer(TIME_PER_TURN);

		receiveFirstPlayerThread = std::thread{ std::bind(&Server::receivePlayerUpdates, this, ClientType::PLAYER_1) };
		receivePlayerUpdates(ClientType::PLAYER_2);

		if (true == receiveFirstPlayerThread.joinable())
		{
			plog_debug(LOG_PREFIX "Receiving updates from second player thread is being joined.");
			receiveFirstPlayerThread.join();
			plog_debug(LOG_PREFIX "Receiving updates from second player thread has joined.");
		}

		stopTimer();

		if (false == createAgain.load())
		{
			break;
		}
		plog_info(LOG_PREFIX "Creating socket again!");
	}
	plog_info(LOG_PREFIX "Server has been finished!");
}

void Server::receivePlayerUpdates(const ClientType clientType) noexcept
{
	Message          message     = {};
	const ClientType otherPlayer = ClientType::PLAYER_1 == clientType ? ClientType::PLAYER_2 : ClientType::PLAYER_1;

	plog_debug(LOG_PREFIX "Player updates are being received. (player: %" PRId32 ")", static_cast<int32_t>(clientType));
	while (true)
	{
		socket.receiveUpdate(message, clientType);
		switch (message.type)
		{
			case MessageType::PING:
			{
				plog_trace(LOG_PREFIX "Ping message is being sent.");
				socket.sendUpdate(message, clientType);

				break;
			}
			case MessageType::TEXT:
			{
				plog_trace(LOG_PREFIX "Text message is being sent. (message: %s)", message.payload.text);
				socket.sendUpdate(message, otherPlayer);

				break;
			}
			case MessageType::END_COMMUNICATION:
			{
				plog_info(LOG_PREFIX "End communication message has been received!");
				socket.close();

				return;
			}
			default:
			{
				plog_error(LOG_PREFIX "Invalid message type received! (type: %" PRId32 ")", static_cast<int32_t>(message.type));
				break;
			}
		}
	}
}

void Server::onTimeUpdate(const uint16_t timeLeft) noexcept
{
	Message timeUpdate = {};

	plog_trace(LOG_PREFIX "Time updates are being sent. (time left: %" PRIu16 ")", timeLeft);

	timeUpdate.type             = MessageType::TIME;
	timeUpdate.payload.timeLeft = timeLeft;

	socket.sendUpdate(timeUpdate, ClientType::PLAYER_1);
	socket.sendUpdate(timeUpdate, ClientType::PLAYER_2);
}

void Server::onTimesUp(uint16_t& timeLeft) const noexcept
{
	Message timesUpUpdate = {};

	plog_info(LOG_PREFIX "Time is up!");

	timesUpUpdate.type = MessageType::END_TURN;
	timeLeft           = TIME_PER_TURN;

	socket.sendUpdate(timesUpUpdate, ClientType::PLAYER_1);
	socket.sendUpdate(timesUpUpdate, ClientType::PLAYER_2);
}

} /*< namespace hobServer */
