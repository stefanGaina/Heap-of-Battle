/******************************************************************************************************
 * @file hob_Sound.hpp                                                                                *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file defines the class and method prototypes of the sound.                           *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_SOUND_HPP_
#define HOB_SOUND_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <string>
#include <SDL_mixer.h>

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Enumerates the possible volumes.
 */
enum class Volume
{
	MUTED     = 0, /**< Muted volume.           */
	LOW       = 1, /**< Low level volume.       */
	MEDIUM    = 2, /**< Medium level volume.    */
	HIGH      = 3, /**< High level volume.      */
	VERY_HIGH = 4, /**< Very high level volume. */
	MAX       = 5  /**< Maximum level volume.   */
};

/**
 * @brief Sound wrapper.
*/
class Sound final
{
public:
	/**
	 * @brief Sets the volume at which all the sounds will be played.
	 * @param volume: Desired level.
	 * @return void
	*/
	static void setVolume(Volume volume) noexcept;

	/**
	 * @brief Default constructor not loading implicitly the sound.
	 * @param void
	*/
	Sound(void) noexcept;

	/**
	 * @brief Loads sound from a .wav file.
	 * @param filePath: Relative path to the .wav file.
	*/
	Sound(std::string filePath) noexcept;

	/**
	 * @brief Frees the loaded sound.
	 * @param void
	*/
	~Sound(void) noexcept;

	/**
	 * @brief Plays the loaded sound.
	 * @param void
	 * @return void
	*/
	void play(void) const noexcept;

	/**
	 * @brief Loads sound from a .wav file.
	 * @param filePath: Relative path to the .wav file.
	 * @return void
	*/
	void load(const std::string& filePath) noexcept;

	/**
	 * @brief Frees the loaded sound.
	 * @param void
	 * @return void
	*/
	void free(void) noexcept;

private:
	/**
	 * @brief The volume at which all the sounds are played.
	*/
	static int32_t s_volume;

	/**
	 * @brief Handle to SDL chunk object.
	*/
	Mix_Chunk* m_chunk;
};

} /*< namespace hob */

#endif /*< HOB_SOUND_HPP_ */
