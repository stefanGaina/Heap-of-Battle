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
 * @file hob_Menu.hpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * 17.01.2024  Gaina Stefan               Added indexes.                                              *
 * @details This file defines the class and method prototypes of the game menu.                       *
 * @todo Fix doxygen.                                                                                 *
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
	MENU_TEXTURE_INDEX_BACKGROUND				 = 0, /**< Index to the game menu's background texture. */
	MENU_TEXTURE_INDEX_FRAME_SELECTED_ALLIANCE	 = 1, /**< Index to the game menu's background variation texture. */
	MENU_TEXTURE_INDEX_FRAME_SELECTED_HORDE		 = 2, /**< TODO */
	MENU_TEXTURE_INDEX_FRAME_UNSELECTED_ALLIANCE = 3, /**< TODO */
	MENU_TEXTURE_INDEX_FRAME_UNSELECTED_HORDE	 = 4, /**< TODO */
	MENU_TEXTURE_INDEX_HOURGLASS_INACTIVE		 = 5, /**< TODO */
	MENU_TEXTURES_COUNT							 = 6  /**< How many textures game menu loads.                     */
};

/**
 * @brief Enumerates game menu's changeable components index.
*/
enum GameMenuComponentIndex
{
	MENU_COMPONENT_INDEX_FRAME_1		= 4, /**< TODO */
	MENU_COMPONENT_INDEX_FRAME_2		= 5, /**< TODO */
	MENU_COMPONENT_INDEX_FRAME_3		= 6, /**< TODO */
	MENU_COMPONENT_INDEX_FRAME_4		= 7, /**< TODO */
	MENU_COMPONENT_INDEX_FRAME_5		= 8, /**< TODO */
	MENU_COMPONENT_INDEX_SELECTED_FRAME = 9, /**< TODO */
	MENU_COMPONENTS_COUNT				= 10 /**< How many components the game menu uses. */
};

/**
 * @brief TODO
*/
enum class Action
{
	NOTHING			 = 0, /**< TODO */
	RECRUIT_INFANTRY = 1, /**< TODO */
	RECRUIT_RANGED	 = 2,
	RECRUIT_CAVALRY	 = 3,
	RECRUIT_AIRCRAFT = 4,
	RECRUIT_MAGE	 = 5
};

/**
 * @brief Draws in-game menu depending of the user's faction.
*/
class Menu final : public TextureInitializer<MENU_TEXTURES_COUNT, MENU_COMPONENTS_COUNT>
{
public:
	/**
	 * @brief Loads textures for the menu.
	 * @param renderer: Rendering context of the window.
	 * @param isAlliance: TODO
	 * @param gold: Start amount of gold.
	*/
	Menu(SDL_Renderer* renderer, bool isAlliance, uint8_t gold) noexcept;

	/**
	 * @brief Destroys the loaded textures.
	 * @param void
	*/
	~Menu(void) = default;

	/**
	 * @brief TODO
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	void draw(SDL_Renderer* renderer) noexcept override;

	/**
	 * @brief TODO
	 * @param click: TODO
	 * @param menuMode: TODO
	 * @param isAlliance: TODO
	 * @return TODO
	*/
	Action handleClick(Coordinate click, hobGame::MenuMode menuMode, bool isAlliance) noexcept;

	/**
	 * @brief TODO
	 * @param mouse: TODO
	 * @param isAlliance: TODO
	 * @return void
	*/
	void handleHover(Coordinate mouse, bool isAlliance) noexcept;

	/**
	 * @brief TODO
	 * @param seconds: TODO
	 * @param isAlliance: TODO
	 * @return void
	*/
	void updateTimer(uint16_t seconds, bool isAlliance) noexcept;

	/**
	 * @brief TODO
	 * @param amount: TODO
	 * @return void
	*/
	void updateGold(uint8_t amount) noexcept;

private:
	void setFramesKeep(SDL_Texture* const texture1, SDL_Texture* const texture2) noexcept;

private:
	/**
	 * @brief Graphical representation of the time left.
	*/
	Timer timer;

	/**
	 * @brief TODO
	*/
	Gold gold;

	/**
	 * @brief TODO
	*/
	Icons icons;
};

} /*< namespace hob */

#endif /*< HOB_MENU_HPP_ */
