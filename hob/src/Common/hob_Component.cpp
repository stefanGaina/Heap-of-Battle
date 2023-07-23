/******************************************************************************************************
 * @file hob_Component.cpp                                                                            *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file implements the class defined in hob_Component.hpp.                              *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Component.hpp"
#include "hob_Renderer.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Component::Component(SDL_Texture* texture, SDL_Rect destination) noexcept
	: m_texture    { texture }
	, m_destination{ destination }
{
	plog_trace("Component is being constructed.");
}

void Component::draw(void) noexcept
{
	int32_t errorCode = 0L;

	plog_verbose("Component is being drawn.");
	if (NULL == m_texture)
	{
		plog_verbose("Invalid texture!");
		return;
	}

	errorCode = SDL_RenderCopy(Renderer::get(), m_texture, NULL, &m_destination);
	if (0L != errorCode)
	{
		plog_warn("Renderer failed to copy texture! (error code: %" PRId32 ") (SDL error message: %s)", errorCode, SDL_GetError());
	}
}

void Component::updateTexture(SDL_Texture* texture) noexcept
{
	plog_verbose("Component's texture is being updated. (texture: %p)", texture);
	m_texture = texture;
}

void Component::updatePosition(SDL_Rect destination) noexcept
{
	plog_verbose("Component's position is being updated. (destination: %" PRId32 ", %" PRId32 ", %" PRId32 ", %" PRId32 ")",
		destination.x, destination.y, destination.w, destination.h);
	m_destination = destination;
}

void Component::correctPosition(SDL_Rect corrections) noexcept
{
	plog_verbose("Component is being corrected. (corrections: %" PRId32 ", %" PRId32 ", %" PRId32 ", %" PRId32 ")",
		corrections.x, corrections.y, corrections.w, corrections.h);

	m_destination.x += corrections.x;
	m_destination.y += corrections.y;
	m_destination.w += corrections.w;
	m_destination.h += corrections.h;
}

bool Component::isMouseInside(hob::Coordinate mouse, SDL_Rect corrections) const noexcept
{
	int32_t verticalBeginning   = m_destination.y                   + corrections.y;
	int32_t verticalEnding      = m_destination.y + m_destination.h + corrections.h;
	int32_t horizontalBeginning = m_destination.x                   + corrections.x;
	int32_t horizontalEnding    = m_destination.x + m_destination.w + corrections.w;

	plog_verbose("Checking if mouse is inside component. (mouse: { %" PRId32 ", %" PRId32 " }, corrections: { %" PRId32 ", %" PRId32 ", %" PRId32 ", %" PRId32 " })",
		mouse.x, mouse.y, corrections.x, corrections.y, corrections.w, corrections.h);

	return verticalBeginning   < mouse.y && verticalEnding   > mouse.y
		&& horizontalBeginning < mouse.x && horizontalEnding > mouse.x;
}

SDL_Texture* Component::getRawTexture(void) const noexcept
{
	plog_verbose("Texture is being got.");
	return m_texture;
}

} /*< namespace hob */
