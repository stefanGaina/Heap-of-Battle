/******************************************************************************************************
 * @file hob_FramesPerSecond.hpp                                                                      *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
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
	 * @param void
	*/
	FramesPerSecond(void) noexcept;

	/**
	 * @brief Destroys the textures and closes the font.
	 * @param
	*/
	~FramesPerSecond(void) noexcept;

	/**
	 * @brief Draws in top right corner in yellow "x FPS".
	 * @param void
	 * @return void
	*/
	void draw(void) noexcept override;

private:
	/**
	 * @brief If the frame rate changed destroy the texture and create a new updated one.
	 * @param framesPerSecond:
	 * @return void
	*/
	void update(uint16_t framesPerSecond) noexcept;

private:
	/**
	 * @brief The time when the first counted frame started.
	*/
	uint64_t m_FrameStartTime;

	/**
	 * @brief How many frames were counted in a second.
	*/
	uint16_t m_framesCount;

	/**
	 * @brief The previous frames count to not recreate the same texture.
	*/
	uint16_t m_previousFramesCount;

	/**
	 * @brief The texture of the displayed text.
	*/
	Texture m_texture;

	/**
	 * @brief The component of the text display in top right corner.
	*/
	Component m_component;

	/**
	 * @brief The font of the text written in the texture.
	*/
	TTF_Font* m_font;
};

} /*< namespace hob */

#endif /*< HOB_FRAMES_PER_SECOND_HPP_ */
