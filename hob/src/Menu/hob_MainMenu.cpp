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
 * @file hob_MainMenu.cpp
 * @author Gaina Stefan
 * @date 23.07.2023
 * @brief This file implements the class defined in hob_MainMenu.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <plog.h>

#include "hob_MainMenu.hpp"
#include "hob_MenuCommon.hpp"
#include "hob_Music.hpp"
#include "hob_Test.hpp"

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Full file path of an image used by the main menu.
 * @param name: The name of the image (without extension).
 * @return The full file path.
 *****************************************************************************************************/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("main_menu/" name)

/******************************************************************************************************
 * METHOD DEFINITION
 *****************************************************************************************************/

namespace hob
{

MainMenu::MainMenu(SDL_Renderer* const renderer, Cursor& cursor, Music& music) noexcept
	: Loop{ renderer, cursor, nullptr }
	, TextureInitializer
	{
		{
			MENU_TEXTURE_PATH_BACKGROUND        , /*< 0  */
			TEXTURE_FILE_PATH("logo")           , /*< 1  */
			TEXTURE_FILE_PATH("heap_text")      , /*< 2  */
			TEXTURE_FILE_PATH("of_text")        , /*< 3  */
			TEXTURE_FILE_PATH("battle_text")    , /*< 4  */
			TEXTURE_FILE_PATH("2_text")         , /*< 5  */
			MENU_TEXTURE_PATH_BUTTON_IDLE       , /*< 6  */
			MENU_TEXTURE_PATH_BUTTON_ACTIVE     , /*< 7  */
			MENU_TEXTURE_PATH_BUTTON_PRESSED    , /*< 8  */
			TEXTURE_FILE_PATH("start_game_text"), /*< 9  */
			TEXTURE_FILE_PATH("settings_text")  , /*< 10 */
			TEXTURE_FILE_PATH("exit_text")        /*< 11 */
		},
		{
			MAIN_MENU_TEXTURE_INDEX_BACKGROUND     , /*< 0  */
			MAIN_MENU_TEXTURE_INDEX_LOGO           , /*< 1  */
			MAIN_MENU_TEXTURE_INDEX_HEAP_TEXT      , /*< 2  */
			MAIN_MENU_TEXTURE_INDEX_OF_TEXT        , /*< 3  */
			MAIN_MENU_TEXTURE_INDEX_BATTLE_TEXT    , /*< 4  */
			MAIN_MENU_TEXTURE_INDEX_2_TEXT         , /*< 5  */
			MAIN_MENU_TEXTURE_INDEX_BUTTON_IDLE    , /*< 6  */
			MAIN_MENU_TEXTURE_INDEX_BUTTON_IDLE    , /*< 7  */
			MAIN_MENU_TEXTURE_INDEX_BUTTON_IDLE    , /*< 8  */
			MAIN_MENU_TEXTURE_INDEX_START_GAME_TEXT, /*< 9  */
			MAIN_MENU_TEXTURE_INDEX_SETTINGS_TEXT  , /*< 10 */
			MAIN_MENU_TEXTURE_INDEX_EXIT_TEXT        /*< 11 */
		},
		{
			{
				{ 0                                          , 0                                    , SCREEN_WIDTH      , SCREEN_HEIGHT     }, /*< 0  */
				{ 4 * SCALE                                  , 0                                    , 2 * BAR_WIDTH     , 2 * BAR_HEIGHT    }, /*< 1  */
				{ 4 * SCALE + SCALE / 2 + SCALE / 4          , SCALE + SCALE / 2                    , 3 * SCALE         , SCALE + SCALE / 2 }, /*< 2  */
				{ 7 * SCALE + SCALE / 2                      , 2 * SCALE                            , SCALE             , SCALE + SCALE / 2 }, /*< 3  */
				{ 8 * SCALE + SCALE / 3                      , SCALE + SCALE / 2                    , 3 * SCALE         , SCALE + SCALE / 2 }, /*< 4  */
				{ 7 * SCALE + SCALE / 2 - 2                  , SCALE / 2 - 8                        , SCALE             , SCALE + SCALE / 2 }, /*< 5  */
				{ BAR_HORIZONTAL_CENTERED                    , 3 * SCALE + SCALE / 2                , BAR_WIDTH         , BAR_HEIGHT        }, /*< 6  */
				{ BAR_HORIZONTAL_CENTERED                    , 3 * SCALE + SCALE / 2 + 4 * SCALE / 3, BAR_WIDTH         , BAR_HEIGHT        }, /*< 7  */
				{ BAR_HORIZONTAL_CENTERED                    , 3 * SCALE + SCALE / 2 + 8 * SCALE / 3, BAR_WIDTH         , BAR_HEIGHT        }, /*< 8  */
				{ BAR_HORIZONTAL_CENTERED + SCALE            , 4 * SCALE + SCALE / 4                , BAR_TEXT_WIDTH    , BAR_TEXT_HEIGHT   }, /*< 9  */
				{ BAR_HORIZONTAL_CENTERED + SCALE            , 4 * SCALE + SCALE / 4 + 4 * SCALE / 3, BAR_TEXT_WIDTH    , BAR_TEXT_HEIGHT   }, /*< 10 */
				{ BAR_HORIZONTAL_CENTERED + SCALE + SCALE / 2, 6 * SCALE + 2 * SCALE / 3 + SCALE / 4, BAR_TEXT_WIDTH / 2, BAR_TEXT_HEIGHT   }  /*< 11 */
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

#ifdef DEVEL_BUILD
	Test::start();
#endif /*< DEVEL_BUILD */
}

void MainMenu::draw(void) noexcept
{
	plog_verbose("Main menu is being drawn.");
	TextureInitializer::draw(renderer);
}

void MainMenu::handleEvent(const SDL_Event& event) noexcept
{
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
			handleMouseMotion();
			break;
		}
		case SDL_MOUSEMOTION:
		{
			handleMouseMotion();
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

void MainMenu::handleButtonDown(void) noexcept
{
	Coordinate     click      = {};
	const uint32_t mouseState = SDL_GetMouseState(&click.x, &click.y);
	size_t         index      = 0UL;

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
}

void MainMenu::handleButtonUp(void) noexcept
{
	Coordinate     click      = {};
	const uint32_t mouseState = SDL_GetMouseState(&click.x, &click.y);

	plog_trace("Mouse (%" PRIu32 ") was released. (coordinates: %" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);
#ifdef PLOG_STRIP_TRACE
	(void)mouseState;
#endif /*< PLOG_STRIP_TRACE */

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
}

void MainMenu::handleMouseMotion(void) noexcept
{
	Coordinate     click      = {};
	const uint32_t mouseState = SDL_GetMouseState(&click.x, &click.y);
	size_t         index      = 0UL;

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
}

void MainMenu::handleQuit(void) noexcept
{
	plog_info("Command to quit game was given!");
	stop(Scene::QUIT);
}

} /*< namespace hob */
