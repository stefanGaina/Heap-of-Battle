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
 * @file hob_Chat.cpp
 * @author Gaina Stefan
 * @date 26.08.2023
 * @brief This file implements the class defined in hob_Chat.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Chat.hpp"
#include "hob_Faction.hpp"
#include "hob_Socket.hpp"
#include "hob_LogManager.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

Chat::Chat(SDL_Renderer* const renderer,
		   LoadingScreen&	   loadingScreen,
		   const Socket* const socket,
		   const SDL_Color	   friendlyColor,
		   const SDL_Color	   opponentColor) noexcept
	: SoundInitializer{ { HOB_SOUNDS_FILE_PATH("message_received") } }
	, friendlyColor{ friendlyColor }
	, opponentColor{ opponentColor }
	, chatFrame{ renderer }
	, encryptor{}
	, textures{}
	, components{}
	, messageQueue{}
	, font{ TTF_OpenFont("assets/textures/chat/Anonymous.ttf", 12) }
	, enteringMessage{}
	, enteringMessageLength{ 0 }
	, barTicks{ 0U }
	, isActive{ false }
	, isMuted{ false }
{
	Coordinate dimension = { .x = 0, .y = 0 };

	plog_trace("Chat is being constructed.");
	plog_assert(nullptr != renderer);

	if (nullptr == font)
	{
		plog_error("Font failed to be opened! (TTF error message: %s)", TTF_GetError());
	}

	dimension = textures[CHAT_TEXTURE_INDEX_BAR].create("|", font, friendlyColor, renderer);
	components[CHAT_TEXTURE_INDEX_BAR].updateTexture(textures[CHAT_TEXTURE_INDEX_BAR]);
	components[CHAT_TEXTURE_INDEX_BAR].updatePosition({ .x = dimension.x, .y = 14 * HSCALE + HSCALE / 3 + 1, .w = 4, .h = 15 });

	dimension = textures[CHAT_TEXTURES_COUNT - 2].create("Commands: ./mute | ./unmute", font, Faction::getNeutralColor(), renderer);
	components[CHAT_TEXTURES_COUNT - 2].updateTexture(textures[CHAT_TEXTURES_COUNT - 2]);
	components[CHAT_TEXTURES_COUNT - 2].updatePosition({ .x = 8, .y = 9 * HSCALE + 10, .w = dimension.x, .h = dimension.y });

	if (nullptr != socket)
	{
		encryptor.sendKey(*socket);
	}

	usleep(100 * 1000);
	loadingScreen.step(renderer);
}

Chat::~Chat(void) noexcept
{
	plog_trace("Chat is being destructed.");
	TTF_CloseFont(font);
}

void Chat::draw(SDL_Renderer* const renderer) noexcept
{
	static constexpr const uint8_t BAR_FREQUENCY = 40U;

	size_t		index			= 0UL;
	std::string opponentMessage = {};

	plog_verbose("Chat is being drawn.");
	plog_assert(nullptr != renderer);

	while (false == messageQueue.isEmpty())
	{
		opponentMessage = messageQueue.pop();
		enterMessage(opponentMessage, opponentColor, renderer);
	}

	chatFrame.draw(renderer);
	for (; index < CHAT_TEXTURE_INDEX_BAR; ++index)
	{
		components[index].draw(renderer);
	}

	if (false == isActive)
	{
		plog_verbose("Bar is not being drawn.");
		return;
	}

	if (BAR_FREQUENCY >= ++barTicks)
	{
		components[CHAT_TEXTURE_INDEX_BAR].draw(renderer);
		return;
	}

	if (2U * BAR_FREQUENCY < barTicks)
	{
		plog_verbose("Bar is being drawn again.");
		barTicks = 0U;
	}
}

void Chat::receivedMessage(char* const message) noexcept
{
	std::string messageCopy = {};

	plog_debug("Message from opponent is being received. (message: %s)", message);
	plog_assert(nullptr != message);

	if (true == isMuted)
	{
		plog_debug("Received message is being dropped! (message: %s)", message);
		return;
	}

	encryptor.decryptMessage(message);
	try
	{
		messageCopy = message;
	}
	catch (const std::exception& exception)
	{
		plog_error("Failed to copy message from opponent! (message length: %" PRIu64 ")", strlen(message));
		return;
	}
	messageQueue.push(messageCopy);
	soundContainer[CHAT_SOUND_INDEX_MESSAGE_RECEIVED].play();
}

void Chat::receivedEncryptKey(const uint64_t encryptKey, const Socket& socket) noexcept
{
	plog_verbose("Received encryption key from the other player.");
	encryptor.receivedKey(encryptKey, socket);
}

void Chat::handleClick(const Coordinate click, SDL_Renderer* const renderer) noexcept
{
	plog_verbose("Click is being handled.");
	plog_assert(nullptr != renderer);

	if (true == chatFrame.isClickInside(click) && false == isActive)
	{
		activate();
		return;
	}

	if (true == isActive)
	{
		deactivate(renderer);
	}
}

void Chat::handleButtonPress(const SDL_Event& event, SDL_Renderer* const renderer, const Socket& socket) noexcept
{
	char		showedKey[] = "\0";
	const char* keyName		= nullptr;

	plog_verbose("Handling key event.");
	plog_assert(nullptr != renderer);

	if (false == isActive)
	{
		if (SDLK_RETURN == event.key.keysym.sym)
		{
			plog_debug("Chat activated by key press.");
			activate();
			return;
		}

		plog_trace("Chat is not active. (key code: %" PRId32 ")", static_cast<int32_t>(event.key.keysym.sym));
		return;
	}

	keyName = SDL_GetKeyName(event.key.keysym.sym);
	plog_assert(nullptr != keyName);

	showedKey[0] = 1 == strlen(keyName) ? handleCharacterKey(keyName) : handleSpecialKey(event.key.keysym.sym, renderer, socket);
	if ('\0' != showedKey[0] && 6 * HSCALE - 24 > enteringMessageLength)
	{
		enteringMessage.append(showedKey);
		updateEnteringMessage(renderer);
	}
}

void Chat::updateEnteringMessage(SDL_Renderer* const renderer) noexcept
{
	Coordinate dimension = { .x = 0, .y = 0 };

	plog_verbose("Entering message is being updated. (entering message: %s)", enteringMessage.c_str());
	plog_assert(nullptr != renderer);

	textures[CHAT_TEXTURE_INDEX_ENTERING_MESSAGE].destroy();
	if ("" != enteringMessage)
	{
		dimension = textures[CHAT_TEXTURE_INDEX_ENTERING_MESSAGE].create(enteringMessage, font, friendlyColor, renderer);
	}
	else
	{
		plog_debug("Entering message is being cleared.");
	}

	components[CHAT_TEXTURE_INDEX_ENTERING_MESSAGE].updateTexture(textures[CHAT_TEXTURE_INDEX_ENTERING_MESSAGE]);
	components[CHAT_TEXTURE_INDEX_ENTERING_MESSAGE].updatePosition({ .x = 8, .y = 14 * HSCALE + HSCALE / 3 + 1, .w = dimension.x, .h = dimension.y });
	components[CHAT_TEXTURE_INDEX_BAR].updatePosition({ .x = dimension.x + 8, .y = 14 * HSCALE + HSCALE / 3 + 1, .w = 4, .h = 15 });
	enteringMessageLength = dimension.x;

	barTicks = 0U;
}

void Chat::sendMessage(SDL_Renderer* const renderer, const Socket& socket) noexcept
{
	hobServer::Message updateMessage = {};

	plog_trace("Message is being sent.");
	plog_assert(nullptr != renderer);

	if ("" == enteringMessage)
	{
		plog_debug("Invalid message entered.");
		return;
	}

	if ('.' == enteringMessage[0] && '/' == enteringMessage[1])
	{
		handleUserCommand(renderer);
		return;
	}

	if (true == isMuted)
	{
		plog_debug("Chat is muted.");
		cleanEnteringMessage(renderer);
		return;
	}

	updateMessage.type = hobServer::MessageType::TEXT;
	(void)strncpy(updateMessage.payload.text, enteringMessage.c_str(), sizeof(updateMessage.payload.text));
	updateMessage.payload.text[sizeof(updateMessage.payload.text) - 1UL] = '\0';

	encryptor.encryptMessage(updateMessage.payload.text);
	socket.sendUpdate(updateMessage);

	enterMessage(enteringMessage, friendlyColor, renderer);
	cleanEnteringMessage(renderer);
}

void Chat::enterMessage(const std::string& message, const SDL_Color color, SDL_Renderer* const renderer) noexcept
{
	Coordinate dimension = { .x = 0, .y = 0 };
	size_t	   index	 = 0UL;

	plog_info("Message is being entered! (message: %s)", message.c_str());
	plog_assert(nullptr != renderer);

	if (nullptr != textures[CHAT_TEXTURES_COUNT - 3].getRawTexture())
	// && nullptr != textures[CHAT_TEXTURES_COUNT - 2].getRawTexture()) <- commented because the row of text on top has commands in the beginning.
	{
		textures[CHAT_TEXTURES_COUNT - 2].destroy();
	}
	for (index = CHAT_TEXTURES_COUNT - 2UL; index > 1UL; --index)
	{
		if (nullptr == textures[index - 1UL].getRawTexture())
		{
			continue;
		}
		textures[index]	  = textures[index - 1UL];
		components[index] = components[index - 1UL];
		components[index].correctPosition({ .x = 0, .y = -10, .w = 0, .h = 0 });
	}
	dimension = textures[1].create(message, font, color, renderer);
	components[1].updateTexture(textures[1UL]);
	components[1].updatePosition({ .x = 8, .y = 14 * HSCALE - 18, .w = dimension.x, .h = dimension.y });
}

void Chat::activate(void) noexcept
{
	plog_debug("Chat is being activated.");

	isActive = true;
	barTicks = 0U;
	chatFrame.showInputBox();
}

void Chat::deactivate(SDL_Renderer* const renderer) noexcept
{
	plog_debug("Chat is being deactivated.");
	plog_assert(nullptr != renderer);

	isActive = false;
	chatFrame.hideInputBox();
	cleanEnteringMessage(renderer);
}

char Chat::handleCharacterKey(const char* const keyName) noexcept
{
	const char		 digitShiftCharacters[]	   = ")!@#$%^&*(";
	const char		 specialShiftCharacters1[] = "<_>?";
	const char		 specialShiftCharacters2[] = "{|}";
	const SDL_Keymod keyMod					   = SDL_GetModState();

	plog_assert(nullptr != keyName);
	plog_trace("Character key is being handled. (key name: %s)", keyName);

	if ((keyName[0] >= 'a' && keyName[0] <= 'z') || (keyName[0] >= 'A' && keyName[0] <= 'Z'))
	{
		plog_verbose("Inputed character is alphabetical.");
		if ((0 == (KMOD_CAPS & keyMod) && 0 == (KMOD_LSHIFT & keyMod) && 0 == (KMOD_RSHIFT & keyMod)) ||
			(0 != (KMOD_CAPS & keyMod) && (0 != (KMOD_LSHIFT & keyMod) || 0 != (KMOD_RSHIFT & keyMod))))
		{
			return keyName[0] + 'a' - 'A';
		}
		return keyName[0];
	}

	if (0 != (KMOD_LSHIFT & keyMod) || 0 != (KMOD_RSHIFT & keyMod))
	{
		if ('0' <= keyName[0] && '9' >= keyName[0])
		{
			return digitShiftCharacters[keyName[0] - '0'];
		}

		if (',' <= keyName[0] && '/' >= keyName[0])
		{
			return specialShiftCharacters1[keyName[0] - ','];
		}

		if ('[' <= keyName[0] && ']' >= keyName[0])
		{
			return specialShiftCharacters2[keyName[0] - '['];
		}

		switch (keyName[0])
		{
			case '=':
			{
				return '+';
			}
			case ';':
			{
				return ':';
			}
			case '\'':
			{
				return '\"';
			}
			default:
			{
				plog_warn("Shift + character combination not handled. (key: %c)", keyName[0]);
				return '\0';
			}
		}
	}

	return keyName[0];
}

char Chat::handleSpecialKey(const SDL_Keycode keyCode, SDL_Renderer* const renderer, const Socket& socket) noexcept
{
	plog_trace("Special key is being handled. (key code: %" PRId32 ")", static_cast<int32_t>(keyCode));
	switch (keyCode)
	{
		case SDLK_SPACE:
		{
			plog_verbose("Space button was pressed.");
			return ' ';
		}
		case SDLK_BACKSPACE:
		{
			plog_verbose("Backspace button was pressed.");
			if (0 < enteringMessage.length())
			{
				enteringMessage.pop_back();
				updateEnteringMessage(renderer);
			}
			break;
		}
		case SDLK_RETURN:
		{
			plog_debug("Return button was pressed.");
			if (false == isActive)
			{
				activate();
				break;
			}
			sendMessage(renderer, socket);
			break;
		}
		case SDLK_ESCAPE:
		{
			plog_trace("Escape button was pressed.");
			deactivate(renderer);
			break;
		}
		default:
		{
			plog_verbose("Special key not handled.");
			break;
		}
	}

	return '\0';
}

void Chat::handleUserCommand(SDL_Renderer* const renderer) noexcept
{
	Coordinate dimension = { .x = 0, .y = 0 };
	size_t	   index	 = 0UL;

	plog_trace("User command is being handled.");
	plog_assert(nullptr != renderer);

	if ("./unmute" == enteringMessage)
	{
		if (true == isMuted)
		{
			plog_info("Chat is being unmuted!");
			isMuted = false;

			textures[CHAT_TEXTURES_COUNT - 2].destroy();
			components[CHAT_TEXTURES_COUNT - 2].updateTexture(textures[CHAT_TEXTURES_COUNT - 2]);
		}

		cleanEnteringMessage(renderer);
		return;
	}

	if ("./mute" == enteringMessage)
	{
		plog_info("Chat is being muted!");
		isMuted = true;

		dimension = textures[CHAT_TEXTURES_COUNT - 2].create("Chat is muted: ./unmute", font, Faction::getNeutralColor(), renderer);
		components[CHAT_TEXTURES_COUNT - 2].updateTexture(textures[CHAT_TEXTURES_COUNT - 2]);
		components[CHAT_TEXTURES_COUNT - 2].updatePosition({ .x = 8, .y = 9 * HSCALE + 10, .w = dimension.x, .h = dimension.y });
		for (index = 1UL; index < CHAT_TEXTURES_COUNT - 2UL; ++index)
		{
			if (nullptr != textures[index].getRawTexture())
			{
				textures[index].destroy();
				components[index].updateTexture(textures[index]);
			}
		}

		cleanEnteringMessage(renderer);
		return;
	}

#ifndef PLOG_STRIP_ALL
	LogManager::handleCommand(enteringMessage.c_str() + 2);
#endif /*< PLOG_STRIP_ALL*/

	cleanEnteringMessage(renderer);
}

void Chat::cleanEnteringMessage(SDL_Renderer* const renderer) noexcept
{
	plog_trace("Entering message is being cleaned.");
	plog_assert(nullptr != renderer);

	enteringMessage = "";
	updateEnteringMessage(renderer);
}

} /*< namespace hob */
