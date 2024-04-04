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
 * @file hob_Component.cpp
 * @author Gaina Stefan
 * @date 23.07.2023
 * @brief This file implements the class defined in hob_Component.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Component.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

Component::Component(SDL_Texture* const texture, const SDL_Rect destination) noexcept
	: destination{ destination }
	, texture{ texture }
{
	plog_trace("Component is being constructed.");
}

void Component::draw(SDL_Renderer* const renderer) noexcept
{
	plog_verbose("Component is being drawn.");
	plog_assert(nullptr != this);
	plog_assert(nullptr != renderer);

	if (nullptr == texture)
	{
		plog_verbose("Invalid texture!");
		return;
	}

	if (0 != SDL_RenderCopy(renderer, texture, nullptr, &destination))
	{
		plog_warn("Renderer failed to copy texture! (SDL error message: %s)", SDL_GetError());
	}
}

void Component::updateTexture(SDL_Texture* const texture) noexcept
{
	plog_verbose("Component's texture is being updated. (texture: 0x%p)", texture);
	plog_assert(nullptr != this);

	this->texture = texture;
}

void Component::updateTexture(const Texture& texture) noexcept
{
	plog_verbose("Component's texture is being updated. (texture: 0x%p)", texture.getRawTexture());
	plog_assert(nullptr != this);

	this->texture = texture.getRawTexture();
}

void Component::updatePosition(const SDL_Rect destination) noexcept
{
	plog_verbose("Component's position is being updated. (destination: %" PRId32 ", %" PRId32 ", %" PRId32 ", %" PRId32 ")", destination.x, destination.y,
				 destination.w, destination.h);
	plog_assert(nullptr != this);

	this->destination = destination;
}

void Component::correctPosition(const SDL_Rect corrections) noexcept
{
	plog_verbose("Component is being corrected. (corrections: %" PRId32 ", %" PRId32 ", %" PRId32 ", %" PRId32 ")", corrections.x, corrections.y, corrections.w,
				 corrections.h);
	plog_assert(nullptr != this);

	destination.x += corrections.x;
	destination.y += corrections.y;
	destination.w += corrections.w;
	destination.h += corrections.h;
}

bool Component::isMouseInside(const Coordinate mouse, const SDL_Rect corrections) const noexcept
{
	const int32_t verticalBeginning	  = destination.y + corrections.y;
	const int32_t verticalEnding	  = destination.y + destination.h + corrections.h;
	const int32_t horizontalBeginning = destination.x + corrections.x;
	const int32_t horizontalEnding	  = destination.x + destination.w + corrections.w;

	plog_verbose("Checking if mouse is inside component. (mouse: { %" PRId32 ", %" PRId32 " }, corrections: { %" PRId32 ", %" PRId32 ", %" PRId32 ", %" PRId32
				 " })",
				 mouse.x, mouse.y, corrections.x, corrections.y, corrections.w, corrections.h);
	plog_assert(nullptr != this);

	return verticalBeginning < mouse.y && verticalEnding > mouse.y && horizontalBeginning < mouse.x && horizontalEnding > mouse.x;
}

SDL_Texture* Component::getRawTexture(void) const noexcept
{
	plog_verbose("Texture is being got.");
	plog_assert(nullptr != this);

	return texture;
}

bool Component::operator==(const Texture& texture) const noexcept
{
	plog_assert(nullptr != this);
	return texture.getRawTexture() == this->texture;
}

} /*< namespace hob */
