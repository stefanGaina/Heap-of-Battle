/******************************************************************************************************
 * @file hob_Faction.cpp                                                                              *
 * @date:      @author:                   Reason for change:                                          *
 * 27.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added direct getters for color.                             *
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

Faction& Faction::getInstance(void) noexcept
{
	static Faction factionInstance = {};

	plog_verbose("Faction instance is being got.");

	return factionInstance;
}

Faction::Faction(void) noexcept
	: m_isAlliance{ true }
{
	plog_trace("Faction is being constructed.");
}

void Faction::setFaction(const bool isAlliance) noexcept
{
	plog_info("Faction is being set! (flag: %" PRId8 ")", static_cast<int8_t>(isAlliance));
	m_isAlliance = isAlliance;
}

bool Faction::getFaction(void) const noexcept
{
	plog_verbose("Faction is being got.");
	return m_isAlliance;
}

SDL_Color Faction::getNeutralColor(void) const noexcept
{
	plog_verbose("Neutral color is being got.");
	return { 0xAAU, 0xAAU, 0xAAU, 0xFFU }; /*< Gray. */
}

SDL_Color Faction::getAllianceColor(void) const noexcept
{
	plog_verbose("Alliance color is being got.");
	return { 0x00U, 0xBFU, 0xBFU, 0xFFU }; /*< Deep sky blue. */
}

SDL_Color Faction::getHordeColor(void) const noexcept
{
	plog_verbose("Horde color is being got.");
	return { 0xFFU, 0x31U, 0x31U, 0xFFU }; /*< Neon red. */
}

SDL_Color Faction::getFriendlyColor(void) const noexcept
{
	return true == m_isAlliance ? getAllianceColor() : getHordeColor();
}

SDL_Color Faction::getOpponentColor(void) const noexcept
{
	return true == m_isAlliance ? getHordeColor() : getAllianceColor();
}

} /*< namespace hob */
