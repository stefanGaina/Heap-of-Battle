/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hobGame_Game.hpp"
#include "hob_Types.hpp"


// Rename to alliance and horde
enum class SquareType
{
	EMPTY       = 0,
	HUMAN_KEEP  = 1,
	HUMAN_TOWER = 2,
	HUMAN_FARM  = 3,
	HUMAN_ALTAR = 4,
	ORC_KEEP    = 5,
	ORC_FARM    = 6,
	ORC_ALTAR   = 7,
	ORC_TOWER   = 8,
	MINE        = 9
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

int32_t board[15][26] =
{
	{ OK, OK, OK, OK, E , E , E, E, OF, OF, E, E, E, E, E, E, OF, OF, E, E, E , E , E, OA, OA, OA },
	{ OK, OK, OK, OK, E , E , E, E, OF, OF, E, E, E, E, E, E, OF, OF, E, E, E , E , E, OA, OA, OA },
	{ OK, OK, OK, OK, E , E , E, E, E , E , E, E, E, E, E, E, E , E , E, E, E , E , E, OA, OA, OA },
	{ OK, OK, OK, OK, OT, OT, E, E, E , E , E, E, E, E, E, E, E , E , E, E, OT, OT, E, E , E , E  },
	{ E , E , E , E , OT, OT, E, E, E , E , E, E, E, E, E, E, E , E , E, E, OT, OT, E, E , E , E  },
	{ E , E , E , E , E , E , E, E, E , E , E, E, E, E, E, E, E , E , E, E, E , E , E, E , E , E  },
	{ M , M , M , E , E , E , E, M, M , M , E, E, E, E, E, E, M , M , M, E, E , E , E, M , M , M  },
	{ M , M , M , E , E , E , E, M, M , M , E, E, E, E, E, E, M , M , M, E, E , E , E, M , M , M  },
	{ M , M , M , E , E , E , E, M, M , M , E, E, E, E, E, E, M , M , M, E, E , E , E, M , M , M  },
	{ E , E , E , E , E , E , E, E, E , E , E, E, E, E, E, E, E , E , E, E, E , E , E, E , E , E  },
	{ E , E , E , E , HT, HT, E, E, E , E , E, E, E, E, E, E, E , E , E, E, HT, HT, E, E , E , E  },
	{ HK, HK, HK, HK, HT, HT, E, E, E , E , E, E, E, E, E, E, E , E , E, E, HT, HT, E, E , E , E  },
	{ HK, HK, HK, HK, E , E , E, E, E , E , E, E, E, E, E, E, E , E , E, E, E , E , E, HA, HA, HA },
	{ HK, HK, HK, HK, E , E , E, E, HF, HF, E, E, E, E, E, E, HF, HF, E, E, E , E , E, HA, HA, HA },
	{ HK, HK, HK, HK, E , E , E, E, HF, HF, E, E, E, E, E, E, HF, HF, E, E, E , E , E, HA, HA, HA }
};

namespace hobGame
{

Game::Game(const bool isAlliance) noexcept
	: m_turn{ isAlliance }
	, m_gold{ 100U }
{
	plog_trace("Game is being constructed. (size: %" PRIu64 ") (1: %" PRIu64 ") (2: %" PRIu64 ")", sizeof(*this), sizeof(m_turn), sizeof(m_gold));
}

void Game::endTurn(void) noexcept
{
	m_turn  = !m_turn;
	if (true == m_turn)
	{
		m_gold += 5U;
	}
}

bool Game::getTurn(void) const noexcept
{
	return m_turn;
}

bool Game::recruit(Unit unit) noexcept
{
	return true;
}

CursorType Game::getCursorType(int32_t x, int32_t y) const noexcept
{
	if (x < 6L * hob::HSCALE || y > 15L * hob::HSCALE)
	{
		return CursorType::IDLE;
	}

	x -= 6L * hob::HSCALE;
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
	if (x < 6L * hob::HSCALE || y > 15L * hob::HSCALE)
	{
		return MenuMode::EMPTY;
	}

	x -= 6L * hob::HSCALE;
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
	return m_gold;
}

} /*< namespace hobGame */
