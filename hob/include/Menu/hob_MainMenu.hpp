/******************************************************************************************************
 * @file hob_MainMenu.hpp                                                                             *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 29.08.2023  Gaina Stefan               Fixed comments.                                             *
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
	MAIN_MENU_TEXTURE_INDEX_BACKGROUND      = 0,  /**< Index to the main menu's background texture.        */
	MAIN_MENU_TEXTURE_INDEX_LOGO            = 1,  /**< Index to the main menu's logo texture.              */
	MAIN_MENU_TEXTURE_INDEX_HEAP_TEXT       = 2,  /**< Index to the main menu's "HEAP" text texture.       */
	MAIN_MENU_TEXTURE_INDEX_OF_TEXT         = 3,  /**< Index to the main menu's "OF" text texture.         */
	MAIN_MENU_TEXTURE_INDEX_BATTLE_TEXT     = 4,  /**< Index to the main menu's "BATTLE" texture.          */
	MAIN_MENU_TEXTURE_INDEX_2_TEXT          = 5,  /**< Index to the main menu's "2" text texture.          */
	MAIN_MENU_TEXTURE_INDEX_BUTTON_IDLE     = 6,  /**< Index to the main menu's idle button texture.       */
	MAIN_MENU_TEXTURE_INDEX_BUTTON_ACTIVE   = 7,  /**< Index to the main menu's active button texture.     */
	MAIN_MENU_TEXTURE_INDEX_BUTTON_PRESSED  = 8,  /**< Index to the main menu's pressed button texture.    */
	MAIN_MENU_TEXTURE_INDEX_START_GAME_TEXT = 9,  /**< Index to the main menu's "START GAME" text texture. */
	MAIN_MENU_TEXTURE_INDEX_SETTINGS_TEXT   = 10, /**< Index to the main menu's "SETTINGS" text texture.   */
	MAIN_MENU_TEXTURE_INDEX_EXIT_TEXT       = 11, /**< Index to the main menu's "EXIT" text texture.       */
	MAIN_MENU_TEXTURES_COUNT                = 12  /**< How many textures main menu loads.                  */
};

/**
 * @brief Enumerates main menu's changeable components index.
*/
enum MainMenuComponentIndex
{
	MAIN_MENU_COMPONENT_INDEX_BUTTON_START_GAME = 6, /**< Index to the main menu's start game button component. */
	MAIN_MENU_COMPONENT_INDEX_BUTTON_SETTINGS   = 7, /**< Index to the main menu's settings button component.   */
	MAIN_MENU_COMPONENT_INDEX_BUTTON_EXIT       = 8, /**< Index to the main menu's exit button component.       */
	MAIN_MENU_COMPONENTS_COUNT                  = 12 /**< How many components the main menu uses.               */
};

/**
 * @brief Enumerates main menu's sounds index.
*/
enum MainMenuSoundIndex
{
	MAIN_MENU_SOUND_INDEX_CLICK = 0, /**< Index to the main menu's click sound. */
	MAIN_MENU_SOUNDS_COUNT      = 1  /**< How many sounds the main menu loads.  */
};

/**
 * @brief Main menu scene.
*/
class MainMenu final : public Loop
					 , public TextureInitializer<MAIN_MENU_TEXTURES_COUNT, MAIN_MENU_COMPONENTS_COUNT>
					 , public SoundInitializer<MAIN_MENU_SOUNDS_COUNT>
{
public:
	/**
	 * @brief Loads the textures and sounds needed for this scene.
	 * @param void
	*/
	MainMenu(void) noexcept;

	/**
	 * @brief Destroys the loaded textures and sound needed for this scene.
	 * @param void
	*/
	~MainMenu(void) = default;

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

private:
	/**
	 * @brief Holds the index of the component that was previously pressed.
	*/
	size_t m_clickDownIndex;
};

} /*< namespace hob */

#endif /*< HOB_MAIN_MENU_SCENE_HPP_ */
