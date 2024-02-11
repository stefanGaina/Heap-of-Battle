/******************************************************************************************************
 * Heap of Battle Copyright (C) 2024
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the
 * authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
 *    original software. If you use this software in a product, an acknowledgment in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being
 *    the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *****************************************************************************************************/

#ifndef HOB_FACTION_MOCK_HPP_
#define HOB_FACTION_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>

#include "hob_Faction.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

class FactionDummy
{
public:
	virtual ~FactionDummy(void) = default;

	virtual void setFaction(bool isAlliance) = 0;
	virtual bool getFaction(void) = 0;
	virtual SDL_Color getNeutralColor(void) = 0;
	virtual SDL_Color getAllianceColor(void) = 0;
	virtual SDL_Color getHordeColor(void) = 0;
	virtual SDL_Color getFriendlyColor(void) = 0;
	virtual SDL_Color getOpponentColor(void) = 0;
};

class FactionMock : public FactionDummy
{
public:
	FactionMock(void)
	{
		factionMock = this;
	}

	virtual ~FactionMock(void)
	{
		factionMock = nullptr;
	}

	MOCK_METHOD1(setFaction, void(bool));
	MOCK_METHOD0(getFaction, bool(void));
	MOCK_METHOD0(getNeutralColor, SDL_Color(void));
	MOCK_METHOD0(getAllianceColor, SDL_Color(void));
	MOCK_METHOD0(getHordeColor, SDL_Color(void));
	MOCK_METHOD0(getFriendlyColor, SDL_Color(void));
	MOCK_METHOD0(getOpponentColor, SDL_Color(void));

public:
	static FactionMock* factionMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

FactionMock* FactionMock::factionMock = nullptr;

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

Faction::Faction(void) noexcept
{
}

void Faction::setFaction(const bool isAlliance) noexcept
{
	ASSERT_NE(nullptr, FactionMock::factionMock) << "setFaction(): nullptr == FactionMock::factionMock";
	FactionMock::factionMock->setFaction(isAlliance);
}

bool Faction::getFaction(void) const noexcept
{
	if (nullptr == FactionMock::factionMock)
	{
		ADD_FAILURE() << "getFaction(): nullptr == FactionMock::factionMock";
		return false;
	}
	return FactionMock::factionMock->getFaction();
}

SDL_Color Faction::getNeutralColor(void) noexcept
{
	if (nullptr == FactionMock::factionMock)
	{
		ADD_FAILURE() << "getNeutralColor(): nullptr == FactionMock::factionMock";
		return { .r = 0, .g = 0, .b = 0, .a = 0 };
	}
	return FactionMock::factionMock->getNeutralColor();
}

SDL_Color Faction::getAllianceColor(void) noexcept
{
	if (nullptr == FactionMock::factionMock)
	{
		ADD_FAILURE() << "getAllianceColor(): nullptr == FactionMock::factionMock";
		return { .r = 0, .g = 0, .b = 0, .a = 0 };
	}
	return FactionMock::factionMock->getAllianceColor();
}

SDL_Color Faction::getHordeColor(void) noexcept
{
	if (nullptr == FactionMock::factionMock)
	{
		ADD_FAILURE() << "getHordeColor(): nullptr == FactionMock::factionMock";
		return { .r = 0, .g = 0, .b = 0, .a = 0 };
	}
	return FactionMock::factionMock->getHordeColor();
}

SDL_Color Faction::getFriendlyColor(void) const noexcept
{
	if (nullptr == FactionMock::factionMock)
	{
		ADD_FAILURE() << "getFriendlyColor(): nullptr == FactionMock::factionMock";
		return { .r = 0, .g = 0, .b = 0, .a = 0 };
	}
	return FactionMock::factionMock->getFriendlyColor();
}

SDL_Color Faction::getOpponentColor(void) const noexcept
{
	if (nullptr == FactionMock::factionMock)
	{
		ADD_FAILURE() << "getOpponentColor(): nullptr == FactionMock::factionMock";
		return { .r = 0, .g = 0, .b = 0, .a = 0 };
	}
	return FactionMock::factionMock->getOpponentColor();
}

} /*< namespace hob */

#endif /*< HOB_FACTION_MOCK_HPP_ */
