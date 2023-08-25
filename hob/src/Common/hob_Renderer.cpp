/******************************************************************************************************
 * @file hob_Renderer.cpp                                                                             *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 24.07.2023  Gaina Stefan               Changed it into a singleton.                                *
 * 25.08.2023  Gaina Stefan               Added const keyword.                                        *
 * @details This file implements the class defined in hob_Renderer.hpp.                               *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Renderer.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Renderer& Renderer::getInstance(void) noexcept
{
	static Renderer rendererInstance = {};

	plog_verbose("Renderer instance is being got.");

	return rendererInstance;
}

Renderer::Renderer(void) noexcept
	: m_renderer{ NULL }
{
	plog_trace("Renderer is being constructed.");
}

void Renderer::set(SDL_Renderer* const renderer) noexcept
{
	plog_info("Renderer is being set! (renderer: %p)", renderer);
	if (NULL == renderer)
	{
		plog_error("Invalid renderer!");
		return;
	}
	m_renderer = renderer;
}

SDL_Renderer* Renderer::get(void) const noexcept
{
	plog_verbose("Renderer is being got. (renderer: %p)", m_renderer);
	return m_renderer;
}

void Renderer::reset(void) noexcept
{
	plog_info("Renderer is being reseted! (renderer: %p)", m_renderer);
	SDL_DestroyRenderer(m_renderer);
	m_renderer = NULL;
}

} /*< namespace hob */
