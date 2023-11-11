/******************************************************************************************************
 * @file hob_Menu.hpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file defines the class and method prototypes of the game menu.                       *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_MENU_HPP_
#define HOB_MENU_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_TextureInitializer.hpp"
#include "hob_Timer.hpp"
#include "hob_Gold.hpp"
#include "hob_Icons.hpp"
#include "hobGame_Game.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Enumerates game menu's textures index.
*/
enum GameMenuTextureIndex
{
	MENU_TEXTURE_INDEX_STONE      = 0, /**< Index to the game menu's background texture.           */
	MENU_TEXTURE_INDEX_STONE_VAR  = 1, /**< Index to the game menu's background variation texture. */
	MENU_TEXTURES_COUNT           = 2  /**< How many textures game menu loads.                     */
};

/**
 * @brief Enumerates game menu's changeable components index.
*/
enum GameMenuComponentIndex
{
	MENU_COMPONENTS_COUNT = 228 /**< How many components the game menu uses. */
};

enum class Action
{
	NOTHING          = 0,
	RECRUIT_INFANTRY = 1
};

/**
 * @brief Draws in-game menu depending of the user's faction.
*/
class Menu final : public TextureInitializer<7ULL, 10ULL>
{
public:
	/**
	 * @brief Loads textures for the menu.
	 * @param gold: Start amount of gold.
	*/
	Menu(uint8_t gold) noexcept;

	/**
	 * @brief Destroys the loaded textures.
	 * @param void
	*/
	~Menu(void) = default;

	void draw(void) noexcept override;

	Action handleClick(Coordinate click, hobGame::MenuMode menuMode) noexcept;

	void handleHover(Coordinate mouse) noexcept;

	void updateTimer(uint16_t seconds, bool isAlliance) noexcept;

	void updateGold(uint8_t amount) noexcept;

private:
	/**
	 * @brief Graphical representation of the time left.
	*/
	Timer m_timer;

	Gold m_gold;

	Icons m_icons;

};

} /*< namespace hob */

#endif /*< HOB_MENU_HPP_ */
