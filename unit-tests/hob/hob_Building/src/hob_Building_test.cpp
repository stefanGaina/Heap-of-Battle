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
 * @file hob_Building_test.cpp
 * @author Gaina Stefan
 * @date 11.03.2024
 * @brief This file unit-tests hob_Building.cpp.
 * @details Current coverage report:
 * <ul>
 * <li> Line coverage: 100.0% (35/35) </li>
 * <li> Functions:     100.0% (5/5)   </li>
 * <li> Branches:      100.0% (16/16) </li>
 * </ul>
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "hob_Component_mock.hpp"
#include "hob_Building.hpp"

/******************************************************************************************************
 * CONSTANTS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Dummy address to pass as a texture.
 *****************************************************************************************************/
static constexpr const size_t not_nullptr_1 = 0x1UL;

/** ***************************************************************************************************
 * @brief Dummy address to pass as a texture.
 *****************************************************************************************************/
static constexpr const size_t not_nullptr_2 = 0x2UL;

/******************************************************************************************************
 * TEST CLASS
 *****************************************************************************************************/

class BuildingTest : public testing::Test
{
public:
	BuildingTest(void)
		: componentMock{}
	{
	}

public:
	ComponentMock componentMock;
};

/******************************************************************************************************
 * draw
 *****************************************************************************************************/

TEST_F(BuildingTest, draw_success)
{
	hob::Building building = {};

	EXPECT_CALL(componentMock, draw(testing::_));

	building.draw(nullptr);
}

/******************************************************************************************************
 * changeWeather
 *****************************************************************************************************/

TEST_F(BuildingTest, changeWeather_summer_success)
{
	hob::Building building = {};

	EXPECT_CALL(componentMock, getRawTexture()).WillOnce(testing::Return(nullptr));

	building.changeWeather(false);
}

TEST_F(BuildingTest, changeWeather_winter_success)
{
	hob::Building building = {};

	EXPECT_CALL(componentMock, updateTexture(testing::Matcher<SDL_Texture*>(testing::_)));
	EXPECT_CALL(componentMock, updatePosition(testing::_));

	building.init(nullptr, nullptr, nullptr, (SDL_Texture*)not_nullptr_1, { .x = 0, .y = 0, .w = 0, .h = 0 });

	EXPECT_CALL(componentMock, getRawTexture()) /**/
		.WillOnce(testing::Return((SDL_Texture*)not_nullptr_1));

	building.changeWeather(true);
}

/******************************************************************************************************
 * switchTexture
 *****************************************************************************************************/

TEST_F(BuildingTest, switchTexture_texture3Nullptr_success)
{
	hob::Building building = {};

	EXPECT_CALL(componentMock, updateTexture(testing::Matcher<SDL_Texture*>(testing::_)));
	EXPECT_CALL(componentMock, updatePosition(testing::_));

	building.init(nullptr, nullptr, (SDL_Texture*)not_nullptr_1, nullptr, { .x = 0, .y = 0, .w = 0, .h = 0 });

	EXPECT_CALL(componentMock, getRawTexture()) /**/
		.WillOnce(testing::Return((SDL_Texture*)not_nullptr_1));

	building.switchTexture(false);
}

TEST_F(BuildingTest, switchTexture_texture3_success)
{
	hob::Building building = {};

	EXPECT_CALL(componentMock, updateTexture(testing::Matcher<SDL_Texture*>(testing::_))) /**/
		.Times(2);
	EXPECT_CALL(componentMock, updatePosition(testing::_));

	building.init((SDL_Texture*)not_nullptr_1, nullptr, (SDL_Texture*)not_nullptr_2, nullptr, { .x = 0, .y = 0, .w = 0, .h = 0 });

	EXPECT_CALL(componentMock, getRawTexture()) /**/
		.WillOnce(testing::Return((SDL_Texture*)not_nullptr_1));

	building.switchTexture(true);
}

TEST_F(BuildingTest, switchTexture_texture4Nullptr_success)
{
	hob::Building building = {};

	EXPECT_CALL(componentMock, updateTexture(testing::Matcher<SDL_Texture*>(testing::_)));
	EXPECT_CALL(componentMock, updatePosition(testing::_));

	building.init(nullptr, (SDL_Texture*)not_nullptr_1, nullptr, nullptr, { .x = 0, .y = 0, .w = 0, .h = 0 });

	EXPECT_CALL(componentMock, getRawTexture()) /**/
		.WillOnce(testing::Return((SDL_Texture*)not_nullptr_1));

	building.switchTexture(true);
}

TEST_F(BuildingTest, switchTexture_texture4_success)
{
	hob::Building building = {};

	EXPECT_CALL(componentMock, updateTexture(testing::Matcher<SDL_Texture*>(testing::_))) /**/
		.Times(2);
	EXPECT_CALL(componentMock, updatePosition(testing::_));

	building.init(nullptr, (SDL_Texture*)not_nullptr_1, nullptr, (SDL_Texture*)not_nullptr_2, { .x = 0, .y = 0, .w = 0, .h = 0 });

	EXPECT_CALL(componentMock, getRawTexture()) /**/
		.WillOnce(testing::Return((SDL_Texture*)not_nullptr_1));

	building.switchTexture(true);
}

TEST_F(BuildingTest, switchTexture_fail)
{
	hob::Building building = {};

	EXPECT_CALL(componentMock, updateTexture(testing::Matcher<SDL_Texture*>(testing::_)));
	EXPECT_CALL(componentMock, updatePosition(testing::_));

	building.init((SDL_Texture*)not_nullptr_2, (SDL_Texture*)not_nullptr_2, nullptr, nullptr, { .x = 0, .y = 0, .w = 0, .h = 0 });

	EXPECT_CALL(componentMock, getRawTexture()) /**/
		.WillOnce(testing::Return((SDL_Texture*)not_nullptr_1));

	building.switchTexture(true);
}
