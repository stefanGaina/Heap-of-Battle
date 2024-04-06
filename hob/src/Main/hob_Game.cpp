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
 * @file hob_Game.cpp
 * @author Gaina Stefan
 * @date 23.07.2023
 * @brief This file implements the class defined in hob_Game.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Game.hpp"
#include "hob_MainMenu.hpp"
#include "hob_LocalMenu.hpp"
#include "hob_Map1.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

Game::Game(void) noexcept(false)
	: initializer{} /*< Can throw, but not handled here. */
	, window{}		/*< Can throw, but not handled here. */
	, cursor{ window.getRenderer() }
	, music{}
	, faction{}
	, server{}
	, socket{}
	, ping{}
{
	plog_trace("Game is being constructed.");
}

void Game::run(void) noexcept
{
	bool  isRunning = true;
	Scene nextScene = Scene::MAIN_MENU;

	plog_debug("Scene loop is being started!");
	plog_assert(nullptr != this);

	while (isRunning)
	{
		isRunning = doScene(nextScene);
	}
}

bool Game::doScene(Scene& nextScene) noexcept
{
	std::unique_ptr<Loop>		   sceneLoop	 = nullptr;
	std::unique_ptr<LoadingScreen> loadingScreen = nullptr;

	plog_debug("Scene is being executed.");
	plog_assert(nullptr != this);

	switch (nextScene)
	{
		case Scene::MAIN_MENU:
		{
			try
			{
				sceneLoop = std::make_unique<MainMenu>(window.getRenderer(), cursor, music);
			}
			catch (...)
			{
				plog_fatal("Failed to allocate memory for main menu scene! (bytes: %" PRIu64 ")", sizeof(MainMenu));
				return false;
			}
			break;
		}
		case Scene::LOCAL_MENU:
		{
			try
			{
				sceneLoop = std::make_unique<LocalMenu>(window.getRenderer(), cursor, &ping, music, faction, server, socket);
			}
			catch (...)
			{
				plog_fatal("Failed to allocate memory for local menu scene! (bytes: %" PRIu64 ")", sizeof(LocalMenu));
				nextScene = Scene::MAIN_MENU;
				return true;
			}
			break;
		}
		case Scene::MAP_1:
		{
			try
			{
				loadingScreen = std::make_unique<LoadingScreen>(window.getRenderer(), faction.getFaction());
			}
			catch (...)
			{
				plog_fatal("Failed to allocate memory for loading screen! (bytes: %" PRIu64 ")", sizeof(LoadingScreen));
				nextScene = Scene::MAIN_MENU;
				return true;
			}

			try
			{
				sceneLoop = std::make_unique<Map1>(window.getRenderer(), cursor, &ping, music, faction, server, socket, *loadingScreen);
			}
			catch (...)
			{
				plog_fatal("Failed to allocate memory for map 1 scene! (bytes: %" PRIu64 ")", sizeof(Map1));
				nextScene = Scene::MAIN_MENU;
				return true;
			}

			try
			{
				loadingScreen->waitOpponent(3000U, socket);
			}
			catch (...)
			{
				plog_error("Timeout while waiting for opponent occurred!");
				nextScene = Scene::MAIN_MENU;
				return true;
			}

			loadingScreen = nullptr;
			break;
		}
		case Scene::QUIT:
		{
			plog_info("Quit scene received!");
			return false;
		}
		default:
		{
			plog_fatal("Scene is invalid! (scene: %" PRId32 ")", static_cast<int32_t>(nextScene));
			plog_assert(false);
			return false;
		}
	}

	nextScene = sceneLoop->start();
	return true;
}

} /*< namespace hob */
