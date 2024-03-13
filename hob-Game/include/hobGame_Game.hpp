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
 * @file hobGame_Game.hpp
 * @author Gaina Stefan
 * @date 12.03.2024
 * @brief This file defines the class and method prototypes of the game.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_GAME_GAME_HPP_
#define HOB_GAME_GAME_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <cstdint>

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hobGame
{

/** ***************************************************************************************************
 * @brief Supported actions of the cursor.
 *****************************************************************************************************/
enum class CursorType : uint8_t
{
	IDLE   = 0, /**< Default type, does not indicate anything. */
	SELECT = 1, /**< Indicates a selection can be done.		   */
	MOVE   = 2, /**< Indicates a move is possible.			   */
	ATTACK = 3	/**< Indicates an attack is possible.		   */
};

/** ***************************************************************************************************
 * @brief
 *****************************************************************************************************/
enum class MenuMode : uint8_t
{
	EMPTY		  = 0, /**< */
	UNCHANGED	  = 1, /**< */
	ALLIANCE_KEEP = 2, /**< */
	HORDE_KEEP	  = 3  /**< */
};

using Square_t = uint8_t;

/** ***************************************************************************************************
 * @brief
 *****************************************************************************************************/
enum class Unit : Square_t
{
	PEASANT	 = 0, /**< */
	INFANTRY = 1, /**< */
	RANGED	 = 2, /**< */
	CAVALRY	 = 3, /**< */
	AIRCRAFT = 4, /**< */
	MAGE	 = 5, /**< */
	NONE	 = 6  /**< */
};

/** ***************************************************************************************************
 * @brief
 *****************************************************************************************************/
class Game
{
public:
	/**
	 * @brief
	 * @param isAlliance: TODO
	*/
	Game(bool isAlliance) noexcept;

	/**
	 * @brief
	 * @param void
	 * @return void
	*/
	void endTurn(void) noexcept;

	/**
	 * @brief
	 * @param void
	 * @return true - it is user's turn.
	 * @return false - it is opponent's turn.
	*/
	bool getTurn(void) const noexcept;

	bool isRecruitPossible(Unit unit) noexcept;

	void recruit(Unit unit) noexcept;

	/**
	 * @brief
	*/
	CursorType getCursorType(int32_t x, int32_t y) const noexcept;

	/**
	 * @brief
	*/
	MenuMode getMenuMode(int32_t x, int32_t y) const noexcept;

	/**
	 * @brief
	*/
	uint8_t getGold(void) const noexcept;

private:
	static void coordinatesToBoardFormat(int32_t& x, int32_t& y) noexcept;

private:
	Square_t board[15][26];

	const uint8_t prices[6];

	const bool faction;

	/**
	 * @brief Flag indicating if it is the user's turn.
	*/
	bool turn;

	/**
	 * @brief TODO
	*/
	uint8_t gold;
};

} /*< namespace hobGame */

#endif /*< HOB_GAME_GAME_HPP_ */
