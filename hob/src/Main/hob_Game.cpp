/******************************************************************************************************
 * @file hob_Game.cpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file implements the class defined in hob_Game.hpp.                                   *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <iostream>
#include <memory>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <plog.h>

#include "hob_Game.hpp"
#include "hob_Version.hpp"
#include "hob_Window.hpp"
#include "hob_MainMenu.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

void Game::run(void) noexcept(false)
{
	Window window = {};

	Window::hideTerminal();
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
		window.create();
	}
	catch(const std::exception& exception)
	{
		deinit();
		throw exception;
	}

#ifdef DEVEL_BUILD
	window.logInfo();
#endif /*< DEVEL_BUILD */

	sceneLoop();

	window.destroy();
	deinit();
}

void Game::init(void) noexcept(false)
{
#ifdef DEVEL_BUILD
	plog_Version_t     plogVersion   = {};
#endif /*< DEVEL_BUILD */
	SDL_version        sdlVersion    = {};
	const SDL_version* sdlVersionRef = NULL;
	int32_t            errorCode     = 0L;

#ifdef DEVEL_BUILD
	plogVersion = plog_get_version();
	if (PLOG_VERSION_MAJOR != plogVersion.major
	 || PLOG_VERSION_MINOR != plogVersion.minor
	 || PLOG_VERSION_PATCH != plogVersion.patch)
	{
		std::cout << "Plog version mismatch! (compiled version: " << PLOG_VERSION_MAJOR << "." << PLOG_VERSION_MINOR << "." << PLOG_VERSION_PATCH << ")" << std::endl;
		throw std::exception();
	}
	plog_init(NULL);
	plog_info("Using Plog %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", plogVersion.major, plogVersion.minor, plogVersion.patch);
#endif /*< DEVEL_BUILD */

	plog_info("Running Heap-of-Battle %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", hob::VERSION_MAJOR, hob::VERSION_MINOR, hob::VERSION_PATCH);

	SDL_GetVersion(&sdlVersion);
	plog_info("Using SDL %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", sdlVersion.major, sdlVersion.minor, sdlVersion.patch);
	if (SDL_MAJOR_VERSION != sdlVersion.major
	 || SDL_MINOR_VERSION != sdlVersion.minor
	 || SDL_PATCHLEVEL    != sdlVersion.patch)
	{
		plog_fatal("SDL version mismatch! (compiled version: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ")", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);
		throw std::exception();
	}

	sdlVersionRef = IMG_Linked_Version();
	plog_info("Using SDL image %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", sdlVersionRef->major, sdlVersionRef->minor, sdlVersionRef->patch);
	if (SDL_IMAGE_MAJOR_VERSION != sdlVersionRef->major
	 || SDL_IMAGE_MINOR_VERSION != sdlVersionRef->minor
	 || SDL_IMAGE_PATCHLEVEL    != sdlVersionRef->patch)
	{
		plog_fatal("SDL image version mismatch! (compiled version: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ")", SDL_IMAGE_MAJOR_VERSION, SDL_IMAGE_MINOR_VERSION, SDL_IMAGE_PATCHLEVEL);
		throw std::exception();
	}

	sdlVersionRef = Mix_Linked_Version();
	plog_info("Using SDL mixer %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", sdlVersionRef->major, sdlVersionRef->minor, sdlVersionRef->patch);
	if (SDL_MIXER_MAJOR_VERSION != sdlVersionRef->major
	 || SDL_MIXER_MINOR_VERSION != sdlVersionRef->minor
	 || SDL_MIXER_PATCHLEVEL    != sdlVersionRef->patch)
	{
		plog_fatal("SDL image version mismatch! (compiled version: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ")", SDL_MIXER_MAJOR_VERSION, SDL_MIXER_MINOR_VERSION, SDL_MIXER_PATCHLEVEL);
		throw std::exception();
	}

	sdlVersionRef = TTF_Linked_Version();
	if (SDL_TTF_MAJOR_VERSION != sdlVersionRef->major
	 || SDL_TTF_MINOR_VERSION != sdlVersionRef->minor
	 || SDL_TTF_PATCHLEVEL    != sdlVersionRef->patch)
	{
		plog_fatal("SDL image version mismatch! (compiled version: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ")", SDL_TTF_MAJOR_VERSION, SDL_TTF_MINOR_VERSION, SDL_TTF_PATCHLEVEL);
		throw std::exception();
	}

	errorCode = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (0L != errorCode)
	{
		plog_fatal("SDL failed to be initialized! (error code: %" PRId32 ") (error message: %s)", errorCode, SDL_GetError());
		throw std::exception();
	}

	errorCode = IMG_Init(IMG_INIT_PNG);
	if (IMG_INIT_PNG != errorCode)
	{
		plog_fatal("SDL image failed to be initializzed! (error code: %" PRId32 ") (error message: %s)", errorCode, IMG_GetError());
		SDL_Quit();

		throw std::exception();
	}

	errorCode = Mix_OpenAudio(44100L, MIX_DEFAULT_FORMAT, 2L, 2048L);
	if (0L > errorCode)
	{
		plog_fatal("Mixer failed to be opened! (error code: %" PRId32 ") (error message: %s)", errorCode, Mix_GetError());
		IMG_Quit();
		SDL_Quit();

		throw std::exception();
	}

	errorCode = TTF_Init();
	if (0L != errorCode)
	{
		plog_error("TTF failed to be initialized! (error code: %" PRId32 ") (error message: %s)", errorCode, TTF_GetError());
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
	plog_info("SDL TTF was cleaned up!");

	Mix_Quit();
	plog_info("SDL mixer was cleaned up!");

	IMG_Quit();
	plog_info("SDL image was cleaned up!");

	SDL_Quit();
	plog_info("SDL was cleaned up!");

#ifdef DEVEL_BUILD
	// plog_info("Plog is being deinitialized!");
	// plog_deinit(); <- Calling this is optional, commented for logs in destructors to appear in file.
#endif /*< DEVEL_BUILD */
}

void Game::sceneLoop(void) noexcept
{
	Scene                 nextScene = Scene::MAIN_MENU;
	std::shared_ptr<Loop> sceneLoop = nullptr;

	plog_debug("Starting scene loop!");
	while (true)
	{
		switch (nextScene)
		{
			case Scene::MAIN_MENU:
			{
				try
				{
					sceneLoop = std::make_shared<MainMenu>();
				}
				catch (const std::bad_alloc& exception)
				{
					plog_fatal("Unable to allocate memory for main menu scene!");
					return;
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
