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
 * @file hob_Timer.hpp                                                                                *
 * @date:      @author:                   Reason for change:                                          *
 * 27.07.2023  Gaina Stefan               Initial version.                                            *
 * 27.08.2023  Gaina Stefan               Added queue.                                                *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file defines the class and method prototypes of the timer.                           *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_TIMER_HPP_
#define HOB_TIMER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_TextureInitializer.hpp"
#include "hob_AsyncQueue.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Encapsulates information about the time.
*/
struct TimeFormat
{
	uint16_t seconds;    /**< How many seconds are left. */
	bool     isAlliance; /**< Whose turn is it.          */
};

/**
 * @brief Graphical representation of the time left.
*/
class Timer final : public TextureInitializer<22UL, 4UL>
{
public:
	/**
	 * @brief Loads the textures needed for drawing the timer.
	 * @param renderer: Rendering context of the window.
	*/
	Timer(SDL_Renderer* renderer) noexcept;

	/**
	 * @brief Destroys the loaded textures.
	 * @param void
	*/
	~Timer(void) = default;

	/**
	 * @brief Draws the time left.
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	void draw(SDL_Renderer* renderer) noexcept override;

	/**
	 * @brief Updates the time left. This method is safe to be called from other thread than rendering thread.
	 * @param seconds: How many seconds are left.
	 * @param isAlliance: Whose turn is it to use the specific textures.
	 * @return void
	*/
	void update(uint16_t seconds, bool isAlliance) noexcept;

private:
	/**
	 * @brief Thread safe queue for buffering updates.
	*/
	AsyncQueue<TimeFormat> queue;
};

} /*< namespace hob */

#endif /*< HOB_TIMER_HPP_ */
