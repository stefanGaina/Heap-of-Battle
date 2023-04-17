/** @file Chat.cpp
 *  @brief Method implementation for the chat.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

/***********************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                *
 **********************************************************************************************************************/

#include <obfuscate.h>
#include <plog.h>

#include "Chat.hpp"
#include "Faction.hpp"
#include "Renderer.hpp"
#include "Socket.hpp"

namespace Game
{

/***********************************************************************************************************************
 * MACROS                                                                                                              *
 **********************************************************************************************************************/

/**
 * @brief TODO
*/
constexpr uint8_t OBFUSCATE_HOUR = 7U;

/**
 * @brief TODO
*/
constexpr uint8_t OBFUSCATE_MINUTE = 8U;

/***********************************************************************************************************************
 * LOCAL VARIABLES                                                                                                     *
 **********************************************************************************************************************/

Color Chat::s_userColor = { 0xFF, 0xFF, 0xFF, 0xFF };

Color Chat::s_opponentColor = { 0xFF, 0xFF, 0xFF, 0xFF };

/***********************************************************************************************************************
 * METHOD DEFINITIONS                                                                                                  *
 **********************************************************************************************************************/

void Chat::setTextColor(bool isAlliance) noexcept
{
	plog_debug("Text color is being set. (flag: %" PRId16 ")", static_cast<int16_t>(isAlliance));
	if (true == isAlliance)
	{
		s_userColor     = Faction::getAllianceColor();
		s_opponentColor = Faction::getHordeColor();
	}
	else
	{
		s_userColor     = Faction::getHordeColor();
		s_opponentColor = Faction::getAllianceColor();
	}
}

Chat::Chat(void) noexcept
	: SoundInitializer       { { "assets/sounds/message_received.wav" } }
	, m_chatFrame            {}
	, m_font                 { nullptr }
	, m_textures             {}
	, m_components           {}
	, m_enteringMessage      { "" }
	, m_enteringMessageLength{ 0L }
	, m_barTicks             { 0U }
	, m_isActive             { false }
	, m_isMuted              { false }
{
	int32_t    errorCode = 0L;
	Coordinate dimension = {};

	plog_trace("Chat is being constructed.");

	errorCode = TTF_Init();
	if (0L != errorCode)
	{
		plog_error("TTF failed to be initialized! (error code: % " PRId32 ")", errorCode);
	}

	m_font = TTF_OpenFont("assets/textures/chat/Anonymous.ttf", 12L);
	if (nullptr == m_font)
	{
		plog_error("Font failed to be opened! (TTF error message: %s)", TTF_GetError());
	}

	dimension = loadTexture("|", s_userColor, CHAT_TEXTURE_INDEX_BAR);
	m_components[CHAT_TEXTURE_INDEX_BAR].updateTexture(m_textures[CHAT_TEXTURE_INDEX_BAR]);
	m_components[CHAT_TEXTURE_INDEX_BAR].updatePosition({ 8L, 7L * SCALE / 3L, dimension.x, dimension.y });

	dimension = loadTexture("Commands: ./mute | ./unmute", Faction::getNeutralColor(), CHAT_TEXTURES_COUNT - 2ULL);
	m_components[CHAT_TEXTURES_COUNT - 2ULL].updateTexture(m_textures[CHAT_TEXTURES_COUNT - 2ULL]);
	m_components[CHAT_TEXTURES_COUNT - 2ULL].updatePosition({ 8L, 7L * SCALE - 190L, dimension.x, dimension.y });
}

Chat::~Chat(void) noexcept
{
	plog_trace("Chat is being destructed.");
	TTF_CloseFont(m_font);
	TTF_Quit();
}

Coordinate Chat::loadTexture(const std::string& text, Color color, size_t index) noexcept
{
	SDL_Surface* temporarySurface = nullptr;
	Coordinate   dimension        = {};

	plog_verbose("Text texture is being loaded. (index: %" PRIu64 ") (text: %s)", index, text.c_str());
	if ("" == text)
	{
		plog_error("Invalid texture text!");
		return dimension;
	}

	temporarySurface = TTF_RenderText_Blended(m_font, text.c_str(), color);
	if (nullptr == temporarySurface)
	{
		plog_error("Text texture failed to be loaded! (text: %s) (TTF error message: %s)", text.c_str(), TTF_GetError());
		return dimension;
	}

	m_textures[index] = SDL_CreateTextureFromSurface(Window::Renderer::getInstance().load(), temporarySurface);
	if (nullptr == m_textures[index])
	{
		plog_error("Text texture failed to be created! (TTF error message: %s)", TTF_GetError());
	}

	dimension.x = temporarySurface->w;
	dimension.y = temporarySurface->h;
	SDL_FreeSurface(temporarySurface);

	return dimension;
}

void Chat::draw(void) noexcept
{
	static constexpr uint8_t BAR_FREQUENCY = 40U;

	size_t index = 0ULL;

	plog_verbose("Chat is being drawn.");

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

void Chat::receivedMessage(char* message) noexcept
{
	plog_debug("Message from opponent is being received.");
	if (nullptr == message)
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

	m_soundContainer[CHAT_SOUND_INDEX_MESSAGE_RECEIVED].play();
	enterMessage(message, s_opponentColor);
}

void Chat::handleClick(Coordinate click) noexcept
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

void Chat::handleButtonPress(const Event& event) noexcept
{
	char        showedKey[] = "\0";
	const char* keyName     = nullptr;
	SDL_Keymod  keyMod      = KMOD_NONE;

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
	if (1L == strlen(keyName) && nullptr != keyName)
	{
		strcpy_s(showedKey, sizeof(showedKey), keyName);
		keyMod = SDL_GetModState();

		if (keyName[0] >= 'a' && keyName[0] <= 'z'
		 || keyName[0] >= 'A' && keyName[0] <= 'Z')
		{
			plog_verbose("Inputed character is alphabetical.");
			if ((0L == (KMOD_CAPS & keyMod) &&  0L == (KMOD_LSHIFT & keyMod) && 0L == (KMOD_RSHIFT & keyMod))
			 || (0L != (KMOD_CAPS & keyMod) && (0L != (KMOD_LSHIFT & keyMod) || 0L != (KMOD_RSHIFT & keyMod))))
			{
				showedKey[0] += 'a' - 'A';
			}
		}
		else
		{
			if (0L != (KMOD_LSHIFT & keyMod) || 0L != (KMOD_RSHIFT & keyMod))
			{
				switch (keyName[0])
				{
					case '1':
					{
						showedKey[0] = '!';
						break;
					}
					case '2':
					{
						showedKey[0] = '@';
						break;
					}
					case '3':
					{
						showedKey[0] = '#';
						break;
					}
					case '4':
					{
						showedKey[0] = '$';
						break;
					}
					case '5':
					{
						showedKey[0] = '%';
						break;
					}
					case '6':
					{
						showedKey[0] = '^';
						break;
					}
					case '7':
					{
						showedKey[0] = '&';
						break;
					}
					case '8':
					{
						showedKey[0] = '*';
						break;
					}
					case '9':
					{
						showedKey[0] = '(';
						break;
					}
					case '0':
					{
						showedKey[0] = ')';
						break;
					}
					case '-':
					{
						showedKey[0] = '_';
						break;
					}
					case '=':
					{
						showedKey[0] = '+';
						break;
					}
					case '[':
					{
						showedKey[0] = '{';
						break;
					}
					case ']':
					{
						showedKey[0] = '}';
						break;
					}
					case '\\':
					{
						showedKey[0] = '|';
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
					case ',':
					{
						showedKey[0] = '<';
						break;
					}
					case '.':
					{
						showedKey[0] = '>';
						break;
					}
					case '/':
					{
						showedKey[0] = '?';
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

	SDL_DestroyTexture(m_textures[CHAT_TEXTURE_INDEX_ENTERING_MESSAGE]);
	m_textures[CHAT_TEXTURE_INDEX_ENTERING_MESSAGE] = nullptr;

	if ("" != m_enteringMessage)
	{
		dimension = loadTexture(m_enteringMessage, s_userColor, CHAT_TEXTURE_INDEX_ENTERING_MESSAGE);
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
	Utility::Message updateMessage = {};
	Coordinate       dimension     = {};
	size_t           index         = 0ULL;

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

			SDL_DestroyTexture(m_textures[CHAT_TEXTURES_COUNT - 2ULL]);
			m_textures[CHAT_TEXTURES_COUNT - 2ULL] = nullptr;
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

		dimension = loadTexture("Chat is muted: ./unmute", Faction::getNeutralColor(), CHAT_TEXTURES_COUNT - 2ULL);
		m_components[CHAT_TEXTURES_COUNT - 2ULL].updateTexture(m_textures[CHAT_TEXTURES_COUNT - 2ULL]);
		m_components[CHAT_TEXTURES_COUNT - 2ULL].updatePosition({ 8L, 7L * SCALE - 190L, dimension.x, dimension.y });
		for (index = 1ULL; index < CHAT_TEXTURES_COUNT - 2ULL; ++index)
		{
			if (nullptr != m_textures[index])
			{
				SDL_DestroyTexture(m_textures[index]);
				m_textures[index] = nullptr;
				m_components[index].updateTexture(m_textures[index]);
			}
		}
		goto CLEAN_ENTERING_MESSAGE;
	}

	updateMessage.type = Utility::MessageType::TEXT;
	strcpy_s(updateMessage.payload.text, sizeof(updateMessage.payload.text), m_enteringMessage.c_str());
	obfuscate_string(updateMessage.payload.text, OBFUSCATE_HOUR, OBFUSCATE_MINUTE);
	Utility::Socket::getInstance().sendUpdate(updateMessage);

	enterMessage(m_enteringMessage, s_userColor);

CLEAN_ENTERING_MESSAGE:

	m_enteringMessage = "";
	updateEnteringMessage();
}

void Chat::enterMessage(std::string message, Color color) noexcept
{
	Coordinate dimension = {};
	size_t     index     = 0ULL;

	plog_info("Message is being entered! (message: %s)", message.c_str());
	if (nullptr != m_textures[CHAT_TEXTURES_COUNT - 3ULL])
	 //&& nullptr != textures[CHAT_TEXTURES_COUNT - 2ULL]) <- commented because the row of text on top has commands in the beginning.
	{
		SDL_DestroyTexture(m_textures[CHAT_TEXTURES_COUNT - 2ULL]);
		m_textures[CHAT_TEXTURES_COUNT - 2ULL] = nullptr;
	}
	for (index = CHAT_TEXTURES_COUNT - 2ULL; index > 1ULL; --index)
	{
		if (nullptr == m_textures[index - 1ULL])
		{
			continue;
		}
		m_textures[index]   = m_textures[index - 1ULL];
		m_components[index] = m_components[index - 1ULL];
		m_components[index].correctPosition({ 0L, -10L, 0L, 0L });
	}
	dimension = loadTexture(message, color, 1ULL);
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

} /*< namespace Game */
