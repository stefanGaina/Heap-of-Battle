#ifndef TILE_INITIALIZER_HPP_
#define TILE_INITIALIZER_HPP_

#include <array>
#include <string>

#include "Tile.hpp"
#include "Texture.hpp"

namespace Game
{

constexpr size_t TILES_COUNT = 390ULL;

template<size_t TEXTURES_SET_COUNT>
class TileInitializer : public Common::IDrawable
{
public:
	TileInitializer(std::array<RawTexture, 4ULL * TEXTURES_SET_COUNT> textures, std::array<size_t, TILES_COUNT> textureIndexes) noexcept;

	virtual ~TileInitializer(void) = default;

	void changeTexture(Season season) noexcept;

	virtual void draw(void) noexcept override;

private:
	std::array<Tile, TILES_COUNT> m_tileContainer;
}; /*< class Tiles */

template<size_t TEXTURES_SET_COUNT>
TileInitializer<TEXTURES_SET_COUNT>::TileInitializer(std::array<RawTexture, 4ULL * TEXTURES_SET_COUNT> textures, std::array<size_t, TILES_COUNT> textureIndexes) noexcept
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

} /*< namespace Game */

#endif /*< TILE_INITIALIZER_HPP_ */
