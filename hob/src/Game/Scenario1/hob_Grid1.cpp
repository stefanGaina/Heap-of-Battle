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
 *****************************************************************************************************/

/******************************************************************************************************
 * @file hob_Grid1.cpp                                                                                *
 * @date:      @author:                   Reason for change:                                          *
 * 27.07.2023  Gaina Stefan               Initial version.                                            *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * 17.01.2024  Gaina Stefan               Moved lines to match new tower position.                    *
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

void Grid1::draw(SDL_Renderer* const renderer) noexcept
{
	static constexpr const uint8_t ALPHA_OPAQUE = 0xA0U;

	SDL_Color					   color		= { .r = 0, .g = 0, .b = 0, .a = 0 };

	plog_verbose("Grid1 is being drawn.");
	plog_assert(nullptr != renderer);

	if (0 != SDL_SetRenderDrawColor(renderer, 0x00U, 0x00U, 0x00U, ALPHA_OPAQUE)) /*< black */
	{
		plog_warn("Failed to set renderer draw color to black! (SDL error message: %s)", SDL_GetError());
	}
	drawHorizontalNeutralLines(renderer);
	drawVerticalNeutralLines(renderer);

	color = Faction::getAllianceColor();
	if (0 != SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, ALPHA_OPAQUE))
	{
		plog_warn("Failed to set renderer draw color to alliance! (SDL error message: %s)", SDL_GetError());
	}
	drawHorizontalAllianceLines(renderer);
	drawVerticalAllianceLines(renderer);

	color = Faction::getHordeColor();
	if (0 != SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, ALPHA_OPAQUE))
	{
		plog_warn("Failed to set renderer draw color to horde! (SDL error message: %s)", SDL_GetError());
	}
	drawHorizontalHordeLines(renderer);
	drawVerticalHordeLines(renderer);

	if (0 != SDL_SetRenderDrawColor(renderer, 0xFFU, 0xFFU, 0xFFU, ALPHA_OPAQUE)) /*< white */
	{
		plog_warn("Failed to set renderer draw color to white! (SDL error message: %s)", SDL_GetError());
	}
	drawHorizontalObjectiveLines(renderer);
	drawVerticalObjectiveLines(renderer);

	if (0 != SDL_SetRenderDrawColor(renderer, 0x00U, 0x00U, 0x00U, SDL_ALPHA_OPAQUE)) /*< black */
	{
		plog_warn("Failed to set renderer draw color to default! (SDL error message: %s)", SDL_GetError());
	}
}

void Grid1::drawHorizontalNeutralLines(SDL_Renderer* const renderer) const noexcept
{
	int32_t row		 = 0 * HSCALE;
	int32_t modifier = 0 * HSCALE;

	plog_verbose("Horizontal neutral lines are being drawn.");
	plog_assert(nullptr != renderer);

	for (modifier = 1 * HSCALE, row = 0; modifier > -2 * HSCALE; modifier -= 2 * HSCALE, row = 15 * HSCALE)
	{
		(void)SDL_RenderDrawLine(renderer, 11 * HSCALE, row, 13 * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 16 * HSCALE, row, 22 * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 25 * HSCALE, row, 29 * HSCALE, row);

		row += modifier;
		(void)SDL_RenderDrawLine(renderer, 11 * HSCALE, row, 13 * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 25 * HSCALE, row, 29 * HSCALE, row);

		row += modifier;
		(void)SDL_RenderDrawLine(renderer, 12 * HSCALE, row, 14 * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 24 * HSCALE, row, 26 * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 28 * HSCALE, row, 29 * HSCALE, row);

		row += modifier;
		(void)SDL_RenderDrawLine(renderer, 13 * HSCALE, row, 25 * HSCALE, row);

		row += modifier;
		(void)SDL_RenderDrawLine(renderer, 13 * HSCALE, row, 25 * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 29 * HSCALE, row, 30 * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 31 * HSCALE, row, 32 * HSCALE, row);

		row += modifier;
		(void)SDL_RenderDrawLine(renderer, 6 * HSCALE, row, 9 * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 13 * HSCALE, row, 25 * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 29 * HSCALE, row, 32 * HSCALE, row);

		row += modifier;
		(void)SDL_RenderDrawLine(renderer, 9 * HSCALE, row, 10 * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 12 * HSCALE, row, 13 * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 25 * HSCALE, row, 26 * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 28 * HSCALE, row, 29 * HSCALE, row);

		row += modifier;
		(void)SDL_RenderDrawLine(renderer, 10 * HSCALE, row, 12 * HSCALE, row);
		(void)SDL_RenderDrawLine(renderer, 26 * HSCALE, row, 28 * HSCALE, row);
	}
}

void Grid1::drawVerticalNeutralLines(SDL_Renderer* const renderer) const noexcept
{
	int32_t column	 = 0 * HSCALE;
	int32_t modifier = 0 * HSCALE;

	plog_verbose("Vertical neutral lines are being drawn.");
	plog_assert(nullptr != renderer);

	for (modifier = 1 * HSCALE, column = 6 * HSCALE; modifier > -2 * HSCALE; modifier -= 2 * HSCALE, column = 32 * HSCALE)
	{
		(void)SDL_RenderDrawLine(renderer, column, 4 * HSCALE, column, 6 * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 9 * HSCALE, column, 11 * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 4 * HSCALE, column, 6 * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 9 * HSCALE, column, 11 * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 4 * HSCALE, column, 6 * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 9 * HSCALE, column, 11 * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 5 * HSCALE, column, 6 * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 9 * HSCALE, column, 10 * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 6 * HSCALE, column, 7 * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 8 * HSCALE, column, 9 * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 1 * HSCALE, column, 2 * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 6 * HSCALE, column, 9 * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 13 * HSCALE, column, 14 * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 0 * HSCALE, column, 2 * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 6 * HSCALE, column, 7 * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 8 * HSCALE, column, 9 * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 13 * HSCALE, column, 15 * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 1 * HSCALE, column, 3 * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 5 * HSCALE, column, 6 * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 9 * HSCALE, column, 10 * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 12 * HSCALE, column, 14 * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 2 * HSCALE, column, 6 * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 9 * HSCALE, column, 13 * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 2 * HSCALE, column, 6 * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 9 * HSCALE, column, 13 * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 2 * HSCALE, column, 6 * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 9 * HSCALE, column, 13 * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 3 * HSCALE, column, 5 * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 10 * HSCALE, column, 12 * HSCALE);

		column += modifier;
		(void)SDL_RenderDrawLine(renderer, column, 3 * HSCALE, column, 5 * HSCALE);
		(void)SDL_RenderDrawLine(renderer, column, 10 * HSCALE, column, 12 * HSCALE);
	}

	column -= 3 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 3 * HSCALE, column, 4 * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 11 * HSCALE, column, 12 * HSCALE);

	column -= 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0 * HSCALE, column, 3 * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 12 * HSCALE, column, 15 * HSCALE);

	column -= 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0 * HSCALE, column, 2 * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 13 * HSCALE, column, 15 * HSCALE);

	column -= 8 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 3 * HSCALE, column, 5 * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 10 * HSCALE, column, 12 * HSCALE);
}

void Grid1::drawHorizontalAllianceLines(SDL_Renderer* const renderer) const noexcept
{
	int32_t row = 0 * HSCALE;

	plog_verbose("Horizontal alliance lines are being drawn.");
	plog_assert(nullptr != renderer);

	row = 9 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 10 * HSCALE, row, 12 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 26 * HSCALE, row, 28 * HSCALE, row);

	row += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 9 * HSCALE, row, 13 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 25 * HSCALE, row, 29 * HSCALE, row);

	row += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 6 * HSCALE, row, 10 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 12 * HSCALE, row, 13 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 25 * HSCALE, row, 26 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 28 * HSCALE, row, 29 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 30 * HSCALE, row, 31 * HSCALE, row);

	row += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 10 * HSCALE, row, 13 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 25 * HSCALE, row, 29 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 29 * HSCALE, row, 32 * HSCALE, row);

	row += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 10 * HSCALE, row, 12 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 14 * HSCALE, row, 16 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 22 * HSCALE, row, 24 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 26 * HSCALE, row, 28 * HSCALE, row);

	row += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 10 * HSCALE, row, 11 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 13 * HSCALE, row, 14 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 24 * HSCALE, row, 25 * HSCALE, row);

	row += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 6 * HSCALE, row, 11 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 13 * HSCALE, row, 16 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 22 * HSCALE, row, 25 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 29 * HSCALE, row, 32 * HSCALE, row);
}

void Grid1::drawVerticalAllianceLines(SDL_Renderer* const renderer) const noexcept
{
	int32_t column = 0 * HSCALE;

	plog_verbose("Vertical alliance lines are being drawn.");
	plog_assert(nullptr != renderer);

	column = 6 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 11 * HSCALE, column, 15 * HSCALE);

	column += 3 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 10 * HSCALE, column, 11 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 9 * HSCALE, column, 15 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 9 * HSCALE, column, 10 * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 12 * HSCALE, column, 13 * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 14 * HSCALE, column, 15 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 9 * HSCALE, column, 13 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 10 * HSCALE, column, 12 * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 14 * HSCALE, column, 15 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 13 * HSCALE, column, 15 * HSCALE);

	column += 2 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 13 * HSCALE, column, 15 * HSCALE);

	column += 6 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 13 * HSCALE, column, 15 * HSCALE);

	column += 2 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 13 * HSCALE, column, 15 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 10 * HSCALE, column, 12 * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 14 * HSCALE, column, 15 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 9 * HSCALE, column, 13 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 9 * HSCALE, column, 10 * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 12 * HSCALE, column, 13 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 9 * HSCALE, column, 13 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 10 * HSCALE, column, 15 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 11 * HSCALE, column, 12 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 11 * HSCALE, column, 12 * HSCALE);
}

void Grid1::drawHorizontalHordeLines(SDL_Renderer* const renderer) const noexcept
{
	int32_t row = 0 * HSCALE;

	plog_verbose("Horizontal horde lines are being drawn.");
	plog_assert(nullptr != renderer);

	row = 6 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 10 * HSCALE, row, 12 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 26 * HSCALE, row, 28 * HSCALE, row);

	row -= 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 9 * HSCALE, row, 13 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 25 * HSCALE, row, 29 * HSCALE, row);

	row -= 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 6 * HSCALE, row, 10 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 12 * HSCALE, row, 13 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 25 * HSCALE, row, 26 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 28 * HSCALE, row, 29 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 30 * HSCALE, row, 31 * HSCALE, row);

	row -= 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 10 * HSCALE, row, 13 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 25 * HSCALE, row, 29 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 29 * HSCALE, row, 32 * HSCALE, row);

	row -= 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 10 * HSCALE, row, 12 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 14 * HSCALE, row, 16 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 22 * HSCALE, row, 24 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 26 * HSCALE, row, 28 * HSCALE, row);

	row -= 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 10 * HSCALE, row, 11 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 13 * HSCALE, row, 14 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 24 * HSCALE, row, 25 * HSCALE, row);

	row -= 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 6 * HSCALE, row, 11 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 13 * HSCALE, row, 16 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 22 * HSCALE, row, 25 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 29 * HSCALE, row, 32 * HSCALE, row);
}

void Grid1::drawVerticalHordeLines(SDL_Renderer* const renderer) const noexcept
{
	int32_t column = 0 * HSCALE;

	plog_verbose("Vertical horde lines are being drawn.");
	plog_assert(nullptr != renderer);

	column = 6 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0 * HSCALE, column, 4 * HSCALE);

	column += 3 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 4 * HSCALE, column, 5 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0 * HSCALE, column, 6 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0 * HSCALE, column, 1 * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 2 * HSCALE, column, 3 * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 5 * HSCALE, column, 6 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 2 * HSCALE, column, 6 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0 * HSCALE, column, 1 * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 3 * HSCALE, column, 5 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0 * HSCALE, column, 2 * HSCALE);

	column += 2 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0 * HSCALE, column, 2 * HSCALE);

	column += 6 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0 * HSCALE, column, 2 * HSCALE);

	column += 2 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0 * HSCALE, column, 2 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0 * HSCALE, column, 1 * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 3 * HSCALE, column, 5 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 2 * HSCALE, column, 6 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 2 * HSCALE, column, 3 * HSCALE);
	(void)SDL_RenderDrawLine(renderer, column, 5 * HSCALE, column, 6 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 2 * HSCALE, column, 6 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 0 * HSCALE, column, 5 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 3 * HSCALE, column, 4 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 3 * HSCALE, column, 4 * HSCALE);
}

void Grid1::drawHorizontalObjectiveLines(SDL_Renderer* const renderer) const noexcept
{
	int32_t row = 0 * HSCALE;

	plog_verbose("Horizontal objective lines are being drawn.");
	plog_assert(nullptr != renderer);

	row = 6 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 6 * HSCALE, row, 9 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 13 * HSCALE, row, 16 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 22 * HSCALE, row, 25 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 29 * HSCALE, row, 32 * HSCALE, row);

	row += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 9 * HSCALE, row, 10 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 12 * HSCALE, row, 13 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 25 * HSCALE, row, 26 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 28 * HSCALE, row, 29 * HSCALE, row);

	row += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 9 * HSCALE, row, 10 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 12 * HSCALE, row, 13 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 25 * HSCALE, row, 26 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 28 * HSCALE, row, 29 * HSCALE, row);

	row += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, 6 * HSCALE, row, 9 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 13 * HSCALE, row, 16 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 22 * HSCALE, row, 25 * HSCALE, row);
	(void)SDL_RenderDrawLine(renderer, 29 * HSCALE, row, 32 * HSCALE, row);
}

void Grid1::drawVerticalObjectiveLines(SDL_Renderer* const renderer) const noexcept
{
	int32_t column = 0 * HSCALE;

	plog_verbose("Vertical objective lines are being drawn.");
	plog_assert(nullptr != renderer);

	column = 6 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 6 * HSCALE, column, 9 * HSCALE);

	column += 3 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 6 * HSCALE, column, 9 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 7 * HSCALE, column, 8 * HSCALE);

	column += 2 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 7 * HSCALE, column, 8 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 6 * HSCALE, column, 9 * HSCALE);

	column += 3 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 6 * HSCALE, column, 9 * HSCALE);

	column += 6 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 6 * HSCALE, column, 9 * HSCALE);

	column += 3 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 6 * HSCALE, column, 9 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 7 * HSCALE, column, 8 * HSCALE);

	column += 2 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 7 * HSCALE, column, 8 * HSCALE);

	column += 1 * HSCALE;
	(void)SDL_RenderDrawLine(renderer, column, 6 * HSCALE, column, 9 * HSCALE);
}

} /*< namespace hob */
