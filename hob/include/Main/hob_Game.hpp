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

#include <memory>

#include "hob_Initializer.hpp"
#include "hob_Window.hpp"
#include "hob_Loop.hpp"
#include "hob_Cursor.hpp"
#include "hob_Music.hpp"
#include "hob_Faction.hpp"
#include "hob_Socket.hpp"
#include "hob_Ping.hpp"
#include "hob_LoadingScreen.hpp"
#include "hobServer_Server.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

/** ***************************************************************************************************
 * @brief Main class that runs the scene loop of the game.
 * @details This stores the common data needed by the scenes (they need to persist without destructing
 * through scene changes), so the size of this class is large, consider instantiating it on the heap.
 *****************************************************************************************************/
class Game final
{
public:
	/** ***********************************************************************************************
	 * @brief Initializes all subsystems and creates the window.
	 * @param void
	 * @throws std::exception If the initialization of any of the subsystems fails or the creation of
	 * the window fails.
	 *************************************************************************************************/
	Game(void) noexcept(false);

	/** ***********************************************************************************************
	 * @brief
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void run(void) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Runs the game loop for the current scene.
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void doScene(void) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief TODO
	 *************************************************************************************************/
	Initializer initializer;

	/** ***********************************************************************************************
	 * @brief TODO
	 *************************************************************************************************/
	Window window;

	/** ***********************************************************************************************
	 * @brief TODO
	 *************************************************************************************************/
	Scene nextScene;

	/** ***********************************************************************************************
	 * @brief TODO
	 *************************************************************************************************/
	std::unique_ptr<Loop> sceneLoop;

	/** ***********************************************************************************************
	 * @brief TODO
	 *************************************************************************************************/
	Cursor cursor;

	/** ***********************************************************************************************
	 * @brief TODO
	 *************************************************************************************************/
	Music music;

	/** ***********************************************************************************************
	 * @brief TODO
	 *************************************************************************************************/
	Faction faction;

	/** ***********************************************************************************************
	 * @brief TODO
	 *************************************************************************************************/
	hobServer::Server server;

	/** ***********************************************************************************************
	 * @brief TODO
	 *************************************************************************************************/
	Socket socket;

	/** ***********************************************************************************************
	 * @brief TODO
	 *************************************************************************************************/
	Ping ping;

	/** ***********************************************************************************************
	 * @brief TODO
	 *************************************************************************************************/
	std::unique_ptr<LoadingScreen> loadingScreen;

	/** ***********************************************************************************************
	 * @brief TODO
	 *************************************************************************************************/
	bool isRunning;
};

} /*< namespace hob */

#endif /*< HOB_GAME_HPP_ */
