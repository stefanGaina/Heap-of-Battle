/******************************************************************************************************
 * @file hob_Menu.cpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * 29.08.2023  Gaina Stefan               Refactored.                                                 *
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
*/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("game_menu/" name)

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Menu::Menu(const uint8_t gold) noexcept
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
			0ULL,
			true == Faction::getInstance().getFaction() ? 3ULL : 4ULL,
			true == Faction::getInstance().getFaction() ? 3ULL : 4ULL,
			5ULL,
			true == Faction::getInstance().getFaction() ? 3ULL : 4ULL,
			true == Faction::getInstance().getFaction() ? 3ULL : 4ULL,
			true == Faction::getInstance().getFaction() ? 3ULL : 4ULL,
			true == Faction::getInstance().getFaction() ? 3ULL : 4ULL,
			true == Faction::getInstance().getFaction() ? 3ULL : 4ULL,
			1ULL
		},
		{
			{
				{ 0L              , 0L                       , 6L * HSCALE, 15L * HSCALE },
				{ 0L              , 0L                       , 3L * HSCALE, 1L  * HSCALE },
				{ 3L * HSCALE     , 0L                       , 3L * HSCALE, 1L  * HSCALE },
				{ 5L * HSCALE + 3L, 1L                       , 1L * HSCALE, 1L  * HSCALE },
				{ 0L              , 1L * HSCALE + HSCALE / 2L, 3L * HSCALE, 1L  * HSCALE },
				{ 0L              , 3L * HSCALE              , 3L * HSCALE, 1L  * HSCALE },
				{ 0L              , 4L * HSCALE + HSCALE / 2L, 3L * HSCALE, 1L  * HSCALE },
				{ 0L              , 6L * HSCALE              , 3L * HSCALE, 1L  * HSCALE },
				{ 0L              , 7L * HSCALE + HSCALE / 2L, 3L * HSCALE, 1L  * HSCALE },
				{ 0L              , 0L                       , 0L         , 0L           }
			}
		}
	}
	, m_timer{}
	, m_gold { gold }
	, m_icons{}
{
	plog_trace("Game menu is being constructed.");
}

void Menu::draw(void) noexcept
{
	plog_verbose("Game menu is being drawn.");

	TextureInitializer::draw();
	m_timer.draw();
	m_gold.draw();
	m_icons.draw();
}

Action Menu::handleClick(Coordinate click, hobGame::MenuMode menuMode) noexcept
{
	size_t index = 0ULL;

	plog_verbose("Menu is handling click. (click: %" PRId32 ", %" PRId32 ")", click.x, click.y);
	if (6L * HSCALE < click.x || 15L * HSCALE < click.y)
	{
		switch (menuMode)
		{
			case hobGame::MenuMode::EMPTY:
			{
				for (index = 4ULL; index < 9ULL; ++index)
				{
					m_componentContainer[index].updateTexture(NULL);
				}
				break;
			}
			case hobGame::MenuMode::UNCHANGED:
			{
				break;
			}
			case hobGame::MenuMode::ALLIANCE_KEEP:
			{
				for (index = 4ULL; index < 9ULL; ++index)
				{
					m_componentContainer[index].updateTexture(m_textureContainer[true == Faction::getInstance().getFaction() ? 3ULL : 4ULL]);
				}
				m_icons.setAllianceKeep();
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

	if (NULL == m_componentContainer[9ULL].getRawTexture())
	{
		return Action::NOTHING;
	}

	if (3L * HSCALE > click.x && HSCALE + HSCALE / 2L < click.y && 2L * HSCALE + HSCALE / 2L > click.y)
	{
		return Action::RECRUIT_INFANTRY;
	}

	return Action::NOTHING;
}

void Menu::handleHover(Coordinate mouse) noexcept
{
	int32_t y = 0L;

	plog_verbose("Menu is handling hover. (mouse: %" PRId32 ", % " PRId32 ")", mouse.x, mouse.y);

	m_componentContainer[9ULL].updateTexture(NULL);
	if (0L >= mouse.x || 0L >= mouse.y)
	{
		return;
	}

	if (3L * HSCALE > mouse.x && HSCALE > mouse.y)
	{
		m_componentContainer[9ULL].updateTexture(true == Faction::getInstance().getFaction() ? m_textureContainer[1ULL] : m_textureContainer[2ULL]);
		m_componentContainer[9ULL].updatePosition({ .x = 0L, .y = 0L, .w = 3L * HSCALE, .h = HSCALE });
		return;
	}

	if (3L * HSCALE < mouse.x && 6L * HSCALE > mouse.x && HSCALE > mouse.y)
	{
		m_componentContainer[9ULL].updateTexture(true == Faction::getInstance().getFaction() ? m_textureContainer[1ULL] : m_textureContainer[2ULL]);
		m_componentContainer[9ULL].updatePosition({ .x = 3L * HSCALE, .y = 0L, .w = 3L * HSCALE, .h = HSCALE });
		return;
	}

	if (NULL == m_componentContainer[4ULL].getRawTexture())
	{
		return;
	}

	if (3L * HSCALE > mouse.x && HSCALE + HSCALE / 2L < mouse.y && 2L * HSCALE + HSCALE / 2L > mouse.y)
	{
		m_componentContainer[9ULL].updateTexture(true == Faction::getInstance().getFaction() ? m_textureContainer[1ULL] : m_textureContainer[2ULL]);
		m_componentContainer[9ULL].updatePosition({ .x = 0L, .y = HSCALE + HSCALE / 2L, .w = 3L * HSCALE, .h = HSCALE });
		return;
	}

	if (NULL == m_componentContainer[5ULL].getRawTexture())
	{
		return;
	}

	for (y = 3L * HSCALE; y < 9L * HSCALE; y += HSCALE + HSCALE / 2L)
	{
		if (3L * HSCALE > mouse.x && y < mouse.y && y + HSCALE > mouse.y)
		{
			m_componentContainer[9ULL].updateTexture(true == Faction::getInstance().getFaction() ? m_textureContainer[1ULL] : m_textureContainer[2ULL]);
			m_componentContainer[9ULL].updatePosition({ .x = 0L, .y = y, .w = 3L * HSCALE, .h = HSCALE });
			return;
		}
	}
}

void Menu::updateTimer(const uint16_t seconds, const bool isAlliance) noexcept
{
	m_timer.update(seconds, isAlliance);
}

void Menu::updateGold(const uint8_t amount) noexcept
{
	m_gold.update(amount);
}

} /*< namespace hob */
