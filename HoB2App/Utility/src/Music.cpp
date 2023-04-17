/** @file Music.cpp
 *  @brief Method implementation for the music.
 *
 *  @author Gaina Stefan!
 *  @bug No known bugs.
 */

/***********************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                *
 **********************************************************************************************************************/

#include <plog.h>

#include "Music.hpp"

/***********************************************************************************************************************
 * MACROS                                                                                                              *
 **********************************************************************************************************************/

/**
 * @brief Path to the song played in main menu.
*/
constexpr const char* SONG_PATH_MAIN_MENU = "assets/sounds/main_menu_music.mp3";

/***********************************************************************************************************************
 * METHOD DEFINITIONS                                                                                                  *
 **********************************************************************************************************************/

namespace Utility
{

Music& Music::getInstance(void) noexcept
{
	static Music musicInstance;

	plog_verbose("Music instance is being got.");

	return musicInstance;
}

Music::Music(void) noexcept
	: m_song       { nullptr }
	, m_playingSong{ Song::MAIN_MENU }
	, m_volume     { MIX_MAX_VOLUME }
{
	plog_trace("Music is being constructed.");
}

Music::~Music(void) noexcept
{
	plog_trace("Music is being destructed.");
	stop();
}

void Music::start(Song song)
{
	plog_info("Music is being started. (song: %" PRId32 ")", static_cast<int32_t>(song));
	if (song == m_playingSong && nullptr != m_song)
	{
		plog_warn("Music is already started! (song: %" PRId32 ")", static_cast<int32_t>(song));
		return;
	}

	switch (song)
	{
		case Song::MAIN_MENU:
		{
			stop();
			m_song        = Mix_LoadMUS(SONG_PATH_MAIN_MENU);
			m_playingSong = song;
			break;
		}
		default:
		{
			plog_error("Invalid music! (song: %" PRId32 ")", static_cast<int32_t>(song));
			return;
		}
	}
	Mix_PlayMusic(m_song, -1L);
	Mix_VolumeMusic(m_volume);
}

void Music::stop(void)
{
	plog_trace("Music is being stopped.");
	if (nullptr == m_song)
	{
		plog_warn("Music is not being played!");
		return;
	}
	Mix_FreeMusic(m_song);
	m_song = nullptr;
}

void Music::pause(void)
{
	plog_info("Music is being paused.");
	if (nullptr == m_song)
	{
		plog_warn("Music is not being played!");
		return;
	}
	Mix_PauseMusic();
}

void Music::resume(void)
{
	plog_info("Music is being resumed.");
	if (nullptr == m_song)
	{
		plog_warn("Music is not being played!");
		return;
	}
	Mix_ResumeMusic();
}

void Music::setVolume(Volume volume)
{
	plog_debug("Setting music volume. (volume: %" PRId32 ")", static_cast<int32_t>(volume));
	switch (volume)
	{
		case Volume::MUTED:
		{
			m_volume = 0L;
			break;
		}
		case Volume::LOW:
		{
			m_volume = MIX_MAX_VOLUME - 4L * MIX_MAX_VOLUME / 5L;
			break;
		}
		case Volume::MEDIUM:
		{
			m_volume = MIX_MAX_VOLUME - 3L * MIX_MAX_VOLUME / 5L;
			break;
		}
		case Volume::HIGH:
		{
			m_volume = MIX_MAX_VOLUME - 2L * MIX_MAX_VOLUME / 5L;
			break;
		}
		case Volume::VERY_HIGH:
		{
			m_volume = MIX_MAX_VOLUME - 1L * MIX_MAX_VOLUME / 5L;
			break;
		}
		case Volume::MAX:
		{
			m_volume = MIX_MAX_VOLUME;
			break;
		}
		default:
		{
			plog_error("Invalid volume! (volume: %" PRId32 ")", static_cast<int32_t>(volume));
			return;
		}
	}
	plog_info("Music volume set! (volume: %" PRId32 ")", m_volume);
	Mix_VolumeMusic(m_volume);
}

} /*< namespace Utility */
