/******************************************************************************************************
 * Heap of Battle Copyright (C) 2024
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the
 * authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
 *    original software. If you use this software in a product, an acknowledgment in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being
 *    the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @file hob_Tiles1.hpp
 * @author Gaina Stefan
 * @date 29.07.2023
 * @brief This file defines the class and method prototypes of the tiles of the first scenario.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_TILES1_HPP_
#define HOB_TILES1_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "hob_TextureInitializer.hpp"
#include "hob_TileInitializer.hpp"
#include "hob_LoadingScreen.hpp"

/******************************************************************************************************
 * CONSTANTS
 *****************************************************************************************************/

namespace hob
{

/** ***************************************************************************************************
 * @brief How many times of tiles are being used.
 *****************************************************************************************************/
constexpr const size_t TILES1_COUNT = 13UL;

/** ***************************************************************************************************
 * @brief How many textures scenario 1 tiles loads.
 *****************************************************************************************************/
constexpr const size_t TILES1_TEXTURES_COUNT = 34UL;

/** ***************************************************************************************************
 * @brief How many components the tiles of scenario 1 uses.
 *****************************************************************************************************/
constexpr const size_t TILES1_COMPONENTS_COUNT = 0UL;

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Tiles of the scenario 1.
 *****************************************************************************************************/
class Tiles1 final : public TextureInitializer<TILES1_TEXTURES_COUNT, TILES1_COMPONENTS_COUNT>,
					 public TileInitializer<TILES1_COUNT>
{
public:
	/** ***********************************************************************************************
	 * @brief Loads the textures and initializes the tiles.
	 * @param renderer: Rendering context of the window.
	 * @param loadingScreen: Loading screen will be stepped after construction is finalized.
	 *************************************************************************************************/
	Tiles1(SDL_Renderer* renderer, LoadingScreen& loadingScreen) noexcept;
};

} /*< namespace hob */

#endif /*< HOB_TILES1_HPP_ */
