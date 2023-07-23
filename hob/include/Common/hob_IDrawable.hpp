/******************************************************************************************************
 * @file hob_IDrawable.hpp                                                                            *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
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
	 * @param void
	 * @return void
	*/
	virtual void draw(void) noexcept = 0;
};

} /*< namespace hob */

#endif /*< HOB_IDRAWABLE_HPP_ */
