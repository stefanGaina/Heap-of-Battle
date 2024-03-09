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

#ifndef HOB_SOUND_MOCK_HPP_
#define HOB_SOUND_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>

#include "stl_string_mock.hpp"
#include "stl_string_begin.hpp"
#include "hob_Sound.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

class SoundDummy
{
public:
	virtual ~SoundDummy(void) = default;

	virtual void setVolume(hob::Volume volume)	   = 0;
	virtual void play(void)						   = 0;
	virtual void load(const std::string& filePath) = 0;
	virtual void free(void)						   = 0;
};

class SoundMock : public SoundDummy
{
public:
	SoundMock(void)
	{
		soundMock = this;
	}

	virtual ~SoundMock(void)
	{
		soundMock = nullptr;
	}

	MOCK_METHOD1(setVolume, void(hob::Volume));
	MOCK_METHOD0(play, void(void));
	MOCK_METHOD1(load, void(const std::string&));
	MOCK_METHOD0(free, void(void));

public:
	static SoundMock* soundMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

SoundMock* SoundMock::soundMock = nullptr;

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

Sound::Sound(const std::string filePath) noexcept
{
}

Sound::~Sound(void) noexcept
{
}

void Sound::load(const std::string& filePath) noexcept
{
	ASSERT_NE(nullptr, SoundMock::soundMock) << "load(): nullptr == SoundMock::soundMock";
	SoundMock::soundMock->load(filePath);
}

void Sound::free(void) noexcept
{
	ASSERT_NE(nullptr, SoundMock::soundMock) << "free(): nullptr == SoundMock::soundMock";
	SoundMock::soundMock->free();
}

void Sound::play(void) const noexcept
{
	ASSERT_NE(nullptr, SoundMock::soundMock) << "play(): nullptr == SoundMock::soundMock";
	SoundMock::soundMock->play();
}

void Sound::setVolume(const Volume volume) noexcept
{
	ASSERT_NE(nullptr, SoundMock::soundMock) << "setVolume(): nullptr == SoundMock::soundMock";
	SoundMock::soundMock->setVolume(volume);
}

} /*< namespace hob */

#include "stl_string_end.hpp"

#endif /*< HOB_SOUND_MOCK_HPP_ */
