/******************************************************************************************************
 * @file hob_SoundInitializer.hpp                                                                     *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Add const keyword.                                          *
 * @details This file defines the class and method prototypes and method implementation of the sound  *
 * initializer.                                                                                       *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_SOUND_INITIALIZER_HPP_
#define HOB_SOUND_INITIALIZER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <array>
#include <plog.h>

#include "hob_Sound.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
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
	 * @param filePaths: Relative paths to the .wav files.
	*/
	SoundInitializer(std::array<std::string, SOUNDS_COUNT> filePaths) noexcept;

	/**
	 * @brief Frees the loaded sounds.
	 * @param void
	*/
	virtual ~SoundInitializer(void) = default;

protected:
	/**
	 * @brief Holds all the sounds needed for the scene.
	*/
	std::array<Sound, SOUNDS_COUNT> m_soundContainer;
};

/***********************************************************************************************************************
 * METHOD DEFINITIONS                                                                                                  *
 **********************************************************************************************************************/

template<size_t SOUNDS_COUNT>
SoundInitializer<SOUNDS_COUNT>::SoundInitializer(const std::array<std::string, SOUNDS_COUNT> filePaths) noexcept
{
	size_t index = 0ULL;

	plog_trace("SoundInitializer is being constructed.");
	for (index = 0ULL; index < SOUNDS_COUNT; ++index)
	{
		m_soundContainer[index].load(filePaths[index]);
	}
}

} /*< namespace hob */

#endif /*< HOB_SOUND_INITIALIZER_HPP_ */
