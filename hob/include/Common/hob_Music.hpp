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
 * @file hob_Music.hpp                                                                                *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 29.08.2023  Gaina Stefan               Made an aesthetic change.                                   *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file defines the class and method prototypes of the music.                           *
 * @todo N/A.                                                                                         *
 * @bug Mix_Quit() is called in game's deinit method and music's destructor is called after so stop   *
 * needs to be called at the end of the scene manually.                                               *
 *****************************************************************************************************/

#ifndef HOB_MUSIC_HPP_
#define HOB_MUSIC_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_Sound.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Enumerates the songs that can be played.
*/
enum class Song
{
	MAIN_MENU         = 0, /**< Song associated to the main menu.                */
	SCENARIO_ALLIANCE = 1, /**< Song that is associated to the alliance faction. */
	SCENARIO_HORDE    = 2  /**< Song that is associated to the horde faction.    */
};

/**
 * @brief Music wrapper.
*/
class Music final
{
public:
	/**
	 * @brief Does not play a song implicitly.
	 * @param void
	*/
	Music(void) noexcept;

	/**
	 * @brief Frees the song that is playing.
	 * @param void
	*/
	~Music(void) noexcept;

	/**
	 * @brief Starts a song. Requesting to start the same song again will not replay it.
	 * @param song: Song to be started.
	 * @return void
	*/
	void start(Song song);

	/**
	 * @brief Stops the playing song and frees it.
	 * @param void
	 * @return void
	*/
	void stop(void);

	/**
	 * @brief Pauses the playing song.
	 * @param void
	 * @return void
	*/
	void pause(void);

	/**
	 * @brief Resumes the paused song.
	 * @param void
	 * @return void
	*/
	void resume(void);

	/**
	 * @brief Sets the volume at which all the songs will be played.
	 * @param volume: Desired level.
	 * @return void
	*/
	void setVolume(Volume volume);

private:
	/**
	 * @brief Handle to SDL music object.
	*/
	Mix_Music* song;

	/**
	 * @brief What song is currently playing.
	*/
	Song playingSong;

	/**
	 * @brief The volume at which all the songs are played.
	*/
	int32_t volume;
};

} /*< namespace hob */

#endif /*< HOB_MUSIC_HPP_ */
