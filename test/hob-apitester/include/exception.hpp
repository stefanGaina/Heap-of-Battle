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
 * @file exception.hpp
 * @author Gaina Stefan
 * @date 26.11.2024
 * @brief This header defines the exception class.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_APITESTER_EXCEPTION_HPP_
#define HOB_APITESTER_EXCEPTION_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <string_view>

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob::apitester
{

/** ***************************************************************************************************
 * @brief This class defines the interface for custom exceptions.
 * @details This is necessary so they can be caught together and allow the user to handle the
 * exceptions from standard library if needed.
 *****************************************************************************************************/
class exception
{
public:
	/** ***********************************************************************************************
	 * @brief Virtual destructor to avoid polymorphically delete undefined behavior.
	 * @param void
	 * @throws N/A.
	 *************************************************************************************************/
	virtual ~exception(void) noexcept = default;

	/** ***********************************************************************************************
	 * @brief Retrieves the description of the exception.
	 * @param void
	 * @returns The description of the exception.
	 * @throws N/A.
	 *************************************************************************************************/
	virtual std::string_view what(void) const noexcept = 0;
};

} /*< namespace hob::apitester */

#endif /*< HOB_APITESTER_EXCEPTION_HPP_ */
