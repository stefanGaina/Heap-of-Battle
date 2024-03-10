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
 * @file hob_Menu.cpp
 * @author Gaina Stefan
 * @date 29.07.2023
 * @brief This file implements the class defined in hob_Menu.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Menu.hpp"
#include "hob_Faction.hpp"

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Full file path of an image of a building.
 * @param name: The name of the image (without extension).
 * @return The full file path.
 *****************************************************************************************************/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("game_menu/" name)

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

Menu::Menu(SDL_Renderer* const renderer, LoadingScreen& loadingScreen, const bool isAlliance, const uint8_t gold) noexcept
	: TextureInitializer{ {
							  true == isAlliance ? TEXTURE_FILE_PATH("background_alliance") : TEXTURE_FILE_PATH("background_horde"), /*< 0 */
							  TEXTURE_FILE_PATH("frame_selected_alliance"),															 /*< 1 */
							  TEXTURE_FILE_PATH("frame_selected_horde"),															 /*< 2 */
							  TEXTURE_FILE_PATH("frame_unselected_alliance"),														 /*< 3 */
							  TEXTURE_FILE_PATH("frame_unselected_horde"),															 /*< 4 */
							  TEXTURE_FILE_PATH("hourglass_inactive")																 /*< 5 */
						  },
						  {
							  MENU_TEXTURE_INDEX_BACKGROUND,																				 /*< 0 */
							  true == isAlliance ? MENU_TEXTURE_INDEX_FRAME_UNSELECTED_ALLIANCE : MENU_TEXTURE_INDEX_FRAME_UNSELECTED_HORDE, /*< 1 */
							  true == isAlliance ? MENU_TEXTURE_INDEX_FRAME_UNSELECTED_ALLIANCE : MENU_TEXTURE_INDEX_FRAME_UNSELECTED_HORDE, /*< 2 */
							  MENU_TEXTURE_INDEX_HOURGLASS_INACTIVE,																		 /*< 3 */
							  true == isAlliance ? MENU_TEXTURE_INDEX_FRAME_UNSELECTED_ALLIANCE : MENU_TEXTURE_INDEX_FRAME_UNSELECTED_HORDE, /*< 4 */
							  true == isAlliance ? MENU_TEXTURE_INDEX_FRAME_UNSELECTED_ALLIANCE : MENU_TEXTURE_INDEX_FRAME_UNSELECTED_HORDE, /*< 5 */
							  true == isAlliance ? MENU_TEXTURE_INDEX_FRAME_UNSELECTED_ALLIANCE : MENU_TEXTURE_INDEX_FRAME_UNSELECTED_HORDE, /*< 6 */
							  true == isAlliance ? MENU_TEXTURE_INDEX_FRAME_UNSELECTED_ALLIANCE : MENU_TEXTURE_INDEX_FRAME_UNSELECTED_HORDE, /*< 7 */
							  true == isAlliance ? MENU_TEXTURE_INDEX_FRAME_UNSELECTED_ALLIANCE : MENU_TEXTURE_INDEX_FRAME_UNSELECTED_HORDE, /*< 8 */
							  MENU_TEXTURE_INDEX_FRAME_SELECTED_ALLIANCE																	 /*< 9 */
						  },
						  { {
							  { 0, 0, 6 * HSCALE, 15 * HSCALE },					  /*< 0 */
							  { 0, 0, 3 * HSCALE, 1 * HSCALE },						  /*< 1 */
							  { 3 * HSCALE, 0, 3 * HSCALE, 1 * HSCALE },			  /*< 2 */
							  { 5 * HSCALE + 3, 1, 1 * HSCALE, 1 * HSCALE },		  /*< 3 */
							  { 0, 1 * HSCALE + HSCALE / 2, 3 * HSCALE, 1 * HSCALE }, /*< 4 */
							  { 0, 3 * HSCALE, 3 * HSCALE, 1 * HSCALE },			  /*< 5 */
							  { 0, 4 * HSCALE + HSCALE / 2, 3 * HSCALE, 1 * HSCALE }, /*< 6 */
							  { 0, 6 * HSCALE, 3 * HSCALE, 1 * HSCALE },			  /*< 7 */
							  { 0, 7 * HSCALE + HSCALE / 2, 3 * HSCALE, 1 * HSCALE }, /*< 8 */
							  { 0, 0, 0, 0 }										  /*< 9 */
						  } },
						  renderer }
	, timer{ renderer }
	, gold{ renderer, gold }
	, icons{ renderer }
	, isUpgradeDone{ false }
{
	plog_trace("Game menu is being constructed.");
	(void)handleClick({ 7 * HSCALE, 14 * HSCALE }, hobGame::MenuMode::EMPTY, isAlliance);
	usleep(150U * 1000U);
	loadingScreen.step(renderer);
}

void Menu::draw(SDL_Renderer* const renderer) noexcept
{
	plog_verbose("Game menu is being drawn.");
	plog_assert(nullptr != this);
	plog_assert(nullptr != renderer);

	TextureInitializer::draw(renderer);
	timer.draw(renderer);
	gold.draw(renderer);
	icons.draw(renderer);
}

MenuAction Menu::handleClick(const Coordinate click, const hobGame::MenuMode menuMode, const bool isAlliance) noexcept
{
	plog_verbose("Menu is handling click. (click: %" PRId32 ", %" PRId32 ")", click.x, click.y);
	plog_assert(nullptr != this);

	if (6 * HSCALE < click.x || 15 * HSCALE < click.y)
	{
		switch (menuMode)
		{
			case hobGame::MenuMode::EMPTY:
			{
				setFramesKeep(nullptr, nullptr);
				icons.hide();
				break;
			}
			case hobGame::MenuMode::UNCHANGED:
			{
				break;
			}
			case hobGame::MenuMode::ALLIANCE_KEEP:
			{
				setFramesKeep(textureContainer[MENU_TEXTURE_INDEX_FRAME_SELECTED_ALLIANCE].getRawTexture(),
							  true == isAlliance ? textureContainer[MENU_TEXTURE_INDEX_FRAME_SELECTED_ALLIANCE].getRawTexture() : nullptr);
				icons.setAllianceKeep(isAlliance);
				break;
			}
			case hobGame::MenuMode::HORDE_KEEP:
			{
				setFramesKeep(textureContainer[MENU_TEXTURE_INDEX_FRAME_SELECTED_HORDE].getRawTexture(),
							  false == isAlliance ? textureContainer[MENU_TEXTURE_INDEX_FRAME_SELECTED_HORDE].getRawTexture() : nullptr);
				icons.setHordeKeep(isAlliance);
				break;
			}
			default:
			{
				plog_error("Invalid menu mode! (mode: %" PRId32 ")", static_cast<int32_t>(menuMode));
				plog_assert(false);
				break;
			}
		}

		return { .recruitUnit = hobGame::Unit::NONE, .doUpgrade = false };
	}

	if (nullptr == componentContainer[MENU_COMPONENT_INDEX_SELECTED_FRAME].getRawTexture() || 3 * HSCALE <= click.x)
	{
		return { .recruitUnit = hobGame::Unit::NONE, .doUpgrade = false };
	}

	if (1 * HSCALE + HSCALE / 2 < click.y && 2 * HSCALE + HSCALE / 2 > click.y)
	{
		return { .recruitUnit = hobGame::Unit::RANGED, .doUpgrade = false };
	}

	if (3 * HSCALE < click.y && 4 * HSCALE > click.y)
	{
		return { .recruitUnit = hobGame::Unit::CAVALRY, .doUpgrade = false };
	}

	if (4 * HSCALE + HSCALE / 2 < click.y && 5 * HSCALE + HSCALE / 2 > click.y)
	{
		return { .recruitUnit = hobGame::Unit::AIRCRAFT, .doUpgrade = false };
	}

	if (6 * HSCALE < click.y && 7 * HSCALE > click.y)
	{
		return { .recruitUnit = hobGame::Unit::MAGE, .doUpgrade = false };
	}

	if (7 * HSCALE + HSCALE < click.y && 8 * HSCALE + HSCALE > click.y)
	{
		(void)handleClick({ .x = 7 * HSCALE, .y = 16 * HSCALE }, hobGame::MenuMode::EMPTY, isAlliance);
		isUpgradeDone = true;
		(void)handleClick({ .x = 7 * HSCALE, .y = 16 * HSCALE }, true == isAlliance ? hobGame::MenuMode::ALLIANCE_KEEP : hobGame::MenuMode::HORDE_KEEP, isAlliance);

		return { .recruitUnit = hobGame::Unit::NONE, .doUpgrade = true };
	}

	return { .recruitUnit = hobGame::Unit::NONE, .doUpgrade = false };
}

void Menu::handleHover(const Coordinate mouse, const bool isAlliance) noexcept
{
	int32_t y = 0;

	plog_verbose("Menu is handling hover. (mouse: %" PRId32 ", % " PRId32 ")", mouse.x, mouse.y);
	plog_assert(nullptr != this);

	componentContainer[MENU_COMPONENT_INDEX_SELECTED_FRAME].updateTexture(nullptr);
	if (0 >= mouse.x || 0 >= mouse.y)
	{
		return;
	}

	if (3 * HSCALE > mouse.x && HSCALE > mouse.y)
	{
		componentContainer[MENU_COMPONENT_INDEX_SELECTED_FRAME].updateTexture(
			true == isAlliance ? textureContainer[MENU_TEXTURE_INDEX_FRAME_SELECTED_ALLIANCE] : textureContainer[MENU_TEXTURE_INDEX_FRAME_SELECTED_HORDE]);
		componentContainer[MENU_COMPONENT_INDEX_SELECTED_FRAME].updatePosition({ .x = 0, .y = 0, .w = 3 * HSCALE, .h = HSCALE });

		return;
	}

	if (3 * HSCALE < mouse.x && 6 * HSCALE > mouse.x && HSCALE > mouse.y)
	{
		componentContainer[MENU_COMPONENT_INDEX_SELECTED_FRAME].updateTexture(
			true == isAlliance ? textureContainer[MENU_TEXTURE_INDEX_FRAME_SELECTED_ALLIANCE] : textureContainer[MENU_TEXTURE_INDEX_FRAME_SELECTED_HORDE]);
		componentContainer[MENU_COMPONENT_INDEX_SELECTED_FRAME].updatePosition({ .x = 3 * HSCALE, .y = 0, .w = 3 * HSCALE, .h = HSCALE });

		return;
	}

	if (nullptr == componentContainer[MENU_COMPONENT_INDEX_FRAME_1].getRawTexture())
	{
		return;
	}

	if (3 * HSCALE > mouse.x && HSCALE + HSCALE / 2 < mouse.y && 2 * HSCALE + HSCALE / 2 > mouse.y)
	{
		componentContainer[MENU_COMPONENT_INDEX_SELECTED_FRAME].updateTexture(
			true == isAlliance ? textureContainer[MENU_TEXTURE_INDEX_FRAME_SELECTED_ALLIANCE] : textureContainer[MENU_TEXTURE_INDEX_FRAME_SELECTED_HORDE]);
		componentContainer[MENU_COMPONENT_INDEX_SELECTED_FRAME].updatePosition({ .x = 0, .y = HSCALE + HSCALE / 2, .w = 3 * HSCALE, .h = HSCALE });

		return;
	}

	if (nullptr == componentContainer[MENU_COMPONENT_INDEX_FRAME_2].getRawTexture())
	{
		return;
	}

	for (y = 3 * HSCALE; y < 9 * HSCALE; y += HSCALE + HSCALE / 2)
	{
		if (3 * HSCALE > mouse.x && y < mouse.y && y + HSCALE > mouse.y)
		{
			componentContainer[MENU_COMPONENT_INDEX_SELECTED_FRAME].updateTexture(
				true == isAlliance ? textureContainer[MENU_TEXTURE_INDEX_FRAME_SELECTED_ALLIANCE] : textureContainer[MENU_TEXTURE_INDEX_FRAME_SELECTED_HORDE]);
			componentContainer[MENU_COMPONENT_INDEX_SELECTED_FRAME].updatePosition({ .x = 0, .y = y, .w = 3 * HSCALE, .h = HSCALE });

			return;
		}
	}
}

void Menu::updateTimer(const uint16_t seconds, const bool isAlliance) noexcept
{
	plog_assert(nullptr != this);
	timer.update(seconds, isAlliance);
}

void Menu::updateGold(const uint8_t amount) noexcept
{
	plog_assert(nullptr != this);
	gold.update(amount);
}

void Menu::setFramesKeep(SDL_Texture* const texture1, SDL_Texture* const texture2) noexcept
{
	size_t index = 0UL;

	plog_assert(nullptr != this);

	componentContainer[MENU_COMPONENT_INDEX_FRAME_1].updateTexture(texture1);
	for (index = MENU_COMPONENT_INDEX_FRAME_2; index < MENU_COMPONENT_INDEX_FRAME_5; ++index)
	{
		componentContainer[index].updateTexture(texture2);
	}

	if (false == isUpgradeDone)
	{
		componentContainer[index].updateTexture(texture2);
	}
}

} /*< namespace hob */
