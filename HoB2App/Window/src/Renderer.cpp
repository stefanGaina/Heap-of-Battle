/** @file Renderer.cpp
 *  @brief Method implementation for the renderer.
 *
 *  @author Gaina Stefan!
 *  @bug No known bugs.
 */

/***********************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                *
 **********************************************************************************************************************/

#include <exception>
#include <plog.h>

#include "Renderer.hpp"

/***********************************************************************************************************************
 * METHOD DEFINITIONS                                                                                                  *
 **********************************************************************************************************************/

namespace Window
{

Renderer& Renderer::getInstance(void) noexcept
{
	static Renderer rendererInstance;

	plog_verbose("Renderer instance is being got.");

	return rendererInstance;
}

Renderer::Renderer(void) noexcept
	: m_rendererHandle{ nullptr }
{
	plog_trace("Renderer is being constructed.");
}

Renderer::~Renderer(void) noexcept
{
	plog_trace("Renderer is being deconstructed.");
	destroy();
}

void Renderer::store(RawRenderer rendererHandle) noexcept
{
	plog_info("Renderer is being stored! (%p)", rendererHandle);
	if (nullptr == rendererHandle)
	{
		plog_error("Invalid renderer!");
		return;
	}

	if (nullptr != m_rendererHandle)
	{
		plog_warn("Renderer is already stored! (%p)", m_rendererHandle);
		return;
	}
	m_rendererHandle = rendererHandle;
}

SDL_Renderer* Renderer::load(void) const noexcept
{
	plog_verbose("Renderer is being loaded.");
	return m_rendererHandle;
}

void Renderer::clear(void) const noexcept(false)
{
	int32_t errorCode = 0L;

	plog_verbose("Renderer is being cleared.");

	errorCode = SDL_RenderClear(m_rendererHandle);
	if (0L != errorCode)
	{
		plog_warn("Renderer failed to be cleared! (error code: %d) (SDL error message: %s)", errorCode, SDL_GetError());
		throw(std::exception(SDL_GetError()));
	}
}

void Renderer::present(void) const noexcept
{
	plog_verbose("Renderer is being presented.");
	SDL_RenderPresent(m_rendererHandle);
}

void Renderer::destroy(void) noexcept
{
	plog_info("Renderer is being destroyed.");
	if (nullptr == m_rendererHandle)
	{
		plog_warn("Renderer is not initialized!");
		return;
	}
	SDL_DestroyRenderer(m_rendererHandle);
	m_rendererHandle = nullptr;
}

} /*< namespace Window */
