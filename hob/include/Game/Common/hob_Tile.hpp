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
 * @file hob_Tile.hpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file defines the class and method prototypes of the tile.                            *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_TILE_HPP_
#define HOB_TILE_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_IDrawable.hpp"
#include "hob_Component.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Enumerates the seasons.
*/
enum class Season
{
	SUMMER = 0, /**< Summer season. */
	AUTUMN = 1, /**< Autumn season. */
	WINTER = 2, /**< Winter season. */
	SPRING = 3	/**< Spring season. */
};

/**
 * @brief HSCALE by HSCALE tile supporting texture for each season.
*/
class Tile final : public IDrawable
{
public:
	/**
	 * @brief Does not initialize the tile implicitly.
	 * @param void
	*/
	Tile(void) noexcept;

	/**
	 * @brief Does not destroy the textures.
	 * @param void
	*/
	~Tile(void) = default;

	/**
	 * @brief Initializes the tile with textures for all seasons and its position.
	 * @param[in] summerTexture: Texture that will be drawn when season is set to summer.
	 * @param[in] autumnTexture: Texture that will be drawn when season is set to autumn.
	 * @param[in] winterTexture: Texture that will be drawn when season is set to winter.
	 * @param[in] springTexture: Texture that will be drawn when season is set to spring.
	 * @param position: Indexes of the playing board matrix.
	 * @return void
	*/
	void init(SDL_Texture* summerTexture, SDL_Texture* autumnTexture, SDL_Texture* winterTexture, SDL_Texture* springTexture, Coordinate position) noexcept;

	/**
	 * @brief Draws the active texture of the tile.
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	void draw(SDL_Renderer* renderer) noexcept override;

	/**
	 * @brief Changes the texture that will be drawn.
	 * @param season: What season will the tile's texture be changed to.
	 * @return void
	*/
	void changeTexture(Season season) noexcept;

private:
	/**
	 * @brief Texture that will be drawn when season is set to summer.
	*/
	SDL_Texture* summerTexture;

	/**
	 * @brief Texture that will be drawn when season is set to autumn.
	*/
	SDL_Texture* autumnTexture;

	/**
	 * @brief Texture that will be drawn when season is set to winter.
	*/
	SDL_Texture* winterTexture;

	/**
	 * @brief Texture that will be drawn when season is set to spring.
	*/
	SDL_Texture* springTexture;

	/**
	 * @brief Component used to draw the tile.
	*/
	Component	 component;
};

} /*< namespace hob */

#endif /*< HOB_TILE_HPP_ */
