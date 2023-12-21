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
 * @file hob_Ping.hpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 26.08.2023  Gaina Stefan               Initial version.                                            *
 * 27.08.2023  Gaina Stefan               Added queue.                                                *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file defines the class and method prototypes of the ping.                            *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_PING_HPP_
#define HOB_PING_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <thread>
#include <mutex>
#include <condition_variable>

#include "hob_IDrawable.hpp"
#include "hob_Texture.hpp"
#include "hob_Component.hpp"
#include "hob_AsyncQueue.hpp"
#include "hob_Socket.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Displays the latency (milliseconds).
*/
class Ping final : public IDrawable
{
public:
	/**
	 * @brief Constructor.
	 * @param void
	*/
	Ping(void) noexcept;

	/**
	 * @brief Destroys the textures and cleans everything.
	 * @param void
	*/
	~Ping(void) noexcept;

	/**
	 * @brief Draws in top right corner in yellow "x ms".
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	void draw(SDL_Renderer* renderer) noexcept override;

	/**
	 * @brief A ping message has been received and the latency is being updated.
	 * @param socket: Reference to the socket object.
	 * @return void
	*/
	void update(const Socket& socket) noexcept;

	/**
	 * @brief Destroys font and texture and joins thread.
	 * @param void
	 * @return void
	*/
	void clean(void) noexcept;

private:
	/**
	 * @brief Sends ping messages every second.
	 * @param void
	 * @return void
	*/
	void sendPings(const Socket* socket) noexcept;

private:
	/**
	 * @brief It is static because it is used in a lambda function.
	*/
	static bool interruptWait;

	/**
	 * @brief Thread safe queue for buffering updates.
	*/
	AsyncQueue<uint64_t> queue;

	/**
	 * @brief The component of the text display in top right corner.
	*/
	Component component;

	/**
	 * @brief The texture of the displayed text.
	*/
	Texture texture;

	/**
	 * @brief The font of the text written in the texture.
	*/
	TTF_Font* font;

	/**
	 * @brief The thread on which the ping messages are being sent.
	*/
	std::thread pingThread;

	/**
	 * @brief The variable signaled when the timer is stopped (to avoid waiting the remaining second).
	*/
	std::condition_variable waitTime;

	/**
	 * @brief Mutex protecting interruptWait.
	*/
	std::mutex waitMutex;

	/**
	 * @brief The time when the ping message is being sent.
	*/
	uint64_t messageStartTime;

	/**
	 * @brief The previous latency to not recreate the same texture.
	*/
	uint16_t previousLatency;
};

} /*< namespace hob */

#endif /*< HOB_PING_HPP_ */
