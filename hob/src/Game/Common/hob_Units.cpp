#include <plog.h>

#include "hob_Units.hpp"
#include "hob_Faction.hpp"

namespace hob
{

Units::Units(void) noexcept
	: TextureInitializer
	{
		{
			HOB_TEXTURES_FILE_PATH("units/Infantry/Figure"), ""
		},
		{ /* No component is used. */ },
		{ /* No component is used. */ }
	}
	, m_components{}
{

}

void Units::draw(void) noexcept
{
	for (auto x : m_components)
	{
		x.draw();
	}
}

void Units::add(hobGame::Unit unit) noexcept
{
	Component component = {};

	component.updatePosition({ 0L, 0L, HSCALE, HSCALE });
	switch (unit)
	{
		case hobGame::Unit::INFANTRY:
		{
			component.updateTexture(m_textureContainer[0]);
			m_components.push_back(component);
			break;
		}
	}
}

} /*< namespace hob */
