/******************************************************************************************************
 * @file hobServer_Server.cpp                                                                         *
 * @date:      @author:                   Reason for change:                                          *
 * 26.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file implements the class defined in hobServer_Server.hpp.                           *
 * @todo Implement communication to clients.                                                          *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <mutex>
#include <plog.h>

#include "hobServer_Server.hpp"
#include "hobServer_Common.hpp"
#include "hobServer_Socket.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hobServer
{

Server::Server(void) noexcept
	: m_socket     {}
	, m_runThread  {}
	, m_createAgain{ false }
{
	plog_trace(LOG_PREFIX "Server is being constructed.");
}

Server::~Server(void) noexcept
{
	plog_trace(LOG_PREFIX "Server is being destructed.");
	stop();
}

void Server::runAsync(uint16_t port) noexcept
{
	m_createAgain = true;
	m_runThread   = std::thread{ std::bind(&Server::runSync, this, port) };
}

void Server::stop(void) noexcept
{
	plog_debug(LOG_PREFIX  "Server is being stopped.");

	m_socket.close();
	m_createAgain = false;

	if (true == m_runThread.joinable())
	{
		plog_debug(LOG_PREFIX "Run thread is being joined.");
		m_runThread.join();
		plog_debug(LOG_PREFIX "Run thread has joined.");
	}
}

void Server::runSync(uint16_t port) noexcept
{
	std::thread receiveFirstPlayerThread = {};

CREATE_SOCKET:

	try
	{
		m_socket.create(port);
	}
	catch (const std::exception& exception)
	{
		return;
	}

	startTimer(30U);

	while (true)
	{

	}

	// receiveFirstPlayerThread = std::thread{ std::bind(&Server::receiveFirstPlayer, this) };
	// receiveSecondPlayer();

	// if (true == receiveFirstPlayerThread.joinable())
	// {
	// 	receiveFirstPlayerThread.join();
	// }

	stopTimer();

	if (true == m_createAgain)
	{
		goto CREATE_SOCKET;
	}
}

// void Server::receiveFirstPlayer(void)
// {
// 	Message message = {};

// 	while (true)
// 	{
// 		m_socket.receiveUpdate(message, ClientType::PLAYER_1);

// 		if (MessageType::END_COMMUNICATION == message.type)
// 		{
// 			m_socket.close();
// 			return;
// 		}
// 	}
// }

// void Server::receiveSecondPlayer(void)
// {
// 	Message message = {};

// 	while (true)
// 	{
// 		m_socket.receiveUpdate(message, ClientType::PLAYER_2);

// 		m_socket.close();
// 	}
// }

void Server::onTimeUpdate(uint16_t timeLeft) noexcept
{
	Message timeUpdate = {};
	timeUpdate.type             = MessageType::TIME;
	timeUpdate.payload.timeLeft = timeLeft;

	m_socket.sendUpdate(timeUpdate, ClientType::PLAYER_1); // TODO
}

void Server::onTimesUp(void) noexcept
{
	// TODO
}

} /*< namespace hobServer */
