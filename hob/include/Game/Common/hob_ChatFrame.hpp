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
 * @file hob_ChatFrame.hpp                                                                            *
 * @date:      @author:                   Reason for change:                                          *
 * 26.08.2023  Gaina Stefan               Initial version.                                            *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file defines the class and method prototypes of the chat frame.                      *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_CHAT_FRAME_HPP_
#define HOB_CHAT_FRAME_HPP_

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
 * @brief Enumerates chat frame's textures index.
*/
enum ChatFrameTextureIndex
{
	CHAT_FRAME_TEXTURE_INDEX_FRAME_INPUT  = 0, /**< Index to the chat frame's input box texture.       */
	CHAT_FRAME_TEXTURE_INDEX_FRAME_CORE   = 1, /**< Index to the chat frame's fill background texture. */
	CHAT_FRAME_TEXTURE_INDEX_FRAME_TOP    = 2, /**< Index to the chat frame's top frame texture.       */
	CHAT_FRAME_TEXTURE_INDEX_FRAME_BOTTOM = 3, /**< Index to the chat frame's bottom frame texture.    */
	CHAT_FRAME_TEXTURE_INDEX_FRAME_LEFT   = 4, /**< Index to the chat frame's left frame texture.      */
	CHAT_FRAME_TEXTURE_INDEX_FRAME_RIGHT  = 5, /**< Index to the chat frame's right frame texture.     */
	CHAT_FRAME_TEXTURES_COUNT             = 6  /**< How many textures chat frame loads.                */
};

/**
 * @brief Enumerates chat frame's components index.
*/
enum ChatFrameComponentIndex
{
	CHAT_FRAME_COMPONENT_INDEX_FRAME_CORE   = 0, /**< Index to the chat frame's input box component.       */
	CHAT_FRAME_COMPONENT_INDEX_FRAME_BOTTOM = 1, /**< Index to the chat frame's fill background component. */
	CHAT_FRAME_COMPONENT_INDEX_FRAME_LEFT   = 2, /**< Index to the chat frame's top frame component.       */
	CHAT_FRAME_COMPONENT_INDEX_FRAME_TOP    = 3, /**< Index to the chat frame's bottom frame component.    */
	CHAT_FRAME_COMPONENT_INDEX_FRAME_RIGHT  = 4, /**< Index to the chat frame's left frame component.      */
	CHAT_FRAME_COMPONENT_INDEX_FRAME_INPUT  = 5, /**< Index to the chat frame's right frame component.     */
	CHAT_FRAME_COMPONENTS_COUNT             = 6  /**< How many components the chat frame uses.             */
};

/**
 * @brief Visual of the chat frame and background.
*/
class ChatFrame final : public TextureInitializer<CHAT_FRAME_TEXTURES_COUNT, CHAT_FRAME_COMPONENTS_COUNT>
{
public:
	/**
	 * @brief Loads textures needed and initializes components.
	 * @param renderer: Rendering context of the window.
	*/
	ChatFrame(SDL_Renderer* renderer) noexcept;

	/**
	 * @brief Destroys the loaded textures.
	 * @param void
	*/
	~ChatFrame(void) = default;

	/**
	 * @brief Checks if coordinates are inside the chat frame's area.
	 * @param click: coordinates of the click.
	 * @return true - it is inside chat frame | false - it is not inside chat frame.
	*/
	bool isClickInside(Coordinate click) const noexcept;

	/**
	 * @brief Makes the box where messages will be inputed by the user visible.
	 * @param void
	 * @return void
	*/
	void showInputBox(void) noexcept;

	/**
	 * @brief Makes the box where messages will be inputed by the user not visible.
	 * @param void
	 * @return void
	*/
	void hideInputBox(void) noexcept;
};

} /*< namespace hob */

#endif /*< HOB_CHAT_FRAME_HPP_ */
