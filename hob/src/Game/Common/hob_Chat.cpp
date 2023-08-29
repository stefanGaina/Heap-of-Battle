/******************************************************************************************************
 * @file hob_Chat.cpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 26.08.2023  Gaina Stefan               Initial version.                                            *
 * 27.08.2023  Gaina Stefan               Delegated update through queue.                             *
 * 29.08.2023  Gaina Stefan               Removed the use of getRawTexture().                         *
 * @details This file implements the class defined in hob_Chat.hpp.                                   *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <obfuscate.h>
#include <plog.h>

#include "hob_Chat.hpp"
#include "hob_Faction.hpp"
#include "hob_Renderer.hpp"
#include "hob_Socket.hpp"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Default hour used for obfuscator key.
*/
static constexpr const uint8_t OBFUSCATE_HOUR = 7U;

/**
 * @brief Default minute used for obfuscator key.
*/
static constexpr const uint8_t OBFUSCATE_MINUTE = 8U;

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

Chat::Chat(void) noexcept
	: SoundInitializer       { { "assets/sounds/message_received.wav" } }
	, m_chatFrame            {}
	, m_textures             {}
	, m_components           {}
	, m_messageQueue         {}
	, m_font                 { NULL }
	, m_enteringMessage      { "" }
	, m_enteringMessageLength{ 0L }
	, m_barTicks             { 0U }
	, m_isActive             { false }
	, m_isMuted              { false }
{
	Coordinate dimension = {};

	plog_trace("Chat is being constructed. (size: %" PRIu64 ") (1: %" PRIu64 ") (2: %" PRIu64 ") (3: %" PRIu64 ") (4: %" PRIu64 ") "
		"(5: %" PRIu64 ") (6: %" PRIu64 ") (7: %" PRIu64 ") (8: %" PRIu64 ") (9: %" PRIu64 ") (10: %" PRIu64 ")", sizeof(*this), sizeof(m_chatFrame),
		sizeof(m_textures), sizeof(m_components), sizeof(m_messageQueue), sizeof(m_font), sizeof(m_enteringMessage), sizeof(m_enteringMessageLength),
		sizeof(m_barTicks), sizeof(m_isActive), sizeof(m_isMuted));

	m_font = TTF_OpenFont("assets/textures/chat/Anonymous.ttf", 12L);
	if (NULL == m_font)
	{
		plog_error("Font failed to be opened! (TTF error message: %s)", TTF_GetError());
	}

	dimension = m_textures[CHAT_TEXTURE_INDEX_BAR].create("|", m_font, Faction::getInstance().getFriendlyColor());
	m_components[CHAT_TEXTURE_INDEX_BAR].updateTexture(m_textures[CHAT_TEXTURE_INDEX_BAR]);
	m_components[CHAT_TEXTURE_INDEX_BAR].updatePosition({ 8L, 7L * SCALE / 3L, dimension.x, dimension.y });

	dimension = m_textures[CHAT_TEXTURES_COUNT - 2ULL].create("Commands: ./mute | ./unmute", m_font, Faction::getInstance().getNeutralColor());
	m_components[CHAT_TEXTURES_COUNT - 2ULL].updateTexture(m_textures[CHAT_TEXTURES_COUNT - 2ULL]);
	m_components[CHAT_TEXTURES_COUNT - 2ULL].updatePosition({ 8L, 7L * SCALE - 190L, dimension.x, dimension.y });
}

Chat::~Chat(void) noexcept
{
	plog_trace("Chat is being destructed.");
	TTF_CloseFont(m_font);
}

void Chat::draw(void) noexcept
{
	static constexpr const uint8_t BAR_FREQUENCY = 40U;

	size_t      index           = 0ULL;
	std::string opponentMessage = {};

	plog_verbose("Chat is being drawn.");
	while (false == m_messageQueue.isEmpty())
	{
		opponentMessage = m_messageQueue.get();
		enterMessage(opponentMessage, Faction::getInstance().getOpponentColor());
	}

	m_chatFrame.draw();
	for (index = 0ULL; index < CHAT_TEXTURE_INDEX_BAR; ++index)
	{
		m_components[index].draw();
	}

	if (false == m_isActive)
	{
		plog_verbose("Bar is not being drawn.");
		return;
	}

	if (BAR_FREQUENCY >= ++m_barTicks)
	{
		m_components[CHAT_TEXTURE_INDEX_BAR].draw();
		return;
	}

	if (2U * BAR_FREQUENCY < m_barTicks)
	{
		plog_verbose("Bar is being drawn again.");
		m_barTicks = 0U;
	}
}

void Chat::receivedMessage(char* const message) noexcept
{
	std::string messageCopy = {};

	plog_debug("Message from opponent is being received. (message: %s)", message);
	if (NULL == message)
	{
		plog_error("Message from opponent is invalid!");
		return;
	}

	deobfuscate_string(message, OBFUSCATE_HOUR, OBFUSCATE_MINUTE);
	if (true == m_isMuted)
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
	m_messageQueue.put(messageCopy);
	m_soundContainer[CHAT_SOUND_INDEX_MESSAGE_RECEIVED].play();
}

void Chat::handleClick(const Coordinate click) noexcept
{
	plog_verbose("Click is being handled.");
	if (true == m_chatFrame.isClickInside(click) && false == m_isActive)
	{
		activate();
		return;
	}

	if (true == m_isActive)
	{
		deactivate();
	}
}

void Chat::handleButtonPress(const SDL_Event& event) noexcept
{
	char        showedKey[]               = "\0";
	char        digitShiftCharacters[]    = ")!@#$%^&*(";
	char        specialShiftCharacters1[] = "<_>?";
	char        specialShiftCharacters2[] = "{|}";
	const char* keyName                   = NULL;
	SDL_Keymod  keyMod                    = KMOD_NONE;

	plog_verbose("Handling key event.");
	if (false == m_isActive)
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
	if (1L == strlen(keyName) && NULL != keyName)
	{
		(void)strncpy(showedKey, keyName, sizeof(showedKey));
		keyMod = SDL_GetModState();

		if ((keyName[0] >= 'a' && keyName[0] <= 'z')
		 || (keyName[0] >= 'A' && keyName[0] <= 'Z'))
		{
			plog_verbose("Inputed character is alphabetical.");
			if ((0L == (KMOD_CAPS & keyMod) &&  0L == (KMOD_LSHIFT & keyMod) && 0L == (KMOD_RSHIFT & keyMod))
			 || (0L != (KMOD_CAPS & keyMod) && (0L != (KMOD_LSHIFT & keyMod) || 0L != (KMOD_RSHIFT & keyMod))))
			{
				showedKey[0] += 'a' - 'A';
			}
		}
		else if (0L != (KMOD_LSHIFT & keyMod) || 0L != (KMOD_RSHIFT & keyMod))
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
				if (0L < m_enteringMessage.length())
				{
					m_enteringMessage.pop_back();
					updateEnteringMessage();
				}
				return;
			}
			case SDLK_RETURN:
			{
				plog_debug("Return button was pressed.");
				if (false == m_isActive)
				{
					activate();
					return;
				}
				sendMessage();
				return;
			}
			case SDLK_ESCAPE:
			{
				plog_trace("Escape button was pressed.");
				deactivate();
			}
			default:
			{
				plog_verbose("Special key not handled.");
				break;
			}
		}
	}
	if ('\0' != showedKey[0ULL] && 3 * SCALE - 24L > m_enteringMessageLength)
	{
		m_enteringMessage.append(showedKey);
		updateEnteringMessage();
	}
}

void Chat::updateEnteringMessage(void) noexcept
{
	Coordinate dimension = {};

	plog_verbose("Entering message is being updated. (entering message: %s)", m_enteringMessage.c_str());

	m_textures[CHAT_TEXTURE_INDEX_ENTERING_MESSAGE].destroy();
	if ("" != m_enteringMessage)
	{
		dimension = m_textures[CHAT_TEXTURE_INDEX_ENTERING_MESSAGE].create(m_enteringMessage, m_font, Faction::getInstance().getFriendlyColor());
	}
	else
	{
		plog_debug("Entering message is being cleared.");
	}

	m_components[CHAT_TEXTURE_INDEX_ENTERING_MESSAGE].updateTexture(m_textures[CHAT_TEXTURE_INDEX_ENTERING_MESSAGE]);
	m_components[CHAT_TEXTURE_INDEX_ENTERING_MESSAGE].updatePosition({ 8L, 6L * SCALE + SCALE / 2L + 2 * SCALE / 3L + 1L, dimension.x, dimension.y });
	m_components[CHAT_TEXTURE_INDEX_BAR].updatePosition({ dimension.x + 8L, 6L * SCALE + SCALE / 2L + 2 * SCALE / 3L + 1L, 4L, 15L });
	m_enteringMessageLength = dimension.x;

	m_barTicks = 0U;
}

void Chat::sendMessage(void) noexcept
{
	hobServer::Message updateMessage = {};
	Coordinate         dimension     = {};
	size_t             index         = 0ULL;

	plog_trace("Message is being sent.");
	if ("" == m_enteringMessage)
	{
		plog_warn("Invalid message entered!");
		return;
	}

	if ("./unmute" == m_enteringMessage)
	{
		if (true == m_isMuted)
		{
			plog_info("Chat is being unmuted!");
			m_isMuted = false;

			m_textures[CHAT_TEXTURES_COUNT - 2ULL].destroy();
			m_components[CHAT_TEXTURES_COUNT - 2ULL].updateTexture(m_textures[CHAT_TEXTURES_COUNT - 2ULL]);
		}
		goto CLEAN_ENTERING_MESSAGE;
	}

	if (true == m_isMuted)
	{
		plog_debug("Chat is muted.");
		goto CLEAN_ENTERING_MESSAGE;
	}

	if ("./mute" == m_enteringMessage)
	{
		plog_info("Chat is being muted!");
		m_isMuted = true;

		dimension = m_textures[CHAT_TEXTURES_COUNT - 2ULL].create("Chat is muted: ./unmute", m_font, Faction::getInstance().getNeutralColor());
		m_components[CHAT_TEXTURES_COUNT - 2ULL].updateTexture(m_textures[CHAT_TEXTURES_COUNT - 2ULL]);
		m_components[CHAT_TEXTURES_COUNT - 2ULL].updatePosition({ 8L, 7L * SCALE - 190L, dimension.x, dimension.y });
		for (index = 1ULL; index < CHAT_TEXTURES_COUNT - 2ULL; ++index)
		{
			if (NULL != m_textures[index].getRawTexture())
			{
				m_textures[index].destroy();
				m_components[index].updateTexture(m_textures[index]);
			}
		}
		goto CLEAN_ENTERING_MESSAGE;
	}

	updateMessage.type = hobServer::MessageType::TEXT;
	(void)strncpy(updateMessage.payload.text, m_enteringMessage.c_str(), sizeof(updateMessage.payload.text));
	obfuscate_string(updateMessage.payload.text, OBFUSCATE_HOUR, OBFUSCATE_MINUTE);
	Socket::getInstance().sendUpdate(updateMessage);

	enterMessage(m_enteringMessage, Faction::getInstance().getFriendlyColor());

CLEAN_ENTERING_MESSAGE:

	m_enteringMessage = "";
	updateEnteringMessage();
}

void Chat::enterMessage(const std::string& message, const SDL_Color color) noexcept
{
	Coordinate dimension = {};
	size_t     index     = 0ULL;

	plog_info("Message is being entered! (message: %s)", message.c_str());
	if (NULL != m_textures[CHAT_TEXTURES_COUNT - 3ULL].getRawTexture())
	 //&& NULL != textures[CHAT_TEXTURES_COUNT - 2ULL].getRawTexture()) <- commented because the row of text on top has commands in the beginning.
	{
		m_textures[CHAT_TEXTURES_COUNT - 2ULL].destroy();
	}
	for (index = CHAT_TEXTURES_COUNT - 2ULL; index > 1ULL; --index)
	{
		if (NULL == m_textures[index - 1ULL].getRawTexture())
		{
			continue;
		}
		m_textures  [index] = m_textures[index - 1ULL];
		m_components[index] = m_components[index - 1ULL];
		m_components[index].correctPosition({ 0L, -10L, 0L, 0L });
	}
	dimension = m_textures[1ULL].create(message, m_font, color);
	m_components[1ULL].updateTexture(m_textures[1ULL]);
	m_components[1ULL].updatePosition({ 8L, 7L * SCALE - 18L, dimension.x, dimension.y });
}

void Chat::activate(void) noexcept
{
	plog_debug("Chat is being activated.");

	m_isActive = true;
	m_barTicks = 0U;
	m_chatFrame.showInputBox();
}

void Chat::deactivate(void) noexcept
{
	plog_debug("Chat is being deactivated.");

	m_isActive = false;
	m_chatFrame.hideInputBox();

	m_enteringMessage = "";
	updateEnteringMessage();
}

} /*< namespace hob */
