/******************************************************************************************************
 * @file hob_Game.hpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file defines the function that runs the game.                                        *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_GAME_HPP_
#define HOB_GAME_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_Types.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Static class that initializes subsystems and run the scene loop of the game.
*/
class Game final
{
public:
	/**
	 * @brief Initializes all subsystems and runs the scenes of the game.
	 * @param void
	 * @return void
	*/
	static void run(void) noexcept(false);

private:
	/**
	 * @brief Checks for loaded libraries versions and initializes SDL, SDL image, SDL mixer and SDL ttf
	 * and Plog in case of development builds.
	 * @param void
	 * @return void
	*/
	static void init(void) noexcept(false);

	/**
	 * @brief Deinitializes SDL, SDL image, SDL mixer and SDL ttff and deinitializes Plog in case
	 * of development builds.
	 * @param void
	 * @return void
	*/
	static void deinit(void) noexcept;

	/**
	 * @brief Runs the game loop for the current scene.
	 * @param void
	 * @return void
	*/
	static void sceneLoop(void) noexcept;
};

} /*< namespace hob */

#endif /*< HOB_GAME_HPP_ */
