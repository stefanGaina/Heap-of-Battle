/******************************************************************************************************
 * @file hob_Grid1.cpp                                                                                *
 * @date:      @author:                   Reason for change:                                          *
 * 27.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file implements the class defined in hob_Grid1.hpp.                                  *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Grid1.hpp"
#include "hob_Faction.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

void Grid1::draw(void) noexcept
{
	static constexpr const uint8_t ALPHA_OPAQUE = 0xA0U;

	SDL_Renderer* const renderer  = Renderer::getInstance().get();
	SDL_Color           color     = {};
	int32_t             errorCode = 0L;

	plog_verbose("Grid1 is being drawn.");

	errorCode = SDL_SetRenderDrawColor(renderer, 0x00U, 0x00U, 0x00U, ALPHA_OPAQUE); /*< Black. */
	if (0L != errorCode)
	{
		plog_error("Failed to set renderer draw color to black! (error code: %" PRId32 ") (SDL error message: %s)", errorCode, SDL_GetError());
	}
	drawHorizontalNeutralLines();
	drawVerticalNeutralLines();

	color     = Faction::getInstance().getAllianceColor();
	errorCode = SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, ALPHA_OPAQUE);
	if (0L != errorCode)
	{
		plog_error("Failed to set renderer draw color to alliance! (error code: %" PRId32 ") (SDL error message: %s)", errorCode, SDL_GetError());
	}
	drawHorizontalAllianceLines();
	drawVerticalAllianceLines();

	color     = Faction::getInstance().getHordeColor();
	errorCode = SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, ALPHA_OPAQUE);
	if (0L != errorCode)
	{
		plog_error("Failed to set renderer draw color to horde! (error code: %" PRId32 ") (SDL error message: %s)", errorCode, SDL_GetError());
	}
	drawHorizontalHordeLines();
	drawVerticalHordeLines();

	errorCode = SDL_SetRenderDrawColor(renderer, 0xFFU, 0xFFU, 0xFFU, ALPHA_OPAQUE); /*< White. */
	if (0L != errorCode)
	{
		plog_error("Failed to set renderer draw color to white! (error code: %" PRId32 ") (SDL error message: %s)", errorCode, SDL_GetError());
	}
	drawHorizontalObjectiveLines();
	drawVerticalObjectiveLines();

	errorCode = SDL_SetRenderDrawColor(renderer, 0xFFU, 0xFFU, 0xFFU, 0xFFU); /*< White. */
	if (0L != errorCode)
	{
		plog_error("Failed to set renderer draw color to default! (error code: %" PRId32 ") (SDL error message: %s)", errorCode, SDL_GetError());
	}
}

void Grid1::drawHorizontalNeutralLines(void) const noexcept
{
	SDL_Renderer* const renderer = Renderer::getInstance().get();
	int32_t             row      = 0L * HSCALE;
	int32_t             modifier = 0L * HSCALE;

	plog_verbose("Horizontal neutral lines are being drawn.");
	for (modifier = 1L * HSCALE, row = 0L; modifier > -2L * HSCALE; modifier -= 2L * HSCALE, row = 15L * HSCALE)
	{
		(void)SDL_RenderDrawLine(renderer, 11L * HSCALE, row, 13L * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 16L * HSCALE, row, 22L * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 25L * HSCALE, row, 29L * HSCALE, row);

		row += modifier;
		(void)SDL_RenderDrawLine(renderer, 11L * HSCALE, row, 13L * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 25L * HSCALE, row, 29L * HSCALE, row);

		row += modifier;
		(void)SDL_RenderDrawLine(renderer, 10L * HSCALE, row, 11L * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 13L * HSCALE, row, 14L * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 24L * HSCALE, row, 25L * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 27L * HSCALE, row, 29L * HSCALE, row);

		row += modifier;
		(void)SDL_RenderDrawLine(renderer, 14L * HSCALE, row, 24L * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 28L * HSCALE, row, 29L * HSCALE, row);

		row += modifier;
		(void)SDL_RenderDrawLine(renderer, 14L * HSCALE, row, 24L * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 28L * HSCALE, row, 30L * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 31L * HSCALE, row, 32L * HSCALE, row);

		row += modifier;
		(void)SDL_RenderDrawLine(renderer, 6L  * HSCALE, row, 10L * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 14L * HSCALE, row, 24L * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 28L * HSCALE, row, 32L * HSCALE, row);

		row += modifier;
		(void)SDL_RenderDrawLine(renderer, 9L  * HSCALE, row, 11L * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 27L * HSCALE, row, 29L * HSCALE, row);

		row += modifier;
		(void)SDL_RenderDrawLine(renderer, 10L * HSCALE, row, 12L * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 26L * HSCALE, row, 28L * HSCALE, row);
	}
}

void Grid1::drawVerticalNeutralLines(void) const noexcept
{
	SDL_Renderer* const renderer = Renderer::getInstance().get();
	int32_t             column   = 0L * HSCALE;
	int32_t             modifier = 0L * HSCALE;

	plog_verbose("Vertical neutral lines are being drawn.");
	for (modifier = 1L * HSCALE, column = 6L * HSCALE; modifier > -2L * HSCALE; modifier -= 2L * HSCALE, column = 32L * HSCALE)
	{
		(void)SDL_RenderDrawLine(renderer, column, 4L * HSCALE, column, 6L  * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 9L * HSCALE, column, 11L * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 4L * HSCALE, column, 6L  * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 9L * HSCALE, column, 11L * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 4L * HSCALE, column, 6L  * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 9L * HSCALE, column, 11L * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 4L * HSCALE, column, 6L  * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 9L * HSCALE, column, 11L * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 5L * HSCALE, column, 7L  * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 8L * HSCALE, column, 10L * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 1L  * HSCALE, column, 2L  * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 6L  * HSCALE, column, 9L  * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 13L * HSCALE, column, 14L * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 0L  * HSCALE, column, 2L  * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 6L  * HSCALE, column, 7L  * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 8L  * HSCALE, column, 9L  * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 13L * HSCALE, column, 15L * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 1L  * HSCALE, column, 2L  * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 13L * HSCALE, column, 14L * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 2L  * HSCALE, column, 3L  * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 5L  * HSCALE, column, 6L  * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 9L  * HSCALE, column, 10L * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 12L * HSCALE, column, 13L * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 2L * HSCALE, column, 6L  * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 9L * HSCALE, column, 13L * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 2L * HSCALE, column, 6L  * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 9L * HSCALE, column, 13L * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 3L  * HSCALE, column, 5L  * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 10L * HSCALE, column, 12L * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 3L  * HSCALE, column, 5L  * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 10L * HSCALE, column, 12L * HSCALE);
	}

	column -= 3L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 3L  * HSCALE, column, 4L  * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 11L * HSCALE, column, 12L * HSCALE);

	column -= 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0L  * HSCALE, column, 3L  * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 12L * HSCALE, column, 15L * HSCALE);

	column -= 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0L  * HSCALE, column, 2L  * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 13L * HSCALE, column, 15L * HSCALE);

	column -= 8 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 3L  * HSCALE, column, 5L  * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 10L * HSCALE, column, 12L * HSCALE);
}

void Grid1::drawHorizontalAllianceLines(void) const noexcept
{
	SDL_Renderer* const renderer = Renderer::getInstance().get();
	int32_t             row      = 0L * HSCALE;

	plog_verbose("Horizontal alliance lines are being drawn.");

	row = 9L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 11L * HSCALE, row, 13L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 25L * HSCALE, row, 27L * HSCALE, row);

	row += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 10L * HSCALE, row, 14L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 24L * HSCALE, row, 28L * HSCALE, row);

	row += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 6L  * HSCALE, row, 11L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 13L * HSCALE, row, 14L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 24L * HSCALE, row, 25L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 27L * HSCALE, row, 28L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 30L * HSCALE, row, 31L * HSCALE, row);

	row += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 10L * HSCALE, row, 14L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 24L * HSCALE, row, 28L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 29L * HSCALE, row, 32L * HSCALE, row);

	row += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 11L * HSCALE, row, 13L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 14L * HSCALE, row, 16L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 22L * HSCALE, row, 24L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 25L * HSCALE, row, 27L * HSCALE, row);

	row += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 10L * HSCALE, row, 11L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 13L * HSCALE, row, 14L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 24L * HSCALE, row, 25L * HSCALE, row);

	row += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 6L  * HSCALE, row, 11L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 13L * HSCALE, row, 16L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 22L * HSCALE, row, 25L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 29L * HSCALE, row, 32L * HSCALE, row);
}

void Grid1::drawVerticalAllianceLines(void) const noexcept
{
	SDL_Renderer* const renderer = Renderer::getInstance().get();
	int32_t             column   = 0L * HSCALE;

	plog_verbose("Vertical alliance lines are being drawn.");

	column = 6L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 11L * HSCALE, column, 15L * HSCALE);

	column += 4L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 10L * HSCALE, column, 15L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 9L * HSCALE, column, 13L * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 14L * HSCALE, column, 15L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 9L * HSCALE, column, 10L * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 12L * HSCALE, column, 13L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 9L * HSCALE, column, 13L * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 14L * HSCALE, column, 15L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 10L * HSCALE, column, 12L * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 13L * HSCALE, column, 15L * HSCALE);

	column += 2L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 13L * HSCALE, column, 15L * HSCALE);

	column += 6L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 13L * HSCALE, column, 15L * HSCALE);

	column += 2L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 10L * HSCALE, column, 12L * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 13L * HSCALE, column, 15L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 9L * HSCALE, column, 13L * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 14L * HSCALE, column, 15L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 9L * HSCALE, column, 10L * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 12L * HSCALE, column, 13L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 9L * HSCALE, column, 13L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 10L * HSCALE, column, 12L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 12L * HSCALE, column, 15L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 11L * HSCALE, column, 12L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 11L * HSCALE, column, 12L * HSCALE);
}

void Grid1::drawHorizontalHordeLines(void) const noexcept
{
	SDL_Renderer* const renderer = Renderer::getInstance().get();
	int32_t             row      = 0L * HSCALE;

	plog_verbose("Horizontal horde lines are being drawn.");

	row = 6L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 11L * HSCALE, row, 13L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 25L * HSCALE, row, 27L * HSCALE, row);

	row -= 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 10L * HSCALE, row, 14L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 24L * HSCALE, row, 28L * HSCALE, row);

	row -= 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 6L  * HSCALE, row, 11L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 13L * HSCALE, row, 14L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 24L * HSCALE, row, 25L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 27L * HSCALE, row, 28L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 30L * HSCALE, row, 31L * HSCALE, row);

	row -= 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 10L * HSCALE, row, 14L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 24L * HSCALE, row, 28L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 29L * HSCALE, row, 32L * HSCALE, row);

	row -= 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 11L * HSCALE, row, 13L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 14L * HSCALE, row, 16L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 22L * HSCALE, row, 24L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 25L * HSCALE, row, 27L * HSCALE, row);

	row -= 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 10L * HSCALE, row, 11L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 13L * HSCALE, row, 14L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 24L * HSCALE, row, 25L * HSCALE, row);

	row -= 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 6L  * HSCALE, row, 11L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 13L * HSCALE, row, 16L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 22L * HSCALE, row, 25L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 29L * HSCALE, row, 32L * HSCALE, row);
}

void Grid1::drawVerticalHordeLines(void) const noexcept
{
	SDL_Renderer* const renderer = Renderer::getInstance().get();
	int32_t             column   = 0L * HSCALE;

	plog_verbose("Vertical horde lines are being drawn.");

	column = 6L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0L * HSCALE, column, 4L * HSCALE);

	column += 4L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0L * HSCALE, column, 5L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0L * HSCALE, column, 1L * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 2L * HSCALE, column, 6L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 2L * HSCALE, column, 3L * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 5L * HSCALE, column, 6L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0L * HSCALE, column, 1L * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 2L * HSCALE, column, 6L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0L * HSCALE, column, 2L * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 3L * HSCALE, column, 5L * HSCALE);

	column += 2L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0L * HSCALE, column, 2L * HSCALE);

	column += 6L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0L * HSCALE, column, 2L * HSCALE);

	column += 2L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0L * HSCALE, column, 2L * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 3L * HSCALE, column, 5L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0L * HSCALE, column, 1L * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 2L * HSCALE, column, 6L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 2L * HSCALE, column, 3L * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 5L * HSCALE, column, 6L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 2L * HSCALE, column, 6L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 3L * HSCALE, column, 5L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0L * HSCALE, column, 3L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 3L * HSCALE, column, 4L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 3L * HSCALE, column, 4L * HSCALE);
}

void Grid1::drawHorizontalObjectiveLines(void) const noexcept
{
	SDL_Renderer* const renderer = Renderer::getInstance().get();
	int32_t             row      = 0L * HSCALE;

	plog_verbose("Horizontal objective lines are being drawn.");

	row = 6L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 6L  * HSCALE, row, 9L  * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 13L * HSCALE, row, 16L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 22L * HSCALE, row, 25L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 29L * HSCALE, row, 32L * HSCALE, row);

	row += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 9L  * HSCALE, row, 10L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 12L * HSCALE, row, 13L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 25L * HSCALE, row, 26L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 28L * HSCALE, row, 29L * HSCALE, row);

	row += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 9L  * HSCALE, row, 10L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 12L * HSCALE, row, 13L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 25L * HSCALE, row, 26L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 28L * HSCALE, row, 29L * HSCALE, row);

	row += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 6L  * HSCALE, row, 9L  * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 13L * HSCALE, row, 16L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 22L * HSCALE, row, 25L * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 29L * HSCALE, row, 32L * HSCALE, row);
}

void Grid1::drawVerticalObjectiveLines(void) const noexcept
{
	SDL_Renderer* const renderer = Renderer::getInstance().get();
	int32_t             column   = 0L * HSCALE;

	plog_verbose("Vertical objective lines are being drawn.");

	column = 6L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 6L * HSCALE, column, 9L * HSCALE);

	column += 3L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 6L * HSCALE, column, 9L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 7L * HSCALE, column, 8L * HSCALE);

	column += 2L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 7L * HSCALE, column, 8L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 6L * HSCALE, column, 9L * HSCALE);

	column += 3L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 6L * HSCALE, column, 9L * HSCALE);

	column += 6L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 6L * HSCALE, column, 9L * HSCALE);

	column += 3L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 6L * HSCALE, column, 9L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 7L * HSCALE, column, 8L * HSCALE);

	column += 2L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 7L * HSCALE, column, 8L * HSCALE);

	column += 1L * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 6L * HSCALE, column, 9L * HSCALE);
}

} /*< namespace hob */
