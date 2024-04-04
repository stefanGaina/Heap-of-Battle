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
 * @file hob_Gold.hpp
 * @author Gaina Stefan
 * @date 27.03.2024
 * @brief This file defines the class and method prototypes of the gold.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_GOLD_HPP_
#define HOB_GOLD_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "hob_TextureInitializer.hpp"
#include "hob_SoundInitializer.hpp"
#include "hob_AsyncQueue.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

/** ***************************************************************************************************
 * @brief Enumerates gold's textures index.
 *****************************************************************************************************/
enum GoldTextureIndex : uint8_t
{
	GOLD_TEXTURE_INDEX_0	= 0,  /**< Index to the gold's '0' digit texture. */
	GOLD_TEXTURE_INDEX_1	= 1,  /**< Index to the gold's '1' digit texture. */
	GOLD_TEXTURE_INDEX_2	= 2,  /**< Index to the gold's '2' digit texture. */
	GOLD_TEXTURE_INDEX_3	= 3,  /**< Index to the gold's '3' digit texture. */
	GOLD_TEXTURE_INDEX_4	= 4,  /**< Index to the gold's '4' digit texture. */
	GOLD_TEXTURE_INDEX_5	= 5,  /**< Index to the gold's '5' digit texture. */
	GOLD_TEXTURE_INDEX_6	= 6,  /**< Index to the gold's '6' digit texture. */
	GOLD_TEXTURE_INDEX_7	= 7,  /**< Index to the gold's '7' digit texture. */
	GOLD_TEXTURE_INDEX_8	= 8,  /**< Index to the gold's '8' digit texture. */
	GOLD_TEXTURE_INDEX_9	= 9,  /**< Index to the gold's '9' digit texture. */
	GOLD_TEXTURE_INDEX_GOLD = 10, /**< Index to the gold's coin icon texture. */
	GOLD_TEXTURES_COUNT		= 11  /**< How many textures gold loads.		  */
};

/** ***************************************************************************************************
 * @brief Enumerates gold's changeable components index.
 *****************************************************************************************************/
enum GoldComponentIndex : uint8_t
{
	GOLD_COMPONENT_INDEX_HUNDREDS	  = 0,	/**< Index to the gold's hundreds digit amount component.	*/
	GOLD_COMPONENT_INDEX_TENS		  = 1,	/**< Index to the gold's tens digit amount component.		*/
	GOLD_COMPONENT_INDEX_ONES		  = 2,	/**< Index to the gold's ones digit amount component.		*/
	GOLD_COMPONENT_INDEX_ICON		  = 3,	/**< Index to the gold's coin icon component.				*/
	GOLD_COMPONENT_INDEX_PRICE_1_TENS = 4,	/**< Index to the gold's tens digit of 1st price component. */
	GOLD_COMPONENT_INDEX_PRICE_1_ONES = 5,	/**< Index to the gold's ones digit of 1st price component. */
	GOLD_COMPONENT_INDEX_PRICE_1_ICON = 6,	/**< Index to the gold's icon of 1st price component.		*/
	GOLD_COMPONENT_INDEX_PRICE_2_TENS = 7,	/**< Index to the gold's tens digit of 2nd price component. */
	GOLD_COMPONENT_INDEX_PRICE_2_ONES = 8,	/**< Index to the gold's ones digit of 2nd price component. */
	GOLD_COMPONENT_INDEX_PRICE_2_ICON = 9,	/**< Index to the gold's icon of 2nd price component.		*/
	GOLD_COMPONENT_INDEX_PRICE_3_TENS = 10, /**< Index to the gold's tens digit of 3rd price component. */
	GOLD_COMPONENT_INDEX_PRICE_3_ONES = 11, /**< Index to the gold's ones digit of 3rd price component. */
	GOLD_COMPONENT_INDEX_PRICE_3_ICON = 12, /**< Index to the gold's icon of 3rd price component.		*/
	GOLD_COMPONENT_INDEX_PRICE_4_TENS = 13, /**< Index to the gold's tens digit of 4th price component. */
	GOLD_COMPONENT_INDEX_PRICE_4_ONES = 14, /**< Index to the gold's ones digit of 4th price component. */
	GOLD_COMPONENT_INDEX_PRICE_4_ICON = 15, /**< Index to the gold's icon of 4th price component.		*/
	GOLD_COMPONENT_INDEX_PRICE_5_TENS = 16, /**< Index to the gold's tens digit of 5th price component. */
	GOLD_COMPONENT_INDEX_PRICE_5_ONES = 17, /**< Index to the gold's ones digit of 5th price component. */
	GOLD_COMPONENT_INDEX_PRICE_5_ICON = 18, /**< Index to the gold's icon of 5th price component.		*/
	GOLD_COMPONENTS_COUNT			  = 19	/**< How many components the gold uses.						*/
};

/** ***************************************************************************************************
 * @brief Enumerates gold's sounds index.
 *****************************************************************************************************/
enum GoldSoundIndex : uint8_t
{
	GOLD_SOUND_INDEX_INCREASE = 0, /**< Index to the gold's increase sound. */
	GOLD_SOUNDS_COUNT		  = 1  /**< How many sounds the gold loads.		*/
};

/** ***************************************************************************************************
 * @brief Graphical representation of the user's amount of gold and prices.
 *****************************************************************************************************/
class Gold final : public TextureInitializer<GOLD_TEXTURES_COUNT, GOLD_COMPONENTS_COUNT>,
				   private SoundInitializer<GOLD_SOUNDS_COUNT>
{
public:
	/** ***********************************************************************************************
	 * @brief Initializes the textures. The prices are hidden by default.
	 * @param renderer: Rendering context of the window.
	 * @param amount: The starting amount of gold of the user.
	 *************************************************************************************************/
	Gold(SDL_Renderer* renderer, uint8_t amount) noexcept;

	/** ***********************************************************************************************
	 * @brief Draws the gold to the screen.
	 * @param renderer: Rendering context of the window.
	 * @return void
	 *************************************************************************************************/
	void draw(SDL_Renderer* renderer) noexcept override;

	/** ***********************************************************************************************
	 * @brief Updates the amount of gold of the user.
	 * @param amount: The amount to be set.
	 * @return void
	 *************************************************************************************************/
	void update(uint8_t amount) noexcept;

	/** ***********************************************************************************************
	 * @brief Hides the prices in the menu (the user's amount remains visible).
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void hide(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Sets the prices to the keep. If the user's faction is not Alliance it will just hide the
	 * prices.
	 * @param isAlliance: true - Alliance, false - Horde.
	 * @return void
	 *************************************************************************************************/
	void setAllianceKeep(bool isAlliance) noexcept;

	/** ***********************************************************************************************
	 * @brief Sets the prices to the keep. If the user's faction is not Horde it will just hide the
	 * prices.
	 * @param isAlliance: true - Alliance, false - Horde.
	 * @return void
	 *************************************************************************************************/
	void setHordeKeep(bool isAlliance) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Handles the updates present in queue.
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void handleQueue(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Sets the prices to the keep.
	 * @param isAlliance: true - Alliance, false - Horde.
	 * @param userFaction: If the user's faction is not the same it will just hide the prices.
	 * @return void
	 *************************************************************************************************/
	void setKeep(bool isAlliance, bool userFaction) noexcept;

	/** ***********************************************************************************************
	 * @brief Sets a price in the menu.
	 * @param componentIndex: The component index (needs to start to tens and be followed by ones and
	 * icon).
	 * @param price: How much gold is needed to make the purchase.
	 * @return void
	 *************************************************************************************************/
	void setPrice(size_t componentIndex, uint8_t price) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Thread safe queue for buffering updates.
	 *************************************************************************************************/
	AsyncQueue<uint8_t> queue;

	/** ***********************************************************************************************
	 * @brief Stores the amount of gold before the new update.
	 *************************************************************************************************/
	uint8_t previousAmount;
};

} /*< namespace hob */

#endif /*< HOB_GOLD_HPP_ */
