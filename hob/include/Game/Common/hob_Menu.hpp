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

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/*
 * @brief Enumerates game menu's textures index.
 */
enum GameMenuTextureIndex
{
	MENU_TEXTURE_INDEX_STONE      = 0, /**< Index to the game menu's background texture.           */
	MENU_TEXTURE_INDEX_STONE_VAR  = 1, /**< Index to the game menu's background variation texture. */
	MENU_TEXTURES_COUNT           = 2  /**< How many textures game menu loads.                     */
};

/*
 * @brief Enumerates game menu's changeable components index.
 */
enum GameMenuComponentIndex
{
	MENU_COMPONENTS_COUNT = 228 /**< How many components the game menu uses. */
};

/**
 * @brief Draws in-game menu depending of the user's faction.
*/
class Menu final : public TextureInitializer<MENU_TEXTURES_COUNT, MENU_COMPONENTS_COUNT>
{
public:
	/**
	 * @brief Loads textures for the menu.
	 * @param void
	*/
	Menu(void) noexcept;

	/**
	 * @brief Destroys the loaded textures.
	 * @param void
	*/
	~Menu(void) = default;
};

} /*< namespace hob */

#endif /*< HOB_MENU_HPP_ */
