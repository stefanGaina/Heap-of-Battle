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

#ifndef HOB_PING_MOCK_HPP_
#define HOB_PING_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>

#include "hob_Ping.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

class PingDummy
{
public:
	virtual ~PingDummy(void)					   = default;

	virtual void draw(SDL_Renderer* renderer)	   = 0;
	virtual void update(const hob::Socket& socket) = 0;
};

class PingMock : public PingDummy
{
public:
	PingMock(void)
	{
		pingMock = this;
	}

	virtual ~PingMock(void)
	{
		pingMock = nullptr;
	}

	MOCK_METHOD1(draw, void(SDL_Renderer*));
	MOCK_METHOD1(update, void(const hob::Socket&));
	MOCK_METHOD0(clean, void(void));

public:
	static PingMock* pingMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

PingMock* PingMock::pingMock = nullptr;

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

Ping::Ping(void) noexcept
{
}

Ping::~Ping(void) noexcept
{
}

void Ping::draw(SDL_Renderer* const renderer) noexcept
{
	ASSERT_NE(nullptr, PingMock::pingMock) << "draw(): nullptr == PingMock::pingMock";
	PingMock::pingMock->draw(renderer);
}

void Ping::update(const Socket& socket) noexcept
{
	ASSERT_NE(nullptr, PingMock::pingMock) << "update(): nullptr == PingMock::pingMock";
	PingMock::pingMock->update(socket);
}

} /*< namespace hob */

#endif /*< HOB_PING_MOCK_HPP_ */
