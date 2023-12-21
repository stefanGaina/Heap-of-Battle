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
 * @file hob_Menu.cpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * 29.08.2023  Gaina Stefan               Refactored.                                                 *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file implements the class defined in hob_Menu.hpp.                                   *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Menu.hpp"
#include "hob_Faction.hpp"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief Full file path of an image of a building.
 * @param name: The name of the image (without extension).
 * @return The full file path.
*/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("game_menu/" name)

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Menu::Menu(SDL_Renderer* const renderer, const uint8_t gold) noexcept
	: TextureInitializer
	{
		{
			true == Faction::getInstance().getFaction() ? TEXTURE_FILE_PATH("background_alliance") : TEXTURE_FILE_PATH("background_horde"), /*< 0 */
			TEXTURE_FILE_PATH("frame_selected_alliance")                                                                                  , /*< 1 */
			TEXTURE_FILE_PATH("frame_selected_horde")                                                                                     , /*< 2 */
			TEXTURE_FILE_PATH("frame_unselected_alliance")                                                                                , /*< 3 */
			TEXTURE_FILE_PATH("frame_unselected_horde")                                                                                   , /*< 4 */
			TEXTURE_FILE_PATH("hourglass_inactive")                                                                                         /*< 5 */
		},
		{
			0UL,
			true == Faction::getInstance().getFaction() ? 3UL : 4UL,
			true == Faction::getInstance().getFaction() ? 3UL : 4UL,
			5UL,
			true == Faction::getInstance().getFaction() ? 3UL : 4UL,
			true == Faction::getInstance().getFaction() ? 3UL : 4UL,
			true == Faction::getInstance().getFaction() ? 3UL : 4UL,
			true == Faction::getInstance().getFaction() ? 3UL : 4UL,
			true == Faction::getInstance().getFaction() ? 3UL : 4UL,
			1UL
		},
		{
			{
				{ 0             , 0                      , 6 * HSCALE, 15 * HSCALE },
				{ 0             , 0                      , 3 * HSCALE, 1  * HSCALE },
				{ 3 * HSCALE    , 0                      , 3 * HSCALE, 1  * HSCALE },
				{ 5 * HSCALE + 3, 1                      , 1 * HSCALE, 1  * HSCALE },
				{ 0             , 1 * HSCALE + HSCALE / 2, 3 * HSCALE, 1  * HSCALE },
				{ 0             , 3 * HSCALE             , 3 * HSCALE, 1  * HSCALE },
				{ 0             , 4 * HSCALE + HSCALE / 2, 3 * HSCALE, 1  * HSCALE },
				{ 0             , 6 * HSCALE             , 3 * HSCALE, 1  * HSCALE },
				{ 0             , 7 * HSCALE + HSCALE / 2, 3 * HSCALE, 1  * HSCALE },
				{ 0             , 0                      , 0         , 0           }
			}
		},
		{ renderer }
	}
	, timer{ renderer }
	, gold { renderer, gold }
	, icons{ renderer }
{
	plog_trace("Game menu is being constructed.");
}

void Menu::draw(SDL_Renderer* const renderer) noexcept
{
	plog_verbose("Game menu is being drawn.");

	TextureInitializer::draw(renderer);
	timer.draw(renderer);
	gold.draw(renderer);
	icons.draw(renderer);
}

Action Menu::handleClick(Coordinate click, hobGame::MenuMode menuMode) noexcept
{
	size_t index = 0UL;

	plog_verbose("Menu is handling click. (click: %" PRId32 ", %" PRId32 ")", click.x, click.y);
	if (6 * HSCALE < click.x || 15 * HSCALE < click.y)
	{
		switch (menuMode)
		{
			case hobGame::MenuMode::EMPTY:
			{
				for (index = 4UL; index < 9UL; ++index)
				{
					componentContainer[index].updateTexture(nullptr);
				}
				break;
			}
			case hobGame::MenuMode::UNCHANGED:
			{
				break;
			}
			case hobGame::MenuMode::ALLIANCE_KEEP:
			{
				for (index = 4UL; index < 9UL; ++index)
				{
					componentContainer[index].updateTexture(textureContainer[true == Faction::getInstance().getFaction() ? 3UL : 4UL]);
				}
				icons.setAllianceKeep();
				break;
			}
			case hobGame::MenuMode::HORDE_KEEP:
			{
				break;
			}
			default:
			{
				plog_error("Invalid menu mode! (mode: %" PRId32 ")", static_cast<int32_t>(menuMode));
				break;
			}
		}
		return Action::NOTHING;
	}

	if (nullptr == componentContainer[9].getRawTexture())
	{
		return Action::NOTHING;
	}

	if (3 * HSCALE > click.x && HSCALE + HSCALE / 2 < click.y && 2 * HSCALE + HSCALE / 2 > click.y)
	{
		return Action::RECRUIT_INFANTRY;
	}

	return Action::NOTHING;
}

void Menu::handleHover(const Coordinate mouse) noexcept
{
	int32_t y = 0;

	plog_verbose("Menu is handling hover. (mouse: %" PRId32 ", % " PRId32 ")", mouse.x, mouse.y);

	componentContainer[9].updateTexture(nullptr);
	if (0 >= mouse.x || 0 >= mouse.y)
	{
		return;
	}

	if (3 * HSCALE > mouse.x && HSCALE > mouse.y)
	{
		componentContainer[9].updateTexture(true == Faction::getInstance().getFaction() ? textureContainer[1] : textureContainer[2]);
		componentContainer[9].updatePosition({ .x = 0, .y = 0, .w = 3 * HSCALE, .h = HSCALE });
		return;
	}

	if (3 * HSCALE < mouse.x && 6 * HSCALE > mouse.x && HSCALE > mouse.y)
	{
		componentContainer[9].updateTexture(true == Faction::getInstance().getFaction() ? textureContainer[1] : textureContainer[2]);
		componentContainer[9].updatePosition({ .x = 3 * HSCALE, .y = 0, .w = 3 * HSCALE, .h = HSCALE });
		return;
	}

	if (nullptr == componentContainer[4].getRawTexture())
	{
		return;
	}

	if (3 * HSCALE > mouse.x && HSCALE + HSCALE / 2 < mouse.y && 2 * HSCALE + HSCALE / 2 > mouse.y)
	{
		componentContainer[9].updateTexture(true == Faction::getInstance().getFaction() ? textureContainer[1] : textureContainer[2]);
		componentContainer[9].updatePosition({ .x = 0, .y = HSCALE + HSCALE / 2, .w = 3 * HSCALE, .h = HSCALE });
		return;
	}

	if (nullptr == componentContainer[5].getRawTexture())
	{
		return;
	}

	for (y = 3 * HSCALE; y < 9 * HSCALE; y += HSCALE + HSCALE / 2)
	{
		if (3 * HSCALE > mouse.x && y < mouse.y && y + HSCALE > mouse.y)
		{
			componentContainer[9].updateTexture(true == Faction::getInstance().getFaction() ? textureContainer[1] : textureContainer[2]);
			componentContainer[9].updatePosition({ .x = 0, .y = y, .w = 3 * HSCALE, .h = HSCALE });
			return;
		}
	}
}

void Menu::updateTimer(const uint16_t seconds, const bool isAlliance) noexcept
{
	timer.update(seconds, isAlliance);
}

void Menu::updateGold(const uint8_t amount) noexcept
{
	gold.update(amount);
}

} /*< namespace hob */
