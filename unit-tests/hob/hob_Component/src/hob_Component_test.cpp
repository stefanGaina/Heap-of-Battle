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
 * @file hob_Component_test.cpp
 * @author Gaina Stefan
 * @date 22.01.2024
 * @brief This file unit-tests hob_Component.cpp.
 * @details Current coverage report:
 * <ul>
 * <li> Line coverage: 100.0% (34/34) </li>
 * <li> Functions:     100.0% (9/9)   </li>
 * <li> Branches:      100.0% (10/10) </li>
 * </ul>
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "SDL_mock.hpp"
#include "hob_Texture_mock.hpp"
#include "hob_Component.hpp"

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

class ComponentTest : public testing::Test
{
public:
	ComponentTest(void)
		: sdlMock{}
		, textureMock{}
	{
	}

public:
	SDLMock		sdlMock;
	TextureMock textureMock;
};

/******************************************************************************************************
 * draw
 *****************************************************************************************************/

TEST_F(ComponentTest, draw_fail)
{
	hob::Component component = {};
	component.draw(nullptr);
}

TEST_F(ComponentTest, draw_success)
{
	hob::Component component = { (SDL_Texture*)not_nullptr };

	EXPECT_CALL(sdlMock, SDL_RenderCopy(testing::_, testing::_, testing::_, testing::_)) /**/
		.WillOnce(testing::Return(0));

	component.draw(nullptr);
}

/******************************************************************************************************
 * updateTexture
 *****************************************************************************************************/

TEST_F(ComponentTest, updateTexture_success)
{
	hob::Component component = {};
	hob::Texture   texture	 = {};

	EXPECT_CALL(textureMock, getRawTexture()) /**/
		.WillRepeatedly(testing::Return((SDL_Texture*)not_nullptr));

	component.updateTexture(nullptr);
	EXPECT_EQ(nullptr, component.getRawTexture()) << "Component has not updated its texture!";

	component.updateTexture(texture);
	EXPECT_EQ(true, component == texture) << "Component has not updated its texture!";
}

/******************************************************************************************************
 * updatePosition
 *****************************************************************************************************/

TEST_F(ComponentTest, updatePosition_success)
{
	hob::Component component = {};
	component.updatePosition({ .x = 10, .y = 10, .w = 10, .h = 10 });
}

/******************************************************************************************************
 * correctPosition
 *****************************************************************************************************/

TEST_F(ComponentTest, correctPosition_success)
{
	hob::Component component = {};
	component.correctPosition({ .x = 10, .y = 10, .w = 10, .h = 10 });
}

/******************************************************************************************************
 * isMouseInside
 *****************************************************************************************************/

TEST_F(ComponentTest, isMouseInside_above_success)
{
	hob::Component component = { nullptr, { .x = 10, .y = 10, .w = 10, .h = 10 } };
	EXPECT_EQ(false, component.isMouseInside({ .x = 15, .y = 0 })) << "The mouse is not inside!";
}

TEST_F(ComponentTest, isMouseInside_below_success)
{
	hob::Component component = { nullptr, { .x = 10, .y = 10, .w = 10, .h = 10 } };
	EXPECT_EQ(false, component.isMouseInside({ .x = 15, .y = 25 })) << "The mouse is not inside!";
}

TEST_F(ComponentTest, isMouseInside_left_success)
{
	hob::Component component = { nullptr, { .x = 10, .y = 10, .w = 10, .h = 10 } };
	EXPECT_EQ(false, component.isMouseInside({ .x = 0, .y = 15 })) << "The mouse is not inside!";
}

TEST_F(ComponentTest, isMouseInside_right_success)
{
	hob::Component component = { nullptr, { .x = 10, .y = 10, .w = 10, .h = 10 } };
	EXPECT_EQ(false, component.isMouseInside({ .x = 25, .y = 15 })) << "The mouse is not inside!";
}

TEST_F(ComponentTest, isMouseInside_success)
{
	hob::Component component = { nullptr, { .x = 10, .y = 10, .w = 10, .h = 10 } };
	EXPECT_EQ(true, component.isMouseInside({ .x = 15, .y = 15 })) << "The mouse is inside!";
}
