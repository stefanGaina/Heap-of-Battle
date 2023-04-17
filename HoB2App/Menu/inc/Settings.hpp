/** @file Settings.hpp
 *  @brief Class definition and method prototypes of the settings.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

/***********************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                *
 **********************************************************************************************************************/

#include "Loop.hpp"
#include "TextureInitializer.hpp"
#include "SoundInitializer.hpp"

namespace Menu
{

/***********************************************************************************************************************
 * TYPE DEFINITIONS                                                                                                    *
 **********************************************************************************************************************/

/*
 * @brief Enumerates settings' textures index.
 */
enum SettingsTextureIndex
{
	//MAIN_MENU_TEXTURE_INDEX_BACKGROUND      = 0,  /**< Index to the main menu's background texture.        */
	//MAIN_MENU_TEXTURE_INDEX_LOGO            = 1,  /**< Index to the main menu's logo texture.              */
	//MAIN_MENU_TEXTURE_INDEX_HEAP_TEXT       = 2,  /**< Index to the main menu's "HEAP" text texture.       */
	//MAIN_MENU_TEXTURE_INDEX_OF_TEXT         = 3,  /**< Index to the main menu's "OF" text texture.         */
	//MAIN_MENU_TEXTURE_INDEX_BATTLE_TEXT     = 4,  /**< Index to the main menu's "BATTLE" texture.          */
	//MAIN_MENU_TEXTURE_INDEX_2_TEXT          = 5,  /**< Index to the main menu's "2" text texture.          */
	//MAIN_MENU_TEXTURE_INDEX_BUTTON_IDLE     = 6,  /**< Index to the main menu's idle button texture.       */
	//MAIN_MENU_TEXTURE_INDEX_BUTTON_ACTIVE   = 7,  /**< Index to the main menu's active button texture.     */
	//MAIN_MENU_TEXTURE_INDEX_BUTTON_PRESSED  = 8,  /**< Index to the main menu's pressed button texture.    */
	//MAIN_MENU_TEXTURE_INDEX_START_GAME_TEXT = 9,  /**< Index to the main menu's "START GAME" text texture. */
	//MAIN_MENU_TEXTURE_INDEX_SETTINGS_TEXT   = 10, /**< Index to the main menu's "SETTINGS" text texture.   */
	//MAIN_MENU_TEXTURE_INDEX_EXIT_TEXT       = 11, /**< Index to the main menu's "EXIT" text texture.       */
	SETTINGS_TEXTURES_COUNT                = 12  /**< How many textures settings loads.                  */
};

/*
 * @brief Enumerates settings' changeable components index.
 */
enum SettingsComponentIndex
{
	//MAIN_MENU_COMPONENT_INDEX_BUTTON_START_GAME = 6, /**< Index to the main menu's start game button component. */
	//MAIN_MENU_COMPONENT_INDEX_BUTTON_SETTINGS   = 7, /**< Index to the main menu's settings button component.   */
	//MAIN_MENU_COMPONENT_INDEX_BUTTON_EXIT       = 8, /**< Index to the main menu's exit button component.       */
	SETTINGS_COMPONENTS_COUNT                  = 12 /**< How many components the settings uses.               */
};

/**
 * @brief Enumerates settings' sounds index.
*/
enum SettingsSoundIndex
{
	SETTINGS_SOUND_INDEX_CLICK = 0, /**< Index to the settings' click sound. */
	SETTINGS_SOUNDS_COUNT      = 1  /**< How many sounds the settings loads. */
};

/**
 * @brief Settings scene.
*/
class Settings final : public Common::Loop
					 , public Common::TextureInitializer<SETTINGS_TEXTURES_COUNT, SETTINGS_COMPONENTS_COUNT>
					 , public Common::SoundInitializer<SETTINGS_SOUNDS_COUNT>
{
public:
	/**
	 * @brief Loads everything needed for the scene.
	 * @param void
	*/
	Settings(void);

	/**
	 * @brief Destroys everything that was loaded.
	 * @param void
	*/
	~Settings(void);

private:
	/**
	 * @brief Handles an event.
	 * @param event: event to be handled.
	 * @return void
	*/
	void handleEvent(const SDL_Event& event) noexcept override;

	/**
	 * @brief Method implementation for drawing scene updates.
	 * @param void
	 * @return void
	*/
	virtual void draw(void) noexcept override;
};

} /*< namespace Menu */

#endif /*< SETTINGS_H_ */
