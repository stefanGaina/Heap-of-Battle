/** @file Types.hpp
 *  @brief Provides common data types and constants.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

#ifndef TYPES_HPP_
#define TYPES_HPP_

/****************************************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                                 *
 ***************************************************************************************************************************************/

#define __STDC_FORMAT_MACROS /*< To enable format macros (%d <-> PRId32). */
#define WIN32_LEAN_AND_MEAN  /*< For winsock to not have linkage issues.  */

#include <cinttypes>
#include <SDL.h>
#include <SDL_ttf.h>

/****************************************************************************************************************************************
 * MACROS                                                                                                                               *
 ***************************************************************************************************************************************/

/**
 * @brief Current version of the game.
*/
#define VERSION_STRING "DEVELOPMENT"

/**
 * @brief TODO
*/
constexpr size_t VERSION_STRING_SIZE = sizeof(VERSION_STRING);

/**
 * @brief Basic unit of measurement of screen resolution (pixels).
 */
constexpr int32_t SCALE = 80L;

/**
 * @brief Half of the unit of measurement of screen resolution (pixels).
*/
constexpr int32_t HSCALE = SCALE / 2L;

/**
 * @brief Screen's width (pixels).
 */
constexpr int32_t SCREEN_WIDTH = 16L * SCALE;

/**
 * @brief Screen's height (pixels).
 */
constexpr int32_t SCREEN_HEIGHT = 9L * SCALE;

/**
 * @brief SDL's mouse state is left click.
 */
constexpr int32_t LEFT_CLICK = 1L;

/****************************************************************************************************************************************
 * TYPE DEFINITIONS                                                                                                                     *
 ***************************************************************************************************************************************/

/**
 * @brief Low level abstraction layer renderer.
*/
using RawRenderer = SDL_Renderer*;

/**
 * @brief TODO
*/
using RawTexture = SDL_Texture*;

/**
 * @brief TODO
*/
using Surface = SDL_Surface*;

/**
 * @brief TODO
*/
using Rect = SDL_Rect;

/**
 * @brief TODO
*/
using Event = SDL_Event;

/**
 * @brief TODO
*/
using Font = TTF_Font*;

/**
 * @brief TODO
*/
using Color = SDL_Color;

/**
 * @brief Enumerates the possible scenes.
 */
enum class Scene
{
	MAIN_MENU   = 0, /**< Main menu scene.   */
	QUIT        = 1, /**< Application quit.  */
	START_GAME  = 2, /**< Start game scene.  */
	LOAD_GAME   = 3, /**< Load game scene.   */
	SETTINGS    = 4, /**< Settings scene.    */
	MULTIPLAYER = 5, /**< Multiplayer scene. */
	GAME        = 6, /**< Game scene.        */
	RESET       = 7  /**< Application reset. */
};

/**
 * @brief Coordinates of an object on the screen (0, 0 <-> top left corner).
 */
struct Coordinate
{
	int32_t x; /**< TODO */
	int32_t y; /**< TODO */
};

/**
 * @brief Enumerates the possible volumes.
 */
enum class Volume
{
	MUTED     = 0, /**< Muted volume.           */
	LOW       = 1, /**< Low level volume.       */
	MEDIUM    = 2, /**< Medium level volume.    */
	HIGH      = 3, /**< High level volume.      */
	VERY_HIGH = 4, /**< Very high level volume. */
	MAX       = 5  /**< Maximum level volume.   */
};

#endif /*< TYPES_HPP_ */
