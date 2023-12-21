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
 * @file hob_Timer.cpp                                                                                *
 * @date:      @author:                   Reason for change:                                          *
 * 27.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added const keywords.                                       *
 * 27.08.2023  Gaina Stefan               Delegated update through queue.                             *
 * 29.08.2023  Gaina Stefan               Refactored the use of the queue.                            *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file implements the class defined in hob_Timer.hpp.                                  *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Timer.hpp"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief Full file path of an image used by the timer.
 * @param name: The name of the image (without extension).
 * @return The full file path.
*/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("game_menu/timer/" name)

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Timer::Timer(SDL_Renderer* const renderer) noexcept
	: TextureInitializer
	{
		{
			TEXTURE_FILE_PATH("alliance_0"),
			TEXTURE_FILE_PATH("alliance_1"),
			TEXTURE_FILE_PATH("alliance_2"),
			TEXTURE_FILE_PATH("alliance_3"),
			TEXTURE_FILE_PATH("alliance_4"),
			TEXTURE_FILE_PATH("alliance_5"),
			TEXTURE_FILE_PATH("alliance_6"),
			TEXTURE_FILE_PATH("alliance_7"),
			TEXTURE_FILE_PATH("alliance_8"),
			TEXTURE_FILE_PATH("alliance_9"),
			TEXTURE_FILE_PATH("alliance_double_points"),
			TEXTURE_FILE_PATH("horde_0"),
			TEXTURE_FILE_PATH("horde_1"),
			TEXTURE_FILE_PATH("horde_2"),
			TEXTURE_FILE_PATH("horde_3"),
			TEXTURE_FILE_PATH("horde_4"),
			TEXTURE_FILE_PATH("horde_5"),
			TEXTURE_FILE_PATH("horde_6"),
			TEXTURE_FILE_PATH("horde_7"),
			TEXTURE_FILE_PATH("horde_8"),
			TEXTURE_FILE_PATH("horde_9"),
			TEXTURE_FILE_PATH("horde_double_points")
		},
		{
			0UL, 10UL, 0UL, 0UL
		},
		{
			{
				{ 3 * HSCALE              + 5, SCALE / 9, SCALE / 3, SCALE / 3 },
				{ 3 * HSCALE + HSCALE / 2 + 5, SCALE / 9, SCALE / 3, SCALE / 3 },
				{ 4 * HSCALE + 5             , SCALE / 9, SCALE / 3, SCALE / 3 },
				{ 4 * HSCALE + HSCALE / 2 + 5, SCALE / 9, SCALE / 3, SCALE / 3 }
			}
		},
		{ renderer }
	}
	, queue{}
{
	plog_trace("Timer is being constructed.");
}

void Timer::draw(SDL_Renderer* const renderer) noexcept
{
	TimeFormat timeFormat = {};
	size_t     modifier   = 0UL;

	plog_verbose("Timer is being drawn.");
	while (false == queue.isEmpty())
	{
		timeFormat = queue.get();
		if (false == timeFormat.isAlliance)
		{
			modifier = 11UL;
		}
		componentContainer[0].updateTexture(textureContainer[ static_cast<size_t>(timeFormat.seconds) / 60UL         + modifier]);
		componentContainer[1].updateTexture(textureContainer[10UL                                                    + modifier]);
		componentContainer[2].updateTexture(textureContainer[(static_cast<size_t>(timeFormat.seconds) % 60UL) / 10UL + modifier]);
		componentContainer[3].updateTexture(textureContainer[(static_cast<size_t>(timeFormat.seconds) % 60UL) % 10UL + modifier]);
	}
	TextureInitializer::draw(renderer);
}

void Timer::update(const uint16_t seconds, const bool isAlliance) noexcept
{
	plog_verbose("Timer is being updated. (time left: %" PRIu16 ") (faction: %" PRIu8 ")", seconds, isAlliance);
	queue.put({ .seconds = seconds, .isAlliance = isAlliance });
}

} /*< namespace hob */
