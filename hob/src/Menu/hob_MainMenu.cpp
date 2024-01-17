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
 * @file hob_MainMenu.cpp                                                                             *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 29.08.2023  Gaina Stefan               Refactored.                                                 *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file implements the class defined in hob_MainMenu.hpp.                               *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_MainMenu.hpp"
#include "hob_MenuCommon.hpp"
#include "hob_Music.hpp"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief Full file path of an image used by the main menu.
 * @param name: The name of the image (without extension).
 * @return The full file path.
*/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("main_menu/" name)

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

MainMenu::MainMenu(SDL_Renderer* const renderer, Cursor& cursor, Music& music) noexcept
	: Loop{ renderer, cursor, nullptr }
	, TextureInitializer
	{
		{
			MENU_TEXTURE_PATH_BACKGROUND        ,
			TEXTURE_FILE_PATH("logo")           ,
			TEXTURE_FILE_PATH("heap_text")      ,
			TEXTURE_FILE_PATH("of_text")        ,
			TEXTURE_FILE_PATH("battle_text")    ,
			TEXTURE_FILE_PATH("2_text")         ,
			MENU_TEXTURE_PATH_BUTTON_IDLE       ,
			MENU_TEXTURE_PATH_BUTTON_ACTIVE     ,
			MENU_TEXTURE_PATH_BUTTON_PRESSED    ,
			TEXTURE_FILE_PATH("start_game_text"),
			TEXTURE_FILE_PATH("settings_text")  ,
			TEXTURE_FILE_PATH("exit_text")
		},
		{
			MAIN_MENU_TEXTURE_INDEX_BACKGROUND     ,
			MAIN_MENU_TEXTURE_INDEX_LOGO           ,
			MAIN_MENU_TEXTURE_INDEX_HEAP_TEXT      ,
			MAIN_MENU_TEXTURE_INDEX_OF_TEXT        ,
			MAIN_MENU_TEXTURE_INDEX_BATTLE_TEXT    ,
			MAIN_MENU_TEXTURE_INDEX_2_TEXT         ,
			MAIN_MENU_TEXTURE_INDEX_BUTTON_IDLE    ,
			MAIN_MENU_TEXTURE_INDEX_BUTTON_IDLE    ,
			MAIN_MENU_TEXTURE_INDEX_BUTTON_IDLE    ,
			MAIN_MENU_TEXTURE_INDEX_START_GAME_TEXT,
			MAIN_MENU_TEXTURE_INDEX_SETTINGS_TEXT  ,
			MAIN_MENU_TEXTURE_INDEX_EXIT_TEXT
		},
		{
			{
				{ 0                                          , 0                                    , SCREEN_WIDTH      , SCREEN_HEIGHT     },
				{ 4 * SCALE                                  , 0                                    , 2 * BAR_WIDTH     , 2 * BAR_HEIGHT    },
				{ 4 * SCALE + SCALE / 2 + SCALE / 4          , SCALE + SCALE / 2                    , 3 * SCALE         , SCALE + SCALE / 2 },
				{ 7 * SCALE + SCALE / 2                      , 2 * SCALE                            , SCALE             , SCALE + SCALE / 2 },
				{ 8 * SCALE + SCALE / 3                      , SCALE + SCALE / 2                    , 3 * SCALE         , SCALE + SCALE / 2 },
				{ 7 * SCALE + SCALE / 2 - 2                  , SCALE / 2 - 8                        , SCALE             , SCALE + SCALE / 2 },
				{ BAR_HORIZONTAL_CENTERED                    , 3 * SCALE + SCALE / 2                , BAR_WIDTH         , BAR_HEIGHT        },
				{ BAR_HORIZONTAL_CENTERED                    , 3 * SCALE + SCALE / 2 + 4 * SCALE / 3, BAR_WIDTH         , BAR_HEIGHT        },
				{ BAR_HORIZONTAL_CENTERED                    , 3 * SCALE + SCALE / 2 + 8 * SCALE / 3, BAR_WIDTH         , BAR_HEIGHT        },
				{ BAR_HORIZONTAL_CENTERED + SCALE            , 4 * SCALE + SCALE / 4                , BAR_TEXT_WIDTH    , BAR_TEXT_HEIGHT   },
				{ BAR_HORIZONTAL_CENTERED + SCALE            , 4 * SCALE + SCALE / 4 + 4 * SCALE / 3, BAR_TEXT_WIDTH    , BAR_TEXT_HEIGHT   },
				{ BAR_HORIZONTAL_CENTERED + SCALE + SCALE / 2, 6 * SCALE + 2 * SCALE / 3 + SCALE / 4, BAR_TEXT_WIDTH / 2, BAR_TEXT_HEIGHT   }
			}
		},
		renderer
	}
	, SoundInitializer
	{
		{
			MENU_SOUND_PATH_CLICK
		}
	}
	, clickDownIndex{ 0UL }
	, music         { music }
{
	plog_trace("Main menu is being constructed.");

	music.start(Song::MAIN_MENU);
	cursor.setFaction(true);
	cursor.setTexture(hobGame::CursorType::IDLE);
}

void MainMenu::draw(void) noexcept
{
	plog_verbose("Main menu is being drawn.");
	TextureInitializer::draw(renderer);
}

void MainMenu::handleEvent(const SDL_Event& event) noexcept
{
	Coordinate click      = {};
	uint32_t   mouseState = 0U;
	size_t     index      = 0UL;

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

			for (index = MAIN_MENU_COMPONENT_INDEX_BUTTON_START_GAME; index <= MAIN_MENU_COMPONENT_INDEX_BUTTON_EXIT; ++index)
			{
				if (componentContainer[index].isMouseInside(click, BAR_CORRECTIONS))
				{
					plog_verbose("Bar is pressed. (index: %" PRIu64 ")", index);
					componentContainer[index].updateTexture(textureContainer[MAIN_MENU_TEXTURE_INDEX_BUTTON_PRESSED]);
					soundContainer[MAIN_MENU_SOUND_INDEX_CLICK].play();
					clickDownIndex = index;
					return;
				}
				componentContainer[index].updateTexture(textureContainer[MAIN_MENU_TEXTURE_INDEX_BUTTON_IDLE]);
			}
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			mouseState = SDL_GetMouseState(&click.x, &click.y);
			plog_trace("Mouse (%" PRIu32 ") was released. (coordinates: %" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);

			if (0UL != clickDownIndex && componentContainer[clickDownIndex].isMouseInside(click, BAR_CORRECTIONS))
			{
				switch (clickDownIndex)
				{
					case MAIN_MENU_COMPONENT_INDEX_BUTTON_START_GAME:
					{
						plog_debug("Start game bar was selected, clicked and released.");
						stop(Scene::LOCAL_MENU);
						break;
					}
					case MAIN_MENU_COMPONENT_INDEX_BUTTON_SETTINGS:
					{
						plog_debug("Settings bar was selected, clicked and released.");
						stop(Scene::SETTINGS);
						break;
					}
					case MAIN_MENU_COMPONENT_INDEX_BUTTON_EXIT:
					{
						plog_debug("Exit bar was selected, clicked and released.");
						stop(Scene::QUIT);
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
			// break; <- omitted so buttons get reselected appropriately.
		}
		case SDL_MOUSEMOTION:
		{
			mouseState = SDL_GetMouseState(&click.x, &click.y);
			plog_verbose("Mouse (%" PRIu32 ") was moved. (coordinates: %" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);

			cursor.updatePosition(click);

			if (1 == SDL_BUTTON(mouseState))
			{
				plog_verbose("Mouse left click is pressed.");
				return;
			}

			for (index = MAIN_MENU_COMPONENT_INDEX_BUTTON_START_GAME; index <= MAIN_MENU_COMPONENT_INDEX_BUTTON_EXIT; ++index)
			{
				if (componentContainer[index].isMouseInside(click, BAR_CORRECTIONS))
				{
					plog_verbose("Bar is selected. (index: %" PRIu64 ")", index);
					componentContainer[index].updateTexture(textureContainer[MAIN_MENU_TEXTURE_INDEX_BUTTON_ACTIVE]);
					return;
				}
				componentContainer[index].updateTexture(textureContainer[MAIN_MENU_TEXTURE_INDEX_BUTTON_IDLE]);
			}
			break;
		}
		case SDL_QUIT:
		{
			plog_info("Command to quit game was given!");
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

} /*< namespace hob */
