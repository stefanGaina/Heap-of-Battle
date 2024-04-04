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

#ifndef HOB_ICONS_HPP_
#define HOB_ICONS_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_TextureInitializer.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Enumerates icons' textures index.
*/
enum IconsTextureIndex : uint8_t
{
	ICONS_TEXTURE_INDEX_FOOTMAN		  = 0,	/**< TODO */
	ICONS_TEXTURE_INDEX_ELF			  = 1,	/**< TODO */
	ICONS_TEXTURE_INDEX_KNIGHT		  = 2,	/**< TODO */
	ICONS_TEXTURE_INDEX_GRYPHON_RIDER = 3,	/**< TODO */
	ICONS_TEXTURE_INDEX_MAGE		  = 4,	/**< TODO */
	ICONS_TEXTURE_INDEX_CASTLE		  = 5,	/**< TODO */
	ICONS_TEXTURE_INDEX_KEEP		  = 6,	/**< TODO */
	ICONS_TEXTURE_INDEX_GRUNT		  = 7,	/**< TODO */
	ICONS_TEXTURE_INDEX_TROLL		  = 8,	/**< TODO */
	ICONS_TEXTURE_INDEX_DEATH_RIDER	  = 9,	/**< TODO */
	ICONS_TEXTURE_INDEX_DRAGON		  = 10, /**< TODO */
	ICONS_TEXTURE_INDEX_OGRE		  = 11, /**< TODO */
	ICONS_TEXTURE_INDEX_STRONGHOLD	  = 12, /**< TODO */
	ICONS_TEXTURE_INDEX_HALL		  = 13, /**< TODO */
	ICONS_TEXTURES_COUNT			  = 14	/**< How many textures icons load.                     */
};

/**
 * @brief Enumerates icons' changeable components index.
*/
enum IconsComponentIndex : uint8_t
{
	ICONS_COMPONENT_INDEX_1 = 0, /**< TODO */
	ICONS_COMPONENT_INDEX_2 = 1, /**< TODO */
	ICONS_COMPONENT_INDEX_3 = 2, /**< TODO */
	ICONS_COMPONENT_INDEX_4 = 3, /**< TODO */
	ICONS_COMPONENT_INDEX_5 = 4, /**< TODO */
	ICONS_COMPONENTS_COUNT	= 5	 /**< How many components the icons use. */
};

/**
 * @brief TODO
*/
class Icons final : public TextureInitializer<ICONS_TEXTURES_COUNT, ICONS_COMPONENTS_COUNT>
{
public:
	/**
	 * @brief TODO
	 * @param renderer: TODO
	*/
	Icons(SDL_Renderer* renderer) noexcept;

	/**
	 * @brief TODO
	 * @param void
	 * @return void
	*/
	void hide(void) noexcept;

	/**
	 * @brief TODO
	 * @param isAlliance: TODO
	 * @return void
	*/
	void setAllianceKeep(bool isAlliance) noexcept;

	/**
	 * @brief TODO
	 * @param isAlliance: TODO
	 * @return void
	*/
	void setHordeKeep(bool isAlliance) noexcept;

private:
	void setKeep(bool isAlliance, bool userFaction, size_t unitTextureIndex, size_t keepTextureIndex) noexcept;
	void setKeep(size_t textureIndex) noexcept;
	void setFirstIcon(size_t textureIndex) noexcept;
};

} /*< namespace hob */

#endif /*< HOB_ICONS_HPP_ */
