/** @file Window.cpp
 *  @brief Method implementation for the window.
 *
 *  @author Gaina Stefan!
 *  @bug No known bugs.
 */

/***********************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                *
 **********************************************************************************************************************/

#include <exception>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <plog.h>

#include "Window.hpp"
#include "Renderer.hpp"

/***********************************************************************************************************************
 * METHOD DEFINITIONS                                                                                                  *
 **********************************************************************************************************************/

namespace Window
{

Window::Window(void) noexcept
	: m_windowHandle{ nullptr }
{
	plog_trace("Window is being constructed.");
}

Window::~Window(void) noexcept
{
	plog_trace("Window is being destructed.");
	if (nullptr != m_windowHandle)
	{
		destroy();
	}
}

void Window::create(bool isFullscreen) noexcept(false)
{
	RawRenderer rendererHandle = nullptr;
	int32_t     errorCode      = 0L;

	plog_info("Window is being created.");

	errorCode = SDL_Init(SDL_INIT_EVERYTHING); //TODO: Check if everything is really needed.
	if (0L != errorCode)
	{
		plog_fatal("SDL failed to initialize everything! (error code: %" PRId32 ")", errorCode);
		goto WINDOW_CLEAN;
	}

	m_windowHandle = SDL_CreateWindow("Heap-of-Battle-2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<uint32_t>(isFullscreen));
	if (nullptr == m_windowHandle)
	{
		plog_fatal("Window failed to be created!");
		goto WINDOW_CLEAN;
	}

	rendererHandle = SDL_CreateRenderer(m_windowHandle, -1L, (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
	if (nullptr == rendererHandle)
	{
		plog_fatal("Renderer failed to be created!");
		goto WINDOW_CLEAN;
	}

	errorCode = IMG_Init(IMG_INIT_PNG);
	if (IMG_INIT_PNG != errorCode)
	{
		plog_fatal("IMG failed to be initialized! (error code: %" PRId32 ")", errorCode);
		goto WINDOW_CLEAN;
	}

	errorCode = Mix_OpenAudio(44100L, MIX_DEFAULT_FORMAT, 2L, 2048L);
	if (0L > errorCode)
	{
		plog_fatal("Mixer failed to be opened! (error code: %" PRId32 ")", errorCode);
		goto WINDOW_CLEAN;
	}

	errorCode = SDL_SetRenderDrawBlendMode(rendererHandle, SDL_BLENDMODE_BLEND);
	if (0L != errorCode)
	{
		plog_warn("Renderer failed to be set in draw blend mode! (error code: %" PRId32 ") (SDL error message: %s)", errorCode, SDL_GetError());
	}

	errorCode = SDL_SetRenderDrawColor(rendererHandle, 0xFF, 0xFF, 0xFF, 0xFF); /*< white */
	if (0L != errorCode)
	{
		plog_warn("Renderer failed to set draw color to white! (error code: %" PRId32 ") (SDL error message: %s)", errorCode, SDL_GetError());
	}

	Renderer::getInstance().store(rendererHandle);

	return;

WINDOW_CLEAN:

	destroy();

	throw std::exception(SDL_GetError());
}

void Window::destroy(void) noexcept
{
	plog_debug("Window is being destroyed.");

	Renderer::getInstance().destroy();
	plog_info("Renderer was destroyed!");

	SDL_DestroyWindow(m_windowHandle);
	m_windowHandle = nullptr;
	plog_info("Window was destroyed!");

	IMG_Quit();
	plog_info("IMG was deinitialized!");

	Mix_Quit();
	plog_info("Mixer was deinitialized!");

	SDL_Quit();
	plog_info("SDL was deinitialized!");
}

} /*< namespace Window */
