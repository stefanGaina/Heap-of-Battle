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
 * @file hob_Chat.hpp
 * @author Gaina Stefan
 * @date 26.08.2023
 * @brief This file defines the class and method prototypes of the chat.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_CHAT_HPP_
#define HOB_CHAT_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <SDL2/SDL_ttf.h>

#include "hob_IDrawable.hpp"
#include "hob_ChatFrame.hpp"
#include "hob_LoadingScreen.hpp"
#include "hob_Encryptor.hpp"
#include "hob_Texture.hpp"
#include "hob_SoundInitializer.hpp"
#include "hob_AsyncQueue.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

/** ***************************************************************************************************
 * @brief Enumerates chat's textures index.
 *****************************************************************************************************/
enum ChatTextureIndex
{
	CHAT_TEXTURE_INDEX_ENTERING_MESSAGE = 0,  /**< Index to the chat's entering message texture. */
	CHAT_TEXTURE_INDEX_BAR				= 19, /**< Index to the chat's bar texture.              */
	CHAT_TEXTURES_COUNT					= 20  /**< How many textures chat loads.                 */
};

/** ***************************************************************************************************
 * @brief Enumerates chat's sounds index.
 *****************************************************************************************************/
enum ChatSoundIndex
{
	CHAT_SOUND_INDEX_MESSAGE_RECEIVED = 0, /**< Index to the chat's message received sound. */
	CHAT_SOUNDS_COUNT				  = 1  /**< How many sounds the chat loads.             */
};

/** ***************************************************************************************************
 * @brief Common visual representation of chat box and messages.
 * @details Abstracts the user's input (handling clicks, keys, shift + key combinations, commands)
 * showing the received messages and also sending messages.
 *****************************************************************************************************/
class Chat final : public IDrawable,
				   private SoundInitializer<CHAT_SOUNDS_COUNT>
{
public:
	/** ***********************************************************************************************
	 * @brief Initializes font and loads textures.
	 * @param renderer: Rendering context of the window.
	 * @param loadingScreen: Loading screen will be stepped after construction is finalized.
	 * @param socket: Sends the encryption key if not null.
	 * @param friendlyColor: The color assigned to the user.
	 * @param opponentColor: The color assigned to the opponent.
	 *************************************************************************************************/
	Chat(SDL_Renderer* renderer, LoadingScreen& loadingScreen, const Socket* socket, SDL_Color friendlyColor, SDL_Color opponentColor) noexcept;

	/** ***********************************************************************************************
	 * @brief Deinitializes font and destroys textures.
	 * @param void
	 *************************************************************************************************/
	~Chat(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Handles the user's press of the click.
	 * @param click: Coordinates of where the click has been pressed.
	 * @param renderer: Rendering context of the window, needed for clearing the existing message in
	 * case of deactivation.
	 * @return void
	 *************************************************************************************************/
	void handleClick(Coordinate click, SDL_Renderer* renderer) noexcept;

	/** ***********************************************************************************************
	 * @brief Handles key input events if chat is active.
	 * @param event: The button press event.
	 * @param renderer: Rendering context of the window, needed for updating the textures.
	 * @param socket: Reference to the socket object, needed in case the message needs to be sent.
	 * @return void
	 *************************************************************************************************/
	void handleButtonPress(const SDL_Event& event, SDL_Renderer* renderer, const Socket& socket) noexcept;

	/** ***********************************************************************************************
	 * @brief Draws messages to the chat box.
	 * @param renderer: Rendering context of the window.
	 * @return void
	 *************************************************************************************************/
	void draw(SDL_Renderer* renderer) noexcept override;

	/** ***********************************************************************************************
	 * @brief Adds the message to the chat box.
	 * @param message: The message sent by the opponent.
	 * @return void
	 *************************************************************************************************/
	void receivedMessage(char* message) noexcept;

	/** ***********************************************************************************************
	 * @brief Determines the common key based on the local key and the newly received key.
	 * @param encryptKey: The key of the other player that in combination with the local key will
	 * determine the commmon key.
	 * @param socket: Sends the local key if it was not send already during constructing.
	 * @return void
	 *************************************************************************************************/
	void receivedEncryptKey(uint64_t encryptKey, const Socket& socket) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Updates the composing message.
	 * @param renderer: Rendering context of the window.
	 * @return void
	 *************************************************************************************************/
	void updateEnteringMessage(SDL_Renderer* renderer) noexcept;

	/** ***********************************************************************************************
	 * @brief Sends the message to the opponent.
	 * @param renderer: Rendering context of the window.
	 * @param socket: Reference to the socket object.
	 * @return void
	 *************************************************************************************************/
	void sendMessage(SDL_Renderer* renderer, const Socket& socket) noexcept;

	/** ***********************************************************************************************
	 * @brief Adds the message to the chat box.
	 * @param message: The text message.
	 * @param color: Color of the text.
	 * @param renderer: Rendering context of the window.
	 * @return void
	 *************************************************************************************************/
	void enterMessage(const std::string& message, SDL_Color color, SDL_Renderer* renderer) noexcept;

	/** ***********************************************************************************************
	 * @brief Activates chat displaying input box and handling user input.
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void activate(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Deactivates chat only displaying already sent messages.
	 * @param renderer: Rendering context of the window.
	 * @return void
	 *************************************************************************************************/
	void deactivate(SDL_Renderer* renderer) noexcept;

	/** ***********************************************************************************************
	 * @brief Handles a character input taking in consideration if shift or caps lock key is pressed.
	 * @param keyName: Reference to the character in ASCII format.
	 * @return The character that will be appended to the entering message string.
	 *************************************************************************************************/
	char handleCharacterKey(const char* keyName) noexcept;

	/** ***********************************************************************************************
	 * @brief Handles special key input (like return, backspace, etc.).
	 * @param keyCode: The SDL code of the key pressed.
	 * @param renderer: Rendering context of the window.
	 * @param socket: In case of return key input the entering message is being sent.
	 * @return The character that will be appended to the entering message string (can be '\0').
	 *************************************************************************************************/
	char handleSpecialKey(SDL_Keycode keyCode, SDL_Renderer* renderer, const Socket& socket) noexcept;

	/** ***********************************************************************************************
	 * @brief Handles a user command with "./" prefix. Supported commands are:
	 * <ul>
	 * <li> ./mute: Prevents receiving and sending text messages (do nothing if already muted). </li>
	 * <li> ./unmute: Allows receiving and sending text messages (do nothing if not muted).     </li>
	 * <li> Debug commands defined in hob::LogManager class.                                    </li>
	 * </ul>
	 * @param renderer: Rendering context of the window.
	 * @return void
	 *************************************************************************************************/
	void handleUserCommand(SDL_Renderer* renderer) noexcept;

	/** ***********************************************************************************************
	 * @brief Cleans the message that is being entered by the user.
	 * @param renderer: Rendering context of the window.
	 * @return void
	 *************************************************************************************************/
	void cleanEnteringMessage(SDL_Renderer* renderer) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief The color assigned to the user.
	 *************************************************************************************************/
	const SDL_Color friendlyColor;

	/** ***********************************************************************************************
	 * @brief The color assigned to the opponent.
	 *************************************************************************************************/
	const SDL_Color opponentColor;

	/** ***********************************************************************************************
	 * @brief Visual of the chat frame and background.
	 *************************************************************************************************/
	ChatFrame chatFrame;

	/** ***********************************************************************************************
	 * @brief Encrypts messages before they are being sent and decrypts the messages received from the
	 * other player.
	 *************************************************************************************************/
	Encryptor encryptor;

	/** ***********************************************************************************************
	 * @brief Contains and manages the life of the text textures.
	 *************************************************************************************************/
	std::array<Texture, CHAT_TEXTURES_COUNT> textures;

	/** ***********************************************************************************************
	 * @brief Contains the text components.
	 *************************************************************************************************/
	std::array<Component, CHAT_TEXTURES_COUNT> components;

	/** ***********************************************************************************************
	 * @brief Thread safe queue for buffering messages.
	 *************************************************************************************************/
	AsyncQueue<std::string> messageQueue;

	/** ***********************************************************************************************
	 * @brief Font with which text will be written.
	 *************************************************************************************************/
	TTF_Font* const font;

	/** ***********************************************************************************************
	 * @brief The message that is being entered by the user.
	 *************************************************************************************************/
	std::string enteringMessage;

	/** ***********************************************************************************************
	 * @brief The length of the message entered by the user (pixels).
	 *************************************************************************************************/
	int32_t enteringMessageLength;

	/** ***********************************************************************************************
	 * @brief How many frames passed since the bar appeared / dissapeared.
	 *************************************************************************************************/
	uint8_t barTicks;

	/** ***********************************************************************************************
	 * @brief Flag determining if chat is active (receives input) or not.
	 *************************************************************************************************/
	bool isActive;

	/** ***********************************************************************************************
	 * @brief Flag indicating if the chat is muted (receives messages) or not.
	 *************************************************************************************************/
	bool isMuted;
};

} /*< namespace hob */

#endif /*< HOB_CHAT_HPP_ */
