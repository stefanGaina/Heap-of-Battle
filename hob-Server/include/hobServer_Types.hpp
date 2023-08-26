/******************************************************************************************************
 * @file hobServer_Types.hpp                                                                          *
 * @date:      @author:                   Reason for change:                                          *
 * 26.07.2023  Gaina Stefan               Initial version.                                            *
 * 26.08.2023  Gaina Stefan               Added ping.                                                 *
 * @details This file defines common data types and macros.                                           *
 * @todo Fix doxygens.                                                                                *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_SERVER_TYPES_HPP_
#define HOB_SERVER_TYPES_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <cinttypes>

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hobServer
{

/**
 * @brief TODO
*/
enum class MessageType
{
	END_COMMUNICATION = 0, /**< TODO */
	VERSION           = 1, /**< TODO */
	TEXT              = 2, /**< TODO */
	END_TURN          = 3, /**< TODO */
	TIME              = 4, /**< TODO */
	PING              = 5, /**< TODO */
};

/**
 * @brief S prefix to differentiate from the class counterpart (example: 2.13.7).
*/
struct SVersion
{
	uint8_t major; /**< Major version (2).  */
	uint8_t minor; /**< Minor version (13). */
	uint8_t patch; /**< Patch version (7).  */
};

/**
 * @brief TODO
*/
union MessagePayload
{
	char     text[128]; /**< Text message.                          */
	SVersion version;   /**< The version of the game.               */
	uint16_t timeLeft;  /**< How many seconds are left in the turn. */
};

/**
 * @brief TODO
*/
struct Message
{
	MessageType    type;    /**< TODO */
	MessagePayload payload; /**< TODO */
};

} /*< namespace hobServer */

#endif /*< HOB_SERVER_TYPES_HPP_ */
