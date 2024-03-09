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
 * @file hob_LoadingScreen_test.cpp
 * @author Gaina Stefan
 * @date 04.03.2024
 * @brief This file unit-tests hob_LoadingScreen.cpp.
 * @details Current coverage report:
 * <ul>
 * <li> Line coverage: 100.0% (33/33) </li>
 * <li> Functions:     100.0% (5/5)   </li>
 * <li> Branches:      83.3% (10/12) </li>
 * </ul>
 * @todo std::unique_lockand wait_for generate branches. Find out how to cover them too.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "SDL_mock.hpp"
#include "hob_TextureInitializer_mock.hpp"
#include "hob_SoundInitializer_mock.hpp"
#include "hob_Component_mock.hpp"
#include "hob_Socket_mock.hpp"
#include "hob_Sound_mock.hpp"
#include "stl_string_begin.hpp"
#include "hob_LoadingScreen.cpp"
#include "stl_string_end.hpp"

/******************************************************************************************************
 * TEST CLASS
 *****************************************************************************************************/

class LoadingScreenTest : public testing::Test
{
public:
	LoadingScreenTest(void)
		: sdlMock{}
		, textureInitializerMock{}
		, componentMock{}
		, socketMock{}
	{
	}

	~LoadingScreenTest(void) = default;

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
	ComponentMock		   componentMock;
	SoundMock			   soundMock;
	SocketMock			   socketMock;
};

/******************************************************************************************************
 * step
 *****************************************************************************************************/

TEST_F(LoadingScreenTest, step_success)
{
	EXPECT_CALL(sdlMock, SDL_RenderClear(testing::_)) /**/
		.WillRepeatedly(testing::Return(0));
	EXPECT_CALL(componentMock, correctPosition(testing::_)) /**/
		.Times(11);
	EXPECT_CALL(textureInitializerMock, draw(testing::_)) /**/
		.Times(12);
	EXPECT_CALL(sdlMock, SDL_RenderPresent(testing::_)) /**/
		.Times(12);

	hob::LoadingScreen loadingScreen = { nullptr, false };

	loadingScreen.step(nullptr);
	loadingScreen.step(nullptr);
	loadingScreen.step(nullptr);
	loadingScreen.step(nullptr);
	loadingScreen.step(nullptr);
	loadingScreen.step(nullptr);
	loadingScreen.step(nullptr);
	loadingScreen.step(nullptr);
	loadingScreen.step(nullptr);
	loadingScreen.step(nullptr);

	EXPECT_CALL(componentMock, updateTexture(testing::Matcher<const hob::Texture&>(testing::_)));
	EXPECT_CALL(componentMock, correctPosition(testing::_)).Times(2);

	loadingScreen.step(nullptr);
}

/******************************************************************************************************
 * waitOpponent
 *****************************************************************************************************/

TEST_F(LoadingScreenTest, waitOpponent_timeout_fail)
{
	EXPECT_CALL(sdlMock, SDL_RenderClear(testing::_)) /**/
		.WillOnce(testing::Return(-1));

	hob::LoadingScreen loadingScreen = { nullptr, true };
	hob::Socket		   socket		 = {};

	EXPECT_CALL(socketMock, sendUpdate(testing::_)) /**/
		.Times(2);
	EXPECT_CALL(soundMock, play());

	try
	{
		loadingScreen.waitOpponent(10, socket);
	}
	catch (...)
	{
		return;
	}

	ADD_FAILURE() << "Opponent wait did not throw exception even though it timed out!";
}

TEST_F(LoadingScreenTest, waitOpponent_success)
{
	EXPECT_CALL(sdlMock, SDL_RenderClear(testing::_)) /**/
		.WillOnce(testing::Return(-1));

	hob::LoadingScreen loadingScreen = { nullptr, true };
	hob::Socket		   socket		 = {};

	EXPECT_CALL(socketMock, sendUpdate(testing::_));

	loadingScreen.startGame();
	try
	{
		loadingScreen.waitOpponent(1000, socket);
	}
	catch (...)
	{
		ADD_FAILURE() << "Opponent wait threw exception even though it did not time out!";
	}
}
