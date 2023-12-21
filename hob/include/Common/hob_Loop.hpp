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
 * @file hob_Loop.hpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 24.07.2023  Gaina Stefan               Removeed frames per second.                                 *
 * 25.08.2023  Gaina Stefan               Added ping monitoring functionality.                        *
 * 29.08.2023  Gaina Stefan               Made m_isRunning atomic.                                    *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file defines the class and method prototypes of the loop.                            *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_LOOP_HPP_
#define HOB_LOOP_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <atomic>

#include "hob_Ping.hpp"
#include "hob_Cursor.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Abstract class that provides the inherited mechanism to keeping up a scene.
*/
class Loop
{
public:
	/**
	 * @brief Loop state is set to not started.
	 * @param renderer: Rendering context of the window.
	 * @param cursor: Reference to the cursor object.
	 * @param ping: Reference to the ping object (can be null).
	*/
	Loop(SDL_Renderer* renderer, Cursor& cursor, Ping* ping) noexcept;

	/**
	 * @brief Default destructor to avoid polymorphically delete undefined behavior
	 * @param void
	*/
	virtual ~Loop(void) = default;

	/**
	 * @brief Blocks until an event to quit or move to another scene is given.
	 * @param void
	 * @return Next scene that will take place.
	*/
	Scene start(void) noexcept;

protected:
	/**
	 * @brief Stops the loop.
	 * @param nextScene: Scene that will be returned after loop stops.
	 * @return void
	*/
	void stop(Scene nextScene) noexcept;

private:
	/**
	 * @brief Handles all pending events.
	 * @param void
	 * @return void
	*/
	void handleEvents(void) noexcept;

	/**
	 * @brief Clears renderer buffer and presents it to the screen after it draws desired objects.
	 * @param void
	 * @return void
	*/
	void render(void) noexcept(false);

	/**
	 * @brief Abstract method, handling an event.
	 * @param void
	 * @return void
	*/
	virtual void handleEvent(const SDL_Event& event) noexcept = 0;

	/**
	 * @brief Abstract method drawing to the renderer the updated scene.
	 * @param void
	 * @return void
	*/
	virtual void draw(void) noexcept = 0;

protected:
	/**
	 * @brief The rendering context of the window.
	*/
	SDL_Renderer* renderer;

	/**
	 * @brief Reference to the cursor object.
	*/
	Cursor& cursor;

	/**
	 * @brief Displays the latency for multiplayer scenes.
	*/
	Ping* ping;

private:
	/**
	 * @brief The scene that will follow after the current one is finished.
	*/
	Scene nextScene;

	/**
	 * @brief Flag indicating if the loop is running or is stopped.
	*/
	std::atomic<bool> isRunning;
};

} /*< namespace hob */

#endif /*< HOB_LOOP_HPP_ */
