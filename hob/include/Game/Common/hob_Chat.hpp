/******************************************************************************************************
 * @file hob_Chat.hpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 26.08.2023  Gaina Stefan               Initial version.                                            *
 * 27.08.2023  Gaina Stefan               Added queue.                                                *
 * @details This file defines the class and method prototypes of the chat.                            *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_CHAT_HPP_
#define HOB_CHAT_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <SDL_ttf.h>

#include "hob_IDrawable.hpp"
#include "hob_ChatFrame.hpp"
#include "hob_Texture.hpp"
#include "hob_SoundInitializer.hpp"
#include "hob_AsyncQueue.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Enumerates chat's textures index.
*/
enum ChatTextureIndex
{
	CHAT_TEXTURE_INDEX_ENTERING_MESSAGE = 0,  /**< Index to the chat's entering message texture. */
	CHAT_TEXTURE_INDEX_BAR              = 19, /**< Index to the chat's bar texture.              */
	CHAT_TEXTURES_COUNT                 = 20  /**< How many textures chat loads.                 */
};

/**
 * @brief Enumerates chat's sounds index.
*/
enum ChatSoundIndex
{
	CHAT_SOUND_INDEX_MESSAGE_RECEIVED = 0, /**< Index to the chat's message received sound. */
	CHAT_SOUNDS_COUNT                 = 1  /**< How many sounds the chat loads.             */
};

/**
 * @brief Visual representation of chat box and messages.
*/
class Chat final : public IDrawable
				 , public SoundInitializer<CHAT_SOUNDS_COUNT>
{
public:
	/**
	 * @brief Initialzies font and loads textures.
	 * @param void
	*/
	Chat(void) noexcept;

	/**
	 * @brief Deinitializes font and destroys textures.
	 * @param void
	*/
	~Chat(void) noexcept;

	/**
	 * @brief Handles the press of the click.
	 * @param click: Coordinates of where the click has been pressed.
	 * @return void
	*/
	void handleClick(Coordinate click) noexcept;

	/**
	 * @brief Handles key input events if chat is active.
	 * @param void
	 * @return void
	*/
	void handleButtonPress(const SDL_Event& event) noexcept;

	/**
	 * @brief Draws messages to the chat box.
	 * @param void
	 * @return void
	*/
	void draw(void) noexcept override;

	/**
	 * @brief Adds the message to the chat box.
	 * @param message: The message sent by the opponent.
	 * @return void
	*/
	void receivedMessage(char* message) noexcept;

private:
	/**
	 * @brief Updates the composing message.
	 * @param void
	 * @return void
	*/
	void updateEnteringMessage(void) noexcept;

	/**
	 * @brief Sends the message to the opponent.
	 * @param void
	 * @return void
	*/
	void sendMessage(void) noexcept;

	/**
	 * @brief Adds the message to the chat box.
	 * @param message: The text message.
	 * @param color: Color of the text.
	 * @return void
	*/
	void enterMessage(const std::string& message, SDL_Color color) noexcept;

	/**
	 * @brief Activates chat displaying input box and handling user input.
	 * @param void
	 * @return void
	*/
	void activate(void) noexcept;

	/**
	 * @brief Deactivates chat only displaying already sent messages.
	 * @param void
	 * @return void
	*/
	void deactivate(void) noexcept;

private:
	/**
	 * @brief Visual of the chat frame and background.
	*/
	ChatFrame m_chatFrame;

	/**
	 * @brief Contains and manages the life of the text textures.
	*/
	std::array<Texture, CHAT_TEXTURES_COUNT> m_textures;

	/**
	 * @brief Contains the text components.
	*/
	std::array<Component, CHAT_TEXTURES_COUNT> m_components;

	/**
	 * @brief Thread safe queue for buffering messages.
	*/
	AsyncQueue<std::string> m_messageQueue;

	/**
	 * @brief Font with which text will be written.
	*/
	TTF_Font* m_font;

	/**
	 * @brief The message that is being entered by the user.
	*/
	std::string m_enteringMessage;

	/**
	 * @brief The length of the message entered by the user (pixels).
	*/
	int32_t m_enteringMessageLength;

	/**
	 * @brief How many frames passed since the bar appeared / dissapeared.
	*/
	uint8_t m_barTicks;

	/**
	 * @brief Flag determining if chat is active(receives input) or not.
	*/
	bool m_isActive;

	/**
	 * @brief Flag indicating if the chat is muted(receives messages) or not.
	*/
	bool m_isMuted;
};

} /*< namespace hob */

#endif /*< HOB_CHAT_HPP_ */
