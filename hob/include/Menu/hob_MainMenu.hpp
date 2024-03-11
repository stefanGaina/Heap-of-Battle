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
 * @file hob_MainMenu.hpp                                                                             *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 29.08.2023  Gaina Stefan               Fixed comments.                                             *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * 18.01.2024  Gaina Stefan               Break handleEvent() into multiple methods().                *
 * @details This file defines the class and method prototypes of the main menu scene.                 *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_MAIN_MENU_SCENE_HPP_
#define HOB_MAIN_MENU_SCENE_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_Loop.hpp"
#include "hob_TextureInitializer.hpp"
#include "hob_SoundInitializer.hpp"
#include "hob_Music.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Enumerates main menu's textures index.
*/
enum MainMenuTextureIndex
{
	MAIN_MENU_TEXTURE_INDEX_BACKGROUND		= 0,  /**< Index to the main menu's background texture.        */
	MAIN_MENU_TEXTURE_INDEX_LOGO			= 1,  /**< Index to the main menu's logo texture.              */
	MAIN_MENU_TEXTURE_INDEX_HEAP_TEXT		= 2,  /**< Index to the main menu's "HEAP" text texture.       */
	MAIN_MENU_TEXTURE_INDEX_OF_TEXT			= 3,  /**< Index to the main menu's "OF" text texture.         */
	MAIN_MENU_TEXTURE_INDEX_BATTLE_TEXT		= 4,  /**< Index to the main menu's "BATTLE" texture.          */
	MAIN_MENU_TEXTURE_INDEX_2_TEXT			= 5,  /**< Index to the main menu's "2" text texture.          */
	MAIN_MENU_TEXTURE_INDEX_BUTTON_IDLE		= 6,  /**< Index to the main menu's idle button texture.       */
	MAIN_MENU_TEXTURE_INDEX_BUTTON_ACTIVE	= 7,  /**< Index to the main menu's active button texture.     */
	MAIN_MENU_TEXTURE_INDEX_BUTTON_PRESSED	= 8,  /**< Index to the main menu's pressed button texture.    */
	MAIN_MENU_TEXTURE_INDEX_START_GAME_TEXT = 9,  /**< Index to the main menu's "START GAME" text texture. */
	MAIN_MENU_TEXTURE_INDEX_SETTINGS_TEXT	= 10, /**< Index to the main menu's "SETTINGS" text texture.   */
	MAIN_MENU_TEXTURE_INDEX_EXIT_TEXT		= 11, /**< Index to the main menu's "EXIT" text texture.       */
	MAIN_MENU_TEXTURES_COUNT				= 12  /**< How many textures main menu loads.                  */
};

/**
 * @brief Enumerates main menu's changeable components index.
*/
enum MainMenuComponentIndex
{
	MAIN_MENU_COMPONENT_INDEX_BUTTON_START_GAME = 6, /**< Index to the main menu's start game button component. */
	MAIN_MENU_COMPONENT_INDEX_BUTTON_SETTINGS	= 7, /**< Index to the main menu's settings button component.   */
	MAIN_MENU_COMPONENT_INDEX_BUTTON_EXIT		= 8, /**< Index to the main menu's exit button component.       */
	MAIN_MENU_COMPONENTS_COUNT					= 12 /**< How many components the main menu uses.               */
};

/**
 * @brief Enumerates main menu's sounds index.
*/
enum MainMenuSoundIndex
{
	MAIN_MENU_SOUND_INDEX_CLICK = 0, /**< Index to the main menu's click sound. */
	MAIN_MENU_SOUNDS_COUNT		= 1	 /**< How many sounds the main menu loads.  */
};

/**
 * @brief Main menu scene.
*/
class MainMenu final
	: public Loop,
	  public TextureInitializer<MAIN_MENU_TEXTURES_COUNT, MAIN_MENU_COMPONENTS_COUNT>,
	  public SoundInitializer<MAIN_MENU_SOUNDS_COUNT>
{
public:
	/**
	 * @brief Loads the textures and sounds needed for this scene.
	 * @param renderer: Rendering context of the window.
	 * @param cursor: Reference to the cursor object.
	 * @param music: Reference to the music object.
	*/
	MainMenu(SDL_Renderer* renderer, Cursor& cursor, Music& music) noexcept;

private:
	/**
	 * @brief Handles an event.
	 * @param event: Event to be handled.
	 * @return void
	*/
	void handleEvent(const SDL_Event& event) noexcept override;

	/**
	 * @brief Method implementation for drawing scene updates.
	 * @param void
	 * @return void
	*/
	void draw(void) noexcept override;

	/**
	 * @brief Handles a button down event.
	 * @param void
	 * @return void
	*/
	void handleButtonDown(void) noexcept;

	/**
	 * @brief Handles a button up event.
	 * @param void
	 * @return void
	*/
	void handleButtonUp(void) noexcept;

	/**
	 * @brief Handles a mouse motion event.
	 * @param void
	 * @return void
	*/
	void handleMouseMotion(void) noexcept;

	/**
	 * @brief Handles a quit event.
	 * @param void
	 * @return void
	*/
	void handleQuit(void) noexcept;

private:
	/**
	 * @brief Holds the index of the component that was previously pressed.
	*/
	size_t clickDownIndex;

	/**
	 * @brief Reference to the music object.
	*/
	Music& music;
};

} /*< namespace hob */

#endif /*< HOB_MAIN_MENU_SCENE_HPP_ */
