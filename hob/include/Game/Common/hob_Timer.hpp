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
 * @file hob_Timer.hpp
 * @author Gaina Stefan
 * @date 27.07.2023
 * @brief This file defines the class and method prototypes of the timer.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_TIMER_HPP_
#define HOB_TIMER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "hob_TextureInitializer.hpp"
#include "hob_SoundInitializer.hpp"
#include "hob_AsyncQueue.hpp"

/******************************************************************************************************
 * CONSTANTS
 *****************************************************************************************************/

namespace hob
{

/** ***************************************************************************************************
 * @brief How many sounds timer loads.
 *****************************************************************************************************/
inline constexpr size_t TIMER_SOUND_COUNT = 5UL;

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Enumerates timer's textures index.
 *****************************************************************************************************/
enum TimerTextureIndex
{
	TIMER_TEXTURE_INDEX_ALLIANCE_0		   = 0,	 /**< Starting index to the timer's alliance textures. */
	TIMER_TEXTURE_INDEX_DOUBLE_POINTS	   = 10, /**< Index to the timer's double points texture.	   */
	TIMER_TEXTURE_INDEX_HORDE_0			   = 11, /**< Starting index to the timer's horde textures.	   */
	TIMER_TEXTURE_INDEX_HOURGLASS_ACTIVE   = 22, /**< Index of the timer's active hourglass texture.   */
	TIMER_TEXTURE_INDEX_HOURGLASS_INACTIVE = 23, /**< Index of the timer's inactive hourglass texture. */
	TIMER_TEXTURES_COUNT				   = 24	 /**< How many textures timer loads.				   */
};

/** ***************************************************************************************************
 * @brief Enumerates timer's changeable components index.
 *****************************************************************************************************/
enum TimerComponentIndex
{
	TIMER_COMPONENT_INDEX_MINUTE		 = 0, /**< Index to the timer's minute component.		 */
	TIMER_COMPONENT_INDEX_DOUBLE_POINTS	 = 1, /**< Index to the timer's double points component. */
	TIMER_COMPONENT_INDEX_SECOND_DIGIT_1 = 2, /**< Index to the timer's first digit component.	 */
	TIMER_COMPONENT_INDEX_SECOND_DIGIT_2 = 3, /**< Index to the timer's second digit component.	 */
	TIMER_COMPONENT_INDEX_HOURGLASS		 = 4, /**< Index to the timer's hourglass component.	 */
	TIMER_COMPONENTS_COUNT				 = 5  /**< How many components the timer uses.			 */
};

/** ***************************************************************************************************
 * @brief Encapsulates information about the time.
 *****************************************************************************************************/
struct TimeFormat
{
	uint16_t seconds;	 /**< How many seconds are left.							*/
	bool	 isAlliance; /**< Faction of the user (true - Alliance, false - Horde). */
	bool	 turn;		 /**< Whose turn is it (true - Alliance | false - Horde).	*/
};

/** ***************************************************************************************************
 * @brief Graphical representation of the time left.
 * @details It supports two different fonts (one for each faction) and a hourglass that changes texture
 * depending if the turn is user's or opponent's. During the last 5 seconds of the user's turn a warning
 * sound is being played.
 *****************************************************************************************************/
class Timer final : public TextureInitializer<TIMER_TEXTURES_COUNT, TIMER_COMPONENTS_COUNT>,
					public SoundInitializer<TIMER_SOUND_COUNT>
{
public:
	/** ***********************************************************************************************
	 * @brief Loads the textures needed for drawing the timer.
	 * @param renderer: Rendering context of the window.
	 *************************************************************************************************/
	Timer(SDL_Renderer* renderer) noexcept;

	/** ***********************************************************************************************
	 * @brief Draws the time left.
	 * @param renderer: Rendering context of the window.
	 * @return void
	 *************************************************************************************************/
	void draw(SDL_Renderer* renderer) noexcept override;

	/** ***********************************************************************************************
	 * @brief Updates the time left. This method is safe to be called from other thread than rendering thread.
	 * @param seconds: How many seconds are left.
	 * @param isAlliance: The faction of the user (true - Alliance | false - Horde).
	 * @param turn: Whose turn is it (true - User | false - Opponent).
	 * @return void
	 *************************************************************************************************/
	void update(uint16_t seconds, bool isAlliance, bool turn) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Handles the updates present in queue.
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void handleQueue(void) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Thread safe queue for buffering updates.
	 *************************************************************************************************/
	AsyncQueue<TimeFormat> queue;
};

} /*< namespace hob */

#endif /*< HOB_TIMER_HPP_ */
