/******************************************************************************************************
 * @file hob_FramesPerSecond.cpp                                                                      *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
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
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

FramesPerSecond::FramesPerSecond(void) noexcept
	: m_FrameStartTime     { SDL_GetTicks64() }
	, m_framesCount        { 0U }
	, m_previousFramesCount{ 10000U }
	, m_texture            {}
	, m_component          {}
	, m_font               { NULL }
{
	plog_trace("Frames per second is being constructed.");

	m_font = TTF_OpenFont("assets/textures/miscellaneous/Anonymous.ttf", 12L);
	if (NULL == m_font)
	{
		plog_error("Font failed to be opened! (TTF error message: %s)", TTF_GetError());
	}
	update(m_framesCount);
}

FramesPerSecond::~FramesPerSecond(void) noexcept
{
	plog_trace("Frames per second is being destructed.");
	TTF_CloseFont(m_font);
}

void FramesPerSecond::draw(void) noexcept
{
	static constexpr const uint64_t SECOND_IN_MILLISECONDS = 1000ULL;

	uint64_t frameEndTime = SDL_GetTicks64();

	plog_verbose("Frames per second is being drawn. (start time: %" PRIu64 ") (end time: %" PRIu64 ")", m_FrameStartTime, frameEndTime);
	if (SECOND_IN_MILLISECONDS <= frameEndTime - m_FrameStartTime)
	{
		update(m_framesCount);
		m_FrameStartTime = frameEndTime;
		m_framesCount    = 0U;
	}
	else
	{
		++m_framesCount;
	}
	m_component.draw();
}

void FramesPerSecond::update(uint16_t framesPerSecond) noexcept
{
	static constexpr const SDL_Color YELLOW = { 0xFF, 0xFF, 0x00, 0xFF };

	Coordinate  textureDimension = {};
	std::string text             = std::to_string(framesPerSecond) + " FPS";

	plog_verbose("Frames per second is being updated. (frames: %" PRIu16 ")", framesPerSecond);
	if (framesPerSecond == m_previousFramesCount)
	{
		return;
	}
	m_previousFramesCount = framesPerSecond;

	m_texture.destroy();
	textureDimension = m_texture.create(text, m_font, YELLOW);

	m_component.updateTexture(m_texture.getRawTexture());
	m_component.updatePosition({ 15L * SCALE + SCALE / 4L, 0L, textureDimension.x, textureDimension.y });
}

} /*< namespace hob */
