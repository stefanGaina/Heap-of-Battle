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
 * @file hob_MenuCommon.hpp                                                                           *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 29.08.2023  Gaina Stefan               Removed the use of ::hob.                                   *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file defines common macros and constants for the menu.                               *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_MAIN_MENU_COMMON_HPP_
#define HOB_MAIN_MENU_COMMON_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_Types.hpp"

/******************************************************************************************************
 * CONSTANTS                                                                                          *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Menu's bar width (pixels).
*/
inline constexpr int32_t BAR_WIDTH = 4 * SCALE;

/**
 * @brief Menu's bar height (pixels).
*/
inline constexpr int32_t BAR_HEIGHT = 2 * SCALE;

/**
 * @brief Menu's bar horizontal centered position (pixels).
*/
inline constexpr int32_t BAR_HORIZONTAL_CENTERED = 6 * SCALE;

/**
 * @brief Menu's bar text width (pixels).
*/
inline constexpr int32_t BAR_TEXT_WIDTH = 2 * SCALE;

/**
 * @brief Menu's bar text height (pixels).
*/
inline constexpr int32_t BAR_TEXT_HEIGHT = SCALE / 2;

/**
 * @brief Relative path to the menu's background texture.
*/
inline constexpr const char* MENU_TEXTURE_PATH_BACKGROUND = HOB_TEXTURES_FILE_PATH("main_menu/background");

/**
 * @brief Relative path to the idle button texture.
*/
inline constexpr const char* MENU_TEXTURE_PATH_BUTTON_IDLE = HOB_TEXTURES_FILE_PATH("main_menu/button_idle");

/**
 * @brief Relative path to the active button texture.
*/
inline constexpr const char* MENU_TEXTURE_PATH_BUTTON_ACTIVE = HOB_TEXTURES_FILE_PATH("main_menu/button_active");

/**
 * @brief Relative path to the pressed button texture.
*/
inline constexpr const char* MENU_TEXTURE_PATH_BUTTON_PRESSED = HOB_TEXTURES_FILE_PATH("main_menu/button_pressed");

/**
 * @brief Relative path to the menu's click sound.
*/
inline constexpr const char* MENU_SOUND_PATH_CLICK = HOB_SOUNDS_FILE_PATH("click");

/**
 * @brief Corrections applied for determining is mouse is inside menu's bar.
*/
inline constexpr SDL_Rect BAR_CORRECTIONS = { SCALE / 8 / 2, BAR_HEIGHT / 4, -SCALE / 16, -SCALE / 8 - BAR_HEIGHT / 4 };

} /*< namespace hob */

#endif /*< HOB_MAIN_MENU_COMMON_HPP_ */
