/** @file Grid1.hpp
 *  @brief Class definition and method prototypes of the grid of scenario 1.
 *
 *  @author Gaina Stefan!
 *  @bug No known bugs.
 */

#ifndef GRID1_HPP_
#define GRID1_HPP_

/****************************************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                                 *
 ***************************************************************************************************************************************/

#include "IDrawable.hpp"
#include "Renderer.hpp"

/****************************************************************************************************************************************
 * TYPE DEFINITIONS                                                                                                                     *
 ***************************************************************************************************************************************/

namespace Game
{

/**
 * @brief Lines on the map of scenario 1.
*/
class Grid1 final : public Common::IDrawable
{
public:
	/**
	 * @brief Draws the grid coresponding to scenario number 1.
	 * @param void
	 * @return void
	*/
	virtual void draw(void) noexcept override;
	
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
}; /*< class Grid1 */

} /*< namespace Game */

#endif /*< GRID1_HPP_ */
