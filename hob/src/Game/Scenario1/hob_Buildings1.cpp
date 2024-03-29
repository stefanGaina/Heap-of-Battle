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
 * @file hob_Buildings1.cpp
 * @author Gaina Stefan
 * @date 29.07.2023
 * @brief This file implements the class defined in hob_Buildings1.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Buildings1.hpp"

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Full file path of an image of a building.
 * @param name: The name of the image (without extension).
 * @return The full file path.
 *****************************************************************************************************/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("buildings/" name)

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

Buildings1::Buildings1(SDL_Renderer* const renderer, LoadingScreen& loadingScreen) noexcept
	: TextureInitializer{ {
							  TEXTURE_FILE_PATH("misc/bridge"),					   /*< 0  */
							  TEXTURE_FILE_PATH("alliance/keep_summer"),		   /*< 1  */
							  TEXTURE_FILE_PATH("alliance/keep_winter"),		   /*< 2  */
							  TEXTURE_FILE_PATH("alliance/keep_upgraded_summer"),  /*< 3  */
							  TEXTURE_FILE_PATH("alliance/keep_upgraded_winter"),  /*< 4  */
							  TEXTURE_FILE_PATH("horde/keep_summer"),			   /*< 5  */
							  TEXTURE_FILE_PATH("horde/keep_winter"),			   /*< 6  */
							  TEXTURE_FILE_PATH("horde/keep_upgraded_summer"),	   /*< 7  */
							  TEXTURE_FILE_PATH("horde/keep_upgraded_winter"),	   /*< 8  */
							  TEXTURE_FILE_PATH("misc/mine_summer"),			   /*< 9  */
							  TEXTURE_FILE_PATH("misc/mine_winter"),			   /*< 10 */
							  TEXTURE_FILE_PATH("misc/mine_active_summer"),		   /*< 11 */
							  TEXTURE_FILE_PATH("misc/mine_active_winter"),		   /*< 12 */
							  TEXTURE_FILE_PATH("alliance/altar_summer"),		   /*< 13 */
							  TEXTURE_FILE_PATH("alliance/altar_winter"),		   /*< 14 */
							  TEXTURE_FILE_PATH("alliance/altar_inactive_summer"), /*< 15 */
							  TEXTURE_FILE_PATH("alliance/altar_inactive_winter"), /*< 16 */
							  TEXTURE_FILE_PATH("horde/altar_summer"),			   /*< 17 */
							  TEXTURE_FILE_PATH("horde/altar_winter"),			   /*< 18 */
							  TEXTURE_FILE_PATH("horde/altar_inactive_summer"),	   /*< 19 */
							  TEXTURE_FILE_PATH("horde/altar_inactive_winter"),	   /*< 20 */
							  TEXTURE_FILE_PATH("alliance/farm_summer"),		   /*< 21 */
							  TEXTURE_FILE_PATH("alliance/farm_winter"),		   /*< 22 */
							  TEXTURE_FILE_PATH("horde/farm_summer"),			   /*< 23 */
							  TEXTURE_FILE_PATH("horde/farm_winter"),			   /*< 24 */
							  TEXTURE_FILE_PATH("alliance/tower_summer"),		   /*< 25 */
							  TEXTURE_FILE_PATH("alliance/tower_winter"),		   /*< 26 */
							  TEXTURE_FILE_PATH("horde/tower_summer"),			   /*< 27 */
							  TEXTURE_FILE_PATH("horde/tower_winter"),			   /*< 28 */
						  },
						  { /* No component is used. */ },
						  { /* No component is used. */ },
						  renderer }
	, BuildingInitializer{ {
							   textureContainer[0].getRawTexture(), /*< 0 */
							   nullptr,
							   nullptr,
							   nullptr,

							   textureContainer[0].getRawTexture(), /*< 1 */
							   nullptr,
							   nullptr,
							   nullptr,

							   textureContainer[1].getRawTexture(), /*< 2 */
							   textureContainer[2].getRawTexture(),
							   textureContainer[3].getRawTexture(),
							   textureContainer[4].getRawTexture(),

							   textureContainer[5].getRawTexture(), /*< 3 */
							   textureContainer[6].getRawTexture(),
							   textureContainer[7].getRawTexture(),
							   textureContainer[8].getRawTexture(),

							   textureContainer[9].getRawTexture(), /*< 4 */
							   textureContainer[10].getRawTexture(),
							   textureContainer[11].getRawTexture(),
							   textureContainer[12].getRawTexture(),

							   textureContainer[9].getRawTexture(), /*< 5 */
							   textureContainer[10].getRawTexture(),
							   textureContainer[11].getRawTexture(),
							   textureContainer[12].getRawTexture(),

							   textureContainer[9].getRawTexture(), /*< 6 */
							   textureContainer[10].getRawTexture(),
							   textureContainer[11].getRawTexture(),
							   textureContainer[12].getRawTexture(),

							   textureContainer[9].getRawTexture(), /*< 7 */
							   textureContainer[10].getRawTexture(),
							   textureContainer[11].getRawTexture(),
							   textureContainer[12].getRawTexture(),

							   textureContainer[13].getRawTexture(), /*< 8 */
							   nullptr,
							   nullptr,
							   nullptr,

							   textureContainer[17].getRawTexture(), /*< 9 */
							   nullptr,
							   nullptr,
							   nullptr,

							   textureContainer[21].getRawTexture(), /*< 10 */
							   textureContainer[22].getRawTexture(),
							   nullptr,
							   nullptr,

							   textureContainer[21].getRawTexture(), /*< 11 */
							   textureContainer[22].getRawTexture(),
							   nullptr,
							   nullptr,

							   textureContainer[23].getRawTexture(), /*< 12 */
							   textureContainer[24].getRawTexture(),
							   nullptr,
							   nullptr,

							   textureContainer[23].getRawTexture(), /*< 13 */
							   textureContainer[24].getRawTexture(),
							   nullptr,
							   nullptr,

							   textureContainer[25].getRawTexture(), /*< 14 */
							   textureContainer[26].getRawTexture(),
							   nullptr,
							   nullptr,

							   textureContainer[25].getRawTexture(), /*< 15 */
							   textureContainer[26].getRawTexture(),
							   nullptr,
							   nullptr,

							   textureContainer[27].getRawTexture(), /*< 16 */
							   textureContainer[28].getRawTexture(),
							   nullptr,
							   nullptr,

							   textureContainer[27].getRawTexture(), /*< 17 */
							   textureContainer[28].getRawTexture(),
							   nullptr,
							   nullptr,
						   },
						   { {
							   { 16 * HSCALE, 2 * HSCALE + SCALE / 3 + 6, 6 * HSCALE, 3 * HSCALE + HSCALE / 3 }, /*< 0  */
							   { 16 * HSCALE, 9 * HSCALE + SCALE / 3 + 6, 6 * HSCALE, 3 * HSCALE + HSCALE / 3 }, /*< 1  */
							   { 6 * HSCALE, 11 * HSCALE, 4 * HSCALE, 4 * HSCALE },								 /*< 2  */
							   { 6 * HSCALE, 0, 4 * HSCALE, 4 * HSCALE },										 /*< 3  */
							   { 6 * HSCALE, 6 * HSCALE, 3 * HSCALE, 3 * HSCALE },								 /*< 4  */
							   { 13 * HSCALE, 6 * HSCALE, 3 * HSCALE, 3 * HSCALE },								 /*< 5  */
							   { 22 * HSCALE, 6 * HSCALE, 3 * HSCALE, 3 * HSCALE },								 /*< 6  */
							   { 29 * HSCALE, 6 * HSCALE, 3 * HSCALE, 3 * HSCALE },								 /*< 7  */
							   { 29 * HSCALE, 12 * HSCALE, 3 * HSCALE, 3 * HSCALE },							 /*< 8  */
							   { 29 * HSCALE, 0, 3 * HSCALE, 3 * HSCALE },										 /*< 9  */
							   { 14 * HSCALE, 13 * HSCALE, 2 * HSCALE, 2 * HSCALE },							 /*< 10 */
							   { 22 * HSCALE, 13 * HSCALE, 2 * HSCALE, 2 * HSCALE },							 /*< 11 */
							   { 14 * HSCALE, 0, 2 * HSCALE, 2 * HSCALE },										 /*< 12 */
							   { 22 * HSCALE, 0, 2 * HSCALE, 2 * HSCALE },										 /*< 13 */
							   { 10 * HSCALE, 10 * HSCALE, 2 * HSCALE, 2 * HSCALE },							 /*< 14 */
							   { 26 * HSCALE, 10 * HSCALE, 2 * HSCALE, 2 * HSCALE },							 /*< 15 */
							   { 10 * HSCALE, 3 * HSCALE, 2 * HSCALE, 2 * HSCALE },								 /*< 16 */
							   { 26 * HSCALE, 3 * HSCALE, 2 * HSCALE, 2 * HSCALE },								 /*< 17 */
						   } } }
	, previousSeason{ false }
{
	plog_trace("Buildings1 is being constructed.");
	usleep(350U * 1000U);
	loadingScreen.step(renderer);
}

void Buildings1::changeWeather(const bool isWinter) noexcept
{
	size_t index = 0UL;

	plog_debug("Buildings are changing weather. (flag: %" PRId16 ")", static_cast<int16_t>(isWinter));
	plog_assert(nullptr != this);

	if (isWinter == previousSeason)
	{
		plog_debug("Buildings already changed weather.");
		return;
	}

	for (; index < 18UL; ++index)
	{
		buildingContainer[index].changeWeather(isWinter);
	}
	previousSeason = isWinter;
}

void Buildings1::upgrade(const bool isAlliance) noexcept
{
	size_t index = true == isAlliance ? 2 : 3;
	buildingContainer[index].switchTexture(true);
}

} /*< namespace hob */
