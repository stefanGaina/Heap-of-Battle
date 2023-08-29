/******************************************************************************************************
 * @file hob_LocalMenu.cpp                                                                            *
 * @date:      @author:                   Reason for change:                                          *
 * 29.08.2023  Gaina Stefan               Initial version.                                            *
 * @details This file implements the class defined in hob_LocalMenu.hpp.                              *
 * @todo Offer a way for IP address of the host to be inputed (after pressing connect).               *
 * @bug When waiting for opponent to connect if connect button is pressed quickly it results in a     *
 * crash. That's why it is disabled until no longer hosting. This will be changed when input of IP    *
 * address will be introduced.                                                                        *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_LocalMenu.hpp"
#include "hob_MenuCommon.hpp"
#include "hob_Cursor.hpp"
#include "hob_Music.hpp"
#include "hob_Socket.hpp"
#include "hob_Server.hpp"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief Full file path of an image used by the local menu.
 * @param name: The name of the image (without extension).
*/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("local_menu/" name)

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

LocalMenu::LocalMenu(void) noexcept
	: Loop{}
	, TextureInitializer
	{
		{
			MENU_TEXTURE_PATH_BACKGROUND       ,
			MENU_TEXTURE_PATH_BUTTON_IDLE      ,
			MENU_TEXTURE_PATH_BUTTON_ACTIVE    ,
			MENU_TEXTURE_PATH_BUTTON_PRESSED   ,
			TEXTURE_FILE_PATH("host_game_text"),
			TEXTURE_FILE_PATH("connect_text")  ,
			TEXTURE_FILE_PATH("back_text")     ,
			TEXTURE_FILE_PATH("waiting_text")  ,
			TEXTURE_FILE_PATH("connecting_text")
		},
		{
			LOCAL_MENU_TEXTURE_INDEX_BACKGROUND    ,
			LOCAL_MENU_TEXTURE_INDEX_BUTTON_IDLE   ,
			LOCAL_MENU_TEXTURE_INDEX_BUTTON_IDLE   ,
			LOCAL_MENU_TEXTURE_INDEX_BUTTON_IDLE   ,
			LOCAL_MENU_TEXTURE_INDEX_HOST_GAME_TEXT,
			LOCAL_MENU_TEXTURE_INDEX_CONNECT_TEXT  ,
			LOCAL_MENU_TEXTURE_INDEX_BACK_TEXT
		},
		{
			{
				{ 0L                                          , 0L                                       , SCREEN_WIDTH       , SCREEN_HEIGHT   },
				{ BAR_HORIZONTAL_CENTERED                     , 3L * SCALE + SCALE / 2L                  , BAR_WIDTH          , BAR_HEIGHT      },
				{ BAR_HORIZONTAL_CENTERED                     , 3L * SCALE + SCALE / 2L + 4L * SCALE / 3L, BAR_WIDTH          , BAR_HEIGHT      },
				{ BAR_HORIZONTAL_CENTERED                     , 3L * SCALE + SCALE / 2L + 8L * SCALE / 3L, BAR_WIDTH          , BAR_HEIGHT      },
				{ BAR_HORIZONTAL_CENTERED + SCALE             , 4L * SCALE + SCALE / 4L                  , BAR_TEXT_WIDTH     , BAR_TEXT_HEIGHT },
				{ BAR_HORIZONTAL_CENTERED + SCALE             , 4L * SCALE + SCALE / 4L + 4L * SCALE / 3L, BAR_TEXT_WIDTH     , BAR_TEXT_HEIGHT },
				{ BAR_HORIZONTAL_CENTERED + SCALE + SCALE / 2L, 6L * SCALE + 2L * SCALE / 3L + SCALE / 4L, BAR_TEXT_WIDTH / 2L, BAR_TEXT_HEIGHT }
			}
		}
	}
	, SoundInitializer
	{
		{
			MENU_SOUND_PATH_CLICK,
			HOB_SOUNDS_FILE_PATH("error")
		}
	}
	, m_queue               {}
	, m_waitConnectionThread{}
	, m_receivingThread     {}
	, m_receivingUpdates    { false }
	, m_clickDownIndex      { 0ULL }
{
	plog_trace("Local menu is being constructed. (size: %" PRIu64 ") (1: %" PRIu64 ") (2: %" PRIu64 ") (3: %" PRIu64 ") (4: %" PRIu64 ") (5: %" PRIu64 ")",
		sizeof(*this), sizeof(m_queue), sizeof(m_waitConnectionThread), sizeof(m_receivingThread), sizeof(m_receivingUpdates), sizeof(m_clickDownIndex));

	Music::getInstance().start(Song::MAIN_MENU);
	Cursor::getInstance().setFaction(true);
	Cursor::getInstance().setTexture(CursorType::IDLE);
}

LocalMenu::~LocalMenu(void) noexcept
{
	plog_trace("Local menu is being destructed.");

	m_receivingUpdates.store(false);
	joinReceivingThread();
	joinWaitConnectionThread();
}

void LocalMenu::draw(void) noexcept
{
	ConnectionStatus connectionStatus = ConnectionStatus::ABORTED;

	plog_verbose("Local menu is being drawn.");
	while (false == m_queue.isEmpty())
	{
		connectionStatus = m_queue.get();
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
				m_soundContainer[LOCAL_MENU_SOUND_INDEX_ERROR].play();

				joinWaitConnectionThread();
				Server::getInstance().close();

				m_componentContainer[LOCAL_MENU_COMPONENT_INDEX_HOST_GAME_TEXT].updateTexture(m_textureContainer[LOCAL_MENU_TEXTURE_INDEX_HOST_GAME_TEXT]);
				m_componentContainer[LOCAL_MENU_COMPONENT_INDEX_CONNECT_TEXT].updateTexture(m_textureContainer[LOCAL_MENU_TEXTURE_INDEX_CONNECT_TEXT]);
				break;
			}
			case ConnectionStatus::ABORTED:
			{
				plog_info("Connection status aborted received!");
				m_soundContainer[LOCAL_MENU_SOUND_INDEX_ERROR].play();

				Socket::getInstance().close();
				Server::getInstance().close();
				joinReceivingThread();

				m_componentContainer[LOCAL_MENU_COMPONENT_INDEX_HOST_GAME_TEXT].updateTexture(m_textureContainer[LOCAL_MENU_TEXTURE_INDEX_HOST_GAME_TEXT]);
				m_componentContainer[LOCAL_MENU_COMPONENT_INDEX_CONNECT_TEXT].updateTexture(m_textureContainer[LOCAL_MENU_TEXTURE_INDEX_CONNECT_TEXT]);
				break;
			}
			default:
			{
				plog_error("Invalid connection status received! (status: %" PRId32 ")", static_cast<int32_t>(connectionStatus));
				break;
			}
		}
	}
	TextureInitializer::draw();
}

void LocalMenu::handleEvent(const SDL_Event& event) noexcept
{
	Coordinate click      = {};
	uint32_t   mouseState = 0UL;
	size_t     index      = 0ULL;

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

			for (index = LOCAL_MENU_COMPONENT_INDEX_BUTTON_HOST_GAME; index <= LOCAL_MENU_COMPONENT_INDEX_BUTTON_BACK; ++index)
			{
				if (m_componentContainer[index].isMouseInside(click, BAR_CORRECTIONS))
				{
					plog_verbose("Bar is pressed. (index: %" PRIu64 ")", index);
					m_componentContainer[index].updateTexture(m_textureContainer[LOCAL_MENU_TEXTURE_INDEX_BUTTON_PRESSED]);
					m_soundContainer[LOCAL_MENU_SOUND_INDEX_CLICK].play();
					m_clickDownIndex = index;
					return;
				}
				m_componentContainer[index].updateTexture(m_textureContainer[LOCAL_MENU_TEXTURE_INDEX_BUTTON_IDLE]);
			}
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			mouseState = SDL_GetMouseState(&click.x, &click.y);
			plog_trace("Mouse (%" PRIu32 ") was released. (coordinates: %" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);

			if (0ULL != m_clickDownIndex && m_componentContainer[m_clickDownIndex].isMouseInside(click, BAR_CORRECTIONS))
			{
				switch (m_clickDownIndex)
				{
					case LOCAL_MENU_COMPONENT_INDEX_BUTTON_HOST_GAME:
					{
						plog_debug("Host game bar was selected, clicked and released.");
						if (m_componentContainer[LOCAL_MENU_COMPONENT_INDEX_CONNECT_TEXT] == m_textureContainer[LOCAL_MENU_TEXTURE_INDEX_CONNECTING_TEXT])
						{
							plog_debug("Aborting the connection to the opponent's server.");

							Socket::getInstance().close();
							joinWaitConnectionThread();

							while (false == m_queue.isEmpty())
							{
								plog_trace("Ignored status from queue.");
								(void)m_queue.get();
							}
							m_componentContainer[LOCAL_MENU_COMPONENT_INDEX_CONNECT_TEXT].updateTexture(m_textureContainer[LOCAL_MENU_TEXTURE_INDEX_CONNECT_TEXT]);
						}
						if (m_componentContainer[LOCAL_MENU_COMPONENT_INDEX_HOST_GAME_TEXT] == m_textureContainer[LOCAL_MENU_TEXTURE_INDEX_HOST_GAME_TEXT])
						{
							plog_debug("Hosting the game by running the server locally.");
							try
							{
								Server::getInstance().create();
							}
							catch (const std::exception& exception)
							{
								plog_error("Failed to create local server!");
								m_soundContainer[LOCAL_MENU_SOUND_INDEX_ERROR].play();
								break;
							}
							m_componentContainer[LOCAL_MENU_COMPONENT_INDEX_HOST_GAME_TEXT].updateTexture(m_textureContainer[LOCAL_MENU_TEXTURE_INDEX_WAITING_TEXT]);
							m_waitConnectionThread = std::thread{ std::bind(&LocalMenu::waitConnectionFunction, this, "127.0.0.1") };
							break;
						}
						if (m_componentContainer[LOCAL_MENU_COMPONENT_INDEX_HOST_GAME_TEXT] == m_textureContainer[LOCAL_MENU_TEXTURE_INDEX_WAITING_TEXT])
						{
							plog_debug("Aborting the host.");

							m_receivingUpdates.store(false);
							Socket::getInstance().close();
							Server::getInstance().close();
							joinReceivingThread();
							m_componentContainer[LOCAL_MENU_COMPONENT_INDEX_HOST_GAME_TEXT].updateTexture(m_textureContainer[LOCAL_MENU_TEXTURE_INDEX_HOST_GAME_TEXT]);
							break;
						}
						plog_error("First button text is not host game or waiting!"); 
						break;
					}
					case LOCAL_MENU_COMPONENT_INDEX_BUTTON_CONNECT:
					{
						plog_debug("Connect bar was selected, clicked and released.");
						if (m_componentContainer[LOCAL_MENU_COMPONENT_INDEX_CONNECT_TEXT] == m_textureContainer[LOCAL_MENU_TEXTURE_INDEX_CONNECTING_TEXT])
						{
							plog_debug("Connection has been interruped by the user.");
							Socket::getInstance().close();
							joinWaitConnectionThread();
							m_componentContainer[LOCAL_MENU_COMPONENT_INDEX_CONNECT_TEXT].updateTexture(m_textureContainer[LOCAL_MENU_TEXTURE_INDEX_CONNECT_TEXT]);
							break;
						}
						if (m_componentContainer[LOCAL_MENU_COMPONENT_INDEX_HOST_GAME_TEXT] == m_textureContainer[LOCAL_MENU_TEXTURE_INDEX_WAITING_TEXT])
						{
							plog_debug("Connecting while hosting is not supported.");
							m_soundContainer[LOCAL_MENU_SOUND_INDEX_ERROR].play();
							break;
						}
						m_waitConnectionThread = std::thread{ std::bind(&LocalMenu::waitConnectionFunction, this, "25.20.35.65") }; // TODO: Update this
						m_componentContainer[LOCAL_MENU_COMPONENT_INDEX_CONNECT_TEXT].updateTexture(m_textureContainer[LOCAL_MENU_TEXTURE_INDEX_CONNECTING_TEXT]);
						break;
					}
					case LOCAL_MENU_COMPONENT_INDEX_BUTTON_BACK:
					{
						plog_debug("Back bar was selected, clicked and released.");
						m_receivingUpdates.store(false);
						Socket::getInstance().close();
						Server::getInstance().close();
						stop(Scene::MAIN_MENU);
						break;
					}
					default:
					{
						plog_error("Invalid click down index! (index: %" PRIu64 ")", m_clickDownIndex);
						break;
					}
				}
			}
			m_clickDownIndex = 0ULL;
			// break; <- omitted so buttons get reselected appropriately.
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

			for (index = LOCAL_MENU_COMPONENT_INDEX_BUTTON_HOST_GAME; index <= LOCAL_MENU_COMPONENT_INDEX_BUTTON_BACK; ++index)
			{
				if (m_componentContainer[index].isMouseInside(click, BAR_CORRECTIONS))
				{
					plog_verbose("Bar is selected. (index: %" PRIu64 ")", index);
					m_componentContainer[index].updateTexture(m_textureContainer[LOCAL_MENU_TEXTURE_INDEX_BUTTON_ACTIVE]);
					return;
				}
				m_componentContainer[index].updateTexture(m_textureContainer[LOCAL_MENU_TEXTURE_INDEX_BUTTON_IDLE]);
			}
			break;
		}
		case SDL_KEYDOWN:
		{
			// To test server error while waiting for opponent connection.
			Socket::getInstance().close();
			// TODO: give a way to input IP address
			break;
		}
		case SDL_QUIT:
		{
			plog_info("Command to quit game was given!");
			stop(Scene::QUIT);
			Socket::getInstance().close();
			Server::getInstance().close();
			break;
		}
		default:
		{
			plog_verbose("Event received but not handled. (type: %" PRIu32 ")", event.type);
			break;
		}
	}
}

void LocalMenu::joinReceivingThread(void) noexcept
{
	plog_trace("Checking if receiving thread is joinable.");
	if (true == m_receivingThread.joinable())
	{
		plog_debug("Receiving thread is being joined.");
		m_receivingThread.join();
		plog_debug("Receiving thread has joined.");
	}
}

void LocalMenu::joinWaitConnectionThread(void) noexcept
{
	plog_trace("Checking if wait connection thread is joinable.");
	if (true == m_waitConnectionThread.joinable())
	{
		plog_debug("Wait connection thread is being joined.");
		m_waitConnectionThread.join();
		plog_debug("Wait connection thread has joined.");
	}
}

void LocalMenu::receivingFunction(void) noexcept
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
				plog_info("First ping message received.");
				pingReceived();

				m_receivingUpdates.store(false);
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
				if (true == m_receivingUpdates.load())
				{
					m_receivingUpdates.store(false);
					m_queue.put(ConnectionStatus::ABORTED);
				}
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

void LocalMenu::waitConnectionFunction(const std::string ipAddress) noexcept
{
	plog_info("Waiting for client connection to be established! (address: %s)", ipAddress.c_str());
	try
	{
		Socket::getInstance().create(ipAddress);
	}
	catch (const std::exception& exception)
	{
		plog_error("Failed to create client socket!");
		m_queue.put(ConnectionStatus::FAILED);
		return;
	}

	m_receivingUpdates.store(true);
	m_receivingThread = std::thread{ std::bind(&LocalMenu::receivingFunction, this) };
	m_queue.put(ConnectionStatus::SUCCESS);
}

} /*< namespace hob */
