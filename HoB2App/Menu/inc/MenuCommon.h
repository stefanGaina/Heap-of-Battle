#ifndef MENU_COMMON_H_
#define MENU_COMMON_H_

/****************************************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                                 *
 ***************************************************************************************************************************************/

#include "Types.hpp"

/****************************************************************************************************************************************
 * MACROS                                                                                                                               *
 ***************************************************************************************************************************************/

/**
 * @brief Menu's bar width (pixels).
 */
constexpr int32_t BAR_WIDTH = 4L * SCALE;

/**
 * @brief Menu's bar height (pixels).
 */
constexpr int32_t BAR_HEIGHT = 2L * SCALE;

/**
 * @brief Menu's bar horizontal centered position (pixels).
 */
constexpr int32_t BAR_HORIZONTAL_CENTERED = 6L * SCALE;

/**
 * @brief Menu's bar text width (pixels).
 */
constexpr int32_t BAR_TEXT_WIDTH = 2L * SCALE;

/**
 * @brief Menu's bar text height (pixels).
 */
constexpr int32_t BAR_TEXT_HEIGHT = SCALE / 2L;

/**
 * @brief Relative path to the menu's background texture.
*/
constexpr const char* MENU_TEXTURE_PATH_BACKGROUND = "assets/textures/main_menu/background.png";

/**
 * @brief Relative path to the idle button texture.
*/
constexpr const char* MENU_TEXTURE_PATH_BUTTON_IDLE = "assets/textures/main_menu/button_idle.png";

/**
 * @brief Relative path to the active button texture.
*/
constexpr const char* MENU_TEXTURE_PATH_BUTTON_ACTIVE = "assets/textures/main_menu/button_active.png";

/**
 * @brief Relative path to the pressed button texture.
*/
constexpr const char* MENU_TEXTURE_PATH_BUTTON_PRESSED = "assets/textures/main_menu/button_pressed.png";

/**
 * @brief Relative path to the menu's click sound.
*/
constexpr const char* MENU_SOUND_PATH_CLICK = "assets/sounds/click.wav";

/**
 * @brief Corrections applied for determining is mouse is inside menu's bar.
*/
constexpr SDL_Rect bar_corrections = { SCALE / 8L / 2L, BAR_HEIGHT / 4L, -SCALE / 16L, -SCALE / 8L - BAR_HEIGHT / 4 };

#endif /*< MENU_COMMON_H_ */
