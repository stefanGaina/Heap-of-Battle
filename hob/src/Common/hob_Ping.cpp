/******************************************************************************************************
 * @file hob_Ping.cpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 26.08.2023  Gaina Stefan               Initial version.                                            *
 * @details This file implements the class defined in hob_Ping.hpp.                                   *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Ping.hpp"
#include "hob_Socket.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

bool Ping::s_interruptWait = true;

Ping::Ping(void) noexcept
	: m_component       {}
	, m_texture         {}
	, m_font            { NULL }
	, m_pingThread      {}
	, m_waitTime        {}
	, m_waitMutex       {}
	, m_messageStartTime{ 0ULL }
	, m_previousLatency { 1000U }
{
	plog_trace("Ping is being constructed. (size: %" PRIu64 ") (1: %" PRIu64 ") (2: %" PRIu64 ") (3: %" PRIu64 ") (4: %" PRIu64 ")"
		"(5: %" PRIu64 ") (6: %" PRIu64 ") (7: %" PRIu64 ") (8: %" PRIu64 ")", sizeof(*this), sizeof(m_component), sizeof(m_texture),
		sizeof(m_font), sizeof(m_pingThread), sizeof(m_waitTime), sizeof(m_waitMutex), sizeof(m_messageStartTime), sizeof(m_previousLatency));
}

Ping::~Ping(void) noexcept
{
	plog_trace("Ping is being destructed.");
	clean();
}

void Ping::draw(void) noexcept
{
	plog_verbose("Ping is being drawn.");
	m_component.draw();
}

void Ping::update(void) noexcept
{
	static constexpr const SDL_Color YELLOW                 = { 0xFF, 0xFF, 0x00, 0xFF };
	static constexpr const uint64_t  SECOND_IN_MILLISECONDS = 1000ULL;

	const uint64_t    pingEndTime      = SDL_GetTicks64();
	const uint64_t    latency          = SECOND_IN_MILLISECONDS <= pingEndTime - m_messageStartTime ? SECOND_IN_MILLISECONDS - 1ULL : pingEndTime - m_messageStartTime;
	const std::string text             = std::to_string(latency) + " ms";
	Coordinate        textureDimension = {};

	plog_verbose("Ping is being updated. (latency: %" PRIu64 ")", latency);
	if (false == m_pingThread.joinable())
	{
		m_font = TTF_OpenFont("assets/textures/miscellaneous/Anonymous.ttf", 12L);
		if (NULL == m_font)
		{
			plog_error("Font failed to be opened! (TTF error message: %s)", TTF_GetError());
			return;
		}

		s_interruptWait = false;
		m_pingThread    = std::thread{ std::bind(&Ping::sendPings, this) };
		return;
	}

	if (latency == m_previousLatency)
	{
		plog_verbose("Ping does not need to be updated.");
		return;
	}
	m_previousLatency = latency;

	m_texture.destroy();
	textureDimension = m_texture.create(text, m_font, YELLOW);

	m_component.updateTexture(m_texture.getRawTexture());
	m_component.updatePosition({ 15L * SCALE - SCALE / 2L + 7L, 0L, textureDimension.x, textureDimension.y });
}

void Ping::clean(void) noexcept
{
	plog_debug("Ping is being cleaned!");

	TTF_CloseFont(m_font);
	m_texture.destroy();
	m_component.updateTexture(NULL);

	{
		std::unique_lock<std::mutex> lock(m_waitMutex);
		s_interruptWait = true;
	}
	m_waitTime.notify_all();

	if (true == m_pingThread.joinable())
	{
		plog_debug("Ping thread is being joined.");
		m_pingThread.join();
		plog_debug("Ping thread has joined.");
	}
}

void Ping::sendPings(void) noexcept
{
	std::unique_lock<std::mutex> lockWait(m_waitMutex);
	hobServer::Message           pingMessage = {};

	plog_trace("Send pings thread has started.");
	pingMessage.type = hobServer::MessageType::PING;

	while (true)
	{
		m_messageStartTime = SDL_GetTicks64();
		Socket::getInstance().sendUpdate(pingMessage);

		plog_verbose("Waiting 1 second.");
		m_waitTime.wait_for(lockWait, std::chrono::milliseconds(1000LL), [] { return s_interruptWait; });

		if (true == s_interruptWait)
		{
			plog_debug("Send pings thread has been interrupted.");
			break;
		}
		plog_trace("One second passed.");
	}
}

} /*< namespace hob */
