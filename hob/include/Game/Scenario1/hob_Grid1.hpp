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
 * @file hob_Grid1.hpp                                                                                *
 * @date:      @author:                   Reason for change:                                          *
 * 27.07.2023  Gaina Stefan               Initial version.                                            *
 * 16.01.2024  Gaina Stefan               Removed tab.                                                *
 * @details This file defines the class and method prototypes of the grid of the first scenario.      *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_GRID1_HPP_
#define HOB_GRID1_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_IDrawable.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Lines on the map of scenario 1.
*/
class Grid1 final : public IDrawable
{
public:
	/**
	 * @brief Draws the grid coresponding to scenario number 1.
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	void draw(SDL_Renderer* renderer) noexcept override;

private:
	/**
	 * @brief Draws the horizontal lines that are playable and not coresponding to any building.
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	void drawHorizontalNeutralLines(SDL_Renderer* renderer) const noexcept;

	/**
	 * @brief Draws the vertical lines that are playable and not coresponding to any building.
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	void drawVerticalNeutralLines(SDL_Renderer* renderer) const noexcept;

	/**
	 * @brief Draws the horizontal lines coresponding to the alliance buildings.
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	void drawHorizontalAllianceLines(SDL_Renderer* renderer) const noexcept;

	/**
	 * @brief Draws the vertical lines coresponding to the alliance buildings.
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	void drawVerticalAllianceLines(SDL_Renderer* renderer) const noexcept;

	/**
	 * @brief Draws the horizontal lines coresponding to the horde buildings.
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	void drawHorizontalHordeLines(SDL_Renderer* renderer) const noexcept;

	/**
	 * @brief Draws the vertical lines coresponding to the horde buildings.
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	void drawVerticalHordeLines(SDL_Renderer* renderer) const noexcept;

	/**
	 * @brief Draws the horizontal lines coresponding to the objective buildings.
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	void drawHorizontalObjectiveLines(SDL_Renderer* renderer) const noexcept;

	/**
	 * @brief Draws the vertical lines coresponding to the objective buildings.
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	void drawVerticalObjectiveLines(SDL_Renderer* renderer) const noexcept;
};

} /*< namespace hob */

#endif /*< HOB_GRID1_HPP_ */
