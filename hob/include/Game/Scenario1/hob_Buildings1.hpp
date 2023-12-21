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
 * @file hob_Buildings1.hpp                                                                           *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file defines the class and method prototypes of the buildings of the first scenario. *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_BUILDINGS1_HPP_
#define HOB_BUILDINGS1_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_TextureInitializer.hpp"
#include "hob_BuildingInitializer.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Graphical representation of all the buildings used in scenario 1.
*/
class Buildings1 final : public TextureInitializer<29UL, 0UL>
					   , public BuildingInitializer<18UL>
{
public:
	/**
	 * @brief Loads the textures and initializes the buildings.
	 * @param renderer: Rendering context of the window.
	*/
	Buildings1(SDL_Renderer* renderer) noexcept;

	/**
	 * @brief Destroys the loaded textures.
	 * @param void
	*/
	~Buildings1(void) = default;

	/**
	 * @brief Calls the draw method of each building.
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	void draw(SDL_Renderer* renderer) noexcept override;

	/**
	 * @brief Changes the textures of the buildings.
	 * @param isWinter: true - winter | false - otherwise.
	 * @return void
	*/
	void changeWeather(bool isWinter) noexcept;

private:
	/**
	 * @brief The season that the textures are set to.
	*/
	bool previousSeason;
};

} /*< namespace hob */

#endif /*< HOB_BUILDINGS1_HPP_ */
