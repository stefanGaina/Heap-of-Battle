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
 * @file hob_BuildingInitializer.hpp                                                                  *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * 27.08.2023  Gaina Stefan               Added comment.                                              *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * 17.01.2024  Gaina Stefan               Added constant for seasons count.                           *
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
 * CONSTANTS                                                                                          *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief How many seasons there are.
*/
constexpr const size_t SEASONS_COUNT = 4UL;

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

/**
 * @brief Initializes a list of buildings.
*/
template<size_t BUILDINGS_COUNT>
class BuildingInitializer : public IDrawable
{
public:
	/**
	 * @brief Initializes a container of buildings.
	 * @param textures: Textures for each building (in order).
	 * @param destinations: Destination for each building.
	*/
	BuildingInitializer(std::array<SDL_Texture*, SEASONS_COUNT * BUILDINGS_COUNT> textures, std::array<SDL_Rect, BUILDINGS_COUNT> destinations) noexcept;

	/**
	 * @brief Does not destroy the textures.
	 * @param void
	*/
	virtual ~BuildingInitializer(void) = default;

	/**
	 * @brief Calls the draw method of each building.
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	virtual void draw(SDL_Renderer* renderer) noexcept override;

protected:
	/**
	 * @brief Holds the initialized buildings.
	*/
	std::array<Building, BUILDINGS_COUNT> buildingContainer;
};

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

template<size_t BUILDINGS_COUNT>
BuildingInitializer<BUILDINGS_COUNT>::BuildingInitializer(std::array<SDL_Texture*, SEASONS_COUNT * BUILDINGS_COUNT> textures,
														  std::array<SDL_Rect, BUILDINGS_COUNT>						destinations) noexcept
	: buildingContainer{}
{
	size_t index		= 0UL;
	size_t textureIndex = 0UL;

	plog_trace("BuildingInitializer is being constructed.");
	for (; index < BUILDINGS_COUNT; ++index)
	{
		textureIndex = SEASONS_COUNT * index;

		buildingContainer[index].init(
			textures[textureIndex], textures[textureIndex + 1UL], textures[textureIndex + 2UL], textures[textureIndex + 3UL], destinations[index]);
	}
}

template<size_t BUILDINGS_COUNT>
void BuildingInitializer<BUILDINGS_COUNT>::draw(SDL_Renderer* const renderer) noexcept
{
	size_t index = 0UL;

	plog_verbose("Buildings are being drawn.");
	for (; index < BUILDINGS_COUNT; ++index)
	{
		buildingContainer[index].draw(renderer);
	}
}

} /*< namespace hob */

#endif /*< HOB_BUILDING_INITIALIZER_HPP_ */
