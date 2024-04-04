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
 * @file hob_Icons.cpp
 * @author Gaina Stefan
 * @date 23.12.2023
 * @brief This file implements the class defined in hob_Icons.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Icons.hpp"
#include "hob_Faction.hpp"

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Full file path of an image used by the icons.
 * @param name: The name of the image (without extension).
 * @return The full file path.
 *****************************************************************************************************/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("game_menu/icons/" name)

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

Icons::Icons(SDL_Renderer* const renderer) noexcept
	: TextureInitializer{
		{
			TEXTURE_FILE_PATH("footman_icon"),		 /*< 0  */
			TEXTURE_FILE_PATH("elf_icon"),			 /*< 1  */
			TEXTURE_FILE_PATH("knight_icon"),		 /*< 2  */
			TEXTURE_FILE_PATH("gryphon_rider_icon"), /*< 3  */
			TEXTURE_FILE_PATH("mage_icon"),			 /*< 4  */
			TEXTURE_FILE_PATH("castle_icon"),		 /*< 5  */
			TEXTURE_FILE_PATH("keep_icon"),			 /*< 6  */
			TEXTURE_FILE_PATH("grunt_icon"),		 /*< 7  */
			TEXTURE_FILE_PATH("troll_icon"),		 /*< 8  */
			TEXTURE_FILE_PATH("death_rider_icon"),	 /*< 9  */
			TEXTURE_FILE_PATH("dragon_icon"),		 /*< 10 */
			TEXTURE_FILE_PATH("ogre_icon"),			 /*< 11 */
			TEXTURE_FILE_PATH("stronghold_icon"),	 /*< 12 */
			TEXTURE_FILE_PATH("hall_icon")			 /*< 13 */
		},
		{
			ICONS_TEXTURE_INDEX_ELF,		   /*< 0 */
			ICONS_TEXTURE_INDEX_KNIGHT,		   /*< 1 */
			ICONS_TEXTURE_INDEX_GRYPHON_RIDER, /*< 2 */
			ICONS_TEXTURE_INDEX_MAGE,		   /*< 3 */
			ICONS_TEXTURE_INDEX_CASTLE		   /*< 4 */
		},
		{ {
			{ .x = 8, .y = 1 * HSCALE + HSCALE / 2 + 4, .w = HSCALE - 8, .h = HSCALE - 8 }, /*< 0 */
			{ .x = 8, .y = 3 * HSCALE + 4, .w = HSCALE - 8, .h = HSCALE - 8 },				/*< 1 */
			{ .x = 8, .y = 4 * HSCALE + HSCALE / 2 + 4, .w = HSCALE - 8, .h = HSCALE - 8 }, /*< 2 */
			{ .x = 8, .y = 6 * HSCALE + 4, .w = HSCALE - 8, .h = HSCALE - 8 },				/*< 3 */
			{ .x = 8, .y = 7 * HSCALE + HSCALE / 2 + 4, .w = HSCALE - 8, .h = HSCALE - 8 }	/*< 4 */
		} },
		renderer
	}
{
	plog_trace("Icons are being constructed.");
}

void Icons::hide(void) noexcept
{
	size_t index = ICONS_COMPONENT_INDEX_1;

	plog_trace("Icons are being hidden.");
	plog_assert(nullptr != this);

	for (; index <= ICONS_COMPONENT_INDEX_5; ++index)
	{
		componentContainer[index].updateTexture(nullptr);
	}
}

void Icons::setAllianceKeep(const bool isAlliance) noexcept
{
	plog_trace("Alliance keep icons are being set. (faction: %s)", FACTION_TO_STRING(isAlliance));
	plog_assert(nullptr != this);

	setKeep(isAlliance, true, ICONS_TEXTURE_INDEX_ELF, ICONS_TEXTURE_INDEX_KEEP);
}

void Icons::setHordeKeep(const bool isAlliance) noexcept
{
	plog_trace("Horde keep icons are being set. (faction: %s)", FACTION_TO_STRING(isAlliance));
	plog_assert(nullptr != this);

	setKeep(isAlliance, false, ICONS_TEXTURE_INDEX_TROLL, ICONS_TEXTURE_INDEX_HALL);
}

void Icons::setKeep(const bool isAlliance, const bool userFaction, const size_t unitTextureIndex, const size_t keepTextureIndex) noexcept
{
	plog_verbose("Keep icons are being set. (faction: %s) (user faction: %s) (unit index: %" PRIu64 ") (keep index: % " PRIu64 ")", FACTION_TO_STRING(isAlliance),
				 FACTION_TO_STRING(userFaction), unitTextureIndex, keepTextureIndex);
	plog_assert(nullptr != this);
	plog_assert(ICONS_TEXTURE_INDEX_FOOTMAN <= unitTextureIndex && ICONS_TEXTURES_COUNT > unitTextureIndex);
	plog_assert(ICONS_TEXTURE_INDEX_FOOTMAN <= keepTextureIndex && ICONS_TEXTURES_COUNT > keepTextureIndex);

	if (userFaction == isAlliance)
	{
		setKeep(unitTextureIndex);
		return;
	}
	setFirstIcon(keepTextureIndex);
}

void Icons::setKeep(size_t textureIndex) noexcept
{
	size_t componentIndex = ICONS_COMPONENT_INDEX_1;

	plog_verbose("Keep icons are being set. (index: %" PRIu64 ")", textureIndex);
	plog_assert(nullptr != this);
	plog_assert(ICONS_TEXTURE_INDEX_FOOTMAN <= textureIndex && ICONS_TEXTURES_COUNT > textureIndex);

	for (; componentIndex <= ICONS_COMPONENT_INDEX_5; ++componentIndex, ++textureIndex)
	{
		componentContainer[componentIndex].updateTexture(textureContainer[textureIndex]);
	}
}

void Icons::setFirstIcon(const size_t textureIndex) noexcept
{
	size_t componentIndex = ICONS_COMPONENT_INDEX_1;

	plog_verbose("First icon is being set. (index: %" PRIu64 ")", textureIndex);
	plog_assert(nullptr != this);
	plog_assert(ICONS_TEXTURE_INDEX_FOOTMAN <= textureIndex && ICONS_TEXTURES_COUNT > textureIndex);

	componentContainer[componentIndex].updateTexture(textureContainer[textureIndex]);
	for (componentIndex = ICONS_COMPONENT_INDEX_2; componentIndex <= ICONS_COMPONENT_INDEX_5; ++componentIndex)
	{
		componentContainer[componentIndex].updateTexture(nullptr);
	}
}

} /*< namespace hob */
