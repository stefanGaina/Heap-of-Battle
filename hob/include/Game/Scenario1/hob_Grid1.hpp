/******************************************************************************************************
 * @file hob_Grid1.hpp                                                                                *
 * @date:      @author:                   Reason for change:                                          *
 * 27.07.2023  Gaina Stefan               Initial version.                                            *
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
#include "hob_Renderer.hpp"

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
	 * @param void
	 * @return void
	*/
	void draw(void) noexcept override;
	
private:
	/**
	 * @brief Draws the horizontal lines that are playable and not coresponding to any building.
	 * @param void
	 * @return void
	*/
	void drawHorizontalNeutralLines(void) const noexcept;

	/**
	 * @brief Draws the vertical lines that are playable and not coresponding to any building.
	 * @param void
	 * @return void
	*/
	void drawVerticalNeutralLines(void) const noexcept;

	/**
	 * @brief Draws the horizontal lines coresponding to the alliance buildings.
	 * @param void
	 * @return void
	*/
	void drawHorizontalAllianceLines(void) const noexcept;

	/**
	 * @brief Draws the vertical lines coresponding to the alliance buildings.
	 * @param void
	 * @return void
	*/
	void drawVerticalAllianceLines(void) const noexcept;

	/**
	 * @brief Draws the horizontal lines coresponding to the horde buildings.
	 * @param void
	 * @return void
	*/
	void drawHorizontalHordeLines(void) const noexcept;

	/**
	 * @brief Draws the vertical lines coresponding to the horde buildings.
	 * @param void
	 * @return void
	*/
	void drawVerticalHordeLines(void) const noexcept;

	/**
	 * @brief Draws the horizontal lines coresponding to the objective buildings.
	 * @param void
	 * @return void
	*/
	void drawHorizontalObjectiveLines(void) const noexcept;

	/**
	 * @brief Draws the vertical lines coresponding to the objective buildings.
	 * @param void
	 * @return void
	*/
	void drawVerticalObjectiveLines(void) const noexcept;
};

} /*< namespace hob */

#endif /*< HOB_GRID1_HPP_ */
