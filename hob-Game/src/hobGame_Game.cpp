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
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hobGame_Game.hpp"
#include "hob_Types.hpp"

// Rename to alliance and horde
enum class SquareType
{
	EMPTY		= 0,
	HUMAN_KEEP	= 1,
	HUMAN_TOWER = 2,
	HUMAN_FARM	= 3,
	HUMAN_ALTAR = 4,
	ORC_KEEP	= 5,
	ORC_FARM	= 6,
	ORC_ALTAR	= 7,
	ORC_TOWER	= 8,
	MINE		= 9
};

static constexpr const int32_t E  = static_cast<int32_t>(SquareType::EMPTY);
static constexpr const int32_t HK = static_cast<int32_t>(SquareType::HUMAN_KEEP);
static constexpr const int32_t HF = static_cast<int32_t>(SquareType::HUMAN_FARM);
static constexpr const int32_t HA = static_cast<int32_t>(SquareType::HUMAN_ALTAR);
static constexpr const int32_t HT = static_cast<int32_t>(SquareType::HUMAN_TOWER);
static constexpr const int32_t OK = static_cast<int32_t>(SquareType::ORC_KEEP);
static constexpr const int32_t OF = static_cast<int32_t>(SquareType::ORC_FARM);
static constexpr const int32_t OA = static_cast<int32_t>(SquareType::ORC_ALTAR);
static constexpr const int32_t OT = static_cast<int32_t>(SquareType::ORC_TOWER);
static constexpr const int32_t M  = static_cast<int32_t>(SquareType::MINE);

int32_t board[15][26] = {
	{ OK, OK, OK, OK, E, E, E, E, OF, OF, E, E, E, E, E, E, OF, OF, E, E, E, E, E, OA, OA, OA },
	{ OK, OK, OK, OK, E, E, E, E, OF, OF, E, E, E, E, E, E, OF, OF, E, E, E, E, E, OA, OA, OA },
	{ OK, OK, OK, OK, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, OA, OA, OA },
	{ OK, OK, OK, OK, OT, OT, E, E, E, E, E, E, E, E, E, E, E, E, E, E, OT, OT, E, E, E, E },
	{ E, E, E, E, OT, OT, E, E, E, E, E, E, E, E, E, E, E, E, E, E, OT, OT, E, E, E, E },
	{ E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E },
	{ M, M, M, E, E, E, E, M, M, M, E, E, E, E, E, E, M, M, M, E, E, E, E, M, M, M },
	{ M, M, M, E, E, E, E, M, M, M, E, E, E, E, E, E, M, M, M, E, E, E, E, M, M, M },
	{ M, M, M, E, E, E, E, M, M, M, E, E, E, E, E, E, M, M, M, E, E, E, E, M, M, M },
	{ E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E },
	{ E, E, E, E, HT, HT, E, E, E, E, E, E, E, E, E, E, E, E, E, E, HT, HT, E, E, E, E },
	{ HK, HK, HK, HK, HT, HT, E, E, E, E, E, E, E, E, E, E, E, E, E, E, HT, HT, E, E, E, E },
	{ HK, HK, HK, HK, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, HA, HA, HA },
	{ HK, HK, HK, HK, E, E, E, E, HF, HF, E, E, E, E, E, E, HF, HF, E, E, E, E, E, HA, HA, HA },
	{ HK, HK, HK, HK, E, E, E, E, HF, HF, E, E, E, E, E, E, HF, HF, E, E, E, E, E, HA, HA, HA }
};

namespace hobGame
{

Game::Game(const bool isAlliance) noexcept
	: turn{ isAlliance }
	, gold{ 100U }
{
	plog_trace("Game is being constructed.");
}

void Game::endTurn(void) noexcept
{
	plog_assert(nullptr != this);

	turn = !turn;
	if (true == turn)
	{
		gold += 5U;
	}
}

bool Game::getTurn(void) const noexcept
{
	plog_assert(nullptr != this);
	return turn;
}

bool Game::isRecruitPossible(Unit unit) noexcept
{
	plog_assert(nullptr != this);

	(void)unit;
	return true;
}

CursorType Game::getCursorType(int32_t x, int32_t y) const noexcept
{
	plog_assert(nullptr != this);

	if (x < 6 * hob::HSCALE || y > 15 * hob::HSCALE)
	{
		return CursorType::IDLE;
	}

	x -= 6 * hob::HSCALE;
	x /= hob::HSCALE;
	y /= hob::HSCALE;

	if (E == board[y][x])
	{
		return CursorType::IDLE;
	}

	return CursorType::SELECT;
}

MenuMode Game::getMenuMode(int32_t x, int32_t y) const noexcept
{
	plog_assert(nullptr != this);

	if (x < 6 * hob::HSCALE || y > 15 * hob::HSCALE)
	{
		return MenuMode::EMPTY;
	}

	x -= 6 * hob::HSCALE;
	x /= hob::HSCALE;
	y /= hob::HSCALE;

	if (HK == board[y][x])
	{
		return MenuMode::ALLIANCE_KEEP;
	}

	if (OK == board[y][x])
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

} /*< namespace hobGame */
