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
 * @file hob_ChatFrame_test.cpp
 * @author Gaina Stefan
 * @date 10.03.2024
 * @brief This file unit-tests hob_ChatFrame.cpp.
 * @details Current coverage report:
 * <ul>
 * <li> Line coverage: 100.0% (11/11) </li>
 * <li> Functions:     100.0% (4/4)   </li>
 * <li> Branches:      N/A    (0/0)   </li>
 * </ul>
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "hob_TextureInitializer_mock.hpp"
#include "hob_ChatFrame.cpp"

/******************************************************************************************************
 * TEST CLASS
 *****************************************************************************************************/

class ChatFrameTest : public testing::Test
{
public:
	ChatFrameTest(void)
		: textureInitializerMock{}
		, componentMock{}
	{
	}

	~ChatFrameTest(void) = default;

protected:
	void SetUp(void) override
	{
	}

	void TearDown(void) override
	{
	}

public:
	TextureInitializerMock textureInitializerMock;
	ComponentMock		   componentMock;
};

/******************************************************************************************************
 * isClickInside
 *****************************************************************************************************/

TEST_F(ChatFrameTest, isClickInside_fail)
{
	const hob::ChatFrame chatFrame = { nullptr };

	EXPECT_CALL(componentMock, isMouseInside(testing::_, testing::_)).WillOnce(testing::Return(false));

	EXPECT_EQ(false, chatFrame.isClickInside({ .x = 0, .y = 0 })) << "Chat frame returned click is inside even though it is not";
}

TEST_F(ChatFrameTest, isClickInside_success)
{
	const hob::ChatFrame chatFrame = { nullptr };

	EXPECT_CALL(componentMock, isMouseInside(testing::_, testing::_)).WillOnce(testing::Return(true));

	EXPECT_EQ(true, chatFrame.isClickInside({ .x = 0, .y = 0 })) << "Chat frame returned click is not inside even though it is";
}

/******************************************************************************************************
 * showInputBox
 *****************************************************************************************************/

TEST_F(ChatFrameTest, showInputBox_success)
{
	hob::ChatFrame chatFrame = { nullptr };

	EXPECT_CALL(componentMock, updatePosition(testing::_));

	chatFrame.showInputBox();
}

/******************************************************************************************************
 * hideInputBox
 *****************************************************************************************************/

TEST_F(ChatFrameTest, hideInputBox_success)
{
	hob::ChatFrame chatFrame = { nullptr };

	EXPECT_CALL(componentMock, updatePosition(testing::_));

	chatFrame.hideInputBox();
}
