/******************************************************************************************************
 * @file hobServer_Timer.hpp                                                                          *
 * @date:      @author:                   Reason for change:                                          *
 * 26.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file defines the class and method prototypes of the timer.                           *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_SERVER_TIMER_HPP_
#define HOB_SERVER_TIMER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hobServer
{

/**
 * @brief Timer with second precision.
*/
class Timer
{
public:
	/**
	 * @brief Does not start the timer implicitly.
	 * @param void
	*/
	Timer(void) noexcept;

	/**
	 * @brief Stops the timer.
	 * @param void
	*/
	virtual ~Timer(void) noexcept;

	/**
	 * @brief Calls onTimeUpdate each second asynchronically.
	 * @param seconds: How many seconds will pass until onTimesUp is called.
	 * @return void
	*/
	void startTimer(uint16_t seconds) noexcept;

	/**
	 * @brief Stops the timer.
	 * @param void
	 * @return void
	*/
	void stopTimer(void) noexcept;

private:
	/**
	 * @brief Function that waits for one second before calling onTimeUpdate.
	 * @param timeLeft: How many more iterations are left.
	 * @return void
	*/
	void timerFunction(uint16_t timeLeft) noexcept;

	/**
	 * @brief Abstract method called each second.
	 * @param timeLeft:
	 * @return void
	*/
	virtual void onTimeUpdate(uint16_t timeLeft) noexcept = 0;

	/**
	 * @brief Abstract method called when there is no time left.
	 * @param void
	 * @return void
	*/
	virtual void onTimesUp(void) noexcept = 0;

private:
	/**
	 * @brief It is static because it is used in a lambda function.
	*/
	static bool s_interruptWait;

	/**
	 * @brief The thread on which the timer runs when it is started.
	*/
	std::thread m_timerThread;

	/**
	 * @brief The variable signaled when the timer is stopped (to avoid waiting the remaining second).
	*/
	std::condition_variable m_waitTime;

	/**
	 * @brief Mutex protecting s_interruptWait.
	*/
	std::mutex m_waitMutex;
};

} /*< namespace hobServer */

#endif /*< HOB_SERVER_TIMER_HPP_ */
