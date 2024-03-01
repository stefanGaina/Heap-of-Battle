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
 * @file hob_FramesPerSecond_test.cpp
 * @author Gaina Stefan
 * @date 29.02.2024
 * @brief This file unit-tests hob_FramesPerSecond.cpp.
 * @details Current coverage report:
 * <ul>
 * <li> Line coverage: 100.0% (34/34) </li>
 * <li> Functions:     100.0% (3/3)   </li>
 * <li> Branches:      100.0% (8/8)   </li>
 * </ul>
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "hob_Texture_mock.hpp"
#include "hob_Component_mock.hpp"
#include "SDL_mock.hpp"
#include "SDL_ttf_mock.hpp"
#include "stl_string_begin.hpp"
#include "hob_FramesPerSecond.cpp"
#include "stl_string_end.hpp"

/******************************************************************************************************
 * TEST CLASS
 *****************************************************************************************************/

class FramesPerSecondTest : public testing::Test
{
public:
	FramesPerSecondTest(void)
		: textureMock{}
		, componentMock{}
		, sdlMock{}
		, ttfMock{}
		, stlStringMock{}
	{
	}

	~FramesPerSecondTest(void) = default;

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
	SDLMock		  sdlMock;
	TTFMock		  ttfMock;
	StlStringMock stlStringMock;
};

/******************************************************************************************************
 * draw
 *****************************************************************************************************/

TEST_F(FramesPerSecondTest, draw_success)
{
	static constexpr const uint64_t SECOND_IN_MILLISECONDS = 1000UL;

	EXPECT_CALL(ttfMock, TTF_OpenFont(testing::_, testing::_)) /**/
		.WillOnce(testing::Return(nullptr));
	EXPECT_CALL(sdlMock, SDL_GetTicks64()) /**/
		.WillOnce(testing::Return(2UL * SECOND_IN_MILLISECONDS))
		.WillOnce(testing::Return(2UL * SECOND_IN_MILLISECONDS))
		.WillOnce(testing::Return(3UL * SECOND_IN_MILLISECONDS))
		.WillOnce(testing::Return(3UL * SECOND_IN_MILLISECONDS + SECOND_IN_MILLISECONDS / 2UL))
		.WillOnce(testing::Return(4UL * SECOND_IN_MILLISECONDS))
		.WillOnce(testing::Return(4UL * SECOND_IN_MILLISECONDS + SECOND_IN_MILLISECONDS / 2UL))
		.WillOnce(testing::Return(5UL * SECOND_IN_MILLISECONDS));
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

	hob::FramesPerSecond framesPerSecond = { nullptr };

	EXPECT_CALL(componentMock, draw(testing::_)) /**/
		.Times(5);

	framesPerSecond.draw(nullptr);
	framesPerSecond.draw(nullptr);

	EXPECT_CALL(stlStringMock, operatorPlus(testing::_, testing::_)) /**/
		.WillOnce(testing::Throw(std::bad_alloc()));

	framesPerSecond.draw(nullptr);
	framesPerSecond.draw(nullptr);

	EXPECT_CALL(stlStringMock, operatorPlus(testing::_, testing::_));
	EXPECT_CALL(stlStringMock, operatorEqual(testing::_)) /**/
		.WillOnce(testing::Throw(std::bad_alloc()));

	framesPerSecond.draw(nullptr);
}
