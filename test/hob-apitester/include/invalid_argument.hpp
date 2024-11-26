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
 * @file invalid_argument.hpp
 * @author Gaina Stefan
 * @date 26.11.2024
 * @brief This header defines the invalid_argument class.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_APITESTER_INVALID_ARGUMENT_HPP_
#define HOB_APITESTER_INVALID_ARGUMENT_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <string>

#include "exception.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob::apitester
{

/** ***************************************************************************************************
 * @brief This class provides the exception thrown by the library when an invalid cast is performed.
 *****************************************************************************************************/
class invalid_argument final : public exception
{
public:
	/** ***********************************************************************************************
	 * @brief Moves the description of the exception without the risk of std::bad_alloc.
	 * @param message: The error message of the exception.
	 * @throws N/A.
	 *************************************************************************************************/
	invalid_argument(std::string&& message) noexcept;

	/** ***********************************************************************************************
	 * @brief Copies the description of the exception.
	 * @param message: The error message of the exception.
	 * @throws std::bad_alloc: If making the copy of the error message fails.
	 *************************************************************************************************/
	invalid_argument(std::string_view message) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Retrieves the description of the exception.
	 * @param void
	 * @returns The description of the exception.
	 * @throws N/A.
	 *************************************************************************************************/
	std::string_view what(void) const noexcept override;

private:
	/** ***********************************************************************************************
	 * @brief The error message describing the exception.
	 *************************************************************************************************/
	const std::string message;
};

} /*< namespace hob::apitester */

#endif /*< HOB_APITESTER_INVALID_ARGUMENT_HPP_ */
