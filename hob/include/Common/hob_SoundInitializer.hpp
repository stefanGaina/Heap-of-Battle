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
 * @file hob_SoundInitializer.hpp                                                                     *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added const keyword.                                        *
 * 26.08.2023  Gaina Stefan               Improved logs.                                              *
 * 27.08.2023  Gaina Stefan               Fixed comment.                                              *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
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
	std::array<Sound, SOUNDS_COUNT> soundContainer;
};

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

template<size_t SOUNDS_COUNT>
SoundInitializer<SOUNDS_COUNT>::SoundInitializer(const std::array<std::string, SOUNDS_COUNT> filePaths) noexcept
{
	size_t index = 0UL;

	plog_trace("SoundInitializer is being constructed.");
	for (; index < SOUNDS_COUNT; ++index)
	{
		soundContainer[index].load(filePaths[index]);
	}
}

} /*< namespace hob */

#endif /*< HOB_SOUND_INITIALIZER_HPP_ */
