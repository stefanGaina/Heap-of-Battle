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
 * @file hob_Loop.cpp
 * @author Gaina Stefan
 * @date 23.07.2023
 * @brief This file implements the class defined in hob_Loop.hpp.
 * @todo N/A.
 * @bug The execution is blocked when the window is being moved. This is a limitation on <i>Windows</i>.
 * (no longer the case on <i>Linux</i> because obviously it is better).
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDE
 *****************************************************************************************************/

#include <exception>
#include <plog.h>

#include "hob_Loop.hpp"
#include "hob_FramesPerSecond.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

Loop::Loop(SDL_Renderer* const renderer, Cursor& cursor, Ping* const ping) noexcept
	: renderer{ renderer }
	, cursor{ cursor }
	, ping{ ping }
	, nextScene{ Scene::QUIT }
	, isRunning{ false }
	, isStopRequested{ false }
{
	SDL_Event event = {};

	plog_trace("Loop is being constructed.");
	plog_assert(nullptr != renderer);

	event.type = SDL_MOUSEMOTION;
	if (1 != SDL_PushEvent(&event))
	{
		plog_warn("Failed to push mouse motion event! (SDL error message: %s)", SDL_GetError());
	}
}

Scene Loop::start(void) noexcept
{
	uint8_t failedRenderCount = 0U;

	plog_debug("Loop is being started.");
	plog_assert(nullptr != this);

	if (true == isStopRequested.load())
	{
		plog_debug("Loop has been stopped before start.");
		isStopRequested.store(false);
		return Scene::MAIN_MENU;
	}

	if (true == isRunning.load())
	{
		plog_warn("Loop is already started!");
		return Scene::QUIT;
	}

	isRunning.store(true);
	while (true == isRunning.load())
	{
		handleEvents();

		while (true)
		{
			try
			{
				render();
			}
			catch (...)
			{
				plog_fatal("Render failed, not handling events until graphics synchronize!");

				++failedRenderCount;
				if (UINT8_MAX == failedRenderCount)
				{
					plog_fatal("Maximum retry attempts reached! (failed count: %" PRIu16 ")", static_cast<uint16_t>(failedRenderCount));
					return Scene::QUIT;
				}

				continue;
			}

			failedRenderCount = 0U;
			break;
		}
	}

	return nextScene;
}

void Loop::stop(const Scene nextScene) noexcept
{
	plog_debug("Loop is being stopped.");
	plog_assert(nullptr != this);

	isStopRequested.store(true);

	if (false == isRunning.load())
	{
		plog_warn("Loop is already stopped!");
		return;
	}

	this->nextScene = nextScene;
	isRunning.store(false);
}

void Loop::handleEvents(void) noexcept
{
	SDL_Event event = {};

	plog_verbose("Events are being handled.");
	plog_assert(nullptr != this);

	while (1 == SDL_PollEvent(&event))
	{
		plog_verbose("Event received.");
		handleEvent(event);
	}
}

void Loop::render(void) noexcept(false)
{
	static FramesPerSecond framesPerSecond = { renderer };

	plog_verbose("Scene is being rendered.");
	plog_assert(nullptr != this);

	if (0 != SDL_RenderClear(renderer))
	{
		plog_error("Renderer failed to be cleared! (error message: %s)", SDL_GetError());
		throw std::exception();
	}

	draw();
	cursor.draw(renderer);
	framesPerSecond.draw(renderer);

	if (nullptr != ping)
	{
		ping->draw(renderer);
	}

	SDL_RenderPresent(renderer);
}

} /*< namespace hob */
