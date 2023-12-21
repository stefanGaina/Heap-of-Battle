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
 * @file hobServer_Common.hpp                                                                         *
 * @date:      @author:                   Reason for change:                                          *
 * 26.07.2023  Gaina Stefan               Initial version.                                            *
 * 21.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file defines common macros that are meant to be kept internally.                     *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_SERVER_COMMON_HPP_
#define HOB_SERVER_COMMON_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <cstdint>

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief Tag to be attached at the beginning of the logs.
*/
#define LOG_PREFIX "[HOB-SERVER] "

/******************************************************************************************************
 * CONSTANTS                                                                                          *
 *****************************************************************************************************/

/**
 * @brief The value indicating a socket error/ the socket is closed or in an invalid state.
*/
static constexpr const int32_t SOCKET_INVALID = -1;

#endif /*< HOB_SERVER_COMMON_HPP_ */
