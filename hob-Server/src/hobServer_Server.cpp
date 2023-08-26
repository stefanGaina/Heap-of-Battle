/******************************************************************************************************
 * @file hobServer_Server.cpp                                                                         *
 * @date:      @author:                   Reason for change:                                          *
 * 26.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added communication to clients.                             *
 * 26.08.2023  Gaina Stefan               Improved logs.                                              *
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
	: m_socket     {}
	, m_runThread  {}
	, m_createAgain{ false }
{
	plog_trace(LOG_PREFIX "Server is being constructed. (size: %" PRIu64 ") (1: %" PRIu64 ") (2: %" PRIu64 ") (3: %" PRIu64 ")",
		sizeof(*this), sizeof(m_runThread), sizeof(m_createAgain));
}

Server::~Server(void) noexcept
{
	plog_trace(LOG_PREFIX "Server is being destructed.");
	stop();
}

void Server::runAsync(const uint16_t port) noexcept
{
	plog_info(LOG_PREFIX "Server is running asynchronically (port: %" PRIu16 ")", port);
	if (true == m_createAgain.load())
	{
		plog_error(LOG_PREFIX "Server is already running asynchronically!");
		return;
	}

	m_createAgain.store(true);
	m_runThread = std::thread{ std::bind(&Server::runSync, this, port) };
}

void Server::stop(void) noexcept
{
	plog_debug(LOG_PREFIX "Server is being stopped.");

	m_createAgain.store(false);
	m_socket.close();

	if (true == m_runThread.joinable())
	{
		plog_debug(LOG_PREFIX "Run thread is being joined.");
		m_runThread.join();
		plog_debug(LOG_PREFIX "Run thread has joined.");
	}
}

void Server::runSync(const uint16_t port) noexcept
{
	std::thread receiveFirstPlayerThread = {};

	plog_debug(LOG_PREFIX "Server is running synchronically (port: %" PRIu16 ")", port);

CREATE_SOCKET:

	try
	{
		m_socket.create(port);
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

	if (true == m_createAgain.load())
	{
		plog_info(LOG_PREFIX "Creating socket again!");
		goto CREATE_SOCKET;
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
		m_socket.receiveUpdate(message, clientType);
		switch (message.type)
		{
			case MessageType::PING:
			{
				plog_trace(LOG_PREFIX "Ping message is being sent.");
				m_socket.sendUpdate(message, clientType);
				break;
			}
			case MessageType::TEXT:
			{
				plog_trace(LOG_PREFIX "Text message is being sent. (message: %s)", message.payload.text);
				m_socket.sendUpdate(message, otherPlayer);
				break;
			}
			case MessageType::END_COMMUNICATION:
			{
				plog_info(LOG_PREFIX "End communication message has been received!");
				m_socket.close();
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

	m_socket.sendUpdate(timeUpdate, ClientType::PLAYER_1);
	m_socket.sendUpdate(timeUpdate, ClientType::PLAYER_2);
}

void Server::onTimesUp(uint16_t& timeLeft) const noexcept
{
	Message timesUpUpdate = {};

	plog_info(LOG_PREFIX "Time is up!");

	timesUpUpdate.type = MessageType::END_TURN;
	timeLeft           = TIME_PER_TURN;

	m_socket.sendUpdate(timesUpUpdate, ClientType::PLAYER_1);
	m_socket.sendUpdate(timesUpUpdate, ClientType::PLAYER_2);
}

} /*< namespace hobServer */
