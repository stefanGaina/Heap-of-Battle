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
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <plog.h>

#include "hobGame_Game.hpp"
#include "hob_Types.hpp"

#ifndef PLOG_STRIP_ASSERT

#define assert_unit(unit)                                                                                                                                          \
	do                                                                                                                                                             \
	{                                                                                                                                                              \
		switch (unit)                                                                                                                                              \
		{                                                                                                                                                          \
			case Unit::NONE:                                                                                                                                       \
			case Unit::PEASANT:                                                                                                                                    \
			case Unit::INFANTRY:                                                                                                                                   \
			case Unit::RANGED:                                                                                                                                     \
			case Unit::CAVALRY:                                                                                                                                    \
			case Unit::AIRCRAFT:                                                                                                                                   \
			case Unit::MAGE:                                                                                                                                       \
			{                                                                                                                                                      \
				break;                                                                                                                                             \
			}                                                                                                                                                      \
			default:                                                                                                                                               \
			{                                                                                                                                                      \
				plog_error("Invalid unit! (unit: %" PRId32 ")", unit);                                                                                             \
				plog_assert(false);                                                                                                                                \
				break;                                                                                                                                             \
			}                                                                                                                                                      \
		}                                                                                                                                                          \
	}                                                                                                                                                              \
	while (false)

#else

#define assert_unit(unit)

#endif /*< PLOG_STRIP_ASSERT */

namespace hobGame
{

enum class SquareType : Square_t
{
	EMPTY		   = 6,
	ALLIANCE_KEEP  = 7,
	ALLIANCE_TOWER = 8,
	ALLIANCE_FARM  = 9,
	ALLIANCE_ALTAR = 10,
	HORDE_KEEP	   = 11,
	HORDE_FARM	   = 12,
	HORDE_ALTAR	   = 13,
	HORDE_TOWER	   = 14,
	MINE		   = 15
};

static constexpr Square_t NE = static_cast<Square_t>(SquareType::EMPTY);
static constexpr Square_t AK = static_cast<Square_t>(SquareType::ALLIANCE_KEEP);
static constexpr Square_t AF = static_cast<Square_t>(SquareType::ALLIANCE_FARM);
static constexpr Square_t AA = static_cast<Square_t>(SquareType::ALLIANCE_ALTAR);
static constexpr Square_t AT = static_cast<Square_t>(SquareType::ALLIANCE_TOWER);
static constexpr Square_t HK = static_cast<Square_t>(SquareType::HORDE_KEEP);
static constexpr Square_t HF = static_cast<Square_t>(SquareType::HORDE_FARM);
static constexpr Square_t HA = static_cast<Square_t>(SquareType::HORDE_ALTAR);
static constexpr Square_t HT = static_cast<Square_t>(SquareType::HORDE_TOWER);
static constexpr Square_t NM = static_cast<Square_t>(SquareType::MINE);

Game::Game(const bool isAlliance) noexcept
	: board{ { HK, HK, HK, HK, NE, NE, NE, NE, HF, HF, NE, NE, NE, NE, NE, NE, HF, HF, NE, NE, NE, NE, NE, HA, HA, HA },
			 { HK, HK, HK, HK, NE, NE, NE, NE, HF, HF, NE, NE, NE, NE, NE, NE, HF, HF, NE, NE, NE, NE, NE, HA, HA, HA },
			 { HK, HK, HK, HK, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, HA, HA, HA },
			 { HK, HK, HK, HK, HT, HT, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, HT, HT, NE, NE, NE, NE },
			 { NE, NE, NE, NE, HT, HT, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, HT, HT, NE, NE, NE, NE },
			 { NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE },
			 { NM, NM, NM, NE, NE, NE, NE, NM, NM, NM, NE, NE, NE, NE, NE, NE, NM, NM, NM, NE, NE, NE, NE, NM, NM, NM },
			 { NM, NM, NM, NE, NE, NE, NE, NM, NM, NM, NE, NE, NE, NE, NE, NE, NM, NM, NM, NE, NE, NE, NE, NM, NM, NM },
			 { NM, NM, NM, NE, NE, NE, NE, NM, NM, NM, NE, NE, NE, NE, NE, NE, NM, NM, NM, NE, NE, NE, NE, NM, NM, NM },
			 { NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE },
			 { NE, NE, NE, NE, AT, AT, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, AT, AT, NE, NE, NE, NE },
			 { AK, AK, AK, AK, AT, AT, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, AT, AT, NE, NE, NE, NE },
			 { AK, AK, AK, AK, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, NE, AA, AA, AA },
			 { AK, AK, AK, AK, NE, NE, NE, NE, AF, AF, NE, NE, NE, NE, NE, NE, AF, AF, NE, NE, NE, NE, NE, AA, AA, AA },
			 { AK, AK, AK, AK, NE, NE, NE, NE, AF, AF, NE, NE, NE, NE, NE, NE, AF, AF, NE, NE, NE, NE, NE, AA, AA, AA } }
	, prices{ 5U, 10U, 15U, 25U, 30U, 50U }
	, faction{ isAlliance }
	, turn{ isAlliance }
	, gold{ 20U }
{
	plog_trace("Game is being constructed. (faction: %s)", FACTION_TO_STRING(isAlliance));
}

void Game::endTurn(void) noexcept
{
	plog_assert(nullptr != this);

	turn = !turn;
	gold += true == turn ? 5U : 0U;
}

bool Game::getTurn(void) const noexcept
{
	plog_assert(nullptr != this);
	return turn;
}

bool Game::isRecruitPossible(const Unit unit) noexcept
{
	const Square_t square = true == faction ? board[14][4] : board[0][4];

	plog_assert(nullptr != this);
	assert_unit(unit);

	return Unit::NONE != unit && prices[static_cast<size_t>(unit)] <= gold && NE == square;
}

void Game::recruit(const Unit unit) noexcept
{
	Square_t& square = true == faction ? board[14][4] : board[0][4];

	plog_assert(nullptr != this);
	assert_unit(unit);
	plog_assert(Unit::NONE != unit);
	plog_assert(prices[static_cast<size_t>(unit)] <= gold);
	plog_assert(NE == square);
	plog_assert(true == turn);

	gold -= prices[static_cast<size_t>(unit)];
	square = static_cast<int32_t>(unit);
}

CursorType Game::getCursorType(int32_t x, int32_t y) const noexcept
{
	plog_assert(nullptr != this);

	if (x < 6 * hob::HSCALE || y > 15 * hob::HSCALE)
	{
		return CursorType::IDLE;
	}

	coordinatesToBoardFormat(x, y);

	return NE == board[y][x] ? CursorType::IDLE : CursorType::SELECT;
}

MenuMode Game::getMenuMode(int32_t x, int32_t y) const noexcept
{
	plog_assert(nullptr != this);

	if (x < 6 * hob::HSCALE || y > 15 * hob::HSCALE)
	{
		return MenuMode::EMPTY;
	}

	coordinatesToBoardFormat(x, y);

	if (AK == board[y][x])
	{
		return MenuMode::ALLIANCE_KEEP;
	}

	if (HK == board[y][x])
	{
		return MenuMode::HORDE_KEEP;
	}

	return MenuMode::EMPTY;
}

uint8_t Game::getGold(void) const noexcept
{
	plog_assert(nullptr != this);
	return gold;
}

void Game::coordinatesToBoardFormat(int32_t& x, int32_t& y) noexcept
{
	x -= 6 * hob::HSCALE;
	x /= hob::HSCALE;
	y /= hob::HSCALE;
}

} /*< namespace hobGame */
