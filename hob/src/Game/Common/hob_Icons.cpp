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

#include <plog.h>

#include "hob_Icons.hpp"
#include "hob_Faction.hpp"

/**
 * @brief Full file path of an image used by the icons.
 * @param name: The name of the image (without extension).
 * @return The full file path.
*/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("game_menu/icons/" name)

namespace hob
{

Icons::Icons(SDL_Renderer* const renderer) noexcept
	: TextureInitializer
	{
		{
			TEXTURE_FILE_PATH("footman_icon")      , /*< 0  */
			TEXTURE_FILE_PATH("elf_icon")          , /*< 1  */
			TEXTURE_FILE_PATH("knight_icon")       , /*< 2  */
			TEXTURE_FILE_PATH("gryphon_rider_icon"), /*< 3  */
			TEXTURE_FILE_PATH("mage_icon")         , /*< 4  */
			TEXTURE_FILE_PATH("castle_icon")       , /*< 5  */
			TEXTURE_FILE_PATH("keep_icon")         , /*< 6  */
			TEXTURE_FILE_PATH("grunt_icon")        , /*< 7  */
			TEXTURE_FILE_PATH("troll_icon")        , /*< 8  */
			TEXTURE_FILE_PATH("death_rider_icon")  , /*< 9  */
			TEXTURE_FILE_PATH("dragon_icon")       , /*< 10 */
			TEXTURE_FILE_PATH("ogre_icon")         , /*< 11 */
			TEXTURE_FILE_PATH("stronghold_icon")   , /*< 12 */
			TEXTURE_FILE_PATH("hall_icon")           /*< 13 */
		},
		{
			0UL,
			0UL,
			0UL,
			0UL,
			0UL
		},
		{
			{
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 }
			}
		},
		{ renderer }
	}
{

}

void Icons::hide(void) noexcept
{

}

void Icons::setAllianceKeep(void) noexcept
{
	if (true == Faction::getInstance().getFaction())
	{
		componentContainer[0UL].updateTexture(textureContainer[0UL]);
		componentContainer[0UL].updatePosition({ .x = 8, .y = HSCALE + HSCALE / 2 + 4, .w = HSCALE - 8, .h = HSCALE - 8 });

		componentContainer[1UL].updateTexture(textureContainer[1UL]);
		componentContainer[1UL].updatePosition({ .x = 8, .y = 3 * HSCALE + 4, .w = HSCALE - 8, .h = HSCALE - 8 });

		componentContainer[2UL].updateTexture(textureContainer[2UL]);
		componentContainer[2UL].updatePosition({ .x = 8, .y = 4 * HSCALE + HSCALE / 2 + 4, .w = HSCALE - 8, .h = HSCALE - 8 });

		componentContainer[3UL].updateTexture(textureContainer[3UL]);
		componentContainer[3UL].updatePosition({ .x = 8, .y = 6 * HSCALE + 4, .w = HSCALE - 8, .h = HSCALE - 8 });

		componentContainer[4UL].updateTexture(textureContainer[4UL]);
		componentContainer[4UL].updatePosition({ .x = 8, .y = 7 * HSCALE + HSCALE / 2 + 4, .w = HSCALE - 8, .h = HSCALE - 8 });
	}
}

} /*< namespace hob */
