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
 * @file hob_TileInitializer.hpp                                                                      *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * 27.08.2023  Gaina Stefan               Added comment.                                              *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file defines the class and method prototypes of the tile initializer.                *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_TILE_INITIALIZER_HPP_
#define HOB_TILE_INITIALIZER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <array>
#include <string>

#include "hob_Tile.hpp"
#include "hob_Texture.hpp"

/******************************************************************************************************
 * CONSTANTS                                                                                          *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief How many tiles are being initialized.
*/
inline constexpr const size_t TILES_COUNT = 390UL;

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

/**
 * @brief Initializes a list of tiles.
*/
template<size_t TEXTURES_SET_COUNT>
class TileInitializer : public IDrawable
{
public:
	/**
	 * @brief Initializes a container of tiles.
	 * @param textures: 4 textures for each building, one for each season (in order: summer, autumn, winter, spring).
	 * @param textureIndexes: What set of textures will each tile be assigned to.
	*/
	TileInitializer(std::array<SDL_Texture*, 4UL * TEXTURES_SET_COUNT> textures, std::array<size_t, TILES_COUNT> textureIndexes) noexcept;

	/**
	 * @brief Does not destroy the textures.
	 * @param void
	*/
	virtual ~TileInitializer(void) = default;

	/**
	 * @brief Changes the texture of the tiles.
	 * @param season: What season will the tiles' textures be changed to.
	 * @return void
	*/
	void changeTexture(Season season) noexcept;

	/**
	 * @brief Calls the draw method of each tile.
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	virtual void draw(SDL_Renderer* renderer) noexcept override;

private:
	/**
	 * @brief Holds the initialized buildings.
	*/
	std::array<Tile, TILES_COUNT> tileContainer;
};

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

template<size_t TEXTURES_SET_COUNT>
TileInitializer<TEXTURES_SET_COUNT>::TileInitializer(std::array<SDL_Texture*, 4UL * TEXTURES_SET_COUNT> textures,
													 std::array<size_t, TILES_COUNT>					textureIndexes) noexcept
	: tileContainer{}
{
	size_t index		= 0UL;
	size_t textureIndex = 0UL;

	plog_trace("TileInitializer is being constructed.");
	for (; index < TILES_COUNT; ++index)
	{
		textureIndex = 4UL * textureIndexes[index];

		tileContainer[index].init(textures[textureIndex], textures[textureIndex + 1UL], textures[textureIndex + 2UL], textures[textureIndex + 3UL],
								  { static_cast<int32_t>(index) % 26, static_cast<int32_t>(index) / 26 });
	}
}

template<size_t TEXTURES_SET_COUNT>
void TileInitializer<TEXTURES_SET_COUNT>::changeTexture(const Season season) noexcept
{
	size_t index = 0UL;

	plog_verbose("Tiles are being changed. (season: %" PRId32 ")", static_cast<int32_t>(season));
	for (; index < TILES_COUNT; ++index)
	{
		tileContainer[index].changeTexture(season);
	}
}

template<size_t TEXTURES_SET_COUNT>
void TileInitializer<TEXTURES_SET_COUNT>::draw(SDL_Renderer* const renderer) noexcept
{
	size_t index = 0UL;

	plog_verbose("Tiles are being drawn.");
	for (; index < TILES_COUNT; ++index)
	{
		tileContainer[index].draw(renderer);
	}
}

} /*< namespace hob */

#endif /*< HOB_TILE_INITIALIZER_HPP_ */
