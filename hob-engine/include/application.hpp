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
 * @file application.hpp
 * @author Gaina Stefan
 * @date 17.12.2024
 * @brief This header defines the application class.
 * @todo Finish the documentation.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_ENGINE_APPLICATION_HPP_
#define HOB_ENGINE_APPLICATION_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <string>
#include <memory>

/******************************************************************************************************
 * FORWARD DECLARATIONS
 *****************************************************************************************************/

namespace hob::engine
{

class application_impl;

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief TODO
 *****************************************************************************************************/
class application final
{
public:
	/** ***********************************************************************************************
	 * @brief Creates the window with the given configuration. Supported format: TODO
	 * @param configuration_file: Path of the file containing the configuration of the application.
	 * @throws TODO
	 *************************************************************************************************/
	application(std::string_view configuration_file) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Default constructor defined in the source file so that std::unique_ptr's destructor
	 * does not get inlined as well and worker can be forward declared.
	 * @param void
	 *************************************************************************************************/
	~application(void) noexcept;

	/** ***********************************************************************************************
	 * @brief TODO
	 * @param void
	 * @returns void
	 * @throws TODO
	 *************************************************************************************************/
	void run(void) noexcept(false);

private:
	/** ***********************************************************************************************
	 * @brief Pointer to implementation idiom to allow changes without recompiling.
	 *************************************************************************************************/
	std::unique_ptr<application_impl> implementation;
};

} /*< namespace hob::engine */

#endif /*< HOB_ENGINE_APPLICATION_HPP_ */
