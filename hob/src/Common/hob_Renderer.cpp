/******************************************************************************************************
 * @file hob_Renderer.cpp                                                                             *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
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

SDL_Renderer* Renderer::s_renderer = NULL;

void Renderer::set(SDL_Renderer* renderer)
{
	plog_info("Renderer is being set! (renderer: %p)", renderer);
	if (NULL == renderer)
	{
		plog_error("Invalid renderer!");
		return;
	}
	s_renderer = renderer;
}

SDL_Renderer* Renderer::get(void)
{
	plog_verbose("Renderer is being got. (renderer: %p)", s_renderer);
	return s_renderer;
}

void Renderer::reset(void)
{
	plog_info("Renderer is being reseted! (renderer: %p)", s_renderer);
	SDL_DestroyRenderer(s_renderer);
	s_renderer = NULL;
}

} /*< namespace hob */
