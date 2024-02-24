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

#ifndef HOB_MUSIC_MOCK_HPP_
#define HOB_MUSIC_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>

#include "hob_Music.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

class MusicDummy
{
public:
	virtual ~MusicDummy(void) = default;

	virtual void start(hob::Song song)		   = 0;
	virtual void stop(void)					   = 0;
	virtual void pause(void)				   = 0;
	virtual void resume(void)				   = 0;
	virtual void setVolume(hob::Volume volume) = 0;
};

class MusicMock : public MusicDummy
{
public:
	MusicMock(void)
	{
		musicMock = this;
	}

	virtual ~MusicMock(void)
	{
		musicMock = nullptr;
	}

	MOCK_METHOD1(start, void(hob::Song));
	MOCK_METHOD0(stop, void(void));
	MOCK_METHOD0(pause, void(void));
	MOCK_METHOD0(resume, void(void));
	MOCK_METHOD1(setVolume, void(hob::Volume));

public:
	static MusicMock* musicMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

MusicMock* MusicMock::musicMock = nullptr;

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

Music::Music(void) noexcept
{
}

Music::~Music(void) noexcept
{
}

void Music::start(const Song song) noexcept
{
	ASSERT_NE(nullptr, MusicMock::musicMock) << "start(): nullptr == MusicMock::musicMock";
	MusicMock::musicMock->start(song);
}

void Music::stop(void) noexcept
{
	ASSERT_NE(nullptr, MusicMock::musicMock) << "stop(): nullptr == MusicMock::musicMock";
	MusicMock::musicMock->stop();
}

void Music::pause(void) const noexcept
{
	ASSERT_NE(nullptr, MusicMock::musicMock) << "pause(): nullptr == MusicMock::musicMock";
	MusicMock::musicMock->pause();
}

void Music::resume(void) const noexcept
{
	ASSERT_NE(nullptr, MusicMock::musicMock) << "resume(): nullptr == MusicMock::musicMock";
	MusicMock::musicMock->resume();
}

void Music::setVolume(const Volume volume) noexcept
{
	ASSERT_NE(nullptr, MusicMock::musicMock) << "setVolume(): nullptr == MusicMock::musicMock";
	MusicMock::musicMock->setVolume(volume);
}

} /*< namespace hob */

#endif /*< HOB_MUSIC_MOCK_HPP_ */
