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
 * @file hob_Initializer.cpp
 * @author Gaina Stefan
 * @date 28.03.2024
 * @brief This file implements the class defined in hob_Initializer.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <plog.h>

#include "hob_Initializer.hpp"
#include "hob_Version.hpp"
#include "hobServer_Version.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

Initializer::Initializer(void) noexcept(false)
{
#ifndef PLOG_STRIP_ALL
	plog_Version_t plogVersion = plog_get_version();
#endif /*< PLOG_STRIP_ALL */
	SDL_version		   sdlVersion	 = { .major = 0U, .minor = 0U, .patch = 0U };
	const SDL_version* sdlVersionRef = IMG_Linked_Version();
	hobServer::Version serverVersion = {};

#ifndef PLOG_STRIP_ALL
	if (false == plog_init("hob_logs.txt"))
	{
		std::cout << "Failed to initialize logger!" << std::endl;
	}
	plog_expect(PLOG_VERSION_MAJOR == plogVersion.major && PLOG_VERSION_MINOR == plogVersion.minor && PLOG_VERSION_PATCH == plogVersion.patch);
#endif /*< PLOG_STRIP_ALL */
	plog_info("Using Plog %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", plogVersion.major, plogVersion.minor, plogVersion.patch);
	plog_info("Running Heap-of-Battle %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);

	SDL_GetVersion(&sdlVersion);
	plog_info("Using SDL %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", sdlVersion.major, sdlVersion.minor, sdlVersion.patch);
	plog_expect(SDL_MAJOR_VERSION == sdlVersion.major && SDL_MINOR_VERSION == sdlVersion.minor && SDL_PATCHLEVEL == sdlVersion.patch);

	plog_info("Using SDL image %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", sdlVersionRef->major, sdlVersionRef->minor, sdlVersionRef->patch);
	plog_expect(SDL_IMAGE_MAJOR_VERSION == sdlVersionRef->major && SDL_IMAGE_MINOR_VERSION == sdlVersionRef->minor && SDL_IMAGE_PATCHLEVEL == sdlVersionRef->patch);

	sdlVersionRef = Mix_Linked_Version();
	plog_info("Using SDL mixer %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", sdlVersionRef->major, sdlVersionRef->minor, sdlVersionRef->patch);
	plog_expect(SDL_MIXER_MAJOR_VERSION == sdlVersionRef->major && SDL_MIXER_MINOR_VERSION == sdlVersionRef->minor && SDL_MIXER_PATCHLEVEL == sdlVersionRef->patch);

	sdlVersionRef = TTF_Linked_Version();
	plog_expect(SDL_TTF_MAJOR_VERSION == sdlVersionRef->major && SDL_TTF_MINOR_VERSION == sdlVersionRef->minor && SDL_TTF_PATCHLEVEL == sdlVersionRef->patch);

	plog_info("Using HOB server %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", serverVersion.getMajor(), serverVersion.getMinor(), serverVersion.getPatch());
	plog_expect(hobServer::VERSION_MAJOR == serverVersion.getMajor() && hobServer::VERSION_MINOR == serverVersion.getMinor() &&
				hobServer::VERSION_PATCH == serverVersion.getPatch());

	if (0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		plog_fatal("Failed to initialize SDL! (error message: %s)", SDL_GetError());
		throw std::exception();
	}

	if (IMG_INIT_PNG != IMG_Init(IMG_INIT_PNG))
	{
		plog_fatal("Failed to initialize SDL image! (error message: %s)", IMG_GetError());
		SDL_Quit();

		throw std::exception();
	}

	if (0 > Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))
	{
		plog_fatal("Failed to initialize SDL mixer! (error message: %s)", Mix_GetError());
		IMG_Quit();
		SDL_Quit();

		throw std::exception();
	}

	if (0 != TTF_Init())
	{
		plog_error("Failed to initialize SDL TTF! (error message: %s)", TTF_GetError());
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();

		throw std::exception();
	}

	plog_info("Everything initialized successfully!");
}

Initializer::~Initializer(void) noexcept
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

} /*< namespace hob */
