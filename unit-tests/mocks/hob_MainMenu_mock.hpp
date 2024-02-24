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

#ifndef HOB_MAIN_MENU_MOCK_HPP_
#define HOB_MAIN_MENU_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>

#include "hob_MainMenu.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

class MainMenuDummy
{
public:
	virtual ~MainMenuDummy(void) = default;

	virtual void draw(void)							 = 0;
	virtual void handleEvent(const SDL_Event& event) = 0;
};

class MainMenuMock : public MainMenuDummy
{
public:
	MainMenuMock(void)
	{
		mainMenuMock = this;
	}

	virtual ~MainMenuMock(void)
	{
		mainMenuMock = nullptr;
	}

	MOCK_METHOD0(draw, void(void));
	MOCK_METHOD1(handleEvent, void(const SDL_Event&));

public:
	static MainMenuMock* mainMenuMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

MainMenuMock* MainMenuMock::mainMenuMock = nullptr;

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

MainMenu::MainMenu(SDL_Renderer* const renderer, Cursor& cursor, Music& music) noexcept
	: Loop{ nullptr, cursor, nullptr }
	, TextureInitializer{ {}, {}, {}, nullptr }
	, SoundInitializer{ {} }
	, music{ music }
{
}

void MainMenu::draw(void) noexcept
{
	ASSERT_NE(nullptr, MainMenuMock::mainMenuMock) << "draw(): nullptr == MainMenuMock::mainMenuMock";
	MainMenuMock::mainMenuMock->draw();
}

void MainMenu::handleEvent(const SDL_Event& event) noexcept
{
	ASSERT_NE(nullptr, MainMenuMock::mainMenuMock) << "handleEvent(): nullptr == MainMenuMock::mainMenuMock";
	MainMenuMock::mainMenuMock->handleEvent(event);
}

} /*< namespace hob */

#endif /*< HOB_MAIN_MENU_MOCK_HPP_ */
