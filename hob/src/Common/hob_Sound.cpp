/******************************************************************************************************
 * @file hob_Sound.cpp                                                                                *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
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

int32_t Sound::s_volume = MIX_MAX_VOLUME;

Sound::Sound(void) noexcept
	: m_chunk{ NULL }
{
	plog_trace("Sound is being default constructed.");
}

Sound::Sound(std::string filePath) noexcept
	: m_chunk{ NULL }
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

	m_chunk = Mix_LoadWAV(filePath.c_str());
	if (NULL == m_chunk)
	{
		plog_error("Failed to load .wav! (file path: %s)", filePath.c_str());
	}
}

void Sound::free(void) noexcept
{
	plog_trace("Sound is being freed.");
	if (NULL == m_chunk)
	{
		plog_warn("Sound was already destroyed!");
		return;
	}
	Mix_FreeChunk(m_chunk);
	m_chunk = NULL;
}

void Sound::play(void) const noexcept
{
	int32_t channel = 0L;

	plog_trace("Sound is being played.");
	if (NULL == m_chunk)
	{
		plog_error("Invalid chunk!");
		return;
	}

	channel = Mix_PlayChannel(-1L, m_chunk, 0L);
	Mix_Volume(channel, s_volume);
}

void Sound::setVolume(Volume volume) noexcept
{
	plog_trace("Setting sound volume. (volume: %" PRId32 ")", static_cast<int32_t>(volume));
	switch (volume)
	{
		case Volume::MUTED:
		{
			s_volume = 0L;
			break;
		}
		case Volume::LOW:
		{
			s_volume = MIX_MAX_VOLUME - 4L * MIX_MAX_VOLUME / 5L;
			break;
		}
		case Volume::MEDIUM:
		{
			s_volume = MIX_MAX_VOLUME - 3L * MIX_MAX_VOLUME / 5L;
			break;
		}
		case Volume::HIGH:
		{
			s_volume = MIX_MAX_VOLUME - 2L * MIX_MAX_VOLUME / 5L;
			break;
		}
		case Volume::VERY_HIGH:
		{
			s_volume = MIX_MAX_VOLUME - 1L * MIX_MAX_VOLUME / 5L;
			break;
		}
		case Volume::MAX:
		{
			s_volume = MIX_MAX_VOLUME;
			break;
		}
		default:
		{
			plog_error("Invalid volume! (volume: %" PRId32 ")", static_cast<int32_t>(volume));
			return;
		}
	}
	plog_info("Sound volume set! (volume: %" PRId32 ")", s_volume);
}

} /*< namespace hob */
