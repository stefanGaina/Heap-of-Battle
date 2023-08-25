/******************************************************************************************************
 * @file hobServer_Timer.cpp                                                                          *
 * @date:      @author:                   Reason for change:                                          *
 * 26.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Updated the use of onTimesUp.                               *
 * @details This file implements the class defined in hobServer_Timer.hpp.                            *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hobServer_Timer.hpp"
#include "hobServer_Common.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hobServer
{

bool Timer::s_interruptWait = true;

Timer::Timer(void) noexcept
	: m_timerThread{}
	, m_waitTime   {}
	, m_waitMutex  {}
{
	plog_trace(LOG_PREFIX "Timer is being constructed.");
}

Timer::~Timer(void) noexcept
{
	plog_trace(LOG_PREFIX "Timer is being destructed.");
	stopTimer();
}

void Timer::startTimer(const uint16_t seconds) noexcept
{
	plog_info(LOG_PREFIX "Timer is being started! (time left: %" PRIu16 ")", seconds);
	stopTimer(); /*< If timer is already started or timer thread is hanging. */

	s_interruptWait = false;
	m_timerThread   = std::thread{ std::bind(&Timer::timerFunction, this, seconds) };
}

void Timer::stopTimer(void) noexcept
{
	plog_info(LOG_PREFIX "Timer is being stopped!");

	{
		std::unique_lock<std::mutex> lock(m_waitMutex);
		s_interruptWait = true;
	}
	m_waitTime.notify_all();

	if (true == m_timerThread.joinable())
	{
		plog_debug(LOG_PREFIX "Timer thread is being joined.");
		m_timerThread.join();
		plog_debug(LOG_PREFIX "Timer thread is has joined.");
	}
}

void Timer::timerFunction(uint16_t timeLeft) noexcept
{
	std::unique_lock<std::mutex> lockWait(m_waitMutex);

	plog_trace(LOG_PREFIX "Timer has started. (time left: %" PRIu16 ")", timeLeft);
	while (true)
	{
		onTimeUpdate(timeLeft);

		plog_verbose(LOG_PREFIX "Waiting 1 second.");
		m_waitTime.wait_for(lockWait, std::chrono::milliseconds(1000), [] { return s_interruptWait; });

		if (true == s_interruptWait)
		{
			plog_debug(LOG_PREFIX "Timer thread has been interrupted.");
			break;
		}

		if (0U == timeLeft)
		{
			onTimesUp(timeLeft);
			continue;
		}
		--timeLeft;
		plog_trace(LOG_PREFIX "One second passed! (time left: %" PRIu16 ")", timeLeft);
	}
}

} /*< namespace hobServer */
