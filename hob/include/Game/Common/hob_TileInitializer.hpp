/******************************************************************************************************
 * @file hob_TileInitializer.hpp                                                                      *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * 27.08.2023  Gaina Stefan               Added comment.                                              *
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
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief How many tiles are being initialized.
*/
constexpr const size_t TILES_COUNT = 390ULL;

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
	TileInitializer(std::array<SDL_Texture*, 4ULL * TEXTURES_SET_COUNT> textures, std::array<size_t, TILES_COUNT> textureIndexes) noexcept;

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
	 * @param void
	 * @return void
	*/
	virtual void draw(void) noexcept override;

private:
	/**
	 * @brief Holds the initialized buildings.
	*/
	std::array<Tile, TILES_COUNT> m_tileContainer;
};

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

template<size_t TEXTURES_SET_COUNT>
TileInitializer<TEXTURES_SET_COUNT>::TileInitializer(std::array<SDL_Texture*, 4ULL * TEXTURES_SET_COUNT> textures, std::array<size_t, TILES_COUNT> textureIndexes) noexcept
{
	size_t index        = 0ULL;
	size_t textureIndex = 0ULL;

	plog_trace("TileInitializer is being constructed.");
	for (index = 0ULL; index < TILES_COUNT; ++index)
	{
		textureIndex = 4ULL * textureIndexes[index];

		m_tileContainer[index].init(textures[textureIndex], textures[textureIndex + 1ULL], textures[textureIndex + 2ULL],
			textures[textureIndex + 3ULL], { static_cast<int32_t>(index) % 26L, static_cast<int32_t>(index) / 26L });
	}
}

template<size_t TEXTURES_SET_COUNT>
void TileInitializer<TEXTURES_SET_COUNT>::changeTexture(Season season) noexcept
{
	size_t index = 0ULL;

	plog_verbose("Tiles are being changed. (season: %" PRId32 ")", static_cast<int32_t>(season));
	for (index = 0ULL; index < TILES_COUNT; ++index)
	{
		m_tileContainer[index].changeTexture(season);
	}
}

template<size_t TEXTURES_SET_COUNT>
void TileInitializer<TEXTURES_SET_COUNT>::draw(void) noexcept
{
	size_t index = 0ULL;

	plog_verbose("Tiles are being drawn.");
	for (index = 0ULL; index < TILES_COUNT; ++index)
	{
		m_tileContainer[index].draw();
	}
}

} /*< namespace hob */

#endif /*< HOB_TILE_INITIALIZER_HPP_ */
