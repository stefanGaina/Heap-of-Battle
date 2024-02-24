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

#ifndef HOB_MAP1_MOCK_HPP_
#define HOB_MAP1_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>

#include "hob_Map1.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

class Map1Dummy
{
public:
	virtual ~Map1Dummy(void) = default;

	virtual void draw(void)							 = 0;
	virtual void handleEvent(const SDL_Event& event) = 0;
};

class Map1Mock : public Map1Dummy
{
public:
	Map1Mock(void)
	{
		map1Mock = this;
	}

	virtual ~Map1Mock(void)
	{
		map1Mock = nullptr;
	}

	MOCK_METHOD0(draw, void(void));
	MOCK_METHOD1(handleEvent, void(const SDL_Event&));

public:
	static Map1Mock* map1Mock;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

Map1Mock* Map1Mock::map1Mock = nullptr;

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

Map1::Map1(SDL_Renderer* const renderer, Cursor& cursor, Ping* const ping, Music& music, const Faction& faction, hobServer::Server& server, Socket& socket) noexcept
	: Loop{ nullptr, cursor, nullptr }
	, SoundInitializer{ {} }
	, game{ false }
	, tiles{ nullptr }
	, menu{ nullptr, false, 0U }
	, buildings{ nullptr }
	, chat{ nullptr, {}, {} }
	, units{ nullptr }
	, music{ music }
	, faction{ faction }
	, server{ server }
	, socket{ socket }
{
}

Map1::~Map1(void) noexcept
{
}

void Map1::draw(void) noexcept
{
	ASSERT_NE(nullptr, Map1Mock::map1Mock) << "draw(): nullptr == Map1Mock::map1Mock";
	Map1Mock::map1Mock->draw();
}

void Map1::handleEvent(const SDL_Event& event) noexcept
{
	ASSERT_NE(nullptr, Map1Mock::map1Mock) << "handleEvent(): nullptr == Map1Mock::map1Mock";
	Map1Mock::map1Mock->handleEvent(event);
}

} /*< namespace hob */

#endif /*< HOB_MAP1_MOCK_HPP_ */
