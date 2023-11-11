/******************************************************************************************************
 * @file hob_Window.cpp                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 24.07.2023  Gaina Stefan               Updated the renderer get.                                   *
 * 26.08.2023  Gaina Stefan               Improved logs.                                              *
 * @details This file implements the class defined in hob_Window.hpp.                                 *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <exception>
#include <Windows.h>
#include <SDL_image.h>
#include <plog.h>

#include "hob_Window.hpp"
#include "hob_Renderer.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

void Window::hideTerminal(void) noexcept
{
	HWND consoleHandle = GetConsoleWindow();

	plog_debug("Terminal is being hidden.");
	if (TRUE == IsWindowVisible(consoleHandle))
	{
		plog_info("Terminal has been hidden!");
		(void)ShowWindow(consoleHandle, SW_HIDE);
	}
}

Window::Window(void) noexcept
	: m_window{ NULL }
{
	plog_trace("Window is being constructed. (size: %" PRIu64 ") (1: %" PRIu64 ")", sizeof(*this), sizeof(m_window));
}

void Window::create(void) noexcept(false)
{
	SDL_Renderer* renderer  = NULL;
	int32_t       errorCode = 0L;

	plog_debug("Window is being created.");

	m_window = SDL_CreateWindow("Heap-of-Battle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0UL);
	if (NULL == m_window)
	{
		plog_fatal("Window failed to be created! (SDL error message: %s)", SDL_GetError());
		throw std::exception();
	}

	renderer = SDL_CreateRenderer(m_window, -1L, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (NULL == renderer)
	{
		plog_fatal("Renderer failed to be created! (SDL error message: %s)", SDL_GetError());
		SDL_DestroyWindow(m_window);
		m_window = NULL;

		throw std::exception();
	}
	Renderer::getInstance().set(renderer);

	errorCode = SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	if (0L != errorCode)
	{
		plog_warn("Renderer failed to be set in draw blend mode! (error code: %" PRId32 ") (SDL error message: %s)", errorCode, SDL_GetError());
	}

	errorCode = SDL_SetRenderDrawColor(renderer, 0x00U, 0x00U, 0x00U, 0xFFU); /*< black */
	if (0L != errorCode)
	{
		plog_warn("Renderer failed to set draw color to white! (error code: %" PRId32 ") (SDL error message: %s)", errorCode, SDL_GetError());
	}
	plog_info("Window has been created successfully!");
}

void Window::destroy(void) noexcept
{
	plog_debug("Window is being destroyed.");
	Renderer::getInstance().reset();

	SDL_DestroyWindow(m_window);
	m_window = NULL;
	plog_info("Window was destroyed successfully!");
}

void Window::setIcon(void) const noexcept
{
	static const char* const ICON_FILE_PATH = HOB_TEXTURES_FILE_PATH("miscellaneous/icon");

	SDL_Surface* iconSurface = NULL;

	plog_debug("Window icon is being set.");

	iconSurface = IMG_Load(ICON_FILE_PATH);
	if (NULL == iconSurface)
	{
		plog_error("Failed to load icon! (file path: %s) (SDL error message: %s)", ICON_FILE_PATH, SDL_GetError());
		return;
	}
	plog_info("Window icon has been set successfully!");

	SDL_SetWindowIcon(m_window, iconSurface);
	SDL_FreeSurface(iconSurface);
}

#ifdef DEVEL_BUILD
void Window::logInfo(void) const noexcept
{
	SDL_RendererInfo rendererInfo   = {};
	int32_t          errorCode      = 0L;
	SDL_PowerState   powerState     = SDL_POWERSTATE_UNKNOWN;
	int32_t          secondsLeft    = 0L;
	int32_t          batteryPercent = 0L;

	plog_trace("Information is being logged.");

	errorCode = SDL_GetRendererInfo(Renderer::getInstance().get(), &rendererInfo);
	if (0L != errorCode)
	{
		plog_warn("Failed to get renderer information! (SDL error message: %s)", SDL_GetError());
	}
	else
	{
		plog_info("Renderer information! (name: %s, flags: %" PRIu32 ", max width: %" PRId32 ", max height: %" PRId32 ")",
			rendererInfo.name, rendererInfo.flags, rendererInfo.max_texture_width, rendererInfo.max_texture_height);
	}
	powerState = SDL_GetPowerInfo(&secondsLeft, &batteryPercent);
	plog_info("Power information! (state: %" PRId32 ", seconds left: %" PRId32 ", battery: %" PRId32 "%%)", powerState, secondsLeft, batteryPercent);
}
#endif /*< DEVEL_BUILD */

} /*< namespace hob */
