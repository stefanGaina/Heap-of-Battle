/******************************************************************************************************
 * @file hob_Tiles1.cpp                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file implements the class defined in hob_Tiles1.hpp.                                 *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Tiles1.hpp"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief Full file path of tiles textures.
 * @param name: The name of the image (without extension).
*/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("tiles/" name)

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Tiles1::Tiles1(void)
	: TextureInitializer
	{
		{
			TEXTURE_FILE_PATH("summer/grass")                , /*< 0  */
			TEXTURE_FILE_PATH("autumn/dirt")                 , /*< 1  */
			TEXTURE_FILE_PATH("winter/snow")                 , /*< 2  */
			TEXTURE_FILE_PATH("spring/dirt")                 , /*< 3  */
			TEXTURE_FILE_PATH("summer/water")                , /*< 4  */
			TEXTURE_FILE_PATH("autumn/water")                , /*< 5  */
			TEXTURE_FILE_PATH("winter/ice")                  , /*< 6  */
			TEXTURE_FILE_PATH("summer/water_1")              , /*< 7  */
			TEXTURE_FILE_PATH("autumn/water_1")              , /*< 8  */
			TEXTURE_FILE_PATH("winter/ice_1")                , /*< 9  */
			TEXTURE_FILE_PATH("summer/river_bank_left")      , /*< 10 */
			TEXTURE_FILE_PATH("autumn/river_bank_left")      , /*< 11 */
			TEXTURE_FILE_PATH("winter/river_bank_left")      , /*< 12 */
			TEXTURE_FILE_PATH("summer/river_bank_left_1")    , /*< 13 */
			TEXTURE_FILE_PATH("autumn/river_bank_left_1")    , /*< 14 */
			TEXTURE_FILE_PATH("winter/river_bank_left_1")    , /*< 15 */
			TEXTURE_FILE_PATH("summer/river_bank_right")     , /*< 16 */
			TEXTURE_FILE_PATH("autumn/river_bank_right")     , /*< 17 */
			TEXTURE_FILE_PATH("winter/river_bank_right")     , /*< 18 */
			TEXTURE_FILE_PATH("summer/river_bank_right_1")   , /*< 19 */
			TEXTURE_FILE_PATH("autumn/river_bank_right_1")   , /*< 20 */
			TEXTURE_FILE_PATH("winter/river_bank_right_1")   , /*< 21 */
			TEXTURE_FILE_PATH("summer/dirt_to_grass_left")   , /*< 22 */
			TEXTURE_FILE_PATH("summer/dirt_to_grass_left_1") , /*< 23 */
			TEXTURE_FILE_PATH("summer/dirt_to_grass_right")  , /*< 24 */
			TEXTURE_FILE_PATH("summer/dirt_to_grass_right_1"), /*< 25 */
			TEXTURE_FILE_PATH("summer/grass_1")              , /*< 26 */
			TEXTURE_FILE_PATH("autumn/dirt_1")               , /*< 27 */
			TEXTURE_FILE_PATH("winter/snow_1")               , /*< 28 */
			TEXTURE_FILE_PATH("spring/dirt_1")               , /*< 29 */
			TEXTURE_FILE_PATH("summer/grass_2")              , /*< 30 */
			TEXTURE_FILE_PATH("autumn/dirt_2")               , /*< 31 */
			TEXTURE_FILE_PATH("winter/snow_2")               , /*< 32 */
			TEXTURE_FILE_PATH("spring/dirt_2")               , /*< 33 */
		},
		{ /* No components are used. */ },
		{ /* No components are used. */ }
	}
	, TileInitializer
	{
		{
			m_textureContainer[0ULL].getRawTexture(), /*< 0 */
			m_textureContainer[1ULL].getRawTexture(),
			m_textureContainer[2ULL].getRawTexture(),
			m_textureContainer[3ULL].getRawTexture(),

			m_textureContainer[4ULL].getRawTexture(), /*< 1 */
			m_textureContainer[5ULL].getRawTexture(),
			m_textureContainer[6ULL].getRawTexture(),
			m_textureContainer[4ULL].getRawTexture(),

			m_textureContainer[7ULL].getRawTexture(), /*< 2 */
			m_textureContainer[8ULL].getRawTexture(),
			m_textureContainer[9ULL].getRawTexture(),
			m_textureContainer[7ULL].getRawTexture(),

			m_textureContainer[10ULL].getRawTexture(), /*< 3 */
			m_textureContainer[11ULL].getRawTexture(),
			m_textureContainer[12ULL].getRawTexture(),
			m_textureContainer[10ULL].getRawTexture(),

			m_textureContainer[13ULL].getRawTexture(), /*< 4 */
			m_textureContainer[14ULL].getRawTexture(),
			m_textureContainer[15ULL].getRawTexture(),
			m_textureContainer[13ULL].getRawTexture(),

			m_textureContainer[16ULL].getRawTexture(), /*< 5 */
			m_textureContainer[17ULL].getRawTexture(),
			m_textureContainer[18ULL].getRawTexture(),
			m_textureContainer[16ULL].getRawTexture(),

			m_textureContainer[19ULL].getRawTexture(), /*< 6 */
			m_textureContainer[20ULL].getRawTexture(),
			m_textureContainer[21ULL].getRawTexture(),
			m_textureContainer[19ULL].getRawTexture(),

			m_textureContainer[22ULL].getRawTexture(), /*< 7 */
			m_textureContainer[27ULL].getRawTexture(),
			m_textureContainer[28ULL].getRawTexture(),
			m_textureContainer[29ULL].getRawTexture(),

			m_textureContainer[23ULL].getRawTexture(), /*< 8 */
			m_textureContainer[1ULL].getRawTexture(),
			m_textureContainer[2ULL].getRawTexture(),
			m_textureContainer[3ULL].getRawTexture(),

			m_textureContainer[24ULL].getRawTexture(), /*< 9 */
			m_textureContainer[27ULL].getRawTexture(),
			m_textureContainer[28ULL].getRawTexture(),
			m_textureContainer[29ULL].getRawTexture(),

			m_textureContainer[25ULL].getRawTexture(), /*< 10 */
			m_textureContainer[1ULL].getRawTexture(),
			m_textureContainer[2ULL].getRawTexture(),
			m_textureContainer[3ULL].getRawTexture(),

			m_textureContainer[26ULL].getRawTexture(), /*< 11 */
			m_textureContainer[27ULL].getRawTexture(),
			m_textureContainer[28ULL].getRawTexture(),
			m_textureContainer[29ULL].getRawTexture(),

			m_textureContainer[30ULL].getRawTexture(), /*< 12 */
			m_textureContainer[31ULL].getRawTexture(),
			m_textureContainer[32ULL].getRawTexture(),
			m_textureContainer[33ULL].getRawTexture(),
		},
		{
			11, 11, 11, 11, 12, 0 , 0 , 12, 11, 7, 3, 1, 2, 2, 1, 5, 9 , 11, 12, 0 , 0 , 0 , 0 , 11, 11, 11,
			11, 11, 11, 11, 0 , 0 , 0 , 0 , 11, 7, 4, 2, 1, 1, 2, 5, 9 , 11, 0 , 0 , 0 , 0 , 0 , 11, 11, 11,
			11, 11, 11, 11, 0 , 12, 12, 0 , 0 , 8, 4, 2, 1, 2, 1, 6, 10, 0 , 0 , 12, 12, 0 , 0 , 11, 11, 11,
			11, 11, 11, 11, 12, 11, 11, 12, 0 , 8, 3, 1, 2, 1, 2, 5, 10, 0 , 12, 11, 11, 12, 0 , 0 , 12, 0 ,
			0 , 0 , 0 , 0 , 12, 11, 11, 12, 0 , 8, 3, 1, 1, 1, 1, 6, 10, 0 , 12, 11, 11, 12, 0 , 0 , 0 , 0 ,
			0 , 0 , 0 , 0 , 0 , 12, 12, 0 , 0 , 8, 4, 1, 2, 2, 2, 6, 10, 0 , 0 , 12, 12, 0 , 0 , 0 , 0 , 0 ,
			11, 11, 11, 0 , 0 , 0 , 0 , 11, 11, 7, 4, 2, 2, 1, 1, 5, 9 , 11, 11, 0 , 0 , 0 , 0 , 11, 11, 11,
			11, 11, 11, 12, 0 , 0 , 12, 11, 11, 7, 4, 1, 1, 2, 1, 6, 9 , 11, 11, 12, 0 , 0 , 12, 11, 11, 11,
			11, 11, 11, 0 , 0 , 0 , 0 , 11, 11, 7, 3, 1, 2, 2, 1, 6, 9 , 11, 11, 0 , 0 , 0 , 0 , 11, 11, 11,
			0 , 0 , 0 , 0 , 0 , 12, 12, 0 , 0 , 8, 4, 1, 1, 1, 1, 6, 10, 0 , 0 , 12, 12, 0 , 0 , 0 , 0 , 0 ,
			0 , 0 , 0 , 0 , 12, 11, 11, 12, 0 , 8, 4, 2, 2, 2, 2, 5, 10, 0 , 12, 11, 11, 12, 0 , 0 , 0 , 0 ,
			11, 11, 11, 11, 12, 11, 11, 12, 0 , 8, 3, 2, 1, 1, 2, 5, 10, 0 , 12, 11, 11, 12, 0 , 0 , 12, 0 ,
			11, 11, 11, 11, 0 , 12, 12, 0 , 0 , 8, 4, 1, 2, 1, 2, 6, 10, 0 , 0 , 12, 12, 0 , 0 , 11, 11, 11,
			11, 11, 11, 11, 0 , 0 , 0 , 0 , 11, 7, 3, 2, 1, 2, 1, 6, 9 , 11, 0 , 0 , 0 , 0 , 0 , 11, 11, 11,
			11, 11, 11, 11, 12, 0 , 0 , 12, 11, 7, 3, 2, 1, 1, 1, 5, 9 , 11, 12, 0 , 0 , 0 , 0 , 11, 11, 11,
		}
	}
{
	plog_trace("Tiles1 are being constructed.");
}

void Tiles1::draw(void) noexcept
{
	plog_verbose("Tiles1 are being drawn.");
	TileInitializer::draw();
}

} /*< namespace hob */
