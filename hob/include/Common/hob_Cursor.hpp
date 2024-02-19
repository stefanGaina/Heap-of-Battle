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
 * @file hob_Cursor.hpp
 * @author Gaina Stefan
 * @date 23.07.2023
 * @brief This file defines the class and method prototypes of the cursor.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_CURSOR_HPP_
#define HOB_CURSOR_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "hob_TextureInitializer.hpp"
#include "hobGame_Game.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

/** ***************************************************************************************************
 * @brief Enumerates cursor's textures index.
 *****************************************************************************************************/
enum CursorTextureIndex
{
	CURSOR_TEXTURE_INDEX_ALLIANCE_IDLE	 = 0, /**< Index to the cursor's alliance idle texture.        */
	CURSOR_TEXTURE_INDEX_ALLIANCE_SELECT = 1, /**< Index to the cursor's alliance select texture.      */
	CURSOR_TEXTURE_INDEX_ALLIANCE_MOVE	 = 2, /**< Index to the cursor's alliance move text texture.   */
	CURSOR_TEXTURE_INDEX_ALLIANCE_ATTACK = 3, /**< Index to the cursor's alliance attack text texture. */
	CURSOR_TEXTURE_INDEX_HORDE_IDLE		 = 4, /**< Index to the cursor's horde idle texture.           */
	CURSOR_TEXTURE_INDEX_HORDE_SELECT	 = 5, /**< Index to the cursor's horde select texture.         */
	CURSOR_TEXTURE_INDEX_HORDE_MOVE		 = 6, /**< Index to the cursor's horde move text texture.      */
	CURSOR_TEXTURE_INDEX_HORDE_ATTACK	 = 7, /**< Index to the cursor's horde attack text texture.    */
	CURSOR_TEXTURES_COUNT				 = 8  /**< How many textures cursor loads.                     */
};

/** ***************************************************************************************************
 * @brief Enumerates cursor's changeable components index.
 *****************************************************************************************************/
enum CursorComponentIndex
{
	CURSOR_COMPONENT_INDEX	= 0, /**< Index to the cursor's component.     */
	CURSOR_COMPONENTS_COUNT = 1	 /**< How many components the cursor uses. */
};

/** ***************************************************************************************************
 * @brief Provides a way to customize the cursor.
 *****************************************************************************************************/
class Cursor final : public TextureInitializer<CURSOR_TEXTURES_COUNT, CURSOR_COMPONENTS_COUNT>
{
public:
	/** ***********************************************************************************************
	 * @brief Loads cursor's textures.
	 * @param renderer: Rendering context of the window.
	 *************************************************************************************************/
	Cursor(SDL_Renderer* renderer) noexcept;

	/** ***********************************************************************************************
	 * @brief Updates the position on screen of the cursor.
	 * @param mouse: Coordinate of the cursor.
	 * @return void
	 *************************************************************************************************/
	void updatePosition(const Coordinate& mouse) noexcept;

	/** ***********************************************************************************************
	 * @brief Draws the cursor to the screen.
	 * @param renderer: Rendering context of the window.
	 * @return void
	 *************************************************************************************************/
	void draw(SDL_Renderer* renderer) noexcept override;

	/** ***********************************************************************************************
	 * @brief Sets from which pool will the cursor choose its textures from.
	 * @param isAlliance: true - Alliance, false - Horde.
	 * @return void
	 *************************************************************************************************/
	void setFaction(bool isAlliance) noexcept;

	/** ***********************************************************************************************
	 * @brief Sets the texture of the cursor.
	 * @param type: Action represented by the cursor.
	 * @return void
	 *************************************************************************************************/
	void setTexture(hobGame::CursorType type) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Index of the current active texture of the cursor.
	 *************************************************************************************************/
	size_t textureIndexOffset;

	/** ***********************************************************************************************
	 * @brief Flag indicating if cursor's functionalities are enabled or disabled.
	 *************************************************************************************************/
	bool enabled;
};

} /*< namespace hob */

#endif /*< HOB_CURSOR_HPP_ */
