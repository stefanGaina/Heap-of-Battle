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
 * @file hob_Timer.cpp
 * @author Gaina Stefan
 * @date 27.07.2023
 * @brief This file implements the class defined in hob_Timer.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Timer.hpp"

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Full file path of an image used by the timer.
 * @param name: The name of the image (without extension).
 * @return The full file path.
 *****************************************************************************************************/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("game_menu/timer/" name)

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

Timer::Timer(SDL_Renderer* const renderer) noexcept
	: TextureInitializer{ {
							  TEXTURE_FILE_PATH("alliance_0"),			   /*< 0  */
							  TEXTURE_FILE_PATH("alliance_1"),			   /*< 1  */
							  TEXTURE_FILE_PATH("alliance_2"),			   /*< 2  */
							  TEXTURE_FILE_PATH("alliance_3"),			   /*< 3  */
							  TEXTURE_FILE_PATH("alliance_4"),			   /*< 4  */
							  TEXTURE_FILE_PATH("alliance_5"),			   /*< 5  */
							  TEXTURE_FILE_PATH("alliance_6"),			   /*< 6  */
							  TEXTURE_FILE_PATH("alliance_7"),			   /*< 7  */
							  TEXTURE_FILE_PATH("alliance_8"),			   /*< 8  */
							  TEXTURE_FILE_PATH("alliance_9"),			   /*< 9  */
							  TEXTURE_FILE_PATH("alliance_double_points"), /*< 10 */
							  TEXTURE_FILE_PATH("horde_0"),				   /*< 11 */
							  TEXTURE_FILE_PATH("horde_1"),				   /*< 12 */
							  TEXTURE_FILE_PATH("horde_2"),				   /*< 13 */
							  TEXTURE_FILE_PATH("horde_3"),				   /*< 14 */
							  TEXTURE_FILE_PATH("horde_4"),				   /*< 15 */
							  TEXTURE_FILE_PATH("horde_5"),				   /*< 16 */
							  TEXTURE_FILE_PATH("horde_6"),				   /*< 17 */
							  TEXTURE_FILE_PATH("horde_7"),				   /*< 18 */
							  TEXTURE_FILE_PATH("horde_8"),				   /*< 19 */
							  TEXTURE_FILE_PATH("horde_9"),				   /*< 20 */
							  TEXTURE_FILE_PATH("horde_double_points")	   /*< 21 */
						  },
						  {
							  TIMER_TEXTURE_INDEX_ALLIANCE_0,	 /*< 0 */
							  TIMER_TEXTURE_INDEX_DOUBLE_POINTS, /*< 1 */
							  TIMER_TEXTURE_INDEX_ALLIANCE_0,	 /*< 2 */
							  TIMER_TEXTURE_INDEX_ALLIANCE_0	 /*< 3 */
						  },
						  { {
							  { 3 * HSCALE + 5, SCALE / 9, SCALE / 3, SCALE / 3 },				/*< 0 */
							  { 3 * HSCALE + HSCALE / 2 + 5, SCALE / 9, SCALE / 3, SCALE / 3 }, /*< 1 */
							  { 4 * HSCALE + 5, SCALE / 9, SCALE / 3, SCALE / 3 },				/*< 2 */
							  { 4 * HSCALE + HSCALE / 2 + 5, SCALE / 9, SCALE / 3, SCALE / 3 }	/*< 3 */
						  } },
						  renderer }
	, queue{}
{
	plog_trace("Timer is being constructed.");
}

void Timer::draw(SDL_Renderer* const renderer) noexcept
{
	plog_verbose("Timer is being drawn.");
	plog_assert(nullptr != this);
	plog_assert(nullptr != renderer);

	handleQueue();
	TextureInitializer::draw(renderer);
}

void Timer::update(const uint16_t seconds, const bool isAlliance) noexcept
{
	plog_verbose("Timer is being updated. (time left: %" PRIu16 ") (faction: %" PRIu8 ")", seconds, isAlliance);
	plog_assert(nullptr != this);

	queue.push({ .seconds = seconds, .isAlliance = isAlliance });
}

void Timer::handleQueue(void) noexcept
{
	TimeFormat timeFormat = {};
	size_t	   modifier	  = 0UL;

	plog_verbose("Queue is being handled.");
	plog_assert(nullptr != this);

	while (false == queue.isEmpty())
	{
		timeFormat = queue.pop();
		if (false == timeFormat.isAlliance)
		{
			modifier = TIMER_TEXTURE_INDEX_HORDE_0;
		}
		else
		{
			modifier = TIMER_TEXTURE_INDEX_ALLIANCE_0;
		}

		componentContainer[TIMER_COMPONENT_INDEX_MINUTE].updateTexture(textureContainer[static_cast<size_t>(timeFormat.seconds) / 60UL + modifier]);
		componentContainer[TIMER_COMPONENT_INDEX_DOUBLE_POINTS].updateTexture(textureContainer[TIMER_TEXTURE_INDEX_DOUBLE_POINTS + modifier]);
		componentContainer[TIMER_COMPONENT_INDEX_SECOND_DIGIT_1].updateTexture(
			textureContainer[(static_cast<size_t>(timeFormat.seconds) % 60UL) / 10UL + modifier]);
		componentContainer[TIMER_COMPONENT_INDEX_SECOND_DIGIT_2].updateTexture(
			textureContainer[(static_cast<size_t>(timeFormat.seconds) % 60UL) % 10UL + modifier]);
	}
}

} /*< namespace hob */
