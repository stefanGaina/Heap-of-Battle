#include <plog.h>

#include "Tile.hpp"

namespace Game
{

Tile::Tile(void) noexcept
	: m_summerTexture{ nullptr }
	, m_autumnTexture{ nullptr }
	, m_winterTexture{ nullptr }
	, m_springTexture{ nullptr }
	, m_component    { nullptr, { 0L, 0L, 0L, 0L } }
{
	plog_trace("Tile is being default constructed."); 
}

Tile::~Tile(void) noexcept
{
	plog_trace("Tile is being destructed.");
}

void Tile::init(RawTexture summerTexture, RawTexture autumnTexture, RawTexture winterTexture, RawTexture springTexture, Coordinate position) noexcept
{
	plog_trace("Initializing tile. (position: %" PRId32 ", %" PRId32 ")", position.x, position.y);
	if (nullptr == summerTexture || nullptr == autumnTexture
	 || nullptr == winterTexture || nullptr == springTexture)
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

void Tile::changeTexture(Season season) noexcept
{
	plog_trace("Tile texture is being changed. (season: %" PRId32 ")", static_cast<int32_t>(season));
	switch (season)
	{
		case Season::SUMMER:
		{
			if (nullptr == m_summerTexture)
			{
				plog_warn("Tile is not changing texture!");
				break;
			}
			m_component.updateTexture(m_summerTexture);
			break;
		}
		case Season::AUTUMN:
		{
			if (nullptr == m_autumnTexture)
			{
				plog_warn("Tile is not changing texture!");
				break;
			}
			m_component.updateTexture(m_autumnTexture);
			break;
		}
		case Season::WINTER:
		{
			if (nullptr == m_winterTexture)
			{
				plog_warn("Tile is not changing texture!");
				break;
			}
			m_component.updateTexture(m_winterTexture);
			break;
		}
		case Season::SPRING:
		{
			if (nullptr == m_springTexture)
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

} /*< namespace Game */
