/******************************************************************************************************
 * @file hob_Map1.cpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 27.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file implements the class defined in hob_Map1.hpp.                                   *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <memory>
#include <plog.h>

#include "hob_Map1.hpp"
#include "hob_Cursor.hpp"
#include "hob_Socket.hpp"
#include "hob_Faction.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Map1::Map1(void)
	: Loop            {}
	, m_menu          {}
	// , chat            {}
	, m_tiles         {}
	, m_buildings     {}
	, m_grid          {}
	, m_timer         {}
	, receivingThread { std::bind(&Map1::receivingFunction, this) }
	, receivingUpdates{ true }
{
	plog_trace("Map1 is being constructed.");
	Cursor::getInstance().setFaction(Faction::getInstance().getFaction());
	Cursor::getInstance().setTexture(CursorType::IDLE);
}

Map1::~Map1(void)
{
	plog_trace("Map1 is being destructed.");

	receivingUpdates = false;
	Socket::getInstance().close();

	if (true == receivingThread.joinable())
	{
		plog_debug("Receiving updates thread is being joined.");
		receivingThread.join();
		plog_debug("Receiving updates thread has joined.");
	}

	Cursor::getInstance().setFaction(true);
	Cursor::getInstance().setTexture(CursorType::IDLE);
}

void Map1::draw(void) noexcept
{
	plog_verbose("Map1 is being drawn.");
	m_menu.draw();
	// chat.draw();
	m_tiles.draw();
	m_buildings.draw();
	m_grid.draw();
	m_timer.draw();
}

void Map1::handleEvent(const SDL_Event& event) noexcept
{
	Coordinate       click      = {};
	hobServer::Message message    = {};
	uint32_t         mouseState = 0UL;
	//size_t           index      = 0ULL;

	plog_verbose("Event is being handled.");
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
		{
			mouseState = SDL_GetMouseState(&click.x, &click.y);
			plog_trace("Mouse (%" PRIu32 ") was clicked. (coordinates: %" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);

			if (1 != SDL_BUTTON(mouseState))
			{
				plog_trace("Mouse click is not left click.");
				return;
			}

			//chat.handleClick(click);
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			mouseState = SDL_GetMouseState(&click.x, &click.y);
			plog_trace("Mouse (%" PRIu32 ") was released. (coordinates: %" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);
			break;
		}
		case SDL_MOUSEMOTION:
		{
			mouseState = SDL_GetMouseState(&click.x, &click.y);
			plog_verbose("Mouse (%" PRIu32 ") was moved. (coordinates: %" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);

			Cursor::getInstance().updatePosition(click);

			if (1 == SDL_BUTTON(mouseState))
			{
				plog_verbose("Mouse left click is pressed.");
				return;
			}
			break;
		}
		case SDL_KEYDOWN:
		{
			//chat.handleButtonPress(event);

			// TODO: remove this
			// switch (event.key.keysym.sym)
			// {
			// 	case SDLK_a:
			// 	{
			// 		tiles.changeTexture(Season::SUMMER);
			// 		m_buildings.changeWeather(false);
			// 		break;
			// 	}
			// 	case SDLK_s:
			// 	{
			// 		tiles.changeTexture(Season::AUTUMN);
			// 		m_buildings.changeWeather(false);
			// 		break;
			// 	}
			// 	case SDLK_d:
			// 	{
			// 		tiles.changeTexture(Season::WINTER);
			// 		m_buildings.changeWeather(true);
			// 		break;
			// 	}
			// 	case SDLK_f:
			// 	{
			// 		tiles.changeTexture(Season::SPRING);
			// 		m_buildings.changeWeather(false);
			// 		break;
			// 	}
			// }
			break;
		}
		case SDL_WINDOWEVENT:
		{
			if (SDL_WINDOWEVENT_FOCUS_LOST == event.window.event)
			{
				plog_debug("Window lost focus.");
				click.x = -1L;
				click.y = -1L;
				Cursor::getInstance().updatePosition(click);
			}
			break;
		}
		case SDL_QUIT:
		{
			plog_info("Command to quit game was given!");

			message.type = hobServer::MessageType::END_COMMUNICATION;
			Socket::getInstance().sendUpdate(message);

			stop(Scene::QUIT);
			break;
		}
		default:
		{
			plog_verbose("Event received but not handled.");
			break;
		}
	}
}

void Map1::receivingFunction(void) noexcept
{
	hobServer::Message receivedMessage = {};

	while (true == receivingUpdates)
	{
		Socket::getInstance().receiveUpdate(receivedMessage);
		switch (receivedMessage.type)
		{
			case hobServer::MessageType::TEXT:
			{
				//plog_trace("Text message received! (message: %s)", receivedMessage.payload.text);
				//chat.receivedMessage(receivedMessage.payload.text);
				break;
			}
			case hobServer::MessageType::TIME:
			{
				plog_verbose("Time update message received! (time left: %" PRIu16 ")", receivedMessage.payload.timeLeft);
				m_timer.update(receivedMessage.payload.timeLeft, false);
				break;
			}
			case hobServer::MessageType::END_TURN:
			{
				plog_info("Opponent turn ended!");
				break;
			}
			case hobServer::MessageType::END_COMMUNICATION:
			{
				plog_info("End communication message received!");
				receivingUpdates = false;
				stop(Scene::MAIN_MENU);
				break;
			}
			case hobServer::MessageType::VERSION:
			{
				//plog_error("Version message type received! (opponent version: %s)", receivedMessage.payload.version);
				break;
			}
			default:
			{
				plog_error("Invalid message type! (message type: %" PRId32 ")", static_cast<int32_t>(receivedMessage.type));
				break;
			}
		}
	}
}

} /*< namespace hob */
