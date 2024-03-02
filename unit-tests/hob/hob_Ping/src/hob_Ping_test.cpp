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
 * @file hob_Ping_test.cpp
 * @author Gaina Stefan
 * @date 01.03.2024
 * @brief This file unit-tests hob_Ping.cpp.
 * @details Current coverage report:
 * <ul>
 * <li> Line coverage: 100.0% (73/73) </li>
 * <li> Functions:     90.0%  (9/10)  </li>
 * <li> Branches:      100.0% (20/20) </li>
 * </ul>
 * @todo The virtual destructor in IDrawable is being called but it is not seen by gcov.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "hob_Texture_mock.hpp"
#include "hob_Component_mock.hpp"
#include "hob_Socket_mock.hpp"
#include "SDL_mock.hpp"
#include "SDL_ttf_mock.hpp"
#include "stl_string_begin.hpp"
#include "hob_Ping.cpp"
#include "stl_string_end.hpp"

/******************************************************************************************************
 * CONSTANTS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Dummy address to pass the != nulllptr check.
 *****************************************************************************************************/
static constexpr const size_t not_nullptr = 0x1UL;

/******************************************************************************************************
 * TEST CLASS
 *****************************************************************************************************/

class PingTest : public testing::Test
{
public:
	PingTest(void)
		: textureMock{}
		, componentMock{}
		, socketMock{}
		, sdlMock{}
		, ttfMock{}
		, stlStringMock{}
	{
	}

	~PingTest(void) = default;

protected:
	void SetUp(void) override
	{
	}

	void TearDown(void) override
	{
	}

public:
	TextureMock	  textureMock;
	ComponentMock componentMock;
	SocketMock	  socketMock;
	SDLMock		  sdlMock;
	TTFMock		  ttfMock;
	StlStringMock stlStringMock;
};

/******************************************************************************************************
 * draw
 *****************************************************************************************************/

TEST_F(PingTest, draw_queueEmpty_success)
{
	hob::Ping ping = {};

	EXPECT_CALL(componentMock, draw(testing::_));

	ping.draw(nullptr);

	EXPECT_CALL(textureMock, destroy());
	EXPECT_CALL(componentMock, updateTexture(nullptr));
}

/******************************************************************************************************
 * update
 *****************************************************************************************************/

TEST_F(PingTest, update_fontOpenError_fail)
{
	const hob::Socket socket = {};
	hob::Ping		  ping	 = {};

	EXPECT_CALL(sdlMock, SDL_GetTicks64()) /**/
		.WillOnce(testing::Return(0UL));
	EXPECT_CALL(ttfMock, TTF_OpenFont("assets/textures/miscellaneous/Anonymous.ttf", 12)) /**/
		.WillOnce(testing::Return(nullptr));

	ping.update(socket);

	EXPECT_CALL(textureMock, destroy());
	EXPECT_CALL(componentMock, updateTexture(nullptr));
}

TEST_F(PingTest, update_success)
{
	const hob::Socket socket = {};
	hob::Ping		  ping	 = {};

	EXPECT_CALL(sdlMock, SDL_GetTicks64()) /**/
		.WillOnce(testing::Return(0UL))
		.WillOnce(testing::Return(0UL))
		.WillOnce(testing::Return(0UL))
		.WillOnce(testing::Return(1UL))
		.WillOnce(testing::Return(1UL + 2UL))
		.WillOnce(testing::Return(1UL + 2UL + 1UL))
		.WillOnce(testing::Return(0UL))
		.WillOnce(testing::Return(0UL));
	EXPECT_CALL(ttfMock, TTF_OpenFont("assets/textures/miscellaneous/Anonymous.ttf", 12)) /**/
		.WillOnce(testing::Return((TTF_Font*)not_nullptr));
	EXPECT_CALL(socketMock, sendUpdate(testing::_)).Times(2);

	ping.update(socket);
	ping.update(socket);
	ping.update(socket);

	EXPECT_CALL(stlStringMock, to_string_ut(testing::_)) /**/
		.Times(3);
	EXPECT_CALL(stlStringMock, operatorPlus(testing::_, testing::_));
	EXPECT_CALL(stlStringMock, operatorEqual(testing::_));
	EXPECT_CALL(stlStringMock, copyConstructor(testing::_)) /**/
		.Times(2);
	EXPECT_CALL(textureMock, destroy());
	EXPECT_CALL(textureMock, create(testing::_, testing::_, testing::_, testing::_));
	EXPECT_CALL(componentMock, updateTexture(testing::Matcher<const hob::Texture&>(testing::_)));
	EXPECT_CALL(componentMock, updatePosition(testing::_));
	EXPECT_CALL(componentMock, draw(testing::_)) /**/
		.Times(3);

	ping.draw(nullptr);
	ping.update(socket);

	EXPECT_CALL(stlStringMock, operatorPlus(testing::_, testing::_)) /**/
		.WillOnce(testing::Throw(std::bad_alloc()));

	ping.draw(nullptr);
	ping.update(socket);

	EXPECT_CALL(stlStringMock, operatorPlus(testing::_, testing::_));
	EXPECT_CALL(stlStringMock, operatorEqual(testing::_)) /**/
		.WillOnce(testing::Throw(std::bad_alloc()));

	ping.draw(nullptr);
	ping.update(socket);
	usleep(1000U * 1000U + 500U * 1000U);

	EXPECT_CALL(ttfMock, TTF_CloseFont(testing::_));
	EXPECT_CALL(textureMock, destroy());
	EXPECT_CALL(componentMock, updateTexture(nullptr));
}
