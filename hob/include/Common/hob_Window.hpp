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
 *****************************************************************************************************/

/******************************************************************************************************
 * @file hob_Window.hpp                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 26.08.2023  Gaina Stefan               Added constructor and destructor.                           *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * 21.01.2024  Gaina Stefan               Commented setIcon().                                        *
 * 23.01.2024  Gaina Stefan               Added comment why setIcon() is commented.                   *
 * @details This file defines the class and method prototypes of the window.                          *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_WINDOW_HPP_
#define HOB_WINDOW_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_Types.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Class used to set up the screen where graphics will be rendered.
*/
class Window final
{
public:
	/**
	 * @brief Creates the window where the textures will be renderer.
	 * @param void
	 * @return The rendering context of the window.
	*/
	SDL_Renderer* create(void) noexcept(false);

	/**
	 * @brief Destroys the created window and renderer.
	 * @param void
	 * @return void
	*/
	void destroy(void) noexcept;

	// /**
	//  * @brief Sets the icon of the window.
	//  * @param void
	//  * @return void
	// */
	// void setIcon(void) const noexcept;

#ifdef DEVEL_BUILD

	/**
	 * @brief Logs information about renderer and power for debugging purposes.
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	void logInfo(SDL_Renderer* renderer) const noexcept;

#endif /*< DEVEL_BUILD */

private:
	/**
	 * @brief The SDL window handle.
	*/
	SDL_Window* window;
};

} /*< namespace hob */

#endif /*< HOB_WINDOW_HPP_ */
