/** @file Music.hpp
 *  @brief Class definition and method prototypes of the music.
 *
 *  @author Gaina Stefan!
 *  @bug Mix_Quit() is called in window's destructor and music's destructor is called after so stop needs to be called
 * at the end of the program manually.
 */

#ifndef MUSIC_H_
#define MUSIC_H_

/****************************************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                                 *
 ***************************************************************************************************************************************/

#include <SDL_mixer.h>

#include "Types.hpp"

/****************************************************************************************************************************************
 * TYPE DEFINITIONS                                                                                                                     *
 ***************************************************************************************************************************************/

namespace Utility
{

/**
 * @brief Enumerates the songs that can be played.
*/
enum class Song
{
	MAIN_MENU = 0, /*< Song associated to the main menu. */
};

/**
 * @brief Music wrapper.
*/
class Music final
{
public:
	/**
	 * @brief Singleton way to get access to the music object.
	 * @param void
	 * @return Reference to the music instance.
	*/
	static Music& getInstance(void) noexcept;

	/**
	 * @brief Starts a song. Requesting to start the same song again will not replay it.
	 * @param song: song to be started.
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
	 * @param volume: desired level.
	 * @return void
	*/
	void setVolume(Volume volume);

	/**
	 * @brief Prevents the creation of another object.
	 * @param otherMusic: instance to be copied.
	*/
	Music(Music& otherMusic) = delete;

	/**
	 * @brief Prevents the creation of another object.
	 * @param music: instance to be copied.
	*/
	void operator=(const Music& music) = delete;

private:
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

private:
	/**
	 * @brief Handle to SDL music object.
	*/
	Mix_Music* m_song;

	/**
	 * @brief What song is currently playing.
	*/
	Song m_playingSong;

	/**
	 * @brief The volume at which all the songs are played.
	*/
	int32_t m_volume;
}; /*< class Music */

} /*< namespace Utility */

#endif /*< MUSIC_H_ */
