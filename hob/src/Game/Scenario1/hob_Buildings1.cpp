/******************************************************************************************************
 * @file hob_Buildings1.cpp                                                                           *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added const keyword.                                        *
 * @details This file implements the class defined in hob_Buildings1.hpp.                             *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Buildings1.hpp"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief Full file path of an image of a building.
 * @param name: The name of the image (without extension).
*/
#define TEXTURE_FILE_PATH(name) "assets/textures/buildings/" name ".png"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Buildings1::Buildings1(void) noexcept
	: TextureInitializer
	{
		{
			TEXTURE_FILE_PATH("misc/bridge")                   , /*< 0  */
			TEXTURE_FILE_PATH("alliance/keep_summer")          , /*< 1  */
			TEXTURE_FILE_PATH("alliance/keep_winter")          , /*< 2  */
			TEXTURE_FILE_PATH("alliance/keep_upgraded_summer") , /*< 3  */
			TEXTURE_FILE_PATH("alliance/keep_upgraded_winter") , /*< 4  */
			TEXTURE_FILE_PATH("horde/keep_summer")             , /*< 5  */
			TEXTURE_FILE_PATH("horde/keep_winter")             , /*< 6  */
			TEXTURE_FILE_PATH("horde/keep_upgraded_summer")    , /*< 7  */
			TEXTURE_FILE_PATH("horde/keep_upgraded_winter")    , /*< 8  */
			TEXTURE_FILE_PATH("misc/mine_summer")              , /*< 9  */
			TEXTURE_FILE_PATH("misc/mine_winter")              , /*< 10 */
			TEXTURE_FILE_PATH("misc/mine_active_summer")       , /*< 11 */
			TEXTURE_FILE_PATH("misc/mine_active_winter")       , /*< 12 */
			TEXTURE_FILE_PATH("alliance/altar_summer")         , /*< 13 */
			TEXTURE_FILE_PATH("alliance/altar_winter")         , /*< 14 */
			TEXTURE_FILE_PATH("alliance/altar_inactive_summer"), /*< 15 */
			TEXTURE_FILE_PATH("alliance/altar_inactive_winter"), /*< 16 */
			TEXTURE_FILE_PATH("horde/altar_summer")            , /*< 17 */
			TEXTURE_FILE_PATH("horde/altar_winter")            , /*< 18 */
			TEXTURE_FILE_PATH("horde/altar_inactive_summer")   , /*< 19 */
			TEXTURE_FILE_PATH("horde/altar_inactive_winter")   , /*< 20 */
			TEXTURE_FILE_PATH("alliance/farm_summer")          , /*< 21 */
			TEXTURE_FILE_PATH("alliance/farm_winter")          , /*< 22 */
			TEXTURE_FILE_PATH("horde/farm_summer")             , /*< 23 */
			TEXTURE_FILE_PATH("horde/farm_winter")             , /*< 24 */
			TEXTURE_FILE_PATH("alliance/tower_summer")         , /*< 25 */
			TEXTURE_FILE_PATH("alliance/tower_winter")         , /*< 26 */
			TEXTURE_FILE_PATH("horde/tower_summer")            , /*< 27 */
			TEXTURE_FILE_PATH("horde/tower_winter")            , /*< 28 */
		},
		{ /* No component is used. */ },
		{ /* No component is used. */ }
	}
	, BuildingInitializer
	{
		{
			m_textureContainer[0ULL].getRawTexture(),
			NULL,
			NULL,
			NULL,

			m_textureContainer[0ULL].getRawTexture(),
			NULL,
			NULL,
			NULL,

			m_textureContainer[1ULL].getRawTexture(),
			m_textureContainer[2ULL].getRawTexture(),
			NULL,
			NULL,

			m_textureContainer[5ULL].getRawTexture(),
			m_textureContainer[6ULL].getRawTexture(),
			NULL,
			NULL,

			m_textureContainer[9ULL].getRawTexture(),
			m_textureContainer[10ULL].getRawTexture(),
			m_textureContainer[11ULL].getRawTexture(),
			m_textureContainer[12ULL].getRawTexture(),

			m_textureContainer[9ULL].getRawTexture(),
			m_textureContainer[10ULL].getRawTexture(),
			m_textureContainer[11ULL].getRawTexture(),
			m_textureContainer[12ULL].getRawTexture(),

			m_textureContainer[9ULL].getRawTexture(),
			m_textureContainer[10ULL].getRawTexture(),
			m_textureContainer[11ULL].getRawTexture(),
			m_textureContainer[12ULL].getRawTexture(),

			m_textureContainer[9ULL].getRawTexture(),
			m_textureContainer[10ULL].getRawTexture(),
			m_textureContainer[11ULL].getRawTexture(),
			m_textureContainer[12ULL].getRawTexture(),

			m_textureContainer[13ULL].getRawTexture(),
			NULL,
			NULL,
			NULL,

			m_textureContainer[17ULL].getRawTexture(),
			NULL,
			NULL,
			NULL,

			m_textureContainer[21ULL].getRawTexture(),
			m_textureContainer[22ULL].getRawTexture(),
			NULL,
			NULL,

			m_textureContainer[21ULL].getRawTexture(),
			m_textureContainer[22ULL].getRawTexture(),
			NULL,
			NULL,

			m_textureContainer[23ULL].getRawTexture(),
			m_textureContainer[24ULL].getRawTexture(),
			NULL,
			NULL,

			m_textureContainer[23ULL].getRawTexture(),
			m_textureContainer[24ULL].getRawTexture(),
			NULL,
			NULL,

			m_textureContainer[25ULL].getRawTexture(),
			m_textureContainer[26ULL].getRawTexture(),
			NULL,
			NULL,

			m_textureContainer[25ULL].getRawTexture(),
			m_textureContainer[26ULL].getRawTexture(),
			NULL,
			NULL,

			m_textureContainer[27ULL].getRawTexture(),
			m_textureContainer[28ULL].getRawTexture(),
			NULL,
			NULL,

			m_textureContainer[27ULL].getRawTexture(),
			m_textureContainer[28ULL].getRawTexture(),
			NULL,
			NULL,
		},
		{
			{
				{ 8L  * SCALE , 2L * HSCALE + SCALE / 3L + 6L, 3L * SCALE , 3L * HSCALE + 1L * HSCALE / 3L },
				{ 8L  * SCALE , 9L * HSCALE + SCALE / 3L + 6L, 3L * SCALE , 3L * HSCALE + 1L * HSCALE / 3L },
				{ 3L  * SCALE , 11L * HSCALE                 , 4L * HSCALE, 4L * HSCALE },
				{ 3L  * SCALE , 0L                           , 4L * HSCALE, 4L * HSCALE },
				{ 3L  * SCALE , 3L* SCALE                    , 3L * HSCALE, 3L * HSCALE },
				{ 13L * HSCALE, 3L* SCALE                    , 3L * HSCALE, 3L * HSCALE },
				{ 22L * HSCALE, 3L* SCALE                    , 3L * HSCALE, 3L * HSCALE },
				{ 29L * HSCALE, 3L* SCALE                    , 3L * HSCALE, 3L * HSCALE },
				{ 29L * HSCALE, 6L * SCALE                   , 3L * HSCALE, 3L * HSCALE },
				{ 29L * HSCALE, 0L                           , 3L * HSCALE, 3L * HSCALE },
				{ 7L  * SCALE , 13L * HSCALE                 , 1L * SCALE , 1L * SCALE  },
				{ 11L * SCALE , 13L * HSCALE                 , 1L * SCALE , 1L * SCALE  },
				{ 7L  * SCALE , 0L                           , 1L * SCALE , 1L * SCALE  },
				{ 11L * SCALE , 0L                           , 1L * SCALE , 1L * SCALE  },
				{ 11L * HSCALE, 10L * HSCALE                 , 1L * SCALE , 1L * SCALE  },
				{ 25L * HSCALE, 10L * HSCALE                 , 1L * SCALE , 1L * SCALE  },
				{ 11L * HSCALE, 3L * HSCALE                  , 1L * SCALE , 1L * SCALE  },
				{ 25L * HSCALE, 3L * HSCALE                  , 1L * SCALE , 1L * SCALE  },
			}
		}
	}
	, m_previousSeason{ false }
{
	plog_trace("Buildings1 is being constructed.");
}

void Buildings1::draw(void) noexcept
{
	plog_verbose("Buildings1 is being drawn.");
	BuildingInitializer::draw();
}

void Buildings1::changeWeather(const bool isWinter) noexcept
{
	size_t index = 0ULL;

	plog_debug("Buildings are changing weather. (flag: %" PRId16 ")", static_cast<int16_t>(isWinter));
	if (isWinter == m_previousSeason)
	{
		plog_debug("Buildings already changed weather.");
		return;
	}

	for (index = 0ULL; index < 18ULL; ++index)
	{
		m_buildingContainer[index].changeWeather(isWinter);
	}
	m_previousSeason = isWinter;
}

} /*< namespace hob */
