#ifndef BUILDING_INITIALIZER_HPP_
#define BUILDING_INITIALIZER_HPP_

#include <array>
#include <string>

#include "Building.hpp"
#include "Texture.hpp"

namespace Game
{

template<size_t BUILDINGS_COUNT>
class BuildingInitializer : public Common::IDrawable
{
public:
	BuildingInitializer(std::array<RawTexture, 4ULL * BUILDINGS_COUNT> textures, std::array<Rect, BUILDINGS_COUNT> destinations) noexcept;

	virtual ~BuildingInitializer(void) = default;

	virtual void draw(void) noexcept override;

protected:
	std::array<Building, BUILDINGS_COUNT> m_buildingContainer;
}; /*< class Tiles */

template<size_t BUILDINGS_COUNT>
BuildingInitializer<BUILDINGS_COUNT>::BuildingInitializer(std::array<RawTexture, 4ULL * BUILDINGS_COUNT> textures, std::array<Rect, BUILDINGS_COUNT> destinations) noexcept
{
	size_t index        = 0ULL;
	size_t textureIndex = 0ULL;

	plog_trace("BuildingInitializer is being constructed.");
	for (index = 0ULL; index < BUILDINGS_COUNT; ++index)
	{
		textureIndex = 4ULL * index;

		m_buildingContainer[index].init(textures[textureIndex], textures[textureIndex + 1ULL], textures[textureIndex + 2ULL],
			textures[textureIndex + 3ULL], destinations[index]);
	}
}

template<size_t BUILDINGS_COUNT>
void BuildingInitializer<BUILDINGS_COUNT>::draw(void) noexcept
{
	size_t index = 0ULL;

	plog_verbose("Buildings are being drawn.");
	for (index = 0ULL; index < BUILDINGS_COUNT; ++index)
	{
		m_buildingContainer[index].draw();
	}
}

} /*< namespace Game */

#endif /*< BUILDING_INITIALIZER_HPP_ */
