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
 * @file hob_Types.hpp                                                                                *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 29.08.2023  Gaina Stefan               Added local menu.                                           *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * 19.01.2024  Gaina Stefan               Changed SDL include.                                        *
 * @details This file defines common data types and macros.                                           *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_TYPES_HPP_
#define HOB_TYPES_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <cinttypes>
#include <SDL2/SDL.h>

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief String of common path to the textures folder to be appended at the beginning of the file paths.
 * @param path: The path to the texture file (.png).
 * @return The full file path.
*/
#define HOB_TEXTURES_FILE_PATH(path) "assets/textures/" path ".png"

/**
 * @brief String of common path to the sounds folder to be appended at the beginning of the file paths.
 * @param path: The path to the sound file (.wav).
 * @return The full file path.
*/
#define HOB_SOUNDS_FILE_PATH(path) "assets/sounds/" path ".wav"

/**
 * @brief String of common path to the music folder to be appended at the beginning of the file paths.
 * @param path: The path to the music file (.mp3).
 * @return The full file path.
*/
#define HOB_MUSIC_FILE_PATH(path) "assets/sounds/" path ".mp3"

/******************************************************************************************************
 * CONSTANTS                                                                                          *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief The length in pixels of a basic graphical unit.
*/
static constexpr const int32_t SCALE = 80;

/**
 * @brief The length in pixels of a smaller graphical unit.
*/
static constexpr const int32_t HSCALE = SCALE / 2;

/**
 * @brief The width in pixels of the window.
*/
static constexpr const int32_t SCREEN_WIDTH = 16 * SCALE;

/**
 * @brief The height in pixels of the window.
*/
static constexpr const int32_t SCREEN_HEIGHT = 9 * SCALE;

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

/**
 * @brief Enumerates the possible scenes.
*/
enum class Scene
{
	QUIT		= 0, /**< The game is closing.             */
	MAIN_MENU	= 1, /**< The game is in main menu.        */
	LOCAL_MENU	= 2, /**< The game is in LAN menu.         */
	SETTINGS	= 3, /**< The game is in settings menu.    */
	MULTIPLAYER = 4, /**< The game is in multiplayer menu. */
	MAP_1		= 5	 /**< The game is in map 1.            */
};

/**
 * @brief Coordinates of an object on the screen (0, 0 <-> top left corner).
*/
struct Coordinate
{
	int32_t x; /**< The coordinate on the X axis. */
	int32_t y; /**< The coordinate on the Y axis. */
};

} /*< namespace hob */

#endif /*< HOB_TYPES_HPP_ */
