/** @file Chat.hpp
 *  @brief Class definition and method prototypes of the chat.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

#ifndef CHAT_HPP_
#define CHAT_HPP_

/****************************************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                                 *
 ***************************************************************************************************************************************/

#include <SDL_ttf.h>

#include "IDrawable.hpp"
#include "ChatFrame.hpp"
#include "TextureInitializer.hpp"
#include "SoundInitializer.hpp"

/****************************************************************************************************************************************
 * TYPE DEFINITIONS                                                                                                                     *
 ***************************************************************************************************************************************/

namespace Game
{

/**
 * @brief TODO
*/
enum ChatTextureIndex
{
	CHAT_TEXTURE_INDEX_ENTERING_MESSAGE = 0,
	CHAT_TEXTURE_INDEX_BAR              = 19,
	CHAT_TEXTURES_COUNT                 = 20
};

/**
 * @brief TODO
*/
enum ChatSoundIndex
{
	CHAT_SOUND_INDEX_MESSAGE_RECEIVED = 0,
	CHAT_SOUNDS_COUNT                 = 1
};

/**
 * @brief TODO
*/
class Chat final : public Common::IDrawable, public Common::SoundInitializer<CHAT_SOUNDS_COUNT>
{
public:
	/**
	 * @brief 
	 * @param isAlliance: true - opponent's color is red | false - opponent's color is blue.
	 * @return void
	*/
	static void setTextColor(bool isAlliance) noexcept;

	/**
	 * @brief Initialzies TTF subsystem and loads textures.
	 * @param void
	*/
	Chat(void) noexcept;

	/**
	 * @brief Deinitializes TTF subsystem and destroys textures.
	 * @param void
	*/
	~Chat(void) noexcept;

	/**
	 * @brief 
	 * @param click 
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
	 * @brief 
	 * @param message 
	 * @return void
	*/
	void receivedMessage(char* message) noexcept;

private:
	/**
	 * @brief 
	 * @param text 
	 * @param color 
	 * @param index 
	 * @return 
	*/
	Coordinate loadTexture(const std::string& text, SDL_Color color, size_t index) noexcept;

	/**
	 * @brief 
	 * @param void
	 * @return void
	*/
	void updateEnteringMessage(void) noexcept;

	/**
	 * @brief 
	 * @param void
	 * @return void
	*/
	void sendMessage(void) noexcept;

	/**
	 * @brief 
	 * @param message 
	 * @param color 
	 * @return void
	*/
	void enterMessage(std::string message, SDL_Color color) noexcept;

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
	 * @brief Color of the text written by the user.
	*/
	static Color s_userColor;

	/**
	 * @brief Color of the text written by the opponent.
	*/
	static Color s_opponentColor;

	/**
	 * @brief 
	*/
	ChatFrame m_chatFrame;

	/**
	 * @brief Font with which text will be written.
	*/
	Font m_font;

	/**
	 * @brief 
	*/
	std::array<RawTexture, CHAT_TEXTURES_COUNT> m_textures;

	/**
	 * @brief 
	*/
	std::array<Common::Component, CHAT_TEXTURES_COUNT> m_components;

	/**
	 * @brief 
	*/
	std::string m_enteringMessage;

	/**
	 * @brief 
	*/
	int32_t m_enteringMessageLength;

	/**
	 * @brief 
	*/
	uint8_t m_barTicks;

	/**
	 * @brief Flag determining if chat is active(receives input) or not.
	*/
	bool m_isActive;

	/**
	 * @brief 
	*/
	bool m_isMuted;
}; /*< class Chat */

} /*< namespace Game */

#endif /*< CHAT_HPP_ */
