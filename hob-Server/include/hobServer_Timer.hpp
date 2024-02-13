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
 * @file hobServer_Timer.hpp
 * @author Gaina Stefan
 * @date 26.07.2023
 * @brief This file defines the class and method prototypes of the timer.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_SERVER_TIMER_HPP_
#define HOB_SERVER_TIMER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hobServer
{

/** ***************************************************************************************************
 * @brief Timer with second precision.
 *****************************************************************************************************/
class Timer
{
public:
	/** ***********************************************************************************************
	 * @brief Stops the timer.
	 * @param void
	 *************************************************************************************************/
	virtual ~Timer(void) noexcept;

protected:
	/** ***********************************************************************************************
	 * @brief Calls onTimeUpdate each second asynchronically.
	 * @param seconds: How many seconds will pass until onTimesUp is called.
	 * @return void
	 *************************************************************************************************/
	void startTimer(uint16_t seconds) noexcept;

	/** ***********************************************************************************************
	 * @brief Stops the timer.
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void stopTimer(void) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Function that waits for one second before calling onTimeUpdate.
	 * @param timeLeft: How many more iterations are left.
	 * @return void
	 *************************************************************************************************/
	void		 timerFunction(uint16_t timeLeft) noexcept;

	/** ***********************************************************************************************
	 * @brief Abstract method called each second.
	 * @param timeLeft:
	 * @return void
	 *************************************************************************************************/
	virtual void onTimeUpdate(uint16_t timeLeft) noexcept	  = 0;

	/** ***********************************************************************************************
	 * @brief Abstract method called when there is no time left.
	 * @param[out] timeLeft: The time allowed for the next turn.
	 * @return void
	 *************************************************************************************************/
	virtual void onTimesUp(uint16_t& timeLeft) const noexcept = 0;

private:
	/** ***********************************************************************************************
	 * @brief It is static because it is used in a lambda function.
	 *************************************************************************************************/
	static bool				interruptWait;

	/** ***********************************************************************************************
	 * @brief The thread on which the timer runs when it is started.
	 *************************************************************************************************/
	std::thread				timerThread;

	/** ***********************************************************************************************
	 * @brief The variable signaled when the timer is stopped (to avoid waiting the remaining second).
	 *************************************************************************************************/
	std::condition_variable waitTime;

	/** ***********************************************************************************************
	 * @brief Mutex protecting interruptWait.
	 *************************************************************************************************/
	std::mutex				waitMutex;
};

} /*< namespace hobServer */

#endif /*< HOB_SERVER_TIMER_HPP_ */
