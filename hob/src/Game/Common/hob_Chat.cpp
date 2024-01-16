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
 * @file hob_Chat.cpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 26.08.2023  Gaina Stefan               Initial version.                                            *
 * 27.08.2023  Gaina Stefan               Delegated update through queue.                             *
 * 29.08.2023  Gaina Stefan               Removed the use of getRawTexture().                         *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file implements the class defined in hob_Chat.hpp.                                   *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Chat.hpp"
#include "hob_Faction.hpp"
#include "hob_Socket.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Chat::Chat(SDL_Renderer* const renderer) noexcept
	: SoundInitializer     { { HOB_SOUNDS_FILE_PATH("message_received") } }
	, chatFrame            { renderer }
	, textures             {}
	, components           {}
	, messageQueue         {}
	, font                 { nullptr }
	, enteringMessage      { "" }
	, enteringMessageLength{ 0 }
	, barTicks             { 0U }
	, isActive             { false }
	, isMuted              { false }
{
	Coordinate dimension = {};

	plog_trace("Chat is being constructed.");

	font = TTF_OpenFont("assets/textures/chat/Anonymous.ttf", 12);
	if (nullptr == font)
	{
		plog_error("Font failed to be opened! (TTF error message: %s)", TTF_GetError());
	}

	dimension = textures[CHAT_TEXTURE_INDEX_BAR].create("|", font, Faction::getInstance().getFriendlyColor(), renderer);
	components[CHAT_TEXTURE_INDEX_BAR].updateTexture(textures[CHAT_TEXTURE_INDEX_BAR]);
	components[CHAT_TEXTURE_INDEX_BAR].updatePosition({ .x = dimension.x, .y = 14 * HSCALE + HSCALE / 3 + 1, .w = 4, .h = 15 });

	dimension = textures[CHAT_TEXTURES_COUNT - 2].create("Commands: ./mute | ./unmute", font, Faction::getInstance().getNeutralColor(), renderer);
	components[CHAT_TEXTURES_COUNT - 2].updateTexture(textures[CHAT_TEXTURES_COUNT - 2]);
	components[CHAT_TEXTURES_COUNT - 2].updatePosition({ .x = 8, .y = 9 * HSCALE + 10, .w = dimension.x, .h = dimension.y });
}

Chat::~Chat(void) noexcept
{
	plog_trace("Chat is being destructed.");
	TTF_CloseFont(font);
}

void Chat::draw(SDL_Renderer* const renderer) noexcept
{
	static constexpr const uint8_t BAR_FREQUENCY = 40U;

	size_t      index           = 0UL;
	std::string opponentMessage = {};

	plog_verbose("Chat is being drawn.");
	while (false == messageQueue.isEmpty())
	{
		opponentMessage = messageQueue.get();
		enterMessage(opponentMessage, Faction::getInstance().getOpponentColor(), renderer);
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
	if (nullptr == message)
	{
		plog_error("Message from opponent is invalid!");
		return;
	}

	if (true == isMuted)
	{
		plog_debug("Received message is being dropped! (message: %s)", message);
		return;
	}

	try
	{
		messageCopy = message;
	}
	catch (const std::exception& exception)
	{
		plog_error("Failed to copy message from opponent! (message length: %" PRIu64 ")", strlen(message));
		return;
	}
	messageQueue.put(messageCopy);
	soundContainer[CHAT_SOUND_INDEX_MESSAGE_RECEIVED].play();
}

void Chat::handleClick(const Coordinate click, SDL_Renderer* const renderer) noexcept
{
	plog_verbose("Click is being handled.");
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
	char        showedKey[]               = "\0";
	char        digitShiftCharacters[]    = ")!@#$%^&*(";
	char        specialShiftCharacters1[] = "<_>?";
	char        specialShiftCharacters2[] = "{|}";
	const char* keyName                   = nullptr;
	SDL_Keymod  keyMod                    = KMOD_NONE;

	plog_verbose("Handling key event.");
	if (false == isActive)
	{
		if (SDLK_RETURN == event.key.keysym.sym)
		{
			plog_debug("Chat activated by key press.");
			activate();
		}
		else
		{
			plog_trace("Chat is not active. (sym: %" PRId32 ")", static_cast<int32_t>(event.key.keysym.sym));
		}
		return;
	}

	keyName = SDL_GetKeyName(event.key.keysym.sym);
	if (1 == strlen(keyName) && nullptr != keyName)
	{
		(void)strncpy(showedKey, keyName, sizeof(showedKey));
		keyMod = SDL_GetModState();

		if ((keyName[0] >= 'a' && keyName[0] <= 'z')
		 || (keyName[0] >= 'A' && keyName[0] <= 'Z'))
		{
			plog_verbose("Inputed character is alphabetical.");
			if ((0 == (KMOD_CAPS & keyMod) &&  0 == (KMOD_LSHIFT & keyMod) && 0 == (KMOD_RSHIFT & keyMod))
			 || (0 != (KMOD_CAPS & keyMod) && (0 != (KMOD_LSHIFT & keyMod) || 0 != (KMOD_RSHIFT & keyMod))))
			{
				showedKey[0] += 'a' - 'A';
			}
		}
		else if (0 != (KMOD_LSHIFT & keyMod) || 0 != (KMOD_RSHIFT & keyMod))
		{
			if ('0' <= keyName[0] && '9' >= keyName[0])
			{
				showedKey[0] = digitShiftCharacters[keyName[0] - '0'];
			}
			else if (',' <= keyName[0] && '/' >= keyName[0])
			{
				showedKey[0] = specialShiftCharacters1[keyName[0] - ','];
			}
			else if ('[' <= keyName[0] && ']' >= keyName[0])
			{
				showedKey[0] = specialShiftCharacters2[keyName[0] - '['];
			}
			else
			{
				switch (keyName[0])
				{
					case '=':
					{
						showedKey[0] = '+';
						break;
					}
					case ';':
					{
						showedKey[0] = ':';
						break;
					}
					case '\'':
					{
						showedKey[0] = '\"';
						break;
					}
					default:
					{
						plog_warn("Shift + character combination not handled. (key: %c)", keyName[0]);
						break;
					}
				}
			}
		}
	}
	else
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_SPACE:
			{
				plog_verbose("Space button was pressed.");
				showedKey[0] = ' ';
				break;
			}
			case SDLK_BACKSPACE:
			{
				plog_verbose("Backspace button was pressed.");
				if (0 < enteringMessage.length())
				{
					enteringMessage.pop_back();
					updateEnteringMessage(renderer);
				}
				return;
			}
			case SDLK_RETURN:
			{
				plog_debug("Return button was pressed.");
				if (false == isActive)
				{
					activate();
					return;
				}
				sendMessage(renderer, socket);
				return;
			}
			case SDLK_ESCAPE:
			{
				plog_trace("Escape button was pressed.");
				deactivate(renderer);
			}
			default:
			{
				plog_verbose("Special key not handled.");
				break;
			}
		}
	}
	if ('\0' != showedKey[0] && 6 * HSCALE - 24 > enteringMessageLength)
	{
		enteringMessage.append(showedKey);
		updateEnteringMessage(renderer);
	}
}

void Chat::updateEnteringMessage(SDL_Renderer* const renderer) noexcept
{
	Coordinate dimension = {};

	plog_verbose("Entering message is being updated. (entering message: %s)", enteringMessage.c_str());

	textures[CHAT_TEXTURE_INDEX_ENTERING_MESSAGE].destroy();
	if ("" != enteringMessage)
	{
		dimension = textures[CHAT_TEXTURE_INDEX_ENTERING_MESSAGE].create(enteringMessage, font, Faction::getInstance().getFriendlyColor(), renderer);
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
	Coordinate         dimension     = {};
	size_t             index         = 0UL;

	plog_trace("Message is being sent.");
	if ("" == enteringMessage)
	{
		plog_warn("Invalid message entered!");
		return;
	}

	if ("./unmute" == enteringMessage)
	{
		if (true == isMuted)
		{
			plog_info("Chat is being unmuted!");
			isMuted = false;

			textures[CHAT_TEXTURES_COUNT - 2].destroy();
			components[CHAT_TEXTURES_COUNT - 2].updateTexture(textures[CHAT_TEXTURES_COUNT - 2]);
		}
		goto CLEAN_ENTERING_MESSAGE;
	}

	if (true == isMuted)
	{
		plog_debug("Chat is muted.");
		goto CLEAN_ENTERING_MESSAGE;
	}

	if ("./mute" == enteringMessage)
	{
		plog_info("Chat is being muted!");
		isMuted = true;

		dimension = textures[CHAT_TEXTURES_COUNT - 2].create("Chat is muted: ./unmute", font, Faction::getInstance().getNeutralColor(), renderer);
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
		goto CLEAN_ENTERING_MESSAGE;
	}

	updateMessage.type = hobServer::MessageType::TEXT;
	(void)strncpy(updateMessage.payload.text, enteringMessage.c_str(), sizeof(updateMessage.payload.text));
	socket.sendUpdate(updateMessage);

	enterMessage(enteringMessage, Faction::getInstance().getFriendlyColor(), renderer);

CLEAN_ENTERING_MESSAGE:

	enteringMessage = "";
	updateEnteringMessage(renderer);
}

void Chat::enterMessage(const std::string& message, const SDL_Color color, SDL_Renderer* const renderer) noexcept
{
	Coordinate dimension = {};
	size_t     index     = 0UL;

	plog_info("Message is being entered! (message: %s)", message.c_str());
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
		textures  [index] = textures[index - 1UL];
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

	isActive = false;
	chatFrame.hideInputBox();

	enteringMessage = "";
	updateEnteringMessage(renderer);
}

} /*< namespace hob */