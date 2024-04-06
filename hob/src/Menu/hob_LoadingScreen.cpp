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
 * @file hob_LoadingScreen.cpp
 * @author Gaina Stefan
 * @date 20.02.2024
 * @brief This file implements the class defined in hob_LoadingScreen.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <functional>

#include "hob_LoadingScreen.hpp"

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Full file path of an image used by the loading screen.
 * @param name: The name of the image (without extension).
 * @return The full file path.
 *****************************************************************************************************/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("loading_screen/" name)

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

namespace hob
{

bool LoadingScreen::interruptWait = false;

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

LoadingScreen::LoadingScreen(SDL_Renderer* const renderer, const bool isAlliance) noexcept
	: TextureInitializer{ {
							  true == isAlliance ? TEXTURE_FILE_PATH("alliance_background") : TEXTURE_FILE_PATH("horde_background"), /*< 0 */
							  TEXTURE_FILE_PATH("progress_bar"),																	 /*< 1 */
							  TEXTURE_FILE_PATH("progress_fill"),																	 /*< 2 */
							  TEXTURE_FILE_PATH("loading_text"),																	 /*< 3 */
							  TEXTURE_FILE_PATH("waiting_for_opponent_text")														 /*< 4 */
						  },
						  {
							  LOADING_SCREEN_TEXTURE_INDEX_BACKGROUND,	  /*< 0  */
							  LOADING_SCREEN_TEXTURE_INDEX_PROGRESS_FILL, /*< 1  */
							  LOADING_SCREEN_TEXTURE_INDEX_PROGRESS_FILL, /*< 2  */
							  LOADING_SCREEN_TEXTURE_INDEX_PROGRESS_FILL, /*< 3  */
							  LOADING_SCREEN_TEXTURE_INDEX_PROGRESS_FILL, /*< 4  */
							  LOADING_SCREEN_TEXTURE_INDEX_PROGRESS_FILL, /*< 5  */
							  LOADING_SCREEN_TEXTURE_INDEX_PROGRESS_FILL, /*< 6  */
							  LOADING_SCREEN_TEXTURE_INDEX_PROGRESS_FILL, /*< 7  */
							  LOADING_SCREEN_TEXTURE_INDEX_PROGRESS_FILL, /*< 8  */
							  LOADING_SCREEN_TEXTURE_INDEX_PROGRESS_FILL, /*< 9  */
							  LOADING_SCREEN_TEXTURE_INDEX_PROGRESS_FILL, /*< 10 */
							  LOADING_SCREEN_TEXTURE_INDEX_PROGRESS_FILL, /*< 11 */
							  LOADING_SCREEN_TEXTURE_INDEX_PROGRESS_FILL, /*< 12 */
							  LOADING_SCREEN_TEXTURE_INDEX_PROGRESS_BAR,  /*< 13 */
							  LOADING_SCREEN_TEXTURE_INDEX_LOADING_TEXT	  /*< 14 */
						  },
						  { {
							  { .x = 0, .y = 0, .w = SCREEN_WIDTH, .h = SCREEN_HEIGHT },													   /*< 0  */
							  { .x = 9 * HSCALE + HSCALE / 3, .y = 17 * HSCALE - HSCALE / 4, .w = 0, .h = 0 },								   /*< 1  */
							  { .x = 10 * HSCALE + HSCALE / 3, .y = 17 * HSCALE - HSCALE / 4, .w = 0, .h = 0 },								   /*< 2  */
							  { .x = 11 * HSCALE + HSCALE / 3, .y = 17 * HSCALE - HSCALE / 4, .w = 0, .h = 0 },								   /*< 3  */
							  { .x = 12 * HSCALE + HSCALE / 3, .y = 17 * HSCALE - HSCALE / 4, .w = 0, .h = 0 },								   /*< 4  */
							  { .x = 13 * HSCALE + HSCALE / 3, .y = 17 * HSCALE - HSCALE / 4, .w = 0, .h = 0 },								   /*< 5  */
							  { .x = 14 * HSCALE + HSCALE / 3, .y = 17 * HSCALE - HSCALE / 4, .w = 0, .h = 0 },								   /*< 6  */
							  { .x = 15 * HSCALE + HSCALE / 3, .y = 17 * HSCALE - HSCALE / 4, .w = 0, .h = 0 },								   /*< 7  */
							  { .x = 16 * HSCALE + HSCALE / 3, .y = 17 * HSCALE - HSCALE / 4, .w = 0, .h = 0 },								   /*< 8  */
							  { .x = 17 * HSCALE + HSCALE / 3, .y = 17 * HSCALE - HSCALE / 4, .w = 0, .h = 0 },								   /*< 9  */
							  { .x = 18 * HSCALE + HSCALE / 3, .y = 17 * HSCALE - HSCALE / 4, .w = 0, .h = 0 },								   /*< 10 */
							  { .x = 19 * HSCALE + HSCALE / 3, .y = 17 * HSCALE - HSCALE / 4, .w = 0, .h = 0 },								   /*< 11 */
							  { .x = 20 * HSCALE + HSCALE / 3, .y = 17 * HSCALE - HSCALE / 4, .w = -HSCALE / 2, .h = 0 },					   /*< 12 */
							  { .x = 9 * HSCALE, .y = 16 * HSCALE + HSCALE / 2, .w = 14 * HSCALE, .h = HSCALE + HSCALE / 2 },				   /*< 13 */
							  { .x = 14 * HSCALE, .y = 16 * HSCALE + HSCALE / 2 + HSCALE / 3, .w = 3 * HSCALE, .h = HSCALE / 2 + HSCALE / 10 } /*< 14 */
						  } },
						  renderer }
	, SoundInitializer{ { HOB_SOUNDS_FILE_PATH("error") } }
	, waitOpponentReady{}
	, fillBarIndex{ LOADING_SCREEN_COMPONENT_INDEX_FILL_FIRST }
{
	plog_trace("Loading screen is being constructed.");
	step(renderer);
	interruptWait = false;
}

void LoadingScreen::step(SDL_Renderer* const renderer) noexcept
{
	plog_trace("Loading screen is being stepped.");
	plog_assert(nullptr != this);
	plog_assert(nullptr != renderer);
	plog_assert(LOADING_SCREEN_COMPONENT_INDEX_FILL_LAST >= fillBarIndex);

	if (0 != SDL_RenderClear(renderer))
	{
		plog_error("Renderer failed to be cleared! (error message: %s)", SDL_GetError());
		return;
	}

	if (LOADING_SCREEN_COMPONENT_INDEX_FILL_LAST == fillBarIndex)
	{
		componentContainer[LOADING_SCREEN_COMPONENT_INDEX_TEXT].updateTexture(textureContainer[LOADING_SCREEN_TEXTURE_INDEX_WAITING_TEXT]);
		componentContainer[LOADING_SCREEN_COMPONENT_INDEX_TEXT].correctPosition({ .x = -2 * HSCALE, .y = 0, .w = 4 * HSCALE, .h = 0 });
	}
	componentContainer[fillBarIndex++].correctPosition({ .x = 0, .y = 0, .w = HSCALE, .h = HSCALE / 2 + HSCALE / 4 - 3 });

	draw(renderer);
	SDL_RenderPresent(renderer);
}

void LoadingScreen::startGame(void) noexcept
{
	plog_debug("Start game notification received.");
	plog_assert(nullptr != this);

	mutex.lock();
	interruptWait = true;
	mutex.unlock();

	waitOpponentReady.notify_one();
}

void LoadingScreen::waitOpponent(const uint16_t timeout, const Socket& socket) noexcept(false)
{
	std::unique_lock<std::mutex> lockWait(mutex);
	hobServer::Message			 startMessage = { .type = hobServer::MessageType::START_GAME, .payload = {} };

	plog_debug("Waiting for the opponent to be ready. (timeout: %" PRIu16 ")", timeout);
	plog_assert(nullptr != this);

	socket.sendUpdate(startMessage);

	(void)waitOpponentReady.wait_for(lockWait, std::chrono::milliseconds(timeout), [] { return interruptWait; });
	if (false == interruptWait)
	{
		startMessage.type = hobServer::MessageType::END_COMMUNICATION;
		socket.sendUpdate(startMessage);
		soundContainer[LOADING_SCREEN_SOUND_INDEX_ERROR].play();

		throw std::exception();
	}

	plog_debug("The opponent is ready.");
}

} /*< namespace hob */
