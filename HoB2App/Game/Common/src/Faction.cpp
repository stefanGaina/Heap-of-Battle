#include "Faction.hpp"
#include "Cursor.hpp"
#include "Menu.hpp"
#include "Chat.hpp"
#include "Timer.hpp"

namespace Game
{

bool Faction::m_isAlliance = true;

void Faction::setFaction(bool isAlliance)
{
	plog_info("Faction is being set! (flag: %" PRId16 ")", static_cast<int16_t>(isAlliance));
	m_isAlliance = isAlliance;

	Chat::setTextColor(isAlliance);
	Timer::setTextures(isAlliance);
}

bool Faction::getFaction(void)
{
	plog_verbose("Faction is being got.");
	return m_isAlliance;
}

Color Faction::getNeutralColor(void) noexcept
{
	plog_verbose("Neutral color is being got.");
	return { 0xAA, 0xAA, 0xAA, 0xFF }; /*< Gray. */
}

Color Faction::getAllianceColor(void) noexcept
{
	plog_verbose("Alliance color is being got.");
	return { 0x00, 0xBF, 0xBF, 0xFF }; /*< Deep sky blue. */
}

Color Faction::getHordeColor(void) noexcept
{
	plog_verbose("Horde color is being got.");
	return { 0xFF, 0x31, 0x31, 0xFF }; /*< Neon red. */
}

} /*< namespace Game */
