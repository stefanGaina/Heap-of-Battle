/******************************************************************************************************
 * @file hob_Cursor.hpp                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 26.08.2023  Gaina Stefan               Changed order of members.                                   *
 * 29.08.2023  Gaina Stefan               Made an aesthetic change.                                   *
 * @details This file defines the class and method prototypes of the cursor.                          *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_CURSOR_HPP_
#define HOB_CURSOR_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_TextureInitializer.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
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

/*
 * @brief Enumerates cursor's textures index.
 */
enum CursorTextureIndex
{
	CURSOR_TEXTURE_INDEX_ALLIANCE_IDLE   = 0, /**< Index to the cursor's alliance idle texture.        */
	CURSOR_TEXTURE_INDEX_ALLIANCE_SELECT = 1, /**< Index to the cursor's alliance select texture.      */
	CURSOR_TEXTURE_INDEX_ALLIANCE_MOVE   = 2, /**< Index to the cursor's alliance move text texture.   */
	CURSOR_TEXTURE_INDEX_ALLIANCE_ATTACK = 3, /**< Index to the cursor's alliance attack text texture. */
	CURSOR_TEXTURE_INDEX_HORDE_IDLE      = 4, /**< Index to the cursor's horde idle texture.           */
	CURSOR_TEXTURE_INDEX_HORDE_SELECT    = 5, /**< Index to the cursor's horde select texture.         */
	CURSOR_TEXTURE_INDEX_HORDE_MOVE      = 6, /**< Index to the cursor's horde move text texture.      */
	CURSOR_TEXTURE_INDEX_HORDE_ATTACK    = 7, /**< Index to the cursor's horde attack text texture.    */
	CURSOR_TEXTURES_COUNT                = 8  /**< How many textures cursor loads.                     */
};

/*
 * @brief Enumerates cursor's changeable components index.
 */
enum CursorComponentIndex
{
	CURSOR_COMPONENT_INDEX  = 0, /**< Index to the cursor's component.     */
	CURSOR_COMPONENTS_COUNT = 1  /**< How many components the cursor uses. */
};

/**
 * @brief Provides a way to customize the cursor.
*/
class Cursor final : public TextureInitializer<CURSOR_TEXTURES_COUNT, CURSOR_COMPONENTS_COUNT>
{
public:
	/**
	 * @brief Singleton way to get access to the cursor object.
	 * @param void
	 * @return Reference to the cursor instance.
	*/
	static Cursor& getInstance(void) noexcept;

	/**
	 * @brief Updates the position on screen of the cursor.
	 * @param click: coordinate of the cursor.
	 * @return void
	*/
	void updatePosition(const Coordinate& mouse) noexcept;

	/**
	 * @brief Draws the cursor to the screen.
	 * @param void
	 * @return void
	*/
	void draw(void) noexcept override;

	/**
	 * @brief Sets from which pool will the cursor choose its textures from.
	 * @param isAlliance: true - Alliance | false - Horde
	 * @return void
	*/
	void setFaction(bool isAlliance) noexcept;

	/**
	 * @brief Sets the texture of the cursor.
	 * @param type: Action represented by the cursor.
	 * @return void
	*/
	void setTexture(CursorType type) noexcept;

	/**
	 * @brief Prevents the creation of another object.
	 * @param otherCursor: Instance to be copied.
	*/
	Cursor(Cursor& otherCursor) = delete;

	/**
	 * @brief Prevents the creation of another object.
	 * @param cursor: Instance to be copied.
	*/
	void operator =(const Cursor& cursor) = delete;

private:
	/**
	 * @brief Loads cursor's textures.
	 * @param void
	*/
	Cursor(void) noexcept;

	/**
	 * @brief Destroys the cursor's textures.
	 * @param void
	*/
	~Cursor(void) = default;

private:
	/**
	 * @brief Index of the current active texture of the cursor.
	*/
	size_t m_textureIndexOffset;

	/**
	 * @brief Flag indicating if cursor's functionalities are enabled or disabled.
	*/
	bool m_enabled;
};

} /*< namespace hob */

#endif /*< HOB_CURSOR_HPP_ */
