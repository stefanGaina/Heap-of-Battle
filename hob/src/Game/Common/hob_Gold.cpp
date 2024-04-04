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
 * @file hob_Gold.cpp
 * @author Gaina Stefan
 * @date 14.02.2024
 * @brief This file implements the class defined in hob_Gold.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Gold.hpp"

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Full file path of an image used by the gold.
 * @param name: The name of the image (without extension).
 * @return The full file path.
 *****************************************************************************************************/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("game_menu/gold/" name)

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

Gold::Gold(SDL_Renderer* const renderer, const uint8_t amount) noexcept
	: TextureInitializer{ {
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
							  TEXTURE_FILE_PATH("gold")	   /*< 10 */
						  },
						  {
							  GOLD_TEXTURE_INDEX_0,	   /*< 0  */
							  GOLD_TEXTURE_INDEX_0,	   /*< 1  */
							  GOLD_TEXTURE_INDEX_0,	   /*< 2  */
							  GOLD_TEXTURE_INDEX_GOLD, /*< 3  */
							  GOLD_TEXTURE_INDEX_0,	   /*< 4  */
							  GOLD_TEXTURE_INDEX_0,	   /*< 5  */
							  GOLD_TEXTURE_INDEX_0,	   /*< 6  */
							  GOLD_TEXTURE_INDEX_0,	   /*< 7  */
							  GOLD_TEXTURE_INDEX_0,	   /*< 8  */
							  GOLD_TEXTURE_INDEX_0,	   /*< 9  */
							  GOLD_TEXTURE_INDEX_0,	   /*< 10 */
							  GOLD_TEXTURE_INDEX_0,	   /*< 11 */
							  GOLD_TEXTURE_INDEX_0,	   /*< 12 */
							  GOLD_TEXTURE_INDEX_0	   /*< 13 */
						  },
						  { {
							  { 0 * HSCALE + 15, SCALE / 9, SCALE / 3, SCALE / 3 },							  /*< 0  */
							  { HSCALE / 2 + 15, SCALE / 9, SCALE / 3, SCALE / 3 },							  /*< 1  */
							  { 1 * HSCALE + 15, SCALE / 9, SCALE / 3, SCALE / 3 },							  /*< 2  */
							  { 2 * HSCALE + 5, SCALE / 9, SCALE / 3, SCALE / 3 },							  /*< 3  */
							  { HSCALE / 2 + 15, HSCALE + HSCALE / 2 + SCALE / 9, SCALE / 3, SCALE / 3 },	  /*< 4  */
							  { 1 * HSCALE + 15, HSCALE + HSCALE / 2 + SCALE / 9, SCALE / 3, SCALE / 3 },	  /*< 5  */
							  { 2 * HSCALE + 5, HSCALE + HSCALE / 2 + SCALE / 9, SCALE / 3, SCALE / 3 },	  /*< 6  */
							  { HSCALE / 2 + 15, 3 * HSCALE + SCALE / 9, SCALE / 3, SCALE / 3 },			  /*< 7  */
							  { 1 * HSCALE + 15, 3 * HSCALE + SCALE / 9, SCALE / 3, SCALE / 3 },			  /*< 8  */
							  { 2 * HSCALE + 5, 3 * HSCALE + SCALE / 9, SCALE / 3, SCALE / 3 },				  /*< 9  */
							  { HSCALE / 2 + 15, 4 * HSCALE + HSCALE / 2 + SCALE / 9, SCALE / 3, SCALE / 3 }, /*< 10 */
							  { 1 * HSCALE + 15, 4 * HSCALE + HSCALE / 2 + SCALE / 9, SCALE / 3, SCALE / 3 }, /*< 11 */
							  { 2 * HSCALE + 5, 4 * HSCALE + HSCALE / 2 + SCALE / 9, SCALE / 3, SCALE / 3 },  /*< 12 */
							  { HSCALE / 2 + 15, 6 * HSCALE + SCALE / 9, SCALE / 3, SCALE / 3 },			  /*< 13 */
							  { 1 * HSCALE + 15, 6 * HSCALE + SCALE / 9, SCALE / 3, SCALE / 3 },			  /*< 14 */
							  { 2 * HSCALE + 5, 6 * HSCALE + SCALE / 9, SCALE / 3, SCALE / 3 },				  /*< 15 */
							  { HSCALE / 2 + 15, 7 * HSCALE + HSCALE / 2 + SCALE / 9, SCALE / 3, SCALE / 3 }, /*< 16 */
							  { 1 * HSCALE + 15, 7 * HSCALE + HSCALE / 2 + SCALE / 9, SCALE / 3, SCALE / 3 }, /*< 17 */
							  { 2 * HSCALE + 5, 7 * HSCALE + HSCALE / 2 + SCALE / 9, SCALE / 3, SCALE / 3 }	  /*< 18 */
						  } },
						  renderer }
	, SoundInitializer{ { HOB_SOUNDS_FILE_PATH("gold_received") } }
	, queue{}
	, previousAmount{ amount }
{
	hide();
	update(--previousAmount + 1U);
}

void Gold::draw(SDL_Renderer* const renderer) noexcept
{
	plog_verbose("Gold is being drawn.");
	plog_assert(nullptr != this);
	plog_assert(nullptr != renderer);

	handleQueue();
	TextureInitializer::draw(renderer);
}

void Gold::update(const uint8_t amount) noexcept
{
	plog_trace("Gold is being updated. (amount: %" PRIu8 ")", amount);
	plog_assert(nullptr != this);

	queue.push(amount);
}

void Gold::hide(void) noexcept
{
	size_t index = GOLD_COMPONENT_INDEX_PRICE_1_TENS;

	plog_assert(nullptr != this);

	for (; index <= GOLD_COMPONENT_INDEX_PRICE_5_ICON; ++index)
	{
		componentContainer[index].updateTexture(nullptr);
	}
}

void Gold::setAllianceKeep(const bool isAlliance) noexcept
{
	plog_trace("Alliance keep gold is being set. (faction: %s)", FACTION_TO_STRING(isAlliance));
	plog_assert(nullptr != this);

	setKeep(isAlliance, true);
}

void Gold::setHordeKeep(const bool isAlliance) noexcept
{
	plog_trace("Horde hall gold is being set. (faction: %s)", FACTION_TO_STRING(isAlliance));
	plog_assert(nullptr != this);

	setKeep(isAlliance, false);
}

void Gold::handleQueue(void) noexcept
{
	uint8_t amount = 0U;

	plog_verbose("Queue is being handled.");
	plog_assert(nullptr != this);

	while (false == queue.isEmpty())
	{
		amount = queue.pop();
		if (amount == previousAmount)
		{
			plog_warn("Gold has not changed! (amount: %" PRIu8 ")", previousAmount);
			continue;
		}

		if (amount > previousAmount)
		{
			plog_verbose("Gold increased. (amount: %" PRIu8 ")", amount);
			soundContainer[GOLD_SOUND_INDEX_INCREASE].play();
		}
		previousAmount = amount;

		componentContainer[GOLD_COMPONENT_INDEX_ONES].updateTexture(textureContainer[amount % 10]);
		amount /= 10;
		if (0U == amount)
		{
			componentContainer[GOLD_COMPONENT_INDEX_TENS].updateTexture(nullptr);
			componentContainer[GOLD_COMPONENT_INDEX_HUNDREDS].updateTexture(nullptr);
			continue;
		}

		componentContainer[GOLD_COMPONENT_INDEX_TENS].updateTexture(textureContainer[amount % 10]);
		amount /= 10;
		if (0U == amount)
		{
			componentContainer[GOLD_COMPONENT_INDEX_HUNDREDS].updateTexture(nullptr);
			continue;
		}
		componentContainer[GOLD_COMPONENT_INDEX_HUNDREDS].updateTexture(textureContainer[amount % 10]);
	}
}

void Gold::setKeep(const bool isAlliance, const bool userFaction) noexcept
{
	static constexpr uint8_t PRICES[]		  = { 5U, 10U, 15U, 25U, 50U };
	static constexpr size_t	 PRICES_COUNT	  = sizeof(PRICES);
	static constexpr size_t	 COMPONENT_OFFSET = GOLD_COMPONENT_INDEX_PRICE_2_TENS - GOLD_COMPONENT_INDEX_PRICE_1_TENS;

	size_t index = 0UL;

	plog_assert(nullptr != this);

	if (userFaction != isAlliance)
	{
		hide();
		return;
	}

	for (; index < PRICES_COUNT; ++index)
	{
		setPrice(GOLD_COMPONENT_INDEX_PRICE_1_TENS + index * COMPONENT_OFFSET, PRICES[index]);
	}
}

void Gold::setPrice(const size_t componentIndex, const uint8_t price) noexcept
{
	static constexpr size_t COMPONENT_OFFSET_TENS		 = GOLD_COMPONENT_INDEX_PRICE_1_TENS - GOLD_COMPONENT_INDEX_PRICE_1_TENS;
	static constexpr size_t COMPONENT_OFFSET_ONES		 = GOLD_COMPONENT_INDEX_PRICE_1_ONES - GOLD_COMPONENT_INDEX_PRICE_1_TENS;
	static constexpr size_t COMPONENT_OFFSET_PURCHASABLE = GOLD_COMPONENT_INDEX_PRICE_1_ICON - GOLD_COMPONENT_INDEX_PRICE_1_TENS;

	plog_assert(nullptr != this);
	plog_assert(100U > price);
	plog_assert(GOLD_COMPONENT_INDEX_PRICE_1_TENS <= componentIndex && GOLD_COMPONENT_INDEX_PRICE_5_TENS >= componentIndex);
	plog_assert(0UL == (componentIndex - GOLD_COMPONENT_INDEX_PRICE_1_TENS) % (GOLD_COMPONENT_INDEX_PRICE_2_TENS - GOLD_COMPONENT_INDEX_PRICE_1_TENS));

	componentContainer[componentIndex + COMPONENT_OFFSET_TENS].updateTexture(0 < price / 10U ? textureContainer[price / 10U].getRawTexture() : nullptr);
	componentContainer[componentIndex + COMPONENT_OFFSET_ONES].updateTexture(textureContainer[price % 10]);
	componentContainer[componentIndex + COMPONENT_OFFSET_PURCHASABLE].updateTexture(
		previousAmount >= price ? textureContainer[GOLD_TEXTURE_INDEX_GOLD].getRawTexture() : nullptr);
}

} /*< namespace hob */
