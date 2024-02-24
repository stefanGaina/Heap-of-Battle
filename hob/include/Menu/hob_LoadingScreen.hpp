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
 * @file hob_AsyncQueue.hpp
 * @author Gaina Stefan
 * @date 27.08.2023
 * @brief This file defines the class and method prototypes of the queue.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_LOADING_SCREEN_HPP_
#define HOB_LOADING_SCREEN_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <condition_variable>
#include <mutex>
#include <unistd.h>

#include "hob_TextureInitializer.hpp"
#include "hob_SoundInitializer.hpp"
#include "hob_Socket.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

/** ***************************************************************************************************
 * @brief Enumerates main menu's textures index.
 *****************************************************************************************************/
enum LoadingScreenTextureIndex
{
	LOADING_SCREEN_TEXTURE_INDEX_BACKGROUND	   = 0, /**< Index to the loading screen's background texture.                     */
	LOADING_SCREEN_TEXTURE_INDEX_PROGRESS_BAR  = 1, /**< Index to the loading screen's progress bar texture.                   */
	LOADING_SCREEN_TEXTURE_INDEX_PROGRESS_FILL = 2, /**< Index to the loading screen's progress fill texture.                  */
	LOADING_SCREEN_TEXTURE_INDEX_LOADING_TEXT  = 3, /**< Index to the loading screen's "LOADING..." text texture.              */
	LOADING_SCREEN_TEXTURE_INDEX_WAITING_TEXT  = 4, /**< Index to the loading screen's "WAITING FOR OPPONENT..." text texture. */
	LOADING_SCREEN_TEXTURES_COUNT			   = 5	/**< How many textures loading screen loads.                               */
};

/** ***************************************************************************************************
 * @brief Enumerates loading screen's changeable components index.
 *****************************************************************************************************/
enum LoadingScreenComponentIndex
{
	LOADING_SCREEN_COMPONENT_INDEX_FILL_FIRST = 1, /**< Index to the loading screen's first progress fill component. */
	LOADING_SCREEN_COMPONENT_INDEX_FILL_LAST  = 2, /**< Index to the loading screen's last progress fill component.  */
	LOADING_SCREEN_COMPONENTS_COUNT			  = 5  /**< How many components the loading screen uses.                 */
};

/** ***************************************************************************************************
 * @brief Enumerates loading screen's sounds index.
 *****************************************************************************************************/
enum LoadingScreenSoundIndex
{
	LOADING_SCREEN_SOUND_INDEX_ERROR = 0, /**< Index to the loading screen's error sound. */
	LOADING_SCREEN_SOUNDS_COUNT		 = 1  /**< How many sounds the loading screen loads.  */
};

class LoadingScreen final : private TextureInitializer<LOADING_SCREEN_TEXTURES_COUNT, LOADING_SCREEN_COMPONENTS_COUNT>,
							private SoundInitializer<LOADING_SCREEN_SOUNDS_COUNT>
{
public:
	LoadingScreen(SDL_Renderer* renderer, bool isAlliance) noexcept;

	void step(SDL_Renderer* renderer) noexcept;

	void startGame(void) noexcept;

	void waitOpponent(uint16_t timeout, const Socket& socket) noexcept(false);

private:
	/** ***********************************************************************************************
	 * @brief It is static because it is used in a lambda function.
	 *************************************************************************************************/
	static bool interruptWait;

	std::condition_variable waitOpponentReady;

	std::mutex mutex;

	uint8_t fillBarIndex;

	bool isOpponentReady;
};

} /*< namespace hob */

#endif /*< HOB_LOADING_SCREEN_HPP_ */
