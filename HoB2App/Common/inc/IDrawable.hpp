/** @file IDrawable.hpp
 *  @brief Class definition and method prototypes of the drawable interface.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

#ifndef IDRAWABLE_HPP_
#define IDRAWABLE_HPP_

/****************************************************************************************************************************************
 * TYPE DEFINITIONS                                                                                                                     *
 ***************************************************************************************************************************************/

namespace Common
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
	virtual ~IDrawable(void) noexcept = default;

	/**
	 * @brief Abstract method, drawing objects to the screen.
	 * @param void
	 * @return void
	*/
	virtual void draw(void) noexcept = 0;
}; /*< class IDrawable */

} /*< namespace Common */

#endif /*< IDRAWABLE_HPP_ */
