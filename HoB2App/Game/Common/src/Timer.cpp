#include <plog.h>

#include "Timer.hpp"
#include "Socket.hpp"

/**
 * @brief TODO
*/
#define TEXTURE_FILE_PATH(name) "assets/textures/timer/" name ".png"

namespace Game
{

/**
 * @brief TODO
*/
std::array<std::string, 22ULL> Timer::s_filePaths = {};

/**
 * @brief TODO
*/
bool Timer::s_interruptWait = false;

void Timer::setTextures(bool isAlliance) noexcept
{
	if (true == isAlliance)
	{
		s_filePaths[0ULL ] = TEXTURE_FILE_PATH("alliance_0");
		s_filePaths[1ULL ] = TEXTURE_FILE_PATH("alliance_1");
		s_filePaths[2ULL ] = TEXTURE_FILE_PATH("alliance_2");
		s_filePaths[3ULL ] = TEXTURE_FILE_PATH("alliance_3");
		s_filePaths[4ULL ] = TEXTURE_FILE_PATH("alliance_4");
		s_filePaths[5ULL ] = TEXTURE_FILE_PATH("alliance_5");
		s_filePaths[6ULL ] = TEXTURE_FILE_PATH("alliance_6");
		s_filePaths[7ULL ] = TEXTURE_FILE_PATH("alliance_7");
		s_filePaths[8ULL ] = TEXTURE_FILE_PATH("alliance_8");
		s_filePaths[9ULL ] = TEXTURE_FILE_PATH("alliance_9");
		s_filePaths[10ULL] = TEXTURE_FILE_PATH("alliance_double_points");
		s_filePaths[11ULL] = TEXTURE_FILE_PATH("horde_0");
		s_filePaths[12ULL] = TEXTURE_FILE_PATH("horde_1");
		s_filePaths[13ULL] = TEXTURE_FILE_PATH("horde_2");
		s_filePaths[14ULL] = TEXTURE_FILE_PATH("horde_3");
		s_filePaths[15ULL] = TEXTURE_FILE_PATH("horde_4");
		s_filePaths[16ULL] = TEXTURE_FILE_PATH("horde_5");
		s_filePaths[17ULL] = TEXTURE_FILE_PATH("horde_6");
		s_filePaths[18ULL] = TEXTURE_FILE_PATH("horde_7");
		s_filePaths[19ULL] = TEXTURE_FILE_PATH("horde_8");
		s_filePaths[20ULL] = TEXTURE_FILE_PATH("horde_9");
		s_filePaths[21ULL] = TEXTURE_FILE_PATH("horde_double_points");
		return;
	}
	s_filePaths[0ULL ] = TEXTURE_FILE_PATH("horde_0");
	s_filePaths[1ULL ] = TEXTURE_FILE_PATH("horde_1");
	s_filePaths[2ULL ] = TEXTURE_FILE_PATH("horde_2");
	s_filePaths[3ULL ] = TEXTURE_FILE_PATH("horde_3");
	s_filePaths[4ULL ] = TEXTURE_FILE_PATH("horde_4");
	s_filePaths[5ULL ] = TEXTURE_FILE_PATH("horde_5");
	s_filePaths[6ULL ] = TEXTURE_FILE_PATH("horde_6");
	s_filePaths[7ULL ] = TEXTURE_FILE_PATH("horde_7");
	s_filePaths[8ULL ] = TEXTURE_FILE_PATH("horde_8");
	s_filePaths[9ULL ] = TEXTURE_FILE_PATH("horde_9");
	s_filePaths[10ULL] = TEXTURE_FILE_PATH("horde_double_points");
	s_filePaths[11ULL] = TEXTURE_FILE_PATH("alliance_0");
	s_filePaths[12ULL] = TEXTURE_FILE_PATH("alliance_1");
	s_filePaths[13ULL] = TEXTURE_FILE_PATH("alliance_2");
	s_filePaths[14ULL] = TEXTURE_FILE_PATH("alliance_3");
	s_filePaths[15ULL] = TEXTURE_FILE_PATH("alliance_4");
	s_filePaths[16ULL] = TEXTURE_FILE_PATH("alliance_5");
	s_filePaths[17ULL] = TEXTURE_FILE_PATH("alliance_6");
	s_filePaths[18ULL] = TEXTURE_FILE_PATH("alliance_7");
	s_filePaths[19ULL] = TEXTURE_FILE_PATH("alliance_8");
	s_filePaths[20ULL] = TEXTURE_FILE_PATH("alliance_9");
	s_filePaths[21ULL] = TEXTURE_FILE_PATH("alliance_double_points");
}

Timer::Timer(void) noexcept
	: TextureInitializer
	{
		s_filePaths,
		{
			0ULL, 10ULL, 0ULL, 0ULL
		},
		{
			{
				{ 2L * SCALE                   - 5L, SCALE / 9L, SCALE / 3L, SCALE / 3L },
				{ 2L * SCALE + SCALE / 4L      - 5L, SCALE / 9L, SCALE / 3L, SCALE / 3L },
				{ 2L * SCALE + 2L * SCALE / 4L - 5L, SCALE / 9L, SCALE / 3L, SCALE / 3L },
				{ 2L * SCALE + 3L * SCALE / 4L - 5L, SCALE / 9L, SCALE / 3L, SCALE / 3L }
			}
		}
	}
	, m_timeLeft      { 0U }
	, m_mutex         {}
	, m_countingThread{}
	, m_waitMutex     {}
	, m_waitTime      {}
{
	plog_trace("Timer is being constructed.");
}

Timer::~Timer(void) noexcept
{
	plog_trace("Timer is being destructed.");
	stop();
}

void Timer::updateEnemyTime(uint16_t seconds) noexcept
{
	plog_verbose("Enemy timer is being updated. (time left: %" PRIu16 ")", seconds);
	m_componentContainer[0ULL].updateTexture(m_textureContainer[ static_cast<size_t>(seconds) / 60ULL          + 11ULL].getRawTexture());
	m_componentContainer[1ULL].updateTexture(m_textureContainer[21ULL                                                 ].getRawTexture());
	m_componentContainer[2ULL].updateTexture(m_textureContainer[(static_cast<size_t>(seconds) % 60ULL) / 10ULL + 11ULL].getRawTexture());
	m_componentContainer[3ULL].updateTexture(m_textureContainer[(static_cast<size_t>(seconds) % 60ULL) % 10ULL + 11ULL].getRawTexture());
}

void Timer::start(uint16_t seconds, Callback callback) noexcept
{
	plog_info("Timer is being started! (time: %" PRIu16 ")", seconds);
	stop(); /*< If timer is already started or counting thread is hanging. */

	m_timeLeft = seconds;
	updateTextures();

	s_interruptWait  = false;
	m_countingThread = std::thread{ std::bind(&Timer::countingFunction, this, callback) };
}

void Timer::stop(void) noexcept
{
	plog_info("Timer is being stopped!");
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_timeLeft = 0U;
	}

	{
		std::unique_lock<std::mutex> lock(m_waitMutex);
		s_interruptWait = true;
	}
	m_waitTime.notify_all();

	if (true == m_countingThread.joinable())
	{
		plog_trace("Counting thread is joining.");
		m_countingThread.join();
	}
}

void Timer::countingFunction(Callback callback) noexcept
{
	Utility::Message message = {};
	message.type = Utility::MessageType::TIME;

	while (true)
	{
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			message.payload.timeLeft = m_timeLeft;
		}
		Utility::Socket::getInstance().sendUpdate(message);

		plog_verbose("Waiting 1 second.");
		std::unique_lock<std::mutex> lockWait(m_waitMutex);
		m_waitTime.wait_for(lockWait, std::chrono::milliseconds(1000), [] { return s_interruptWait; });

		std::lock_guard<std::mutex> lock(m_mutex);
		if (0U == m_timeLeft)
		{
			plog_info("Time is up!");
			if (nullptr == callback)
			{
				plog_warn("Callback is invalid!");
				break;
			}
			(*callback)();
			break;
		}
		--m_timeLeft;
		updateTextures();
		plog_trace("One second passed! (time left: %" PRIu16 ")", m_timeLeft);
	}
}

void Timer::updateTextures(void) noexcept
{
	plog_verbose("User timer textures are being updated.");
	m_componentContainer[0ULL].updateTexture(m_textureContainer[ m_timeLeft / 60U       ].getRawTexture());
	m_componentContainer[1ULL].updateTexture(m_textureContainer[10ULL                   ].getRawTexture());
	m_componentContainer[2ULL].updateTexture(m_textureContainer[(m_timeLeft % 60U) / 10U].getRawTexture());
	m_componentContainer[3ULL].updateTexture(m_textureContainer[(m_timeLeft % 60U) % 10U].getRawTexture());
}

} /*< namespace Game */
