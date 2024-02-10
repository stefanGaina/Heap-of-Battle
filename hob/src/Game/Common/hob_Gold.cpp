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

#include "hob_Gold.hpp"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief Full file path of an image used by the gold.
 * @param name: The name of the image (without extension).
 * @return The full file path.
*/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("game_menu/gold/" name)

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Gold::Gold(SDL_Renderer* const renderer, const uint8_t amount) noexcept
	: TextureInitializer
	{
		{
			TEXTURE_FILE_PATH("gold_0"), /*< 0  */
			TEXTURE_FILE_PATH("gold_1"), /*< 1  */
			TEXTURE_FILE_PATH("gold_2"), /*< 2  */
			TEXTURE_FILE_PATH("gold_3"), /*< 3  */
			TEXTURE_FILE_PATH("gold_4"), /*< 4  */
			TEXTURE_FILE_PATH("gold_5"), /*< 5  */
			TEXTURE_FILE_PATH("gold_6"), /*< 6  */
			TEXTURE_FILE_PATH("gold_7"), /*< 7  */
			TEXTURE_FILE_PATH("gold_8"), /*< 8  */
			TEXTURE_FILE_PATH("gold_9"), /*< 9  */
			TEXTURE_FILE_PATH("gold")    /*< 10 */
		},
		{
			0UL, 0UL, 0UL, 10UL
		},
		{
			{
				{ 0 * HSCALE + 15, SCALE / 9, SCALE / 3, SCALE / 3 }, /*< 0 */
				{ HSCALE / 2 + 15, SCALE / 9, SCALE / 3, SCALE / 3 }, /*< 1 */
				{ 1 * HSCALE + 15, SCALE / 9, SCALE / 3, SCALE / 3 }, /*< 2 */
				{ 2 * HSCALE + 5 , SCALE / 9, SCALE / 3, SCALE / 3 }  /*< 3 */
			}
		},
		renderer
	}
	, SoundInitializer
	{
		{
			HOB_SOUNDS_FILE_PATH("gold_received")
		}
	}
	, queue         {}
	, previousAmount{ amount }
{
	update(--previousAmount + 1U);
}

void Gold::draw(SDL_Renderer* const renderer) noexcept
{
	uint8_t amount = 0U;

	plog_verbose("Gold is being drawn.");
	plog_assert(nullptr != renderer);

	while (false == queue.isEmpty())
	{
		amount = queue.pop();

		componentContainer[2].updateTexture(textureContainer[amount % 10]);
		amount /= 10;
		if (0U == amount)
		{
			componentContainer[1].updateTexture(nullptr);
			componentContainer[0].updateTexture(nullptr);
			continue;
		}

		componentContainer[1].updateTexture(textureContainer[amount % 10]);
		amount /= 10;
		if (0U == amount)
		{
			componentContainer[0].updateTexture(nullptr);
			continue;
		}
		componentContainer[0].updateTexture(textureContainer[amount % 10]);
	}

	TextureInitializer::draw(renderer);
}

void Gold::update(const uint8_t amount) noexcept
{
	plog_trace("Gold is being updated. (amount: %" PRIu8 ")", amount);
	if (amount == previousAmount)
	{
		return;
	}

	if (amount > previousAmount)
	{
		plog_verbose("Gold increased.");
		soundContainer[0].play();
	}
	previousAmount = amount;
	queue.push(previousAmount);
}

} /*< namespace hob */
