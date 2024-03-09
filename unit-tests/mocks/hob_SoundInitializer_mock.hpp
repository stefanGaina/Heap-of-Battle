/******************************************************************************************************
 * Heap of Battle Copyright (C) 2024
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the
 * authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
 *    original software. If you use this software in a product, an acknowledgment in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being
 *    the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *****************************************************************************************************/

#ifndef HOB_SOUND_INITIALIZER_MOCK_HPP_
#define HOB_SOUND_INITIALIZER_MOCK_HPP_

#ifdef HOB_SOUND_INITIALIZER_HPP_
#error "hob_SoundInitializer_mock.hpp is included after hob_SoundInitializer.hpp"
#else
#define HOB_SOUND_INITIALIZER_HPP_
#endif /*< HOB_SOUND_INITIALIZER_MOCK_HPP_ */

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <array>
#include <gmock/gmock.h>

#include "hob_IDrawable.hpp"
#include "hob_Sound_mock.hpp"
#include "hob_Component_mock.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

template<size_t SOUNDS_COUNT>
class SoundInitializer
{
public:
	SoundInitializer(std::array<std::string, SOUNDS_COUNT> filePaths) noexcept;
	virtual ~SoundInitializer(void) = default;

protected:
	std::array<Sound, SOUNDS_COUNT> soundContainer;
};

} /*< namespace hob */

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

template<size_t SOUNDS_COUNT>
SoundInitializer<SOUNDS_COUNT>::SoundInitializer(const std::array<std::string, SOUNDS_COUNT> filePaths) noexcept
{
}

} /*< namespace hob */

#endif /*< HOB_SOUND_INITIALIZER_MOCK_HPP_ */
