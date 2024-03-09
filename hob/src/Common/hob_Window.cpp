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
 * @file hob_Window.cpp
 * @author Gaina Stefan
 * @date 23.07.2023
 * @brief This file implements the class defined in hob_Window.hpp.
 * @todo Find a way to change executable icon and how it appears in task bar. Also setIcon() is
 * currently commented because Linux Mint window does not have an icon.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <exception>
#include <plog.h>

#include "hob_Window.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

SDL_Renderer* Window::create(void) noexcept(false)
{
	SDL_Renderer* renderer = nullptr;

	plog_debug("Window is being created.");
	plog_assert(nullptr != this);
	plog_assert(nullptr == window);

	window = SDL_CreateWindow("Heap-of-Battle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0U);
	if (nullptr == window)
	{
		plog_fatal("Window failed to be created! (SDL error message: %s)", SDL_GetError());
		throw std::exception();
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (nullptr == renderer)
	{
		plog_fatal("Renderer failed to be created! (SDL error message: %s)", SDL_GetError());
		SDL_DestroyWindow(window);
		window = nullptr;

		throw std::exception();
	}

	if (0 != SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND))
	{
		plog_warn("Renderer failed to be set in draw blend mode! (SDL error message: %s)", SDL_GetError());
	}

	if (0 != SDL_SetRenderDrawColor(renderer, 0x00U, 0x00U, 0x00U, 0xFFU)) /*< black */
	{
		plog_warn("Renderer failed to set draw color to white! (SDL error message: %s)", SDL_GetError());
	}

	plog_info("Window has been created successfully!");
	return renderer;
}

void Window::destroy(void) noexcept
{
	plog_debug("Window is being destroyed.");
	plog_assert(nullptr != this);
	plog_assert(nullptr != window);

	SDL_DestroyWindow(window);
	window = nullptr;
	plog_info("Window was destroyed successfully!");
}

// void Window::setIcon(void) const noexcept
// {
// 	static const char* const ICON_FILE_PATH = HOB_TEXTURES_FILE_PATH("miscellaneous/icon");

// 	SDL_Surface* iconSurface = nullptr;

// 	plog_debug("Window icon is being set.");

// 	iconSurface = IMG_Load(ICON_FILE_PATH);
// 	if (nullptr == iconSurface)
// 	{
// 		plog_error("Failed to load icon! (file path: %s) (SDL error message: %s)", ICON_FILE_PATH, SDL_GetError());
// 		return;
// 	}
// 	plog_info("Window icon has been set successfully!");

// 	SDL_SetWindowIcon(window, iconSurface);
// 	SDL_FreeSurface(iconSurface);
// }

#ifdef DEVEL_BUILD

void Window::logInfo(SDL_Renderer* const renderer) const noexcept
{
	SDL_RendererInfo rendererInfo	= {};
	SDL_PowerState	 powerState		= SDL_POWERSTATE_UNKNOWN;
	int32_t			 secondsLeft	= 0;
	int32_t			 batteryPercent = 0;

	plog_trace("Information is being logged.");
	plog_assert(nullptr != this);
	plog_assert(nullptr != renderer);

	if (0 != SDL_GetRendererInfo(renderer, &rendererInfo))
	{
		plog_warn("Failed to get renderer information! (SDL error message: %s)", SDL_GetError());
	}
	else
	{
		plog_info("Renderer information! (name: %s, flags: %" PRIu32 ", max width: %" PRId32 ", max height: %" PRId32 ")", rendererInfo.name, rendererInfo.flags,
				  rendererInfo.max_texture_width, rendererInfo.max_texture_height);
	}

	powerState = SDL_GetPowerInfo(&secondsLeft, &batteryPercent);
	plog_info("Power information! (state: %" PRId32 ", seconds left: %" PRId32 ", battery: %" PRId32 "%%)", powerState, secondsLeft, batteryPercent);
}

#endif /*< DEVEL_BUILD */

} /*< namespace hob */
