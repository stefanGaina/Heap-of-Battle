/** @file Menu.hpp
 *  @brief Class definition and method prototypes of the game menu.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

#ifndef MENU_HPP_
#define MENU_HPP_

/****************************************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                                 *
 ***************************************************************************************************************************************/

#include "TextureInitializer.hpp"

/****************************************************************************************************************************************
 * TYPE DEFINITIONS                                                                                                                     *
 ***************************************************************************************************************************************/

namespace Game
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
class Menu final : public Common::TextureInitializer<MENU_TEXTURES_COUNT, MENU_COMPONENTS_COUNT>
{
public:
	/**
	 * @brief Loads textures for the menu.
	 * @param void
	*/
	Menu(void) noexcept;

	/**
	 * @brief Default destructor.
	 * @param void
	*/
	~Menu(void) = default;

	/**
	 * @brief Constructed objects will load alliance or horde textures.
	 * @param isAlliance: true - background will be gray | false - background will be red.
	*/
	static void setTextureType(bool isAlliance) noexcept;
}; /*< class Menu */

} /*< namespace Game */

#endif /*< MENU_HPP_ */
