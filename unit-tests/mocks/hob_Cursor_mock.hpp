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

#ifndef HOB_CURSOR_MOCK_HPP_
#define HOB_CURSOR_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>

#include "hob_Cursor.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

class CursorDummy
{
public:
	virtual ~CursorDummy(void)								  = default;

	virtual void updatePosition(const hob::Coordinate& mouse) = 0;
	virtual void draw(SDL_Renderer* renderer)				  = 0;
	virtual void setFaction(bool isAlliance)				  = 0;
	virtual void setTexture(hobGame::CursorType type)		  = 0;
};

class CursorMock : public CursorDummy
{
public:
	CursorMock(void)
	{
		cursorMock = this;
	}

	virtual ~CursorMock(void)
	{
		cursorMock = nullptr;
	}

	MOCK_METHOD1(updatePosition, void(const hob::Coordinate&));
	MOCK_METHOD1(draw, void(SDL_Renderer*));
	MOCK_METHOD1(setFaction, void(bool));
	MOCK_METHOD1(setTexture, void(hobGame::CursorType));

public:
	static CursorMock* cursorMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

CursorMock* CursorMock::cursorMock = nullptr;

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

Cursor::Cursor(SDL_Renderer* const renderer) noexcept
	: TextureInitializer{ {}, {}, {}, renderer }
{
}

void Cursor::updatePosition(const Coordinate& mouse) noexcept
{
	ASSERT_NE(nullptr, CursorMock::cursorMock) << "updatePosition(): nullptr == CursorMock::cursorMock";
	CursorMock::cursorMock->updatePosition(mouse);
}

void Cursor::draw(SDL_Renderer* const renderer) noexcept
{
	ASSERT_NE(nullptr, CursorMock::cursorMock) << "draw(): nullptr == CursorMock::cursorMock";
	CursorMock::cursorMock->draw(renderer);
}

void Cursor::setFaction(const bool isAlliance) noexcept
{
	ASSERT_NE(nullptr, CursorMock::cursorMock) << "setFaction(): nullptr == CursorMock::cursorMock";
	CursorMock::cursorMock->setFaction(isAlliance);
}

void Cursor::setTexture(const hobGame::CursorType type) noexcept
{
	ASSERT_NE(nullptr, CursorMock::cursorMock) << "setTexture(): nullptr == CursorMock::cursorMock";
	CursorMock::cursorMock->setTexture(type);
}

} /*< namespace hob */

#endif /*< HOB_CURSOR_MOCK_HPP_ */
