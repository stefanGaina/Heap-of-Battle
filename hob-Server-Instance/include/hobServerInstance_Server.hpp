/******************************************************************************************************
 * @file hobServerInstance_Server.hpp                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 26.07.2023  Gaina Stefan               Initial version.                                            *
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
	 * @brief Checks for loaded libraries versions and initializes Winsock and Plog in case of
	 * development builds.
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
