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
 * @file hob_Cursor_test.cpp
 * @author Gaina Stefan
 * @date 23.01.2024
 * @brief This file unit-tests hob_Cursor.cpp.
 * @details Current coverage report:
 * <ul>
 * <li> Line coverage: 100.0% (44/44) </li>
 * <li> Functions:     100.0% (5/5)   </li>
 * <li> Branches:      100.0% (19/19) </li>
 * </ul>
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "SDL_mock.hpp"
#include "hob_TextureInitializer_mock.hpp"
#include "hob_Texture_mock.hpp"
#include "hob_Component_mock.hpp"
#include "hob_Cursor.cpp"

/******************************************************************************************************
 * TEST CLASS
 *****************************************************************************************************/

class CursorTest : public testing::Test
{
public:
	CursorTest(void)
		: sdlMock{}
		, textureInitializerMock{}
		, textureMock{}
		, componentMock{}
	{
	}

	~CursorTest(void) = default;

protected:
	void SetUp(void) override
	{
	}

	void TearDown(void) override
	{
	}

public:
	SDLMock				   sdlMock;
	TextureInitializerMock textureInitializerMock;
	TextureMock			   textureMock;
	ComponentMock		   componentMock;
};

/******************************************************************************************************
 * updatePosition
 *****************************************************************************************************/

TEST_F(CursorTest, updatePosition_success)
{
	EXPECT_CALL(sdlMock, SDL_ShowCursor(testing::_)) /**/
		.WillOnce(testing::Return(-1));

	hob::Cursor		cursor	   = { nullptr };
	hob::Coordinate coordinate = { .x = 0, .y = 0 };

	EXPECT_CALL(componentMock, updatePosition(testing::_));
	cursor.updatePosition(coordinate);

	coordinate.x = 10;

	EXPECT_CALL(componentMock, updatePosition(testing::_));
	cursor.updatePosition(coordinate);

	coordinate.y = 10;

	EXPECT_CALL(componentMock, updatePosition(testing::_));
	cursor.updatePosition(coordinate);
}

/******************************************************************************************************
 * draw
 *****************************************************************************************************/

TEST_F(CursorTest, draw_cursorHidden_success)
{
	EXPECT_CALL(sdlMock, SDL_ShowCursor(SDL_QUERY)) /**/
		.WillOnce(testing::Return(SDL_ENABLE));
	EXPECT_CALL(sdlMock, SDL_ShowCursor(SDL_DISABLE)) /**/
		.WillOnce(testing::Return(-1));

	hob::Cursor cursor = { nullptr };
	cursor.draw(nullptr);
}

TEST_F(CursorTest, draw_success)
{
	EXPECT_CALL(sdlMock, SDL_ShowCursor(SDL_QUERY)) /**/
		.WillOnce(testing::Return(SDL_ENABLE));
	EXPECT_CALL(sdlMock, SDL_ShowCursor(SDL_DISABLE)) /**/
		.WillOnce(testing::Return(SDL_DISABLE));

	hob::Cursor cursor = { nullptr };

	EXPECT_CALL(textureInitializerMock, draw(testing::_));
	cursor.draw(nullptr);
}

/******************************************************************************************************
 * setFaction
 *****************************************************************************************************/

TEST_F(CursorTest, setFaction_success)
{
	EXPECT_CALL(sdlMock, SDL_ShowCursor(testing::_)) /**/
		.WillOnce(testing::Return(SDL_DISABLE));

	hob::Cursor cursor = { nullptr };

	cursor.setFaction(true);
	cursor.setFaction(false);
}

/******************************************************************************************************
 * setTexture
 *****************************************************************************************************/

TEST_F(CursorTest, setTexture_success)
{
	EXPECT_CALL(sdlMock, SDL_ShowCursor(testing::_)) /**/
		.WillOnce(testing::Return(SDL_DISABLE));

	hob::Cursor cursor = { nullptr };

	EXPECT_CALL(componentMock, updateTexture(testing::Matcher<const hob::Texture&>(testing::_))) /**/
		.Times(4);

	cursor.setTexture(hobGame::CursorType::IDLE);
	cursor.setTexture(hobGame::CursorType::SELECT);
	cursor.setTexture(hobGame::CursorType::MOVE);
	cursor.setTexture(hobGame::CursorType::ATTACK);
	cursor.setTexture(static_cast<hobGame::CursorType>(static_cast<int32_t>(hobGame::CursorType::ATTACK) + 1));
}
