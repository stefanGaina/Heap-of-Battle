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
 * @file hob_Sound_test.cpp
 * @author Gaina Stefan
 * @date 21.01.2024
 * @brief This file unit-tests hob_Sound.cpp.
 * @details Current coverage report:
 * <ul>
 * <li> Line coverage: 100.0% (44/44) </li>
 * <li> Functions:     100.0% (6/6)   </li>
 * <li> Branches:      100.0% (11/11) </li>
 * </ul>
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "SDL_mock.hpp"
#include "SDL_mixer_mock.hpp"
#include "hob_Sound.hpp"

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

class SoundTest : public testing::Test
{
public:
	SoundTest(void)
		: sdlMock{}
		, mixMock{}
	{
	}

	~SoundTest(void) = default;

protected:
	void SetUp(void) override
	{
	}

	void TearDown(void) override
	{
	}

public:
	SDLMock sdlMock;
	MixMock mixMock;
};

/******************************************************************************************************
 * play
 *****************************************************************************************************/

TEST_F(SoundTest, play_fail)
{
	hob::Sound sound = {};
	sound.play();
}

TEST_F(SoundTest, play_success)
{
	EXPECT_CALL(sdlMock, SDL_RWFromFile(testing::_, testing::_));
	EXPECT_CALL(mixMock, Mix_LoadWAV_RW(testing::_, testing::_)) /**/
		.WillOnce(testing::Return((Mix_Chunk*)not_nullptr));
	EXPECT_CALL(mixMock, Mix_PlayChannelTimed(testing::_, testing::_, testing::_, testing::_));
	EXPECT_CALL(mixMock, Mix_Volume(testing::_, testing::_));

	hob::Sound sound = { "test" };
	sound.play();

	EXPECT_CALL(mixMock, Mix_FreeChunk(testing::_));
}

/******************************************************************************************************
 * setVolume
 *****************************************************************************************************/

TEST_F(SoundTest, setVolume_success)
{
	hob::Sound sound = {};

	sound.setVolume(hob::Volume::MUTED);
	sound.setVolume(hob::Volume::LOW);
	sound.setVolume(hob::Volume::MEDIUM);
	sound.setVolume(hob::Volume::HIGH);
	sound.setVolume(hob::Volume::VERY_HIGH);
	sound.setVolume(hob::Volume::MAX);
	sound.setVolume(static_cast<hob::Volume>(static_cast<int32_t>(hob::Volume::MAX) + 1));
}
