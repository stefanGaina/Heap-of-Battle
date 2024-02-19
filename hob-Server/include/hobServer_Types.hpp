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
 * @file hobServer_Types.hpp
 * @author Gaina Stefan
 * @date 26.07.2023
 * @brief This file defines common data types and macros.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_SERVER_TYPES_HPP_
#define HOB_SERVER_TYPES_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <cinttypes>

#include "hobServer_Version.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hobServer
{

/** ***************************************************************************************************
 * @brief The type of message that has been received/transmitted.
 *****************************************************************************************************/
enum class MessageType
{
	END_COMMUNICATION = 0, /**< The communication is no longer needed/possible.             */
	VERSION			  = 1, /**< The payload contains the version of the game.               */
	TEXT			  = 2, /**< The payload contains a text message written by a player.    */
	END_TURN		  = 3, /**< The current turn has ended.                                 */
	TIME			  = 4, /**< The payload contains how many seconds are left in the turn. */
	PING			  = 5, /**< The client is still listening.                              */
	ENCRYPT_KEY		  = 6, /**< The payload contains the encryption key.                    */
	START_GAME		  = 7  /**< The player is ready to start the game.                      */
};

/** ***************************************************************************************************
 * @brief The actual data transmitted over the socket.
 *****************************************************************************************************/
union MessagePayload
{
	char	 text[128];	 /**< Text message written by a player.            */
	Version	 version;	 /**< The version of the game.                     */
	uint16_t timeLeft;	 /**< How many seconds are left in the turn.       */
	uint64_t encryptKey; /**< The key needed for encrypting text messages. */
};

/** ***************************************************************************************************
 * @brief The message format transmitted over the socket.
 *****************************************************************************************************/
struct Message
{
	MessageType	   type;	/**< The type of message that has been transmitted. */
	MessagePayload payload; /**< The actual data.                               */
};

} /*< namespace hobServer */

#endif /*< HOB_SERVER_TYPES_HPP_ */
