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
 * @file hobServer_Timer.cpp                                                                          *
 * @date:      @author:                   Reason for change:                                          *
 * 26.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Updated the use of onTimesUp.                               *
 * 26.08.2023  Gaina Stefan               Improved logs.                                              *
 * 27.08.2023  Gaina Stefan               Changed the way mutex is locked.                            *
 * 21.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file implements the class defined in hobServer_Timer.hpp.                            *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <cinttypes>
#include <plog.h>

#include "hobServer_Timer.hpp"
#include "hobServer_Common.hpp"

/******************************************************************************************************
 * LOCAL VARIABLES                                                                                    *
 *****************************************************************************************************/

namespace hobServer
{

bool Timer::interruptWait = true;

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

Timer::Timer(void) noexcept
	: timerThread{}
	, waitTime   {}
	, waitMutex  {}
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

	interruptWait = false;
	timerThread   = std::thread{ std::bind(&Timer::timerFunction, this, seconds) };
}

void Timer::stopTimer(void) noexcept
{
	plog_info(LOG_PREFIX "Timer is being stopped!");

	waitMutex.lock();
	interruptWait = true;
	waitMutex.unlock();

	waitTime.notify_all();

	if (true == timerThread.joinable())
	{
		plog_debug(LOG_PREFIX "Timer thread is being joined.");
		timerThread.join();
		plog_debug(LOG_PREFIX "Timer thread has joined.");
	}
}

void Timer::timerFunction(uint16_t timeLeft) noexcept
{
	std::unique_lock<std::mutex> lockWait(waitMutex);

	plog_trace(LOG_PREFIX "Timer has started. (time left: %" PRIu16 ")", timeLeft);
	while (true)
	{
		onTimeUpdate(timeLeft);

		plog_verbose(LOG_PREFIX "Waiting 1 second.");
		waitTime.wait_for(lockWait, std::chrono::milliseconds(1000L), [] { return interruptWait; });

		if (true == interruptWait)
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
		plog_trace(LOG_PREFIX "One second passed. (time left: %" PRIu16 ")", timeLeft);
	}
}

} /*< namespace hobServer */
