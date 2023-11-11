/******************************************************************************************************
 * @file hob_Map1.cpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 27.07.2023  Gaina Stefan               Initial version.                                            *
 * 26.08.2023  Gaina Stefan               Added chat.                                                 *
 * 27.08.2023  Gaina Stefan               Fixed compilation error due to removal of header.           *
 * @details This file implements the class defined in hob_Map1.hpp.                                   *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <memory>
#include <functional>
#include <plog.h>

#include "hob_Map1.hpp"
#include "hob_Music.hpp"
#include "hob_Cursor.hpp"
#include "hob_Socket.hpp"
#include "hob_Server.hpp"
#include "hob_Faction.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Map1::Map1(void) noexcept
	: Loop              {}
	, m_game            { Faction::getInstance().getFaction() }
	, m_tiles           {}
	, m_menu            { m_game.getGold() }
	, m_buildings       {}
	, m_chat            {}
	, m_grid            {}
	, m_units           {}
	, m_receivingThread { std::bind(&Map1::receivingFunction, this) }
	, m_receivingUpdates{ true }
{
	plog_trace("Map1 is being constructed. (size: %" PRIu64 ") (1: %" PRIu64 ") (2: %" PRIu64 ") (3: %" PRIu64 ") (4: %" PRIu64 ") "
		"(5: %" PRIu64 ") (6: %" PRIu64 ") (7: %" PRIu64 ") (8: %" PRIu64 ")", sizeof(*this), sizeof(m_game), sizeof(m_tiles), sizeof(m_menu),
		 sizeof(m_buildings), sizeof(m_chat), sizeof(m_grid), sizeof(m_receivingThread), sizeof(m_receivingUpdates));

	Music::getInstance().start(true == Faction::getInstance().getFaction() ? Song::SCENARIO_ALLIANCE : Song::SCENARIO_HORDE);

	Cursor::getInstance().setFaction(Faction::getInstance().getFaction());
	Cursor::getInstance().setTexture(hobGame::CursorType::IDLE);
}

Map1::~Map1(void) noexcept
{
	plog_trace("Map1 is being destructed.");

	m_receivingUpdates.store(false);
	Server::getInstance().close();
	Socket::getInstance().close();
	pingStop();

	if (true == m_receivingThread.joinable())
	{
		plog_debug("Receiving updates thread is being joined.");
		m_receivingThread.join();
		plog_debug("Receiving updates thread has joined.");
	}

	Cursor::getInstance().setFaction(true);
	Cursor::getInstance().setTexture(hobGame::CursorType::IDLE);
}

void Map1::draw(void) noexcept
{
	plog_verbose("Map1 is being drawn.");
	m_menu.draw();
	m_chat.draw();
	m_tiles.draw();
	m_buildings.draw();
	m_units.draw();
	m_grid.draw();
}

void Map1::handleEvent(const SDL_Event& event) noexcept
{
	Coordinate         click      = {};
	hobServer::Message message    = {};
	uint32_t           mouseState = 0UL;
	Action             action     = Action::NOTHING;

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

			m_chat.handleClick(click);

			action = m_menu.handleClick(click, m_game.getMenuMode(click.x, click.y));
			switch (action)
			{
				case Action::NOTHING:
				{
					break;
				}
				case Action::RECRUIT_INFANTRY:
				{
					if (true == m_game.recruit(hobGame::Unit::INFANTRY))
					{
						m_units.add(hobGame::Unit::INFANTRY);
					}
					break;
				}
				default:
				{
					break;
				}
			}
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
			Cursor::getInstance().setTexture(m_game.getCursorType(click.x, click.y));
			m_menu.handleHover(click);
			break;
		}
		case SDL_KEYDOWN:
		{
			m_chat.handleButtonPress(event);

			// TODO: remove this
			switch (event.key.keysym.sym)
			{
				case SDLK_a:
				{
					m_tiles.changeTexture(Season::SUMMER);
					m_buildings.changeWeather(false);
					break;
				}
				case SDLK_s:
				{
					m_tiles.changeTexture(Season::AUTUMN);
					m_buildings.changeWeather(false);
					break;
				}
				case SDLK_d:
				{
					m_tiles.changeTexture(Season::WINTER);
					m_buildings.changeWeather(true);
					break;
				}
				case SDLK_f:
				{
					m_tiles.changeTexture(Season::SPRING);
					m_buildings.changeWeather(false);
					break;
				}
			}
			break;
		}
		case SDL_WINDOWEVENT:
		{
			plog_verbose("Window event received.");
			if (SDL_WINDOWEVENT_FOCUS_LOST == event.window.event)
			{
				plog_trace("Window lost focus.");
				click = { .x = -1L, .y = -1L };
				Cursor::getInstance().updatePosition(click);
				m_menu.handleHover(click);
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
			plog_verbose("Event received but not handled. (type: %" PRIu32 ")", event.type);
			break;
		}
	}
}

void Map1::receivingFunction(void) noexcept
{
	hobServer::Message receivedMessage = {};

	plog_trace("Update messages are being received.");
	while (true == m_receivingUpdates.load())
	{
		Socket::getInstance().receiveUpdate(receivedMessage);
		switch (receivedMessage.type)
		{
			case hobServer::MessageType::PING:
			{
				plog_trace("Ping message received.");
				pingReceived();
				break;
			}
			case hobServer::MessageType::TIME:
			{
				plog_verbose("Time update message received. (time left: %" PRIu16 ")", receivedMessage.payload.timeLeft);
				if (false == Faction::getInstance().getFaction() && false == m_game.getTurn())
				{
					m_menu.updateTimer(receivedMessage.payload.timeLeft, true);
					break;
				}
				m_menu.updateTimer(receivedMessage.payload.timeLeft, Faction::getInstance().getFaction() && m_game.getTurn());
				break;
			}
			case hobServer::MessageType::TEXT:
			{
				plog_trace("Text message received. (message: %s)", receivedMessage.payload.text);
				m_chat.receivedMessage(receivedMessage.payload.text);
				break;
			}
			case hobServer::MessageType::END_TURN:
			{
				plog_info("End turn message received!");
				m_game.endTurn();
				m_menu.updateGold(m_game.getGold());
				break;
			}
			case hobServer::MessageType::END_COMMUNICATION:
			{
				plog_info("End communication message received!");
				m_receivingUpdates.store(false);
				stop(Scene::MAIN_MENU);
				break;
			}
			case hobServer::MessageType::VERSION:
			{
				plog_error("Version message type received! (opponent version: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ")",
					receivedMessage.payload.version.major, receivedMessage.payload.version.minor, receivedMessage.payload.version.patch);
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
