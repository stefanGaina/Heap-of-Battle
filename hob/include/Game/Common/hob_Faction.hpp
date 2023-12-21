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
 * @file hob_Faction.hpp                                                                              *
 * @date:      @author:                   Reason for change:                                          *
 * 27.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added direct getters for color.                             *
 * 29.08.2023  Gaina Stefan               Made an aesthetic change.                                   *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file defines the class and method prototypes of the faction.                         *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_FACTION_H_
#define HOB_FACTION_H_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_Types.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Global user faction (Alliance | Horde).
*/
class Faction final
{
public:
	/**
	 * @brief Singleton way to get access to the faction object.
	 * @param void
	 * @return Reference to the faction instance.
	*/
	static Faction& getInstance(void) noexcept;

	/**
	 * @brief Sets the faction of the user.
	 * @param isAlliance: true - alliance | false - horde.
	 * @return void
	*/
	void setFaction(bool isAlliance) noexcept;

	/**
	 * @brief Gets the faction the user has been assigned to.
	 * @param void
	 * @return true - alliance | false - horde
	*/
	bool getFaction(void) const noexcept;

	/**
	 * @brief Gets the color used for neutral related text.
	 * @param void
	 * @return Color used for neutral related text.
	*/
	SDL_Color getNeutralColor(void) const noexcept;

	/**
	 * @brief Gets the color used for alliance related text.
	 * @param void
	 * @return Color used for alliance related text.
	*/
	SDL_Color getAllianceColor(void) const noexcept;

	/**
	 * @brief Gets the color used for horde related text.
	 * @param void
	 * @return Color used for horde related text.
	*/
	SDL_Color getHordeColor(void) const noexcept;

	/**
	 * @brief Gets the color associated to the user.
	 * @param void
	 * @return Color associated to the user.
	*/
	SDL_Color getFriendlyColor(void) const noexcept;

	/**
	 * @brief Gets the color associated to the opponent.
	 * @param void
	 * @return Color associated to the opponent.
	*/
	SDL_Color getOpponentColor(void) const noexcept;

	/**
	 * @brief Prevents the creation of another object.
	 * @param otherFaction: instance to be copied.
	*/
	Faction(Faction& otherFaction) = delete;

	/**
	 * @brief Prevents the creation of another object.
	 * @param faction: Instance to be copied.
	*/
	void operator =(const Faction& faction) = delete;

private:
	/**
	 * @brief It assigns to Alliance by default.
	 * @param void
	*/
	Faction(void) noexcept;

	/**
	 * @brief Default destructor.
	 * @param void
	*/
	~Faction(void) = default;

private:
	/**
	 * @brief What faction the user has been assigned to.
	*/
	bool isAlliance;
};

} /*< namespace hob */

#endif /*< HOB_FACTION_H_ */
