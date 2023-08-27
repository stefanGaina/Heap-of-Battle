/******************************************************************************************************
 * @file hob_BuildingInitializer.hpp                                                                  *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * 27.08.2023  Gaina Stefan               Added comment.                                              *
 * @details This file defines the class and method prototypes of the building initializer.            *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_BUILDING_INITIALIZER_HPP_
#define HOB_BUILDING_INITIALIZER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <array>
#include <string>

#include "hob_Building.hpp"
#include "hob_Texture.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Initializes a list of buildings.
*/
template<size_t BUILDINGS_COUNT>
class BuildingInitializer : public IDrawable
{
public:
	/**
	 * @brief Initializes a container of buildings.
	 * @param textures: 4 textures for each building (in order).
	 * @param destinations: Destination for each building.
	*/
	BuildingInitializer(std::array<SDL_Texture*, 4ULL * BUILDINGS_COUNT> textures, std::array<SDL_Rect, BUILDINGS_COUNT> destinations) noexcept;

	/**
	 * @brief Does not destroy the textures.
	 * @param void
	*/
	virtual ~BuildingInitializer(void) = default;

	/**
	 * @brief Calls the draw method of each building.
	 * @param void
	 * @return void
	*/
	virtual void draw(void) noexcept override;

protected:
	/**
	 * @brief Holds the initialized buildings.
	*/
	std::array<Building, BUILDINGS_COUNT> m_buildingContainer;
};

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

template<size_t BUILDINGS_COUNT>
BuildingInitializer<BUILDINGS_COUNT>::BuildingInitializer(std::array<SDL_Texture*, 4ULL * BUILDINGS_COUNT> textures, std::array<SDL_Rect, BUILDINGS_COUNT> destinations) noexcept
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

} /*< namespace hob */

#endif /*< HOB_BUILDING_INITIALIZER_HPP_ */
