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

/******************************************************************************************************
 * @file hob_Sound.cpp                                                                                *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added const keywords.                                       *
 * 26.08.2023  Gaina Stefan               Improved logs.                                              *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file implements the class defined in hob_Sound.hpp.                                  *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Sound.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

int32_t Sound::volume = MIX_MAX_VOLUME;

Sound::Sound(void) noexcept
	: chunk{ nullptr }
{
	plog_trace("Sound is being default constructed.");
}

Sound::Sound(const std::string filePath) noexcept
	: chunk{ nullptr }
{
	plog_trace("Sound is being constructed.");
	load(filePath);
}

Sound::~Sound(void) noexcept
{
	plog_trace("Sound is being destructed.");
	free();
}

void Sound::load(const std::string& filePath) noexcept
{
	plog_trace("Sound is being loaded. (file path: %s)", filePath.c_str());

	chunk = Mix_LoadWAV(filePath.c_str());
	if (nullptr == chunk)
	{
		plog_error("Failed to load .wav! (file path: %s)", filePath.c_str());
	}
}

void Sound::free(void) noexcept
{
	plog_trace("Sound is being freed.");
	if (nullptr == chunk)
	{
		plog_warn("Sound was already destroyed!");
		return;
	}

	Mix_FreeChunk(chunk);
	chunk = nullptr;
}

void Sound::play(void) const noexcept
{
	int32_t channel = 0;

	plog_trace("Sound is being played.");
	if (nullptr == chunk)
	{
		plog_error("Invalid chunk!");
		return;
	}

	channel = Mix_PlayChannel(-1, chunk, 0);
	Mix_Volume(channel, volume);
}

void Sound::setVolume(const Volume volume) noexcept
{
	plog_trace("Setting sound volume. (volume: %" PRId32 ")", static_cast<int32_t>(volume));
	switch (volume)
	{
		case Volume::MUTED:
		{
			Sound::volume = 0;
			break;
		}
		case Volume::LOW:
		{
			Sound::volume = MIX_MAX_VOLUME - 4 * MIX_MAX_VOLUME / 5;
			break;
		}
		case Volume::MEDIUM:
		{
			Sound::volume = MIX_MAX_VOLUME - 3 * MIX_MAX_VOLUME / 5;
			break;
		}
		case Volume::HIGH:
		{
			Sound::volume = MIX_MAX_VOLUME - 2 * MIX_MAX_VOLUME / 5;
			break;
		}
		case Volume::VERY_HIGH:
		{
			Sound::volume = MIX_MAX_VOLUME - 1 * MIX_MAX_VOLUME / 5;
			break;
		}
		case Volume::MAX:
		{
			Sound::volume = MIX_MAX_VOLUME;
			break;
		}
		default:
		{
			plog_error("Invalid volume! (volume: %" PRId32 ")", static_cast<int32_t>(volume));
			return;
		}
	}
	plog_info("Sound volume set! (volume: %" PRId32 ")", Sound::volume);
}

} /*< namespace hob */
