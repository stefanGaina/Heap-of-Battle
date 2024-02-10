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
 * @file hob_Game.hpp
 * @author Gaina Stefan
 * @date 23.07.2023
 * @brief This file defines the function that runs the game.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_GAME_HPP_
#define HOB_GAME_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "hob_Types.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

/** ***************************************************************************************************
 * @brief Static class that initializes subsystems and run the scene loop of the game.
 *****************************************************************************************************/
class Game final
{
public:
	/** ***********************************************************************************************
	 * @brief Initializes all subsystems and runs the scenes of the game.
	 * @param void
	 * @return void
	 * @throws std::exception If the initialization of any of the subsystems fails or the creation of
	 * the window fails.
	 *************************************************************************************************/
	static void run(void) noexcept(false);

private:
	/** ***********************************************************************************************
	 * @brief Checks for loaded libraries versions and initializes SDL, SDL image, SDL mixer, SDL ttf,
	 * and Plog in case of development builds.
	 * @param void
	 * @return void
	 * @throws std::exception If the initialization of any of the subsystems fails.
	 *************************************************************************************************/
	static void init(void) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Deinitializes SDL, SDL image, SDL mixer, SDL ttff and deinitializes Plog in case
	 * of development builds.
	 * @param void
	 * @return void
	 *************************************************************************************************/
	static void deinit(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Runs the game loop for the current scene.
	 * @param renderer: Rendering context of the window.
	 * @return void
	 *************************************************************************************************/
	static void sceneLoop(SDL_Renderer* renderer) noexcept;
};

} /*< namespace hob */

#endif /*< HOB_GAME_HPP_ */
