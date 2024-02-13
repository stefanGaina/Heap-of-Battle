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
 *****************************************************************************************************/

/******************************************************************************************************
 * @file hob_Map1.cpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 27.07.2023  Gaina Stefan               Initial version.                                            *
 * 26.08.2023  Gaina Stefan               Added chat.                                                 *
 * 27.08.2023  Gaina Stefan               Fixed compilation error due to removal of header.           *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * 17.01.2024  Gaina Stefan               Added faction member.                                       *
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
#include "hob_Faction.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Map1::Map1(SDL_Renderer* const renderer, Cursor& cursor, Ping* const ping, Music& music, const Faction& faction, hobServer::Server& server, Socket& socket) noexcept
	: Loop{ renderer, cursor, ping }
	, SoundInitializer{ { HOB_SOUNDS_FILE_PATH("error") } }
	, game{ faction.getFaction() }
	, tiles{ renderer }
	, menu{ renderer, faction.getFaction(), game.getGold() }
	, buildings{ renderer }
	, chat{ renderer, true == faction.getFaction() ? &socket : nullptr, faction.getFriendlyColor(), faction.getOpponentColor() }
	, grid{}
	, units{ renderer }
	, receivingThread{ std::bind(&Map1::receivingFunction, this) }
	, receivingUpdates{ true }
	, music{ music }
	, faction{ faction }
	, server{ server }
	, socket{ socket }
{
	plog_trace("Map1 is being constructed.");

	music.start(true == faction.getFaction() ? Song::SCENARIO_ALLIANCE : Song::SCENARIO_HORDE);
	cursor.setFaction(faction.getFaction());
	cursor.setTexture(hobGame::CursorType::IDLE);
}

Map1::~Map1(void) noexcept
{
	plog_trace("Map1 is being destructed.");

	receivingUpdates.store(false);
	server.stop();
	socket.close();
	ping->clean();

	if (true == receivingThread.joinable())
	{
		plog_debug("Receiving updates thread is being joined.");
		receivingThread.join();
		plog_debug("Receiving updates thread has joined.");
	}

	cursor.setFaction(true);
	cursor.setTexture(hobGame::CursorType::IDLE);
}

void Map1::draw(void) noexcept
{
	plog_verbose("Map1 is being drawn.");
	menu.draw(renderer);
	chat.draw(renderer);
	tiles.TileInitializer::draw(renderer);
	buildings.BuildingInitializer::draw(renderer);
	units.draw(renderer);
	grid.draw(renderer);
}

void Map1::handleEvent(const SDL_Event& event) noexcept
{
	Coordinate click = { .x = 0, .y = 0 };

	plog_verbose("Event is being handled.");
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
		{
			handleButtonDown();
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			handleButtonUp();
			break;
		}
		case SDL_MOUSEMOTION:
		{
			handleMouseMotion();
			break;
		}
		case SDL_KEYDOWN:
		{
			chat.handleButtonPress(event, renderer, socket);

#ifdef DEVEL_BUILD // TODO: remove this
			switch (event.key.keysym.sym)
			{
				case SDLK_a:
				{
					tiles.changeTexture(Season::SUMMER);
					buildings.changeWeather(false);
					break;
				}
				case SDLK_s:
				{
					tiles.changeTexture(Season::AUTUMN);
					buildings.changeWeather(false);
					break;
				}
				case SDLK_d:
				{
					tiles.changeTexture(Season::WINTER);
					buildings.changeWeather(true);
					break;
				}
				case SDLK_f:
				{
					tiles.changeTexture(Season::SPRING);
					buildings.changeWeather(false);
					break;
				}
			}
#endif /*< DEVEL_BUILD */
			break;
		}
		case SDL_WINDOWEVENT:
		{
			plog_verbose("Window event received.");
			if (SDL_WINDOWEVENT_FOCUS_LOST == event.window.event)
			{
				plog_trace("Window lost focus.");
				click = { .x = -1, .y = -1 };
				cursor.updatePosition(click);
				menu.handleHover(click, faction.getFaction());
			}
			break;
		}
		case SDL_QUIT:
		{
			handleQuit();
			break;
		}
		default:
		{
			plog_verbose("Event received but not handled. (type: %" PRIu32 ")", event.type);
			break;
		}
	}
}

void Map1::handleButtonDown(void) noexcept
{
	Coordinate	   click	  = { .x = 0, .y = 0 };
	const uint32_t mouseState = SDL_GetMouseState(&click.x, &click.y);
	Action		   action	  = Action::NOTHING;

	plog_trace("Mouse (%" PRIu32 ") was clicked. (coordinates: %" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);
#ifdef PLOG_STRIP_TRACE
	(void)mouseState;
#endif /*< PLOG_STRIP_TRACE */

	if (1 != SDL_BUTTON(mouseState))
	{
		plog_trace("Mouse click is not left click.");
		return;
	}

	chat.handleClick(click, renderer);

	action = menu.handleClick(click, game.getMenuMode(click.x, click.y), faction.getFaction());
	switch (action)
	{
		case Action::NOTHING:
		{
			break;
		}
		case Action::RECRUIT_INFANTRY:
		{
			if (true == game.isRecruitPossible(hobGame::Unit::INFANTRY))
			{
				try
				{
					units.add(hobGame::Unit::INFANTRY, faction.getFaction());
				}
				catch (const std::exception& exception)
				{
					plog_error("Failed to add infantry unit!");
				}
			}
			break;
		}
		case Action::RECRUIT_RANGED:
		{
			break;
		}
		default:
		{
			break;
		}
	}
}

void Map1::handleButtonUp(void) noexcept
{
	Coordinate	   click	  = { .x = 0, .y = 0 };
	const uint32_t mouseState = SDL_GetMouseState(&click.x, &click.y);

	plog_trace("Mouse (%" PRIu32 ") was released. (coordinates: %" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);
#ifdef PLOG_STRIP_TRACE
	(void)mouseState;
#endif /*< PLOG_STRIP_TRACE */
}

void Map1::handleMouseMotion(void) noexcept
{
	Coordinate	   click	  = { .x = 0, .y = 0 };
	const uint32_t mouseState = SDL_GetMouseState(&click.x, &click.y);

	plog_verbose("Mouse (%" PRIu32 ") was moved. (coordinates: %" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);
#ifdef PLOG_STRIP_VERBOSE
	(void)mouseState;
#endif /*< PLOG_STRIP_VERBOSE */

	cursor.updatePosition(click);
	cursor.setTexture(game.getCursorType(click.x, click.y));
	menu.handleHover(click, faction.getFaction());
}

void Map1::handleQuit(void) noexcept
{
	hobServer::Message message = { .type = hobServer::MessageType::END_COMMUNICATION, .payload = {} };

	plog_info("Command to quit game was given!");

	socket.sendUpdate(message);
	stop(Scene::QUIT);
}

void Map1::receivingFunction(void) noexcept
{
	hobServer::Message receivedMessage = {};

	plog_trace("Update messages are being received.");
	while (true == receivingUpdates.load())
	{
		socket.receiveUpdate(receivedMessage);
		switch (receivedMessage.type)
		{
			case hobServer::MessageType::PING:
			{
				plog_trace("Ping message received.");
				ping->update(socket);
				break;
			}
			case hobServer::MessageType::TIME:
			{
				plog_verbose("Time update message received. (time left: %" PRIu16 ")", receivedMessage.payload.timeLeft);
				if (false == faction.getFaction() && false == game.getTurn())
				{
					menu.updateTimer(receivedMessage.payload.timeLeft, true);
					break;
				}
				menu.updateTimer(receivedMessage.payload.timeLeft, faction.getFaction() && game.getTurn());
				break;
			}
			case hobServer::MessageType::TEXT:
			{
				plog_trace("Text message received. (message: %s)", receivedMessage.payload.text);
				chat.receivedMessage(receivedMessage.payload.text);
				break;
			}
			case hobServer::MessageType::END_TURN:
			{
				plog_info("End turn message received!");
				game.endTurn();
				menu.updateGold(game.getGold());
				break;
			}
			case hobServer::MessageType::ENCRYPT_KEY:
			{
				plog_trace("Encrypt key message received.");
				chat.receivedEncryptKey(receivedMessage.payload.encryptKey, socket);
				break;
			}
			case hobServer::MessageType::END_COMMUNICATION:
			{
				plog_info("End communication message received!");
				receivingUpdates.store(false);
				stop(Scene::MAIN_MENU);
				break;
			}
			case hobServer::MessageType::VERSION:
			{
				plog_error("Version message type received! (opponent version: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ")", receivedMessage.payload.version.getMajor(),
						   receivedMessage.payload.version.getMinor(), receivedMessage.payload.version.getPatch());
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
