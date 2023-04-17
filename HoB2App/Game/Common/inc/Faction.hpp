#ifndef FACTION_H_
#define FACTION_H_

#include "Types.hpp"

namespace Game
{

class Faction final
{
public:
	// TODO: make singleton

	static void setFaction(bool isAlliance);

	static bool getFaction(void);

	static Color getNeutralColor(void) noexcept;

	static Color getAllianceColor(void) noexcept;

	static Color getHordeColor(void) noexcept;

private:
	static bool m_isAlliance;

}; /*< class Faction */

} /*< namespace Game */

#endif /*< FACTION_H_ */
