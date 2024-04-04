/******************************************************************************************************
 * Heap of Battle Copyright (C) 2024
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the
 * authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
 *    original software. If you use this software in a product, an acknowledgment in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being
 *    the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @file hob_LogManager.hpp
 * @author Gaina Stefan
 * @date 09.02.2024
 * @brief This file defines the class and method prototypes of the log manager.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_LOG_MANAGER_HPP_
#define HOB_LOG_MANAGER_HPP_

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

#ifndef PLOG_STRIP_ALL

/** ***************************************************************************************************
 * @brief Static class handling chat commands regarding logging.
 * @details This class is present only if libplog.so is loaded.
 *****************************************************************************************************/
class LogManager final
{
public:
	/** ***********************************************************************************************
	 * @brief Handles a user's command regarding logging. Supported commands are:
	 * <ul>
	 * <li> ssl <uint8>: Sets the log severity level. </li>
	 * <li> sfs <uint64>: Sets the log file size.     </li>
	 * <li> sfc <uint8>: Sets the log file count.     </li>
	 * <li> stm <bool>: Sets the log terminal mode.   </li>
	 * <li> sbs <uint64>: Sets the log buffer size.   </li>
	 * <li> gsl: Gets the log severity level.         </li>
	 * <li> gfs: Gets the log file size.              </li>
	 * <li> gfc: Gets the log file count.             </li>
	 * <li> gtm: Gets the log terminal mode.          </li>
	 * <li> gbs: Gets the log buffer size.            </li>
	 * </ul>
	 * @param command: The command ommiting the "./".
	 * @return void
	 *************************************************************************************************/
	static void handleCommand(const char* command) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Handles a user's set command regarding logging.
	 * @param command: The command ommiting the "./" and the character for set ("s").
	 * @return void
	 *************************************************************************************************/
	static void handleSetCommand(const char* command) noexcept;

	/** ***********************************************************************************************
	 * @brief Handles a user's get command regarding logging.
	 * @param command: The command ommiting the "./" and the character for get ("g").
	 * @return void
	 *************************************************************************************************/
	static void handleGetCommand(const char* command) noexcept;

	/** ***********************************************************************************************
	 * @brief Checks if the command starts with "sl".
	 * @param command: The command ommiting the "./" and the character for set/get ("s"/"g").
	 * @return true - the command is requesting log severity level.
	 * @return false - the command is invalid or is requesting something else.
	 *************************************************************************************************/
	static bool isCommandSeverityLevel(const char* command) noexcept;

	/** ***********************************************************************************************
	 * @brief Checks if the command starts with "fs".
	 * @param command: The command ommiting the "./" and the character for set/get ("s"/"g").
	 * @return true - the command is requesting log file size.
	 * @return false - the command is invalid or is requesting something else.
	 *************************************************************************************************/
	static bool isCommandFileSize(const char* command) noexcept;

	/** ***********************************************************************************************
	 * @brief Checks if the command starts with "fc".
	 * @param command: The command ommiting the "./" and the character for set/get ("s"/"g").
	 * @return true - the command is requesting log file count.
	 * @return false - the command is invalid or is requesting something else.
	 *************************************************************************************************/
	static bool isCommandFileCount(const char* command) noexcept;

	/** ***********************************************************************************************
	 * @brief Checks if the command starts with "tm".
	 * @param command: The command ommiting the "./" and the character for set/get ("s"/"g").
	 * @return true - the command is requesting log terminal mode.
	 * @return false - the command is invalid or is requesting something else.
	 *************************************************************************************************/
	static bool isCommandTerminalMode(const char* command) noexcept;

	/** ***********************************************************************************************
	 * @brief Checks if the command starts with "bm".
	 * @param command: The command ommiting the "./" and the character for set/get ("s"/"g").
	 * @return true - the command is requesting log buffer mode.
	 * @return false - the command is invalid or is requesting something else.
	 *************************************************************************************************/
	static bool isCommandBufferMode(const char* command) noexcept;

	/** ***********************************************************************************************
	 * @brief Checks if the command starts with a string.
	 * @param command: The command ommiting the "./" and the character for set/get ("s"/"g").
	 * @param identifier: String associated to a specific request.
	 * @return true - the command is matching that request.
	 * @return false - the command is invalid or is requesting something else.
	 *************************************************************************************************/
	static bool isCommand(const char* command, const char* identifier) noexcept;
};

#endif /*< PLOG_STRIP_ALL */

} /*< namespace hob */

#endif /*< HOB_LOG_MANAGER_HPP_ */
