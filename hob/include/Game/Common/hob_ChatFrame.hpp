/******************************************************************************************************
 * @file hob_ChatFrame.hpp                                                                            *
 * @date:      @author:                   Reason for change:                                          *
 * 26.08.2023  Gaina Stefan               Initial version.                                            *
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
	 * @param void
	*/
	ChatFrame(void) noexcept;

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
