/******************************************************************************************************
 * @file hob_Types.hpp                                                                                *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
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
#include <SDL.h>

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief The length in pixels of a basic graphical unit.
*/
static constexpr const int32_t SCALE = 80L;

/**
 * @brief The length in pixels of a smaller graphical unit.
*/
static constexpr const int32_t HSCALE = SCALE / 2L;

/**
 * @brief The width in pixels of the window.
*/
static constexpr const int32_t SCREEN_WIDTH = 16L * SCALE;

/**
 * @brief The height in pixels of the window.
*/
static constexpr const int32_t SCREEN_HEIGHT = 9L * SCALE;

/**
 * @brief String of common path to the textures folder to be appended at the beginning of the file paths.
*/
#define HOB_TEXTURES_FILE_PATH "assets/textures/"

/**
 * @brief String of common path to the sounds folder to be appended at the beginning of the file paths.
*/
#define HOB_SOUNDS_FILE_PATH "assets/sounds/"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

/**
 * @brief Enumerates the possible scenes.
*/
enum class Scene
{
	QUIT        = 0, /**< The game is closing.             */
	MAIN_MENU   = 1, /**< The game is in main menu.        */
	SETTINGS    = 2, /**< The game is in settings menu.    */
	MULTIPLAYER = 3, /**< The game is in multiplayer menu. */
	MAP_1       = 4  /**< The game is in map 1.            */
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
