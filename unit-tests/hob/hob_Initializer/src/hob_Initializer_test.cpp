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
 * @file hob_Initializer_test.cpp
 * @author Gaina Stefan
 * @date 06.04.2024
 * @brief This file unit-tests hob_Initializer.cpp.
 * @details Current coverage report:
 * <ul>
 * <li> Line coverage: 100.0% (22/22) </li>
 * <li> Functions:     100.0% (2/2)   </li>
 * <li> Branches:      100.0% (8/8)   </li>
 * </ul>
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "SDL_mock.hpp"
#include "SDL_image_mock.hpp"
#include "SDL_mixer_mock.hpp"
#include "SDL_ttf_mock.hpp"
#include "hob_Initializer.hpp"

class InitializerTest : public testing::Test
{
public:
	InitializerTest(void)
		: sdlMock{}
		, imgMock{}
		, mixMock{}
		, ttfMock{}
	{
	}

public:
	SDLMock sdlMock;
	IMGMock imgMock;
	MixMock mixMock;
	TTFMock ttfMock;
};

/******************************************************************************************************
 * constructor
 *****************************************************************************************************/

TEST_F(InitializerTest, constructor_sdlInitError_fail)
{
	EXPECT_CALL(sdlMock, SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) /**/
		.WillOnce(testing::Return(-1));

	try
	{
		hob::Initializer initializer = {};
	}
	catch (...)
	{
		return;
	}

	ADD_FAILURE() << "Initializer did not throw exception even though constructor failed!";
}

TEST_F(InitializerTest, constructor_imgInitError_fail)
{
	EXPECT_CALL(sdlMock, SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) /**/
		.WillOnce(testing::Return(0));
	EXPECT_CALL(imgMock, IMG_Init(IMG_INIT_PNG)) /**/
		.WillOnce(testing::Return(0));

	EXPECT_CALL(sdlMock, SDL_Quit());

	try
	{
		hob::Initializer initializer = {};
	}
	catch (...)
	{
		return;
	}

	ADD_FAILURE() << "Initializer did not throw exception even though constructor failed!";
}

TEST_F(InitializerTest, constructor_mixOpenAudioError_fail)
{
	EXPECT_CALL(sdlMock, SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) /**/
		.WillOnce(testing::Return(0));
	EXPECT_CALL(imgMock, IMG_Init(IMG_INIT_PNG)) /**/
		.WillOnce(testing::Return(IMG_INIT_PNG));
	EXPECT_CALL(mixMock, Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)) /**/
		.WillOnce(testing::Return(-1));

	EXPECT_CALL(imgMock, IMG_Quit());
	EXPECT_CALL(sdlMock, SDL_Quit());

	try
	{
		hob::Initializer initializer = {};
	}
	catch (...)
	{
		return;
	}

	ADD_FAILURE() << "Initializer did not throw exception even though constructor failed!";
}

TEST_F(InitializerTest, constructor_ttfInitError_fail)
{
	EXPECT_CALL(sdlMock, SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) /**/
		.WillOnce(testing::Return(0));
	EXPECT_CALL(imgMock, IMG_Init(IMG_INIT_PNG)) /**/
		.WillOnce(testing::Return(IMG_INIT_PNG));
	EXPECT_CALL(mixMock, Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)) /**/
		.WillOnce(testing::Return(0));
	EXPECT_CALL(ttfMock, TTF_Init()) /**/
		.WillOnce(testing::Return(-1));

	EXPECT_CALL(mixMock, Mix_Quit());
	EXPECT_CALL(imgMock, IMG_Quit());
	EXPECT_CALL(sdlMock, SDL_Quit());

	try
	{
		hob::Initializer initializer = {};
	}
	catch (...)
	{
		return;
	}

	ADD_FAILURE() << "Initializer did not throw exception even though constructor failed!";
}

TEST_F(InitializerTest, constructor_success)
{
	EXPECT_CALL(sdlMock, SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) /**/
		.WillOnce(testing::Return(0));
	EXPECT_CALL(imgMock, IMG_Init(IMG_INIT_PNG)) /**/
		.WillOnce(testing::Return(IMG_INIT_PNG));
	EXPECT_CALL(mixMock, Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)) /**/
		.WillOnce(testing::Return(0));
	EXPECT_CALL(ttfMock, TTF_Init()) /**/
		.WillOnce(testing::Return(0));

	EXPECT_CALL(ttfMock, TTF_Quit());
	EXPECT_CALL(mixMock, Mix_Quit());
	EXPECT_CALL(imgMock, IMG_Quit());
	EXPECT_CALL(sdlMock, SDL_Quit());

	try
	{
		hob::Initializer initializer = {};
	}
	catch (...)
	{
		ADD_FAILURE() << "Initializer threw exception even though constructor succeeded!";
	}
}
