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
 * @file hob_LocalMenu.cpp
 * @author Gaina Stefan
 * @date 29.08.2023
 * @brief This file implements the class defined in hob_LocalMenu.hpp.
 * @todo Offer a way for IP address of the host to be inputed (after pressing connect).
 * @bug When waiting for opponent to connect if connect button is pressed quickly it results in a
 * crash. That's why it is disabled until no longer hosting. This will be changed when input of IP
 * address will be introduced.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <plog.h>

#include "hob_LocalMenu.hpp"
#include "hob_MenuCommon.hpp"
#include "hob_Music.hpp"
#include "hob_Socket.hpp"
#include "hob_Faction.hpp"

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Full file path of an image used by the local menu.
 * @param name: The name of the image (without extension).
 * @return The full file path.
 *****************************************************************************************************/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("local_menu/" name)

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

LocalMenu::LocalMenu(SDL_Renderer* const renderer,
					 Cursor&			 cursor,
					 Ping* const		 ping,
					 Music&				 music,
					 Faction&			 faction,
					 hobServer::Server&	 server,
					 Socket&			 socket) noexcept
	: Loop{ renderer, cursor, ping }
	, TextureInitializer{ {
							  MENU_TEXTURE_PATH_BACKGROUND,		   /*< 0 */
							  MENU_TEXTURE_PATH_BUTTON_IDLE,	   /*< 1 */
							  MENU_TEXTURE_PATH_BUTTON_ACTIVE,	   /*< 2 */
							  MENU_TEXTURE_PATH_BUTTON_PRESSED,	   /*< 3 */
							  TEXTURE_FILE_PATH("host_game_text"), /*< 4 */
							  TEXTURE_FILE_PATH("connect_text"),   /*< 5 */
							  TEXTURE_FILE_PATH("back_text"),	   /*< 6 */
							  TEXTURE_FILE_PATH("waiting_text"),   /*< 7 */
							  TEXTURE_FILE_PATH("connecting_text") /*< 8 */
						  },
						  {
							  LOCAL_MENU_TEXTURE_INDEX_BACKGROUND,	   /*< 0 */
							  LOCAL_MENU_TEXTURE_INDEX_BUTTON_IDLE,	   /*< 1 */
							  LOCAL_MENU_TEXTURE_INDEX_BUTTON_IDLE,	   /*< 2 */
							  LOCAL_MENU_TEXTURE_INDEX_BUTTON_IDLE,	   /*< 3 */
							  LOCAL_MENU_TEXTURE_INDEX_HOST_GAME_TEXT, /*< 4 */
							  LOCAL_MENU_TEXTURE_INDEX_CONNECT_TEXT,   /*< 5 */
							  LOCAL_MENU_TEXTURE_INDEX_BACK_TEXT	   /*< 6 */
						  },
						  { {
							  { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT },																					  /*< 0 */
							  { BAR_HORIZONTAL_CENTERED, 3 * SCALE + SCALE / 2, BAR_WIDTH, BAR_HEIGHT },												  /*< 1 */
							  { BAR_HORIZONTAL_CENTERED, 3 * SCALE + SCALE / 2 + 4 * SCALE / 3, BAR_WIDTH, BAR_HEIGHT },								  /*< 2 */
							  { BAR_HORIZONTAL_CENTERED, 3 * SCALE + SCALE / 2 + 8 * SCALE / 3, BAR_WIDTH, BAR_HEIGHT },								  /*< 3 */
							  { BAR_HORIZONTAL_CENTERED + SCALE, 4 * SCALE + SCALE / 4, BAR_TEXT_WIDTH, BAR_TEXT_HEIGHT },								  /*< 4 */
							  { BAR_HORIZONTAL_CENTERED + SCALE, 4 * SCALE + SCALE / 4 + 4 * SCALE / 3, BAR_TEXT_WIDTH, BAR_TEXT_HEIGHT },				  /*< 5 */
							  { BAR_HORIZONTAL_CENTERED + SCALE + SCALE / 2, 6 * SCALE + 2 * SCALE / 3 + SCALE / 4, BAR_TEXT_WIDTH / 2, BAR_TEXT_HEIGHT } /*< 6 */
						  } },
						  renderer }
	, SoundInitializer{ { MENU_SOUND_PATH_CLICK, HOB_SOUNDS_FILE_PATH("error") } }
	, queue{}
	, waitConnectionThread{}
	, receivingThread{}
	, receivingUpdates{ false }
	, clickDownIndex{ 0UL }
	, music{ music }
	, faction{ faction }
	, server{ server }
	, socket{ socket }
{
	plog_trace("Local menu is being constructed.");
	plog_assert(nullptr != ping);

	music.start(Song::MAIN_MENU);
	cursor.setFaction(true);
	cursor.setTexture(hobGame::CursorType::IDLE);
}

LocalMenu::~LocalMenu(void) noexcept
{
	plog_trace("Local menu is being destructed.");

	receivingUpdates.store(false);
	joinReceivingThread();
	joinWaitConnectionThread();

	if (componentContainer[LOCAL_MENU_COMPONENT_INDEX_HOST_GAME_TEXT] == textureContainer[LOCAL_MENU_TEXTURE_INDEX_WAITING_TEXT])
	{
		faction.setFaction(true);
	}
	else if (componentContainer[LOCAL_MENU_COMPONENT_INDEX_CONNECT_TEXT] == textureContainer[LOCAL_MENU_TEXTURE_INDEX_CONNECTING_TEXT])
	{
		faction.setFaction(false);
	}
}

void LocalMenu::draw(void) noexcept
{
	plog_verbose("Local menu is being drawn.");
	plog_assert(nullptr != this);

	handleQueue();
	TextureInitializer::draw(renderer);
}

void LocalMenu::handleEvent(const SDL_Event& event) noexcept
{
	plog_verbose("Event is being handled.");
	plog_assert(nullptr != this);

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
			handleMouseMotion();
			break;
		}
		case SDL_MOUSEMOTION:
		{
			handleMouseMotion();
			break;
		}
		case SDL_KEYDOWN:
		{
			// To test server error while waiting for opponent connection.
			socket.close();
			// TODO: give a way to input IP address
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

void LocalMenu::handleButtonDown(void) noexcept
{
	Coordinate	   click	  = { .x = 0, .y = 0 };
	const uint32_t mouseState = SDL_GetMouseState(&click.x, &click.y);
	size_t		   index	  = 0UL;

	plog_trace("Mouse (%" PRIu32 ") was clicked. (coordinates: %" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);
	plog_assert(nullptr != this);

	if (1 != SDL_BUTTON(mouseState))
	{
		plog_trace("Mouse click is not left click.");
		return;
	}

	for (index = LOCAL_MENU_COMPONENT_INDEX_BUTTON_HOST_GAME; index <= LOCAL_MENU_COMPONENT_INDEX_BUTTON_BACK; ++index)
	{
		if (componentContainer[index].isMouseInside(click, BAR_CORRECTIONS))
		{
			plog_verbose("Bar is pressed. (index: %" PRIu64 ")", index);
			componentContainer[index].updateTexture(textureContainer[LOCAL_MENU_TEXTURE_INDEX_BUTTON_PRESSED]);
			soundContainer[LOCAL_MENU_SOUND_INDEX_CLICK].play();
			clickDownIndex = index;
			return;
		}
		componentContainer[index].updateTexture(textureContainer[LOCAL_MENU_TEXTURE_INDEX_BUTTON_IDLE]);
	}
}

void LocalMenu::handleButtonUp(void) noexcept
{
	Coordinate	   click	  = { .x = 0, .y = 0 };
	const uint32_t mouseState = SDL_GetMouseState(&click.x, &click.y);

	plog_trace("Mouse (%" PRIu32 ") was released. (coordinates: %" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);
	plog_assert(nullptr != this);
#ifdef PLOG_STRIP_TRACE
	(void)mouseState;
#endif /*< PLOG_STRIP_TRACE */

	if (0UL != clickDownIndex && componentContainer[clickDownIndex].isMouseInside(click, BAR_CORRECTIONS))
	{
		switch (clickDownIndex)
		{
			case LOCAL_MENU_COMPONENT_INDEX_BUTTON_HOST_GAME:
			{
				plog_debug("Host game bar was selected, clicked and released.");
				if (componentContainer[LOCAL_MENU_COMPONENT_INDEX_CONNECT_TEXT] == textureContainer[LOCAL_MENU_TEXTURE_INDEX_CONNECTING_TEXT])
				{
					plog_debug("Aborting the connection to the opponent's server.");

					socket.close();
					joinWaitConnectionThread();

					while (false == queue.isEmpty())
					{
						plog_trace("Ignored status from queue.");
						(void)queue.pop();
					}
					componentContainer[LOCAL_MENU_COMPONENT_INDEX_CONNECT_TEXT].updateTexture(textureContainer[LOCAL_MENU_TEXTURE_INDEX_CONNECT_TEXT]);
				}
				if (componentContainer[LOCAL_MENU_COMPONENT_INDEX_HOST_GAME_TEXT] == textureContainer[LOCAL_MENU_TEXTURE_INDEX_HOST_GAME_TEXT])
				{
					plog_debug("Hosting the game by running the server locally.");
					try
					{
						server.runAsync(8787U, 40U);
					}
					catch (...)
					{
						plog_error("Failed to create the local server!");
						soundContainer[LOCAL_MENU_SOUND_INDEX_ERROR].play();
						break;
					}

					componentContainer[LOCAL_MENU_COMPONENT_INDEX_HOST_GAME_TEXT].updateTexture(textureContainer[LOCAL_MENU_TEXTURE_INDEX_WAITING_TEXT]);
					waitConnectionThread = std::thread{ std::bind(&LocalMenu::waitConnectionFunction, this, "127.0.0.1") };
					break;
				}
				if (componentContainer[LOCAL_MENU_COMPONENT_INDEX_HOST_GAME_TEXT] == textureContainer[LOCAL_MENU_TEXTURE_INDEX_WAITING_TEXT])
				{
					plog_debug("Aborting the host.");

					receivingUpdates.store(false);
					socket.close();
					server.stop();
					joinReceivingThread();
					componentContainer[LOCAL_MENU_COMPONENT_INDEX_HOST_GAME_TEXT].updateTexture(textureContainer[LOCAL_MENU_TEXTURE_INDEX_HOST_GAME_TEXT]);
					break;
				}
				plog_error("First button text is not host game or waiting!");
				break;
			}
			case LOCAL_MENU_COMPONENT_INDEX_BUTTON_CONNECT:
			{
				plog_debug("Connect bar was selected, clicked and released.");
				if (componentContainer[LOCAL_MENU_COMPONENT_INDEX_CONNECT_TEXT] == textureContainer[LOCAL_MENU_TEXTURE_INDEX_CONNECTING_TEXT])
				{
					plog_debug("Connection has been interruped by the user.");
					socket.close();
					joinWaitConnectionThread();
					componentContainer[LOCAL_MENU_COMPONENT_INDEX_CONNECT_TEXT].updateTexture(textureContainer[LOCAL_MENU_TEXTURE_INDEX_CONNECT_TEXT]);
					break;
				}
				if (componentContainer[LOCAL_MENU_COMPONENT_INDEX_HOST_GAME_TEXT] == textureContainer[LOCAL_MENU_TEXTURE_INDEX_WAITING_TEXT])
				{
					plog_debug("Connecting while hosting is not supported.");
					soundContainer[LOCAL_MENU_SOUND_INDEX_ERROR].play();
					break;
				}
				waitConnectionThread = std::thread{ std::bind(&LocalMenu::waitConnectionFunction, this, "127.0.0.1") }; // TODO: Update this
				componentContainer[LOCAL_MENU_COMPONENT_INDEX_CONNECT_TEXT].updateTexture(textureContainer[LOCAL_MENU_TEXTURE_INDEX_CONNECTING_TEXT]);
				break;
			}
			case LOCAL_MENU_COMPONENT_INDEX_BUTTON_BACK:
			{
				plog_debug("Back bar was selected, clicked and released.");
				receivingUpdates.store(false);
				socket.close();
				server.stop();
				stop(Scene::MAIN_MENU);
				break;
			}
			default:
			{
				plog_error("Invalid click down index! (index: %" PRIu64 ")", clickDownIndex);
				break;
			}
		}
	}
	clickDownIndex = 0UL;
}

void LocalMenu::handleMouseMotion(void) noexcept
{
	Coordinate	   click	  = { .x = 0, .y = 0 };
	const uint32_t mouseState = SDL_GetMouseState(&click.x, &click.y);
	size_t		   index	  = 0UL;

	plog_verbose("Mouse (%" PRIu32 ") was moved. (coordinates: %" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);
	plog_assert(nullptr != this);

	cursor.updatePosition(click);

	if (1 == SDL_BUTTON(mouseState))
	{
		plog_verbose("Mouse left click is pressed.");
		return;
	}

	for (index = LOCAL_MENU_COMPONENT_INDEX_BUTTON_HOST_GAME; index <= LOCAL_MENU_COMPONENT_INDEX_BUTTON_BACK; ++index)
	{
		if (componentContainer[index].isMouseInside(click, BAR_CORRECTIONS))
		{
			plog_verbose("Bar is selected. (index: %" PRIu64 ")", index);
			componentContainer[index].updateTexture(textureContainer[LOCAL_MENU_TEXTURE_INDEX_BUTTON_ACTIVE]);
			return;
		}
		componentContainer[index].updateTexture(textureContainer[LOCAL_MENU_TEXTURE_INDEX_BUTTON_IDLE]);
	}
}

void LocalMenu::handleQuit(void) noexcept
{
	plog_info("Command to quit game was given!");
	plog_assert(nullptr != this);

	stop(Scene::QUIT);
	socket.close();
	server.stop();
}

void LocalMenu::handleQueue(void) noexcept
{
	ConnectionStatus connectionStatus = ConnectionStatus::ABORTED;

	plog_verbose("Queue is being handled.");
	plog_assert(nullptr != this);

	while (false == queue.isEmpty())
	{
		connectionStatus = queue.pop();
		switch (connectionStatus)
		{
			case ConnectionStatus::SUCCESS:
			{
				plog_info("Connection status success received!");
				joinWaitConnectionThread();
				break;
			}
			case ConnectionStatus::FAILED:
			{
				plog_info("Connection status failed received!");
				soundContainer[LOCAL_MENU_SOUND_INDEX_ERROR].play();

				joinWaitConnectionThread();
				server.stop();

				componentContainer[LOCAL_MENU_COMPONENT_INDEX_HOST_GAME_TEXT].updateTexture(textureContainer[LOCAL_MENU_TEXTURE_INDEX_HOST_GAME_TEXT]);
				componentContainer[LOCAL_MENU_COMPONENT_INDEX_CONNECT_TEXT].updateTexture(textureContainer[LOCAL_MENU_TEXTURE_INDEX_CONNECT_TEXT]);
				break;
			}
			case ConnectionStatus::ABORTED:
			{
				plog_info("Connection status aborted received!");
				soundContainer[LOCAL_MENU_SOUND_INDEX_ERROR].play();

				socket.close();
				server.stop();
				joinReceivingThread();

				componentContainer[LOCAL_MENU_COMPONENT_INDEX_HOST_GAME_TEXT].updateTexture(textureContainer[LOCAL_MENU_TEXTURE_INDEX_HOST_GAME_TEXT]);
				componentContainer[LOCAL_MENU_COMPONENT_INDEX_CONNECT_TEXT].updateTexture(textureContainer[LOCAL_MENU_TEXTURE_INDEX_CONNECT_TEXT]);
				break;
			}
			default:
			{
				plog_error("Invalid connection status received! (status: %" PRId32 ")", static_cast<int32_t>(connectionStatus));
				plog_assert(false);
				break;
			}
		}
	}
}

void LocalMenu::joinReceivingThread(void) noexcept
{
	plog_trace("Checking if receiving thread is joinable.");
	plog_assert(nullptr != this);

	if (true == receivingThread.joinable())
	{
		plog_debug("Receiving thread is being joined.");
		receivingThread.join();
		plog_debug("Receiving thread has joined.");
	}
}

void LocalMenu::joinWaitConnectionThread(void) noexcept
{
	plog_trace("Checking if wait connection thread is joinable.");
	plog_assert(nullptr != this);

	if (true == waitConnectionThread.joinable())
	{
		plog_debug("Wait connection thread is being joined.");
		waitConnectionThread.join();
		plog_debug("Wait connection thread has joined.");
	}
}

void LocalMenu::receivingFunction(void) noexcept
{
	hobServer::Message receivedMessage = {};

	plog_trace("Update messages are being received.");
	plog_assert(nullptr != this);

	while (true == receivingUpdates.load())
	{
		socket.receiveUpdate(receivedMessage);
		switch (receivedMessage.type)
		{
			case hobServer::MessageType::PING:
			{
				plog_info("First ping message received.");
				ping->update(socket);

				receivingUpdates.store(false);
				stop(Scene::MAP_1);
				break;
			}
			case hobServer::MessageType::TIME:
			{
				plog_error("Time update message received. (time left: %" PRIu16 ")", receivedMessage.payload.timeLeft);
				break;
			}
			case hobServer::MessageType::TEXT:
			{
				plog_error("Text message received. (message: %s)", receivedMessage.payload.text);
				break;
			}
			case hobServer::MessageType::END_COMMUNICATION:
			{
				plog_info("End communication message received!");
				if (true == receivingUpdates.load())
				{
					receivingUpdates.store(false);
					queue.push(ConnectionStatus::ABORTED);
				}
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

void LocalMenu::waitConnectionFunction(const std::string ipAddress) noexcept
{
	plog_info("Waiting for client connection to be established! (address: %s)", ipAddress.c_str());
	plog_assert(nullptr != this);

	try
	{
		socket.create(ipAddress);
	}
	catch (...)
	{
		plog_error("Failed to create client socket!");
		queue.push(ConnectionStatus::FAILED);
		return;
	}

	receivingUpdates.store(true);
	receivingThread = std::thread{ std::bind(&LocalMenu::receivingFunction, this) };
	queue.push(ConnectionStatus::SUCCESS);
}

} /*< namespace hob */
