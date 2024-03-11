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
 * @file hob_Game_test.cpp
 * @author Gaina Stefan
 * @date 24.01.2024
 * @brief This file unit-tests hob_Game_test.cpp.
 * @details Current coverage report:
 * <ul>
 * <li> Line coverage: 0.0% (0/0) </li>
 * <li> Functions:     0.0% (0/0) </li>
 * <li> Branches:      0.0% (0/0) </li>
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
#include "hobServer_Version_mock.hpp"
#include "hob_Window_mock.hpp"
#include "hob_TextureInitializer_mock.hpp"
#include "hob_Cursor_mock.hpp"
#include "hob_Music_mock.hpp"
#include "hob_Faction_mock.hpp"
#include "hobServer_Server_mock.hpp"
#include "hob_Socket_mock.hpp"
#include "hob_Ping_mock.hpp"
#include "hob_MainMenu_mock.hpp"
#include "hob_LocalMenu_mock.hpp"
#include "hob_Map1_mock.hpp"
#include "hob_Game.cpp"

/******************************************************************************************************
 * TEST CLASS
 *****************************************************************************************************/

class GameTest : public testing::Test
{
public:
	GameTest(void)
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

TEST_F(GameTest, tralalal)
{
	EXPECT_EQ(true, true);
}
