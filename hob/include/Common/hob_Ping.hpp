/******************************************************************************************************
 * @file hob_Ping.hpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 26.08.2023  Gaina Stefan               Initial version.                                            *
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
	 * @param
	*/
	~Ping(void) noexcept;

	/**
	 * @brief Draws in top right corner in yellow "x ms".
	 * @param void
	 * @return void
	*/
	void draw(void) noexcept override;

	/**
	 * @brief A ping message has been received and the latency is being updated.
	 * @param void
	 * @return void
	*/
	void update(void) noexcept;

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
	void sendPings(void) noexcept;

private:
	/**
	 * @brief It is static because it is used in a lambda function.
	*/
	static bool s_interruptWait;

	/**
	 * @brief The component of the text display in top right corner.
	*/
	Component m_component;

	/**
	 * @brief The texture of the displayed text.
	*/
	Texture m_texture;

	/**
	 * @brief The font of the text written in the texture.
	*/
	TTF_Font* m_font;

	/**
	 * @brief The thread on which the ping messages are being sent.
	*/
	std::thread m_pingThread;

	/**
	 * @brief The variable signaled when the timer is stopped (to avoid waiting the remaining second).
	*/
	std::condition_variable m_waitTime;

	/**
	 * @brief Mutex protecting s_interruptWait.
	*/
	std::mutex m_waitMutex;

	/**
	 * @brief The time when the ping message is being sent.
	*/
	uint64_t m_messageStartTime;

	/**
	 * @brief The previous latency to not recreate the same texture.
	*/
	uint16_t m_previousLatency;
};

} /*< namespace hob */

#endif /*< HOB_PING_HPP_ */
