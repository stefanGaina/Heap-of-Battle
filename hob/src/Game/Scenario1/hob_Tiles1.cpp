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
 * @file hob_Tiles1.cpp                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
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
 * @return The full file path.
*/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("tiles/" name)

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Tiles1::Tiles1(SDL_Renderer* const renderer)
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
		{ /* No components are used. */ },
		{ renderer }
	}
	, TileInitializer
	{
		{
			textureContainer[0].getRawTexture(), /*< 0 */
			textureContainer[1].getRawTexture(),
			textureContainer[2].getRawTexture(),
			textureContainer[3].getRawTexture(),

			textureContainer[4].getRawTexture(), /*< 1 */
			textureContainer[5].getRawTexture(),
			textureContainer[6].getRawTexture(),
			textureContainer[4].getRawTexture(),

			textureContainer[7].getRawTexture(), /*< 2 */
			textureContainer[8].getRawTexture(),
			textureContainer[9].getRawTexture(),
			textureContainer[7].getRawTexture(),

			textureContainer[10].getRawTexture(), /*< 3 */
			textureContainer[11].getRawTexture(),
			textureContainer[12].getRawTexture(),
			textureContainer[10].getRawTexture(),

			textureContainer[13].getRawTexture(), /*< 4 */
			textureContainer[14].getRawTexture(),
			textureContainer[15].getRawTexture(),
			textureContainer[13].getRawTexture(),

			textureContainer[16].getRawTexture(), /*< 5 */
			textureContainer[17].getRawTexture(),
			textureContainer[18].getRawTexture(),
			textureContainer[16].getRawTexture(),

			textureContainer[19].getRawTexture(), /*< 6 */
			textureContainer[20].getRawTexture(),
			textureContainer[21].getRawTexture(),
			textureContainer[19].getRawTexture(),

			textureContainer[22].getRawTexture(), /*< 7 */
			textureContainer[27].getRawTexture(),
			textureContainer[28].getRawTexture(),
			textureContainer[29].getRawTexture(),

			textureContainer[23].getRawTexture(), /*< 8 */
			textureContainer[1].getRawTexture(),
			textureContainer[2].getRawTexture(),
			textureContainer[3].getRawTexture(),

			textureContainer[24].getRawTexture(), /*< 9 */
			textureContainer[27].getRawTexture(),
			textureContainer[28].getRawTexture(),
			textureContainer[29].getRawTexture(),

			textureContainer[25].getRawTexture(), /*< 10 */
			textureContainer[1].getRawTexture(),
			textureContainer[2].getRawTexture(),
			textureContainer[3].getRawTexture(),

			textureContainer[26].getRawTexture(), /*< 11 */
			textureContainer[27].getRawTexture(),
			textureContainer[28].getRawTexture(),
			textureContainer[29].getRawTexture(),

			textureContainer[30].getRawTexture(), /*< 12 */
			textureContainer[31].getRawTexture(),
			textureContainer[32].getRawTexture(),
			textureContainer[33].getRawTexture(),
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

void Tiles1::draw(SDL_Renderer* const renderer) noexcept
{
	plog_verbose("Tiles1 are being drawn.");
	TileInitializer::draw(renderer);
}

} /*< namespace hob */
