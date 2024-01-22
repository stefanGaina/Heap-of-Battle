/******************************************************************************************************
 * Heap of Battle Copyright (C) 2024                                                                  *
 *                                                                                                    *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the   *
 * authors be held liable for any damages arising from the use of this software.                      *
 *                                                                                                    *
 * Permission is granted to anyone to use this software for any purpose, including commercial         *
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:   *
 *                                                                                                    *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the   *
 *    original software. If you use this software in a product, an acknowledgment in the product      *
 *    documentation would be appreciated but is not required.                                         *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being *
 *    the original software.                                                                          *
 * 3. This notice may not be removed or altered from any source distribution.                         *
 *****************************************************************************************************/

/******************************************************************************************************
 * @file hob_Music_test.cpp                                                                           *
 * @date:      @author:                   Reason for change:                                          *
 * 22.01.2024  Gaina Stefan               Initial version.                                            *
 * @details This file unit-tests hob_Music.cpp.                                                       *
 * Current coverage report:                                                                           *
 * Line coverage: 100.0% (63/63)                                                                      *
 * Functions:     100.0% (7/7)                                                                        *
 * Branches:      100.0% (20/20)                                                                      *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "SDL_mixer_mock.hpp"
#include "hob_Music.hpp"

/******************************************************************************************************
 * CONSTANTS                                                                                          *
 *****************************************************************************************************/

/**
 * @brief Dummy address to pass the != nulllptr check.
*/
static constexpr const size_t not_nullptr = 0x1UL;

/******************************************************************************************************
 * TEST CLASS                                                                                         *
 *****************************************************************************************************/

class MusicTest : public testing::Test
{
public:
	MusicTest(void)
		: mixMock{}
	{
	}

	~MusicTest(void) = default;

protected:
	void SetUp(void) override
	{
	}

	void TearDown(void) override
	{
	}

public:
	MixMock mixMock;
};

/******************************************************************************************************
 * start                                                                                              *
 *****************************************************************************************************/

TEST_F(MusicTest, start_loadMus_fail)
{
	hob::Music music = {};

	EXPECT_CALL(mixMock, Mix_LoadMUS(testing::_))
		.WillOnce(testing::Return(nullptr));

	music.start(hob::Song::MAIN_MENU);
}

TEST_F(MusicTest, start_songInvalid_fail)
{
	hob::Music music = {};
	music.start(static_cast<hob::Song>(static_cast<int32_t>(hob::Song::SCENARIO_HORDE) + 1));
}

TEST_F(MusicTest, start_alreadyStarted_success)
{
	hob::Music music = {};

	EXPECT_CALL(mixMock, Mix_LoadMUS(testing::_))
		.WillOnce(testing::Return((Mix_Music*)not_nullptr));
	EXPECT_CALL(mixMock, Mix_PlayMusic(testing::_, testing::_));
	EXPECT_CALL(mixMock, Mix_VolumeMusic(testing::_));

	music.start(hob::Song::SCENARIO_ALLIANCE);
	music.start(hob::Song::SCENARIO_ALLIANCE);

	EXPECT_CALL(mixMock, Mix_FreeMusic(testing::_));
}

/******************************************************************************************************
 * pause                                                                                              *
 *****************************************************************************************************/

TEST_F(MusicTest, pause_fail)
{
	hob::Music music = {};
	music.pause();
}

TEST_F(MusicTest, pause_success)
{
	hob::Music music = {};

	EXPECT_CALL(mixMock, Mix_LoadMUS(testing::_))
		.WillOnce(testing::Return((Mix_Music*)not_nullptr));
	EXPECT_CALL(mixMock, Mix_PlayMusic(testing::_, testing::_));
	EXPECT_CALL(mixMock, Mix_VolumeMusic(testing::_));

	music.start(hob::Song::SCENARIO_HORDE);
	music.pause();

	EXPECT_CALL(mixMock, Mix_FreeMusic(testing::_));
}

/******************************************************************************************************
 * resume                                                                                             *
 *****************************************************************************************************/

TEST_F(MusicTest, resume_fail)
{
	hob::Music music = {};

	music.resume();
}

TEST_F(MusicTest, resume_success)
{
	hob::Music music = {};

	EXPECT_CALL(mixMock, Mix_LoadMUS(testing::_))
		.WillOnce(testing::Return((Mix_Music*)not_nullptr));
	EXPECT_CALL(mixMock, Mix_PlayMusic(testing::_, testing::_));
	EXPECT_CALL(mixMock, Mix_VolumeMusic(testing::_));

	music.start(hob::Song::SCENARIO_HORDE);
	music.resume();

	EXPECT_CALL(mixMock, Mix_FreeMusic(testing::_));
}

/******************************************************************************************************
 * setVolume                                                                                          *
 *****************************************************************************************************/

TEST_F(MusicTest, setVolume_success)
{
	hob::Music music = {};

	EXPECT_CALL(mixMock, Mix_VolumeMusic(testing::_))
		.Times(6);

	music.setVolume(hob::Volume::MUTED);
	music.setVolume(hob::Volume::LOW);
	music.setVolume(hob::Volume::MEDIUM);
	music.setVolume(hob::Volume::HIGH);
	music.setVolume(hob::Volume::VERY_HIGH);
	music.setVolume(hob::Volume::MAX);
	music.setVolume(static_cast<hob::Volume>(static_cast<int32_t>(hob::Volume::MAX) + 1));
}
