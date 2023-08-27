/******************************************************************************************************
 * @file hob_Timer.cpp                                                                                *
 * @date:      @author:                   Reason for change:                                          *
 * 27.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added const keywords.                                       *
 * 27.08.2023  Gaina Stefan               Delegated update through queue.                             *
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
*/
#define TEXTURE_FILE_PATH(name) "assets/textures/timer/" name ".png"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Timer::Timer(void) noexcept
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
			0ULL, 10ULL, 0ULL, 0ULL
		},
		{
			{
				{ 2L * SCALE                   - 5L, SCALE / 9L, SCALE / 3L, SCALE / 3L },
				{ 2L * SCALE + SCALE / 4L      - 5L, SCALE / 9L, SCALE / 3L, SCALE / 3L },
				{ 2L * SCALE + 2L * SCALE / 4L - 5L, SCALE / 9L, SCALE / 3L, SCALE / 3L },
				{ 2L * SCALE + 3L * SCALE / 4L - 5L, SCALE / 9L, SCALE / 3L, SCALE / 3L }
			}
		}
	}
	, m_queue{}
{
	plog_trace("Timer is being constructed. (size: %" PRIu64 ") (1: %" PRIu64 ")", sizeof(*this), sizeof(m_queue));
}

void Timer::draw(void) noexcept
{
	TimeFormat timeFormat = {};
	size_t     modifier   = 0ULL;

	if (true == m_queue.isEmpty())
	{
		goto DRAW;
	}

	do
	{
		timeFormat = m_queue.get();
	}
	while (false == m_queue.isEmpty());

	if (false == timeFormat.isAlliance)
	{
		modifier = 11ULL;
	}
	m_componentContainer[0ULL].updateTexture(m_textureContainer[ static_cast<size_t>(timeFormat.seconds) / 60ULL          + modifier].getRawTexture());
	m_componentContainer[1ULL].updateTexture(m_textureContainer[10ULL                                                     + modifier].getRawTexture());
	m_componentContainer[2ULL].updateTexture(m_textureContainer[(static_cast<size_t>(timeFormat.seconds) % 60ULL) / 10ULL + modifier].getRawTexture());
	m_componentContainer[3ULL].updateTexture(m_textureContainer[(static_cast<size_t>(timeFormat.seconds) % 60ULL) % 10ULL + modifier].getRawTexture());

DRAW:

	TextureInitializer::draw();
}

void Timer::update(const uint16_t seconds, const bool isAlliance) noexcept
{
	plog_verbose("Enemy timer is being updated. (time left: %" PRIu16 ") (faction: %" PRIu8 ")", seconds, isAlliance);
	m_queue.put((TimeFormat){ .seconds = seconds, .isAlliance = isAlliance });
}

} /*< namespace hob */
