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
 * @file hob_Game.cpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 27.07.2023  Gaina Stefan               Added WSA.                                                  *
 * 29.08.2023  Gaina Stefan               Added LAN menu.                                             *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * 19.01.2024  Gaina Stefan               Changed SDL includes.                                       *
 * @details This file implements the class defined in hob_Game.hpp.                                   *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <iostream>
#include <memory>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <plog.h>

#include "hob_Game.hpp"
#include "hob_Version.hpp"
#include "hob_Window.hpp"
#include "hob_MainMenu.hpp"
#include "hob_LocalMenu.hpp"
#include "hob_Map1.hpp"
#include "hobServer_Version.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

void Game::run(void) noexcept(false)
{
	Window        window   = {};
	SDL_Renderer* renderer = nullptr;

	try
	{
		init();
	}
	catch (const std::exception& exception)
	{
		throw exception;
	}

	try
	{
		renderer = window.create();
	}
	catch (const std::exception& exception)
	{
		deinit();
		throw exception;
	}

#ifdef DEVEL_BUILD
	window.logInfo(renderer);
#endif /*< DEVEL_BUILD */

	sceneLoop(renderer);

	window.destroy();
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	deinit();
}

void Game::init(void) noexcept(false)
{
#ifndef PLOG_STRIP_ALL
	plog_Version_t     plogVersion      = plog_get_version();
#endif /*< PLOG_STRIP_ALL */
	SDL_version        sdlVersion       = {};
	const SDL_version* sdlVersionRef    = IMG_Linked_Version();
	hobServer::Version serverVersion    = {};

#ifndef PLOG_STRIP_ALL
	if (PLOG_VERSION_MAJOR != plogVersion.major
	 || PLOG_VERSION_MINOR != plogVersion.minor
	 || PLOG_VERSION_PATCH != plogVersion.patch)
	{
		plog_warn("Plog version mismatch! (compiled version: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ")\n", PLOG_VERSION_MAJOR, PLOG_VERSION_MINOR, PLOG_VERSION_PATCH);
	}

	plog_init("hob_logs.txt");
	plog_info("Using Plog %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", plogVersion.major, plogVersion.minor, plogVersion.patch);

	plog_info("Running Heap-of-Battle %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
#endif /*< PLOG_STRIP_ALL */

	SDL_GetVersion(&sdlVersion);
	plog_info("Using SDL %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", sdlVersion.major, sdlVersion.minor, sdlVersion.patch);
	if (SDL_MAJOR_VERSION != sdlVersion.major
	 || SDL_MINOR_VERSION != sdlVersion.minor
	 || SDL_PATCHLEVEL    != sdlVersion.patch)
	{
		plog_warn("SDL version mismatch! (compiled version: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ")", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);
	}

	plog_info("Using SDL image %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", sdlVersionRef->major, sdlVersionRef->minor, sdlVersionRef->patch);
	if (SDL_IMAGE_MAJOR_VERSION != sdlVersionRef->major
	 || SDL_IMAGE_MINOR_VERSION != sdlVersionRef->minor
	 || SDL_IMAGE_PATCHLEVEL    != sdlVersionRef->patch)
	{
		plog_warn("SDL image version mismatch! (compiled version: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ")", SDL_IMAGE_MAJOR_VERSION, SDL_IMAGE_MINOR_VERSION, SDL_IMAGE_PATCHLEVEL);
	}

	sdlVersionRef = Mix_Linked_Version();
	plog_info("Using SDL mixer %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", sdlVersionRef->major, sdlVersionRef->minor, sdlVersionRef->patch);
	if (SDL_MIXER_MAJOR_VERSION != sdlVersionRef->major
	 || SDL_MIXER_MINOR_VERSION != sdlVersionRef->minor
	 || SDL_MIXER_PATCHLEVEL    != sdlVersionRef->patch)
	{
		plog_warn("SDL image version mismatch! (compiled version: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ")", SDL_MIXER_MAJOR_VERSION, SDL_MIXER_MINOR_VERSION, SDL_MIXER_PATCHLEVEL);
	}

	sdlVersionRef = TTF_Linked_Version();
	if (SDL_TTF_MAJOR_VERSION != sdlVersionRef->major
	 || SDL_TTF_MINOR_VERSION != sdlVersionRef->minor
	 || SDL_TTF_PATCHLEVEL    != sdlVersionRef->patch)
	{
		plog_warn("SDL image version mismatch! (compiled version: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ")", SDL_TTF_MAJOR_VERSION, SDL_TTF_MINOR_VERSION, SDL_TTF_PATCHLEVEL);
	}

	plog_info("Using HOB server %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", serverVersion.getMajor(), serverVersion.getMinor(), serverVersion.getPatch());
	if (hobServer::VERSION_MAJOR != serverVersion.getMajor()
	 || hobServer::VERSION_MINOR != serverVersion.getMinor()
	 || hobServer::VERSION_PATCH != serverVersion.getPatch())
	{
		plog_warn("HOB server version mismatch! (compiled version: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ")", hobServer::VERSION_MAJOR, hobServer::VERSION_MINOR, hobServer::VERSION_PATCH);
	}

	if (0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		plog_fatal("SDL failed to be initialized! (error message: %s)", SDL_GetError());
		throw std::exception();
	}

	if (IMG_INIT_PNG != IMG_Init(IMG_INIT_PNG))
	{
		plog_fatal("SDL image failed to be initializzed! (error message: %s)", IMG_GetError());
		SDL_Quit();

		throw std::exception();
	}

	if (0 > Mix_OpenAudio(44100L, MIX_DEFAULT_FORMAT, 2L, 2048L))
	{
		plog_fatal("Mixer failed to be opened! (error message: %s)", Mix_GetError());
		IMG_Quit();
		SDL_Quit();

		throw std::exception();
	}

	if (0 != TTF_Init())
	{
		plog_error("TTF failed to be initialized! (error message: %s)", TTF_GetError());
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();

		throw std::exception();
	}
	plog_info("Everything initialized successfully!");
}

void Game::deinit(void) noexcept
{
	TTF_Quit();
	plog_info("SDL TTF has been cleaned up!");

	Mix_Quit();
	plog_info("SDL mixer has been cleaned up!");

	IMG_Quit();
	plog_info("SDL image has been cleaned up!");

	SDL_Quit();
	plog_info("SDL has been cleaned up!");

	plog_info("Plog is being deinitialized!");
#ifndef PLOG_STRIP_ALL
	plog_deinit();
#endif /*< PLOG_STRIP_ALL */
}

void Game::sceneLoop(SDL_Renderer* const renderer) noexcept
{
	Scene                 nextScene = Scene::MAIN_MENU;
	std::unique_ptr<Loop> sceneLoop = nullptr;
	Cursor                cursor    = { renderer };
	Music                 music     = {};
	Faction               faction   = {};
	hobServer::Server     server    = {};
	Socket                socket    = {};
	Ping                  ping      = {};

	plog_debug("Starting scene loop!");
	while (true)
	{
		switch (nextScene)
		{
			case Scene::MAIN_MENU:
			{
				try
				{
					sceneLoop = std::make_unique<MainMenu>(renderer, cursor, music);
				}
				catch (const std::bad_alloc& exception)
				{
					plog_fatal("Unable to allocate memory for main menu scene! (bytes: %" PRIu64 ")", sizeof(MainMenu));
					return;
				}
				break;
			}
			case Scene::LOCAL_MENU:
			{
				try
				{
					sceneLoop = std::make_unique<LocalMenu>(renderer, cursor, &ping, music, faction, server, socket);
				}
				catch (const std::bad_alloc& exception)
				{
					plog_fatal("Unable to allocate memory for local menu scene! (bytes: %" PRIu64 ")", sizeof(LocalMenu));
					nextScene = Scene::MAIN_MENU;
				}
				break;
			}
			case Scene::MAP_1:
			{
				try
				{
					sceneLoop = std::make_unique<Map1>(renderer, cursor, &ping, music, faction, server, socket);
				}
				catch (const std::bad_alloc& exception)
				{
					plog_fatal("Unable to allocate memory for map 1 scene! (bytes: %" PRIu64 ")", sizeof(Map1));
					nextScene = Scene::MAIN_MENU;
				}
				break;
			}
			case Scene::QUIT:
			{
				plog_info("Quit scene received!");
				return;
			}
			default:
			{
				plog_fatal("Scene is invalid! (scene: %" PRId32 ")", static_cast<int32_t>(nextScene));
				return;
			}
		}
		nextScene = sceneLoop->start();
		sceneLoop = nullptr;
	}
}

} /*< namespace hob */
