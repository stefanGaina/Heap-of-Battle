/** @file SoundInitializes.hpp
 *  @brief Class definition, method prototypes and method implementations of the sound initializer.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

#ifndef SOUND_INITIALIZER_HPP_
#define SOUND_INITIALIZER_HPP_

/****************************************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                                 *
 ***************************************************************************************************************************************/

#include <string>
#include <array>
#include <plog.h>

#include "Sound.hpp"

/****************************************************************************************************************************************
 * TYPE DEFINITIONS                                                                                                                     *
 ***************************************************************************************************************************************/

namespace Common
{

/**
 * @brief Initializes a list of sounds.
*/
template<size_t SOUNDS_COUNT>
class SoundInitializer
{
public:
	/**
	 * @brief Loads sounds from specified paths.
	 * @param filePaths: relative paths to the .wav files.
	*/
	SoundInitializer(std::array<std::string, SOUNDS_COUNT> filePaths) noexcept;

	/**
	 * @brief Frees the loaded sounds.
	 * @param void
	*/
	virtual ~SoundInitializer(void) noexcept;

protected:
	/**
	 * @brief Holds all the sounds needed for the scene.
	*/
	std::array<Sound, SOUNDS_COUNT> m_soundContainer;

}; /*< class SoundInitializer */

/***********************************************************************************************************************
 * METHOD DEFINITIONS                                                                                                  *
 **********************************************************************************************************************/

template<size_t SOUNDS_COUNT>
SoundInitializer<SOUNDS_COUNT>::SoundInitializer(std::array<std::string, SOUNDS_COUNT> filePaths) noexcept
{
	size_t index = 0ULL;

	plog_trace("SoundInitializer is being constructed.");
	for (index = 0ULL; index < SOUNDS_COUNT; ++index)
	{
		m_soundContainer[index].load(filePaths[index]);
	}
}

template<size_t SOUNDS_COUNT>
SoundInitializer<SOUNDS_COUNT>::~SoundInitializer(void) noexcept
{
	plog_trace("SoundInitializer is being destructed.");
}

} /*< namespace Common */

#endif /*< SOUND_INITIALIZER_HPP_ */
