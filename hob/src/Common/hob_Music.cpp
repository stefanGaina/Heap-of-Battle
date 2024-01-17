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
 * @file hob_Music.cpp                                                                                *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added const keywords.                                       *
 * 26.08.2023  Gaina Stefan               Improved logs.                                              *
 * 29.08.2023  Gaina Stefan               Added use of HOB_MUSIC_FILE_PATH.                           *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * 17.01.2024  Gaina Stefan               Added missing noexcept/const.                               *
 * @details This file implements the class defined in hob_Music.hpp.                                  *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Music.hpp"
#include "hob_Types.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Music::Music(void) noexcept
	: song       { nullptr }
	, playingSong{ Song::MAIN_MENU }
	, volume     { MIX_MAX_VOLUME }
{
	plog_trace("Music is being constructed.");
}

Music::~Music(void) noexcept
{
	plog_trace("Music is being destructed.");
	stop();
}

void Music::start(const Song song) noexcept
{
	int32_t errorCode = 0;

	plog_info("Music is being started. (song: %" PRId32 ")", static_cast<int32_t>(song));
	if (song == playingSong && nullptr != this->song)
	{
		plog_warn("Music is already started! (song: %" PRId32 ")", static_cast<int32_t>(song));
		return;
	}

	switch (song)
	{
		case Song::MAIN_MENU:
		{
			stop();
			this->song  = Mix_LoadMUS(HOB_MUSIC_FILE_PATH("main_menu_music"));
			playingSong = song;
			break;
		}
		case Song::SCENARIO_ALLIANCE:
		{
			stop();
			this->song  = Mix_LoadMUS(HOB_MUSIC_FILE_PATH("scenario_music_alliance"));
			playingSong = song;
			break;
		}
		case Song::SCENARIO_HORDE:
		{
			stop();
			this->song  = Mix_LoadMUS(HOB_MUSIC_FILE_PATH("scenario_music_horde"));
			playingSong = song;
			break;
		}
		default:
		{
			plog_error("Invalid music! (song: %" PRId32 ")", static_cast<int32_t>(song));
			return;
		}
	}

	errorCode = Mix_PlayMusic(this->song, -1);
	if (0 != errorCode)
	{
		plog_error("Failed to play music! (error code: %" PRId32 ")", errorCode);
	}

	(void)Mix_VolumeMusic(volume);
}

void Music::stop(void) noexcept
{
	plog_trace("Music is being stopped.");
	if (nullptr == song)
	{
		plog_warn("Music is not being played!");
		return;
	}
	Mix_FreeMusic(song);
	song = nullptr;
}

void Music::pause(void) const noexcept
{
	plog_info("Music is being paused.");
	if (nullptr == song)
	{
		plog_warn("Music is not being played!");
		return;
	}
	Mix_PauseMusic();
}

void Music::resume(void) const noexcept
{
	plog_info("Music is being resumed.");
	if (nullptr == song)
	{
		plog_warn("Music is not being played!");
		return;
	}
	Mix_ResumeMusic();
}

void Music::setVolume(const Volume volume) noexcept
{
	plog_debug("Setting music volume. (volume: %" PRId32 ")", static_cast<int32_t>(volume));
	switch (volume)
	{
		case Volume::MUTED:
		{
			this->volume = 0;
			break;
		}
		case Volume::LOW:
		{
			this->volume = MIX_MAX_VOLUME - 4 * MIX_MAX_VOLUME / 5;
			break;
		}
		case Volume::MEDIUM:
		{
			this->volume = MIX_MAX_VOLUME - 3 * MIX_MAX_VOLUME / 5;
			break;
		}
		case Volume::HIGH:
		{
			this->volume = MIX_MAX_VOLUME - 2 * MIX_MAX_VOLUME / 5;
			break;
		}
		case Volume::VERY_HIGH:
		{
			this->volume = MIX_MAX_VOLUME - 1 * MIX_MAX_VOLUME / 5;
			break;
		}
		case Volume::MAX:
		{
			this->volume = MIX_MAX_VOLUME;
			break;
		}
		default:
		{
			plog_error("Invalid volume! (volume: %" PRId32 ")", static_cast<int32_t>(volume));
			return;
		}
	}
	plog_info("Music volume set! (volume: %" PRId32 ")", this->volume);
	Mix_VolumeMusic(this->volume);
}

} /*< namespace hob */
