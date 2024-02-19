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
 * @file hob_Ping.cpp
 * @author Gaina Stefan
 * @date 23.07.2023
 * @brief This file implements the class defined in hob_Ping.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <functional>
#include <plog.h>

#include "hob_Ping.hpp"
#include "hob_Socket.hpp"

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

namespace hob
{

bool Ping::interruptWait = true;

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

Ping::Ping(void) noexcept
	: queue{}
	, component{}
	, texture{}
	, font{ nullptr }
	, pingThread{}
	, waitTime{}
	, waitMutex{}
	, messageStartTime{ 0UL }
	, previousLatency{ 1000U }
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
	plog_verbose("Ping is being drawn.");
	plog_assert(nullptr != renderer);

	handleQueue(renderer);
	component.draw(renderer);
}

void Ping::update(const Socket& socket) noexcept
{
	static constexpr const uint64_t SECOND_IN_MILLISECONDS = 1000UL;

	const uint64_t					pingEndTime			   = SDL_GetTicks64();
	const uint64_t latency = SECOND_IN_MILLISECONDS <= pingEndTime - messageStartTime ? SECOND_IN_MILLISECONDS - 1UL : pingEndTime - messageStartTime;

	plog_verbose("Ping is being updated. (latency: %" PRIu64 ")", latency);
	if (true == pingThread.joinable())
	{
		queue.push(latency);
		return;
	}

	font = TTF_OpenFont("assets/textures/miscellaneous/Anonymous.ttf", 12);
	if (nullptr == font)
	{
		plog_error("Font failed to be opened! (TTF error message: %s)", TTF_GetError());
		return;
	}
	interruptWait = false;
	pingThread	  = std::thread{ std::bind(&Ping::sendPings, this, &socket) };
}

void Ping::clean(void) noexcept
{
	plog_debug("Ping is being cleaned!");

	if (nullptr != font)
	{
		TTF_CloseFont(font);
		font = nullptr;
	}
	texture.destroy();
	component.updateTexture(nullptr);

	while (false == queue.isEmpty())
	{
		(void)queue.pop();
	}

	stop();
}

void Ping::stop(void) noexcept
{
	plog_debug("Ping is being stopped.");

	waitMutex.lock();
	interruptWait = true;
	waitMutex.unlock();

	waitTime.notify_one();

	if (true == pingThread.joinable())
	{
		plog_debug("Ping thread is being joined.");
		pingThread.join();
		plog_debug("Ping thread has joined.");
	}
}

void Ping::handleQueue(SDL_Renderer* const renderer) noexcept
{
	static constexpr const SDL_Color YELLOW			  = { 0xFFU, 0xFFU, 0x00U, 0xFFU };

	std::string						 text			  = {};
	Coordinate						 textureDimension = {};
	uint64_t						 latency		  = 0UL;

	plog_verbose("Queue is being handled.");
	plog_assert(nullptr != renderer);

	while (false == queue.isEmpty())
	{
		latency = queue.pop();
		if (latency == previousLatency)
		{
			plog_verbose("Ping does not need to be updated.");
			continue;
		}

		try
		{
			text = std::to_string(latency) + " ms";
		}
		catch (const std::bad_alloc& exception)
		{
			plog_error("Failed to allocate memory for ping string!");
			return;
		}
		previousLatency = latency;

		texture.destroy();
		textureDimension = texture.create(text, font, YELLOW, renderer);

		component.updateTexture(texture);
		component.updatePosition({ .x = 30 * HSCALE - HSCALE + 7, .y = 0, .w = textureDimension.x, .h = textureDimension.y });
	}
}

void Ping::sendPings(const Socket* const socket) noexcept
{
	std::unique_lock<std::mutex> lockWait(waitMutex);
	hobServer::Message			 pingMessage = { .type = hobServer::MessageType::PING, .payload = {} };

	plog_trace("Send pings thread has started.");
	plog_assert(nullptr != socket);

	while (true)
	{
		messageStartTime = SDL_GetTicks64();
		socket->sendUpdate(pingMessage);

		plog_verbose("Waiting 1 second.");
		if (true == waitTime.wait_for(lockWait, std::chrono::milliseconds(1000L), [] { return interruptWait; }))
		{
			plog_warn("Ping thread did not wait for the entire time!");
		}

		if (true == interruptWait)
		{
			plog_debug("Send pings thread has been interrupted.");
			break;
		}
		plog_trace("One second passed.");
	}
}

} /*< namespace hob */
