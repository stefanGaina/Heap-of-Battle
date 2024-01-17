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
 * @file hob_Faction.cpp                                                                              *
 * @date:      @author:                   Reason for change:                                          *
 * 27.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added direct getters for color.                             *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * 17.01.2024  Gaina Stefan               Made the class no longer Singleton.                         *
 * @details This file implements the class defined in hob_Faction.hpp.                                *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Faction.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Faction::Faction(void) noexcept
	: isAlliance{ true }
{
	plog_trace("Faction is being constructed.");
}

void Faction::setFaction(const bool isAlliance) noexcept
{
	plog_info("Faction is being set! (flag: %" PRId8 ")", static_cast<int8_t>(isAlliance));
	this->isAlliance = isAlliance;
}

bool Faction::getFaction(void) const noexcept
{
	plog_verbose("Faction is being got.");
	return isAlliance;
}

SDL_Color Faction::getNeutralColor(void) noexcept
{
	plog_verbose("Neutral color is being got.");
	return { 0xAAU, 0xAAU, 0xAAU, 0xFFU }; /*< gray */
}

SDL_Color Faction::getAllianceColor(void) noexcept
{
	plog_verbose("Alliance color is being got.");
	return { 0x00U, 0xBFU, 0xBFU, 0xFFU }; /*< deep sky blue */
}

SDL_Color Faction::getHordeColor(void) noexcept
{
	plog_verbose("Horde color is being got.");
	return { 0xFFU, 0x31U, 0x31U, 0xFFU }; /*< neon red */
}

SDL_Color Faction::getFriendlyColor(void) const noexcept
{
	return true == isAlliance ? getAllianceColor() : getHordeColor();
}

SDL_Color Faction::getOpponentColor(void) const noexcept
{
	return true == isAlliance ? Faction::getHordeColor() : Faction::getAllianceColor();
}

} /*< namespace hob */
