/******************************************************************************************************
 * Copyright (C) 2024 Gaina Stefan
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
 * OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @file drawable.hpp
 * @author Gaina Stefan
 * @date 17.12.2024
 * @brief This header defines the drawable class.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_ENGINE_DETAILS_DRAWABLE_HPP_
#define HOB_ENGINE_DETAILS_DRAWABLE_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <vector>
#include <memory>
#include <SFML/Graphics/Drawable.hpp>

#include "details/visibility.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob::engine
{

/** ***************************************************************************************************
 * @brief Class providing the interface for the engine to draw the object to the window.
 *****************************************************************************************************/
class HOB_ENGINE_API drawable
{
public:
	/** ***********************************************************************************************
	 * @brief Gets the objects that can be drawn. It is thread-safe.
	 * @param void
	 * @returns The drawable objects.
	 * @throws N/A.
	 *************************************************************************************************/
	const std::vector<std::shared_ptr<sf::Drawable>>& get_drawables(void) const noexcept;

protected:
	/** ***********************************************************************************************
	 * @brief Collection of drawables (sprites, text, etc.) that are meant to be used by the inheriting
	 * class.
	 *************************************************************************************************/
	std::vector<std::shared_ptr<sf::Drawable>> drawables;
};

} /*< namespace hob::engine */

#endif /*< HOB_ENGINE_DRAWABLE_HPP_ */
