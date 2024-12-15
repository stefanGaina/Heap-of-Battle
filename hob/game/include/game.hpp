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
 * @file game.hpp
 * @author Gaina Stefan
 * @date 15.12.2024
 * @brief This header defines the game class.
 * @todo Document which exceptions can be thrown when the implementation is mature enough.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_GAME_HPP_
#define HOB_GAME_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <string_view>

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

/** ***************************************************************************************************
 * @brief This class is responsible for managing the lifecycle of a game session, including
 * initialization, configuration, and execution.
 *****************************************************************************************************/
class game final
{
public:
	/** ***********************************************************************************************
	 * @brief Initializes logger, creates application and runs it with given configuration.
	 * @param game_configuration: The path to the game configuration file (CBOR and JSON in debug mode
	 * formats supported).
	 * @param logger_configuration: The path to the logger configuration file (CBOR and JSON in debug
	 * mode formats supported).
	 * @returns void
	 * @throws TODO
	 *************************************************************************************************/
	static void run(std::string_view game_configuration, std::string_view logger_configuration) noexcept(false);
};

} /*< namespace hob */

#endif /*< HOB_GAME_HPP_ */
