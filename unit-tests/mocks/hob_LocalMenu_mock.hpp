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

#ifndef HOB_LOCAL_MENU_MOCK_HPP_
#define HOB_LOCAL_MENU_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>

#include "hob_LocalMenu.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

class LocalMenuDummy
{
public:
	virtual ~LocalMenuDummy(void) = default;

	virtual void draw(void) = 0;
	virtual void handleEvent(const SDL_Event& event) = 0;
};

class LocalMenuMock : public LocalMenuDummy
{
public:
	LocalMenuMock(void)
	{
		localMenuMock = this;
	}

	virtual ~LocalMenuMock(void)
	{
		localMenuMock = nullptr;
	}

	MOCK_METHOD0(draw, void(void));
	MOCK_METHOD1(handleEvent, void(const SDL_Event&));

public:
	static LocalMenuMock* localMenuMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

LocalMenuMock* LocalMenuMock::localMenuMock = nullptr;

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

LocalMenu::LocalMenu(SDL_Renderer* const renderer, Cursor& cursor, Ping* const ping, Music& music,
	Faction& faction, hobServer::Server& server, Socket& socket) noexcept
	: Loop{ nullptr, cursor, nullptr }
	, TextureInitializer
	{
		{},
		{},
		{},
		nullptr
	}
	, SoundInitializer
	{
		{}
	}
	, music  { music }
	, faction{ faction }
	, server { server }
	, socket { socket }
{
}

LocalMenu::~LocalMenu(void) noexcept
{
}

void LocalMenu::draw(void) noexcept
{
	ASSERT_NE(nullptr, LocalMenuMock::localMenuMock) << "draw(): nullptr == LocalMenuMock::localMenuMock";
	LocalMenuMock::localMenuMock->draw();
}

void LocalMenu::handleEvent(const SDL_Event& event) noexcept
{
	ASSERT_NE(nullptr, LocalMenuMock::localMenuMock) << "handleEvent(): nullptr == LocalMenuMock::localMenuMock";
	LocalMenuMock::localMenuMock->handleEvent(event);
}

} /*< namespace hob */

#endif /*< HOB_LOCAL_MENU_MOCK_HPP_ */
