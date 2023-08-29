/******************************************************************************************************
 * @file hob_MenuCommon.hpp                                                                           *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 29.08.2023  Gaina Stefan               Removed the use of ::hob.                                   *
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
 * MACROS                                                                                             *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Menu's bar width (pixels).
 */
constexpr const int32_t BAR_WIDTH = 4L * SCALE;

/**
 * @brief Menu's bar height (pixels).
 */
constexpr const int32_t BAR_HEIGHT = 2L * SCALE;

/**
 * @brief Menu's bar horizontal centered position (pixels).
 */
constexpr const int32_t BAR_HORIZONTAL_CENTERED = 6L * SCALE;

/**
 * @brief Menu's bar text width (pixels).
 */
constexpr const int32_t BAR_TEXT_WIDTH = 2L * SCALE;

/**
 * @brief Menu's bar text height (pixels).
 */
constexpr const int32_t BAR_TEXT_HEIGHT = SCALE / 2L;

/**
 * @brief Relative path to the menu's background texture.
*/
constexpr const char* const MENU_TEXTURE_PATH_BACKGROUND = HOB_TEXTURES_FILE_PATH("main_menu/background");

/**
 * @brief Relative path to the idle button texture.
*/
constexpr const char* const MENU_TEXTURE_PATH_BUTTON_IDLE = HOB_TEXTURES_FILE_PATH("main_menu/button_idle");

/**
 * @brief Relative path to the active button texture.
*/
constexpr const char* const MENU_TEXTURE_PATH_BUTTON_ACTIVE = HOB_TEXTURES_FILE_PATH("main_menu/button_active");

/**
 * @brief Relative path to the pressed button texture.
*/
constexpr const char* const MENU_TEXTURE_PATH_BUTTON_PRESSED = HOB_TEXTURES_FILE_PATH("main_menu/button_pressed");

/**
 * @brief Relative path to the menu's click sound.
*/
constexpr const char* const MENU_SOUND_PATH_CLICK = HOB_SOUNDS_FILE_PATH("click");

/**
 * @brief Corrections applied for determining is mouse is inside menu's bar.
*/
constexpr const SDL_Rect BAR_CORRECTIONS = { SCALE / 8L / 2L, BAR_HEIGHT / 4L, -SCALE / 16L, -SCALE / 8L - BAR_HEIGHT / 4L };

} /*< namespace hob */

#endif /*< HOB_MAIN_MENU_COMMON_HPP_ */
