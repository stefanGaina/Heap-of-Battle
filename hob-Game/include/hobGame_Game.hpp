#ifndef HOB_GAME_GAME_HPP_
#define HOB_GAME_GAME_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <cstdint>

namespace hobGame
{

/**
 * @brief Supported actions of the cursor.
*/
enum class CursorType
{
	IDLE   = 0, /**< Default type, does not indicate anything. */
	SELECT = 1, /**< Indicates a selection can be done.        */
	MOVE   = 2, /**< Indicates a move is possible.             */
	ATTACK = 3  /**< Indicates an attack is possible.          */
};

/**
 * @brief
*/
enum class MenuMode
{
	EMPTY         = 0, /**< */
	UNCHANGED     = 1,
	ALLIANCE_KEEP = 2, /**< */
	HORDE_KEEP    = 3  /**< */
};

enum class Unit
{
	INFANTRY = 0
};

/**
 * @brief
*/
class Game
{
public:
	/**
	 * @brief
	*/
	Game(bool isAlliance) noexcept;

	/**
	 * @brief
	*/
	~Game(void) = default;

	/**
	 * @brief
	 * @param void
	 * @return void
	*/
	void endTurn(void) noexcept;

	/**
	 * @brief
	 * @param void
	 * @return true - it is user's turn | false - it is opponent's turn.
	*/
	bool getTurn(void) const noexcept;

	bool recruit(Unit unit) noexcept;

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
	/**
	 * @brief Flag indicating if it is the user's turn.
	*/
	bool m_turn;

	/**
	 * @brief
	*/
	uint8_t m_gold;
};

} /*< namespace hobGame */

#endif /*< HOB_GAME_GAME_HPP_ */
