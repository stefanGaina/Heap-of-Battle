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
 * @file hobServerInstance_Server.hpp                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 26.07.2023  Gaina Stefan               Initial version.                                            *
 * 21.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file defines the function that runs the server.                                      *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_SERVER_INSTANCE_SERVER_HPP_
#define HOB_SERVER_INSTANCE_SERVER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <cinttypes>

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hobServerInstance
{

/**
 * @brief Static class that initializes subsystems and runs the server.
*/
class Server final
{
public:
	/**
	 * @brief Runs the server and opens the way to stop it through terminal input.
	 * @param port: The port on which the server will be opened.
	 * @return void
	*/
	static void run(uint16_t port) noexcept(false);

private:
	/**
	 * @brief Checks for loaded libraries versions and initializes Plog in case of development
	 * builds.
	 * @param void
	 * @return void
	*/
	static void init(void) noexcept(false);

	/**
	 * @brief Deinitializes Winsock and deinitializes Plog in case of development builds.
	 * @param void
	 * @return void
	*/
	static void deinit(void) noexcept;
};

} /*< hobServerInstance */

#endif /*< HOB_SERVER_INSTANCE_SERVER_HPP_ */
