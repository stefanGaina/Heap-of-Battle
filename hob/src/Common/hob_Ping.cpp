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
 * @file hob_Ping.cpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 26.08.2023  Gaina Stefan               Initial version.                                            *
 * 27.08.2023  Gaina Stefan               Delegated update through queue.                             *
 * 29.08.2023  Gaina Stefan               Refactored the use of the queue.                            *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file implements the class defined in hob_Ping.hpp.                                   *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <functional>
#include <plog.h>

#include "hob_Ping.hpp"
#include "hob_Socket.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

bool Ping::interruptWait = true;

Ping::Ping(void) noexcept
	: queue           {}
	, component       {}
	, texture         {}
	, font            { nullptr }
	, pingThread      {}
	, waitTime        {}
	, waitMutex       {}
	, messageStartTime{ 0UL }
	, previousLatency { 1000U }
{
	plog_trace("Ping is being constructed.");
}

Ping::~Ping(void) noexcept
{
	plog_trace("Ping is being destructed.");
	clean();
}

void Ping::draw(SDL_Renderer* const renderer) noexcept
{
	static constexpr const SDL_Color YELLOW = { 0xFFU, 0xFFU, 0x00U, 0xFFU };

	std::string text             = "";
	Coordinate  textureDimension = {};
	uint64_t    latency          = 0UL;

	plog_verbose("Ping is being drawn.");
	while (false == queue.isEmpty())
	{
		latency = queue.get();
		if (latency == previousLatency)
		{
			plog_verbose("Ping does not need to be updated.");
			continue;
		}
		previousLatency = latency;
		text            = std::to_string(latency) + " ms";

		texture.destroy();
		textureDimension = texture.create(text, font, YELLOW, renderer);

		component.updateTexture(texture);
		component.updatePosition({ .x = 30 * HSCALE - HSCALE + 7, .y = 0, .w = textureDimension.x, .h = textureDimension.y });
	}
	component.draw(renderer);
}

void Ping::update(const Socket& socket) noexcept
{
	static constexpr const uint64_t SECOND_IN_MILLISECONDS = 1000UL;

	const uint64_t pingEndTime = SDL_GetTicks64();
	const uint64_t latency     = SECOND_IN_MILLISECONDS <= pingEndTime - messageStartTime ? SECOND_IN_MILLISECONDS - 1UL : pingEndTime - messageStartTime;

	plog_verbose("Ping is being updated. (latency: %" PRIu64 ")", latency);
	if (true == pingThread.joinable())
	{
		queue.put(latency);
		return;
	}

	font = TTF_OpenFont("assets/textures/miscellaneous/Anonymous.ttf", 12);
	if (nullptr == font)
	{
		plog_error("Font failed to be opened! (TTF error message: %s)", TTF_GetError());
		return;
	}
	interruptWait = false;
	pingThread    = std::thread{ std::bind(&Ping::sendPings, this, &socket) };
}

void Ping::clean(void) noexcept
{
	plog_debug("Ping is being cleaned!");

	TTF_CloseFont(font);
	texture.destroy();
	component.updateTexture(nullptr);

	waitMutex.lock();
	interruptWait = true;
	waitMutex.unlock();

	waitTime.notify_all();

	if (true == pingThread.joinable())
	{
		plog_debug("Ping thread is being joined.");
		pingThread.join();
		plog_debug("Ping thread has joined.");
	}
}

void Ping::sendPings(const Socket* const socket) noexcept
{
	std::unique_lock<std::mutex> lockWait(waitMutex);
	hobServer::Message           pingMessage = {};

	plog_trace("Send pings thread has started.");
	pingMessage.type = hobServer::MessageType::PING;

	while (true)
	{
		messageStartTime = SDL_GetTicks64();
		socket->sendUpdate(pingMessage);

		plog_verbose("Waiting 1 second.");
		waitTime.wait_for(lockWait, std::chrono::milliseconds(1000L), [] { return interruptWait; });

		if (true == interruptWait)
		{
			plog_debug("Send pings thread has been interrupted.");
			break;
		}
		plog_trace("One second passed.");
	}
}

} /*< namespace hob */
