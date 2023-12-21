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

#include <plog.h>

#include "hob_Units.hpp"
#include "hob_Faction.hpp"

namespace hob
{

Units::Units(SDL_Renderer* const renderer) noexcept
	: TextureInitializer
	{
		{
			HOB_TEXTURES_FILE_PATH("units/Infantry/Figure"), ""
		},
		{ /* No component is used. */ },
		{ /* No component is used. */ },
		{ renderer }
	}
	, components{}
{

}

void Units::draw(SDL_Renderer* const renderer) noexcept
{
	for (auto component : components)
	{
		component.draw(renderer);
	}
}

void Units::add(hobGame::Unit unit) noexcept
{
	Component component = {};

	component.updatePosition({ 0, 0, HSCALE, HSCALE });
	switch (unit)
	{
		case hobGame::Unit::INFANTRY:
		{
			component.updateTexture(textureContainer[0]);
			components.push_back(component);
			break;
		}
	}
}

} /*< namespace hob */
