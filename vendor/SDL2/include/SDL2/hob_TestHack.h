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
 * @file hob_TestHack.h
 * @author Gaina Stefan
 * @date 12.02.2024
 * @brief This file is included only during development builds in SDL.h overridding SDL_GetMouseState()
 * with a function that is defined in hob_Test.cpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_TEST_HACK_H_
#define HOB_TEST_HACK_H_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#ifdef DEVEL_BUILD

#include <stdint.h>

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Substitutes the SDL_GetMouseState() call with hob_getMouseState().
 * @param[out] x: Filled in with the current X coordinate relative to the focus window; can be NULL.
 * @param[out] y: Filled in with the current Y coordinate relative to the focus window; can be NULL.
 * @return The current button state as a bitmask which can be tested using the SDL_BUTTON(X) macros.
 *****************************************************************************************************/
#define SDL_GetMouseState(x, y) hob_getMouseState(x, y)

/******************************************************************************************************
 * FUNCTION PROTOTYPES
 *****************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/** ***************************************************************************************************
 * @brief Retrieve the current state of the mouse.
 * @param[out] x: Filled in with the current X coordinate relative to the focus window; can be NULL.
 * @param[out] y: Filled in with the current Y coordinate relative to the focus window; can be NULL.
 * @return The current button state as a bitmask which can be tested using the SDL_BUTTON(X) macros.
 *****************************************************************************************************/
extern uint32_t hob_getMouseState(int32_t* x, int32_t* y);

#ifdef __cplusplus
}
#endif

#endif /*< DEVEL_BUILD */

#endif /*< HOB_TEST_HACK_H_ */
