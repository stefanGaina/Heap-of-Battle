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
 * @file hob_FramesPerSecond.hpp                                                                      *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 26.08.2023  Gaina Stefan               Change order of members.                                    *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * 16.01.2024  Gaina Stefan               Added const to font.                                        *
 * 19.01.2024  Gaina Stefan               Changed update().                                           *
 * @details This file defines the class and method prototypes of the frames per second.               *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_FRAMES_PER_SECOND_HPP_
#define HOB_FRAMES_PER_SECOND_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_IDrawable.hpp"
#include "hob_Texture.hpp"
#include "hob_Component.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Displays the FPS (frames per second).
*/
class FramesPerSecond final : public IDrawable
{
public:
	/**
	 * @brief Loads font and initializes frames to 0 until a second has passed.
	 * @param renderer: Rendering context of the window.
	*/
	FramesPerSecond(SDL_Renderer* renderer) noexcept;

	/**
	 * @brief Destroys the textures and closes the font.
	 * @param void
	*/
	~FramesPerSecond(void) noexcept;

	/**
	 * @brief Draws in top right corner in yellow "x FPS".
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	void draw(SDL_Renderer* renderer) noexcept override;

private:
	/**
	 * @brief If the frame rate changed destroy the texture and create a new updated one.
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	void update(SDL_Renderer* renderer) noexcept;

	/**
	 * @brief Resets the frame count and the frame start time.
	 * @param frameEndTime: Time when the last counted frame ended.
	 * @return void
	*/
	void reset(const uint64_t frameEndTime) noexcept;

private:
	/**
	 * @brief The component of the text display in top right corner.
	*/
	Component		component;

	/**
	 * @brief The texture of the displayed text.
	*/
	Texture			texture;

	/**
	 * @brief The font of the text written in the texture.
	*/
	TTF_Font* const font;

	/**
	 * @brief The time when the first counted frame started.
	*/
	uint64_t		frameStartTime;

	/**
	 * @brief How many frames were counted in a second.
	*/
	uint16_t		framesCount;

	/**
	 * @brief The previous frames count to not recreate the same texture.
	*/
	uint16_t		previousFramesCount;
};

} /*< namespace hob */

#endif /*< HOB_FRAMES_PER_SECOND_HPP_ */
