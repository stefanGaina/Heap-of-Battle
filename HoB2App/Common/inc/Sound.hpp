/** @file Sound.hpp
 *  @brief Class definition and method prototypes of the sound.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

#ifndef SOUND_HPP_
#define SOUND_HPP_

/****************************************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                                 *
 ***************************************************************************************************************************************/

#include <string>
#include <SDL_mixer.h>

#include "Types.hpp"

/****************************************************************************************************************************************
 * TYPE DEFINITIONS                                                                                                                     *
 ***************************************************************************************************************************************/

namespace Common
{

/**
 * @brief Sound wrapper.
*/
class Sound final
{
public:
	/**
	 * @brief TODO
	*/
	using Chunk = Mix_Chunk*;

	/**
	 * @brief Default constructor not loading implicitly the sound.
	 * @param void
	*/
	Sound(void) noexcept;

	/**
	 * @brief Loads sound from a .wav file.
	 * @param filePath: relative path to the .wav file.
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
	 * @param filePath: relative path to the .wav file.
	 * @return void
	*/
	void load(const std::string& filePath) noexcept;

	/**
	 * @brief Frees the loaded sound.
	 * @param void
	 * @return void
	*/
	void free(void) noexcept;

	/**
	 * @brief Sets the volume at which all the sounds will be played.
	 * @param volume: desired level.
	 * @return void
	*/
	static void setVolume(Volume volume) noexcept;

private:
	/**
	 * @brief Handle to SDL chunk object.
	*/
	Chunk m_chunk;

	/**
	 * @brief The volume at which all the sounds are played.
	*/
	static int32_t s_volume;
}; /*< class Sound */

} /*< namespace Common */

#endif /*< SOUND_HPP_ */
