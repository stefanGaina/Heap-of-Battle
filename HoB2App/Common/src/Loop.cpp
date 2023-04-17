/** @file Loop.cpp
 *  @brief Method implementation for the loop.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

/****************************************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                                 *
 ***************************************************************************************************************************************/

#include <plog.h>

#include "Loop.hpp"
#include "Renderer.hpp"
#include "Cursor.hpp"

/****************************************************************************************************************************************
 * METHOD DEFINITIONS                                                                                                                   *
 ***************************************************************************************************************************************/

namespace Common
{

Loop::Loop(void) noexcept
	: m_isRunning{ false }
	, m_nextScene{ Scene::QUIT }
{
	Event   event     = {};
	int32_t errorCode = 0L;

	plog_trace("Loop is being constructed.");

	event.type = SDL_MOUSEMOTION;

	errorCode = SDL_PushEvent(&event);
	if (1L != errorCode)
	{
		plog_warn("Failed to push mouse motion event! (error code: %" PRId32 ") (SDL error message: %s)", errorCode, SDL_GetError());
	}
}

Scene Loop::startLoop(void) noexcept
{
	uint8_t  failedRenderCount = 0U;

	plog_debug("Loop is being started.");
	if (true == m_isRunning)
	{
		plog_warn("Loop is already started!");
		return m_nextScene;
	}

	m_isRunning = true;
	while (true == m_isRunning)
	{
		handleEvents();

SKIP_HANDLE_EVENTS:

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

			goto SKIP_HANDLE_EVENTS;
		}
		failedRenderCount = 0U;
	}

	return m_nextScene;
}

void Loop::stopLoop(Scene nextScene) noexcept
{
	plog_debug("Loop is being stopped.");
	if (false == m_isRunning)
	{
		plog_warn("Loop is already stopped!");
		return;
	}
	m_nextScene = nextScene;
	m_isRunning = false;
}

void Loop::handleEvents(void) noexcept
{
	Event event = {};

	plog_verbose("Events are being handled.");
	while (1L == SDL_PollEvent(&event))
	{
		plog_verbose("Event received.");
		handleEvent(event);
	}
}

void Loop::render(void) noexcept(false)
{
	size_t            index    = 0ULL;
	Window::Renderer& renderer = Window::Renderer::getInstance();

	plog_verbose("Scene is being rendered.");
	try
	{
		renderer.clear();
	}
	catch (std::exception& exception)
	{
		plog_fatal("Renderer failed to be cleared! (Exception message: %s)", exception.what());
		throw(exception);
	}

	draw();
	Utility::Cursor::getInstance().draw();

	renderer.present();
}

} /*< namespace Common */
