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
 * @file hob_FramesPerSecond.cpp                                                                      *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added const keywords.                                       *
 * 26.08.2023  Gaina Stefan               Improved logs.                                              *
 * 29.08.2023  Gaina Stefan               Removed the use of getRawTexture().                         *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * 17.01.2024  Gaina Stefan               Made font const.                                            *
 * 19.01.2024  Gaina Stefan               Changed update().                                           *
 * @details This file implements the class defined in hob_FramesPerSecond.hpp.                        *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <string>
#include <plog.h>

#include "hob_FramesPerSecond.hpp"

/******************************************************************************************************
 * CONSTANTS                                                                                          *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief How many milliseconds are in a second.
*/
static constexpr const uint64_t SECOND_IN_MILLISECONDS = 1000UL;

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

FramesPerSecond::FramesPerSecond(SDL_Renderer* const renderer) noexcept
	: component          {}
	, texture            {}
	, font               { TTF_OpenFont("assets/textures/miscellaneous/Anonymous.ttf", 12) }
	, frameStartTime     { SDL_GetTicks64() - SECOND_IN_MILLISECONDS }
	, framesCount        { 0U }
	, previousFramesCount{ 10000U }
{
	plog_trace("Frames per second is being constructed.");

	if (nullptr == font)
	{
		plog_error("Font failed to be opened! (TTF error message: %s)", TTF_GetError());
	}
	update(renderer);
}

FramesPerSecond::~FramesPerSecond(void) noexcept
{
	plog_trace("Frames per second is being destructed.");
	// TTF_CloseFont(font); <- this has been removed on purpose.
}

void FramesPerSecond::draw(SDL_Renderer* const renderer) noexcept
{
	plog_verbose("Frames per second is being drawn.");

	update(renderer);
	component.draw(renderer);
}

void FramesPerSecond::update(SDL_Renderer* const renderer) noexcept
{
	static constexpr const SDL_Color YELLOW = { 0xFFU, 0xFFU, 0x00U, 0xFFU };

	const uint64_t frameEndTime     = SDL_GetTicks64();
	std::string    text             = {};
	Coordinate     textureDimension = {};

	plog_verbose("Frames per second is being updated.(start time: %" PRIu64 ") (end time: %" PRIu64 ")", frameStartTime, frameEndTime);
	if (SECOND_IN_MILLISECONDS > frameEndTime - frameStartTime)
	{
		++framesCount;
		return;
	}

	plog_verbose("A second has been reached. (frames: %" PRIu16 ")", framesCount);
	if (framesCount == previousFramesCount)
	{
		plog_verbose("Frames per second does not need to be changed.");
		return;
	}

	try
	{
		text = std::to_string(framesCount) + " FPS";
	}
	catch (const std::bad_alloc& exception)
	{
		plog_error("Failed to allocate memory for frames per second string!");

		frameStartTime = frameEndTime;
		framesCount    = 0U;

		return;
	}
	previousFramesCount = framesCount;

	texture.destroy();
	textureDimension = texture.create(text, font, YELLOW, renderer);

	component.updateTexture(texture);
	component.updatePosition({.x = 30 * HSCALE + HSCALE / 2, .y = 0, .w = textureDimension.x, .h = textureDimension.y });

	frameStartTime = frameEndTime;
	framesCount    = 0U;
}

} /*< namespace hob */
