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
 * @file hob_Window_test.cpp
 * @author Gaina Stefan
 * @date 21.01.2024
 * @brief This file unit-tests hob_Window.cpp.
 * @details Current coverage report:
 * <ul>
 * <li> Line coverage: 100.0% (17/17) </li>
 * <li> Functions:     100.0% (2/2)   </li>
 * <li> Branches:      100.0% (4/4)   </li>
 * </ul>
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "SDL_mock.hpp"
#include "hob_Window.hpp"

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

class WindowTest : public testing::Test
{
public:
	WindowTest(void)
		: sdlMock{}
	{
	}

	~WindowTest(void) = default;

protected:
	void SetUp(void) override
	{
	}

	void TearDown(void) override
	{
	}

public:
	SDLMock sdlMock;
};

/******************************************************************************************************
 * create
 *****************************************************************************************************/

TEST_F(WindowTest, create_createWindow_fail)
{
	hob::Window window = {};

	EXPECT_CALL(sdlMock, SDL_CreateWindow(testing::_, testing::_, testing::_, testing::_, testing::_, testing::_))
		.WillOnce(testing::Return(nullptr));

	try
	{
		EXPECT_EQ(nullptr, window.create()) << "Window create did not return nullptr even though it failed!";
	}
	catch (const std::exception& exception)
	{
		return;
	}

	ADD_FAILURE() << "Window create did not throw exception even though it failed!";
}

TEST_F(WindowTest, create_createRenderer_fail)
{
	hob::Window window = {};

	EXPECT_CALL(sdlMock, SDL_CreateWindow(testing::_, testing::_, testing::_, testing::_, testing::_, testing::_))
		.WillOnce(testing::Return((SDL_Window*)not_nullptr));
	EXPECT_CALL(sdlMock, SDL_CreateRenderer(testing::_, testing::_, testing::_))
		.WillOnce(testing::Return(nullptr));
	EXPECT_CALL(sdlMock, SDL_DestroyWindow(testing::_));

	try
	{
		EXPECT_EQ(nullptr, window.create()) << "Window create did not return nullptr even though it failed!";
	}
	catch (const std::exception& exception)
	{
		return;
	}

	ADD_FAILURE() << "Window create did not throw exception even though it failed!";
}

TEST_F(WindowTest, create_success)
{
	hob::Window window = {};

	EXPECT_CALL(sdlMock, SDL_CreateWindow(testing::_, testing::_, testing::_, testing::_, testing::_, testing::_))
		.WillOnce(testing::Return((SDL_Window*)not_nullptr));
	EXPECT_CALL(sdlMock, SDL_CreateRenderer(testing::_, testing::_, testing::_))
		.WillOnce(testing::Return((SDL_Renderer*)not_nullptr));
	EXPECT_CALL(sdlMock, SDL_SetRenderDrawBlendMode(testing::_, testing::_));
	EXPECT_CALL(sdlMock, SDL_SetRenderDrawColor(testing::_, testing::_, testing::_, testing::_, testing::_));

	try
	{
		EXPECT_NE(nullptr, window.create()) << "Window create returned nullptr even though it did not failed!";
	}
	catch (const std::exception& exception)
	{
		ADD_FAILURE() << "Window create threw exception even though it did not failed!";
	}
}

/******************************************************************************************************
 * destroy
 *****************************************************************************************************/

TEST_F(WindowTest, destroy_success)
{
	hob::Window window = {};

	EXPECT_CALL(sdlMock, SDL_DestroyWindow(testing::_));
	window.destroy();
}
