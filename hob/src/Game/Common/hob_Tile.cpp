/******************************************************************************************************
 * Heap of Battle Copyright (C) 2024                                                                  *
 *                                                                                                    *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the   *
 * authors be held liable for any damages arising from the use of this software.                      *
 *                                                                                                    *
 * Permission is granted to anyone to use this software for any purpose, including commercial         *
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:   *
 *                                                                                                    *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the   *
 *    original software. If you use this software in a product, an acknowledgment in the product      *
 *    documentation would be appreciated but is not required.                                         *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being *
 *    the original software.                                                                          *
 * 3. This notice may not be removed or altered from any source distribution.                         *
******************************************************************************************************/

/******************************************************************************************************
 * @file hob_Tile.cpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added const keywords.                                       *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file implements the class defined in hob_Tile.hpp.                                   *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Tile.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Tile::Tile(void) noexcept
	: summerTexture{ nullptr }
	, autumnTexture{ nullptr }
	, winterTexture{ nullptr }
	, springTexture{ nullptr }
	, component    { nullptr, { 0, 0, 0, 0 } }
{
	plog_trace("Tile is being default constructed.");
}

void Tile::init(SDL_Texture* const summerTexture, SDL_Texture* const autumnTexture, SDL_Texture* const winterTexture,
	SDL_Texture* const springTexture, const Coordinate position) noexcept
{
	plog_trace("Initializing tile. (position: %" PRId32 ", %" PRId32 ")", position.x, position.y);
	if (nullptr == summerTexture || nullptr == autumnTexture
	 || nullptr == winterTexture || nullptr == springTexture)
	{
		plog_warn("Tile is incomplete!");
	}

	if (0 > position.x || 26 < position.x
	 || 0 > position.x || 26 < position.x)
	{
		plog_warn("Invalid tile position! (position: %" PRId32 ", %" PRId32 ")", position.x, position.y);
	}

	this->summerTexture = summerTexture;
	this->autumnTexture = autumnTexture;
	this->winterTexture = winterTexture;
	this->springTexture = springTexture;

	component.updateTexture(summerTexture);
	component.updatePosition({ .x = (position.x + 6) * HSCALE, .y = position.y * HSCALE, .w = HSCALE, .h = HSCALE });
}

void Tile::draw(SDL_Renderer* const renderer) noexcept
{
	plog_verbose("Tile is being drawn.");
	plog_assert(nullptr != renderer);

	component.draw(renderer);
}

void Tile::changeTexture(const Season season) noexcept
{
	plog_trace("Tile texture is being changed. (season: %" PRId32 ")", static_cast<int32_t>(season));
	switch (season)
	{
		case Season::SUMMER:
		{
			if (nullptr == summerTexture)
			{
				plog_warn("Tile is not changing texture!");
				break;
			}

			component.updateTexture(summerTexture);
			break;
		}
		case Season::AUTUMN:
		{
			if (nullptr == autumnTexture)
			{
				plog_warn("Tile is not changing texture!");
				break;
			}

			component.updateTexture(autumnTexture);
			break;
		}
		case Season::WINTER:
		{
			if (nullptr == winterTexture)
			{
				plog_warn("Tile is not changing texture!");
				break;
			}

			component.updateTexture(winterTexture);
			break;
		}
		case Season::SPRING:
		{
			if (nullptr == springTexture)
			{
				plog_warn("Tile is not changing texture!");
				break;
			}

			component.updateTexture(springTexture);
			break;
		}
		default:
		{
			plog_error("Invalid season! (season: %" PRId32 ")", static_cast<int32_t>(season));
			break;
		}
	}
}

} /*< namespace hob */
