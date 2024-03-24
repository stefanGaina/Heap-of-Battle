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

/** ***************************************************************************************************
 * @file hob_Faction_test.cpp
 * @author Gaina Stefan
 * @date 13.03.2024
 * @brief This file unit-tests hob_Faction.cpp.
 * @details Current coverage report:
 * <ul>
 * <li> Line coverage: 100.0% (18/18) </li>
 * <li> Functions:     100.0% (8/8)   </li>
 * <li> Branches:      100.0% (4/4)   </li>
 * </ul>
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "hob_Faction.hpp"

/******************************************************************************************************
 * CONSTANTS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief The color assigned to neutral objectives.
 *****************************************************************************************************/
static constexpr SDL_Color neutralColor = { .r = 0xAAU, .g = 0xAAU, .b = 0xAAU, .a = 0xFFU };

/** ***************************************************************************************************
 * @brief The color assigned to alliance faction.
 *****************************************************************************************************/
static constexpr SDL_Color allianceColor = { .r = 0x00U, .g = 0xBFU, .b = 0xBFU, .a = 0xFFU };

/** ***************************************************************************************************
 * @brief The color assigned to horde faction.
 *****************************************************************************************************/
static constexpr SDL_Color hordeColor = { .r = 0xFFU, .g = 0x31U, .b = 0x31U, .a = 0xFFU };

/******************************************************************************************************
 * setFaction
 *****************************************************************************************************/

TEST(FactionTest, setFaction_success)
{
	hob::Faction faction = {};
	SDL_Color	 color	 = { .r = 0x00U, .g = 0x00U, .b = 0x00U, .a = 0x00U };

	EXPECT_EQ(true, faction.getFaction()) << "Faction is horde by default!";

	faction.setFaction(false);
	EXPECT_EQ(false, faction.getFaction()) << "Faction is alliance after setting it to horde!";

	color = faction.getFriendlyColor();
	EXPECT_EQ(hordeColor.r, color.r) << "Wrong horde color red intensity!";
	EXPECT_EQ(hordeColor.g, color.g) << "Wrong horde color green intensity!";
	EXPECT_EQ(hordeColor.b, color.b) << "Wrong horde color blue intensity!";
	EXPECT_EQ(hordeColor.a, color.a) << "Wrong horde color alpha intensity!";

	color = faction.getOpponentColor();
	EXPECT_EQ(allianceColor.r, color.r) << "Wrong alliance color red intensity!";
	EXPECT_EQ(allianceColor.g, color.g) << "Wrong alliance color green intensity!";
	EXPECT_EQ(allianceColor.b, color.b) << "Wrong alliance color blue intensity!";
	EXPECT_EQ(allianceColor.a, color.a) << "Wrong alliance color alpha intensity!";

	faction.setFaction(true);
	EXPECT_EQ(true, faction.getFaction()) << "Faction is horde after setting it to alliance!";

	color = faction.getFriendlyColor();
	EXPECT_EQ(allianceColor.r, color.r) << "Wrong alliance color red intensity!";
	EXPECT_EQ(allianceColor.g, color.g) << "Wrong alliance color green intensity!";
	EXPECT_EQ(allianceColor.b, color.b) << "Wrong alliance color blue intensity!";
	EXPECT_EQ(allianceColor.a, color.a) << "Wrong alliance color alpha intensity!";

	color = faction.getOpponentColor();
	EXPECT_EQ(hordeColor.r, color.r) << "Wrong horde color red intensity!";
	EXPECT_EQ(hordeColor.g, color.g) << "Wrong horde color green intensity!";
	EXPECT_EQ(hordeColor.b, color.b) << "Wrong horde color blue intensity!";
	EXPECT_EQ(hordeColor.a, color.a) << "Wrong horde color alpha intensity!";
}

/******************************************************************************************************
 * getNeutralColor
 *****************************************************************************************************/

TEST(FactionTest, getNeutralColor_success)
{
	const SDL_Color color = hob::Faction::getNeutralColor();

	EXPECT_EQ(neutralColor.r, color.r) << "Wrong neutral color red intensity!";
	EXPECT_EQ(neutralColor.g, color.g) << "Wrong neutral color green intensity!";
	EXPECT_EQ(neutralColor.b, color.b) << "Wrong neutral color blue intensity!";
	EXPECT_EQ(neutralColor.a, color.a) << "Wrong neutral color alpha intensity!";
}

/******************************************************************************************************
 * getAllianceColor
 *****************************************************************************************************/

TEST(FactionTest, getAllianceColor_success)
{
	const SDL_Color color = hob::Faction::getAllianceColor();

	EXPECT_EQ(allianceColor.r, color.r) << "Wrong alliance color red intensity!";
	EXPECT_EQ(allianceColor.g, color.g) << "Wrong alliance color green intensity!";
	EXPECT_EQ(allianceColor.b, color.b) << "Wrong alliance color blue intensity!";
	EXPECT_EQ(allianceColor.a, color.a) << "Wrong alliance color alpha intensity!";
}

/******************************************************************************************************
 * getHordeColor
 *****************************************************************************************************/

TEST(FactionTest, getHordeColor_success)
{
	const SDL_Color color = hob::Faction::getHordeColor();

	EXPECT_EQ(hordeColor.r, color.r) << "Wrong horde color red intensity!";
	EXPECT_EQ(hordeColor.g, color.g) << "Wrong horde color green intensity!";
	EXPECT_EQ(hordeColor.b, color.b) << "Wrong horde color blue intensity!";
	EXPECT_EQ(hordeColor.a, color.a) << "Wrong horde color alpha intensity!";
}
