/******************************************************************************************************
 * @file hob_Tile.cpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added const keywords.                                       *
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
	: m_summerTexture{ NULL }
	, m_autumnTexture{ NULL }
	, m_winterTexture{ NULL }
	, m_springTexture{ NULL }
	, m_component    { NULL, { 0L, 0L, 0L, 0L } }
{
	plog_trace("Tile is being default constructed."); 
}

void Tile::init(SDL_Texture* const summerTexture, SDL_Texture* const autumnTexture, SDL_Texture* const winterTexture,
	SDL_Texture* const springTexture, const Coordinate position) noexcept
{
	plog_trace("Initializing tile. (position: %" PRId32 ", %" PRId32 ")", position.x, position.y);
	if (NULL == summerTexture || NULL == autumnTexture
	 || NULL == winterTexture || NULL == springTexture)
	{
		plog_warn("Tile is incomplete!");
	}

	if (0L > position.x || 26L < position.x
	 || 0L > position.x || 26L < position.x)
	{
		plog_warn("Invalid tile position! (position: %" PRId32 ", %" PRId32 ")", position.x, position.y);
	}

	m_summerTexture = summerTexture;
	m_autumnTexture = autumnTexture;
	m_winterTexture = winterTexture;
	m_springTexture = springTexture;

	m_component.updateTexture(m_summerTexture);
	m_component.updatePosition({ (position.x + 6L) * (SCALE / 2L), position.y * (SCALE / 2L), SCALE / 2L, SCALE / 2L });
}

void Tile::draw(void) noexcept
{
	plog_verbose("Tile is being drawn.");
	m_component.draw();
}

void Tile::changeTexture(const Season season) noexcept
{
	plog_trace("Tile texture is being changed. (season: %" PRId32 ")", static_cast<int32_t>(season));
	switch (season)
	{
		case Season::SUMMER:
		{
			if (NULL == m_summerTexture)
			{
				plog_warn("Tile is not changing texture!");
				break;
			}
			m_component.updateTexture(m_summerTexture);
			break;
		}
		case Season::AUTUMN:
		{
			if (NULL == m_autumnTexture)
			{
				plog_warn("Tile is not changing texture!");
				break;
			}
			m_component.updateTexture(m_autumnTexture);
			break;
		}
		case Season::WINTER:
		{
			if (NULL == m_winterTexture)
			{
				plog_warn("Tile is not changing texture!");
				break;
			}
			m_component.updateTexture(m_winterTexture);
			break;
		}
		case Season::SPRING:
		{
			if (NULL == m_springTexture)
			{
				plog_warn("Tile is not changing texture!");
				break;
			}
			m_component.updateTexture(m_springTexture);
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
