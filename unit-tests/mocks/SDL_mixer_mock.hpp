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
******************************************************************************************************/

#ifndef SDL_MIXER_MOCK_HPP_
#define SDL_MIXER_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <gmock/gmock.h>
#include <SDL2/SDL_mixer.h>

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

class Mix
{
public:
	virtual ~Mix(void) = default;

	virtual const SDL_version* Mix_Linked_Version(void) = 0;
	virtual int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize) = 0;
	virtual void Mix_Quit(void) = 0;
	virtual Mix_Chunk* Mix_LoadWAV_RW(SDL_RWops* src, int freesrc) = 0;
	virtual void Mix_FreeChunk(Mix_Chunk* chunk) = 0;
	virtual int Mix_PlayChannelTimed(int channel, Mix_Chunk* chunk, int loops, int ticks) = 0;
	virtual int Mix_Volume(int channel, int volume) = 0;
};

class MixMock : public Mix
{
public:
	MixMock(void)
	{
		mixMock = this;
	}

	virtual ~MixMock(void)
	{
		mixMock = nullptr;
	}

	MOCK_METHOD0(Mix_Linked_Version, const SDL_version*(void));
	MOCK_METHOD4(Mix_OpenAudio, int(int, Uint16, int, int));
	MOCK_METHOD0(Mix_Quit, void(void));
	MOCK_METHOD2(Mix_LoadWAV_RW, Mix_Chunk*(SDL_RWops*, int));
	MOCK_METHOD1(Mix_FreeChunk, void(Mix_Chunk*));
	MOCK_METHOD4(Mix_PlayChannelTimed, int(int, Mix_Chunk*, int, int));
	MOCK_METHOD2(Mix_Volume, int(int, int));

public:
	static MixMock* mixMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES                                                                                    *
 *****************************************************************************************************/

MixMock* MixMock::mixMock = nullptr;

/******************************************************************************************************
 * FUNCTION DEFINITIONS                                                                               *
 *****************************************************************************************************/

extern "C" {

const SDL_version* Mix_Linked_Version(void)
{
	if (nullptr == MixMock::mixMock)
	{
		ADD_FAILURE() << "Mix_Linked_Version(): nullptr == MixMock::mixMock";
		return nullptr;
	}
	return MixMock::mixMock->Mix_Linked_Version();
}

int Mix_OpenAudio(const int frequency, const Uint16 format, const int channels, const int chunksize)
{
	if (nullptr == MixMock::mixMock)
	{
		ADD_FAILURE() << "Mix_OpenAudio(): nullptr == MixMock::mixMock";
		return -1;
	}
	return MixMock::mixMock->Mix_OpenAudio(frequency, format, channels, chunksize);
}

void Mix_Quit(void)
{
	ASSERT_NE(nullptr, MixMock::mixMock) << "Mix_Quit(): nullptr == MixMock::mixMock";
	MixMock::mixMock->Mix_Quit();
}

Mix_Chunk* Mix_LoadWAV_RW(SDL_RWops* const src, const int freesrc)
{
	if (nullptr == MixMock::mixMock)
	{
		ADD_FAILURE() << "Mix_LoadWAV_RW(): nullptr == MixMock::mixMock";
		return nullptr;
	}
	return MixMock::mixMock->Mix_LoadWAV_RW(src, freesrc);
}

void Mix_FreeChunk(Mix_Chunk* const chunk)
{
	ASSERT_NE(nullptr, MixMock::mixMock) << "Mix_FreeChunk(): nullptr == MixMock::mixMock";
	MixMock::mixMock->Mix_FreeChunk(chunk);
}

int Mix_PlayChannelTimed(const int channel, Mix_Chunk* const chunk, const int loops, const int ticks)
{
	if (nullptr == MixMock::mixMock)
	{
		ADD_FAILURE() << "Mix_PlayChannelTimed(): nullptr == MixMock::mixMock";
		return -1;
	}
	return MixMock::mixMock->Mix_PlayChannelTimed(channel, chunk, loops, ticks);
}

int Mix_Volume(const int channel, const int volume)
{
	if (nullptr == MixMock::mixMock)
	{
		ADD_FAILURE() << "Mix_Volume(): nullptr == MixMock::mixMock";
		return -1;
	}
	return MixMock::mixMock->Mix_Volume(channel, volume);
}

}

#endif /*< SDL_MIXER_MOCK_HPP_ */
