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
 * @file hob_IDrawable.hpp                                                                            *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file defines the class and method prototypes of the drawable interface.              *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_IDRAWABLE_HPP_
#define HOB_IDRAWABLE_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <SDL.h>

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Interface of classes that can be drawn.
*/
class IDrawable
{
public:
	/**
	 * @brief Virtual destructor to avoid polymorphically delete undefined behavior.
	 * @param void
	*/
	virtual ~IDrawable(void) = default;

	/**
	 * @brief Abstract method, drawing objects to the screen.
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	virtual void draw(SDL_Renderer* renderer) noexcept = 0;
};

} /*< namespace hob */

#endif /*< HOB_IDRAWABLE_HPP_ */
