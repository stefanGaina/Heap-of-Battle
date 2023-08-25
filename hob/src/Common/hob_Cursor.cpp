/******************************************************************************************************
 * @file hob_Cursor.cpp                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added const keywords.                                       *
 * @details This file implements the class defined in hob_Cursor.hpp                                  *
 * @todo Create static variables for the initialization of textures for consistency.                  *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Cursor.hpp"
#include "hob_Types.hpp"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief Full file path of an image used by the cursor.
*/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH "cursor/" name ".png"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Cursor& Cursor::getInstance(void) noexcept
{
	static Cursor cursorInstance = {};

	plog_verbose("Cursor instance is being got.");
	return cursorInstance;
}

Cursor::Cursor(void) noexcept
	: TextureInitializer
	{
		{
			TEXTURE_FILE_PATH("alliance_idle")  ,
			TEXTURE_FILE_PATH("alliance_select"),
			TEXTURE_FILE_PATH("alliance_move")  ,
			TEXTURE_FILE_PATH("alliance_attack"),
			TEXTURE_FILE_PATH("horde_idle")     ,
			TEXTURE_FILE_PATH("horde_select")   ,
			TEXTURE_FILE_PATH("horde_move")     ,
			TEXTURE_FILE_PATH("horde_attack")
		},
		{ CURSOR_TEXTURE_INDEX_ALLIANCE_IDLE },
		{
			{ hob::SCREEN_WIDTH, hob::SCREEN_HEIGHT, hob::SCALE / 3L, hob::SCALE / 3L }
		}
	}
	, m_enabled           { false }
	, m_textureIndexOffset{ CURSOR_TEXTURE_INDEX_ALLIANCE_IDLE }
{
	int32_t errorCode = 0L;

	plog_trace("Cursor is being constructed.");

	errorCode = SDL_ShowCursor(SDL_QUERY);
	if (0L > errorCode)
	{
		plog_error("SDL Cursor failed to be queried! (error code: %" PRId32 ") (SDL error message: %s)", errorCode, SDL_GetError());
		return;
	}

	if (SDL_ENABLE == errorCode)
	{
		errorCode = SDL_ShowCursor(SDL_DISABLE);
		if (0L > errorCode)
		{
			plog_error("SDL Cursor failed to be hidden! (error code: %" PRId32 ") (SDL error message: %s)", errorCode, SDL_GetError());
			return;
		}
	}
	else
	{
		plog_debug("SDL Cursor is already hidden.");
	}
	m_enabled = true;
}

void Cursor::updatePosition(const hob::Coordinate& mouse) noexcept
{
	SDL_Rect destination = { 0L, 0L, hob::SCALE / 3L, hob::SCALE / 3L };

	plog_verbose("Cursor position is being updated. (coordinates: %" PRId32 ", %" PRId32 ")", mouse.x, mouse.y);
	if (0L >= mouse.x || 0L >= mouse.y)
	{
		destination.x = hob::SCREEN_WIDTH;
		destination.y = hob::SCREEN_HEIGHT;
	}
	else
	{
		destination.x = mouse.x;
		destination.y = mouse.y;
	}
	m_componentContainer[CURSOR_COMPONENT_INDEX].updatePosition(destination);
}

void Cursor::draw(void) noexcept
{
	plog_verbose("Cursor is being drawn.");
	if (true == m_enabled)
	{
		TextureInitializer::draw();
	}
}

void Cursor::setFaction(const bool isAlliance) noexcept
{
	plog_info("Cursor's faction is being set! (faction: %" PRId16 ")", static_cast<int16_t>(isAlliance));
	m_textureIndexOffset = (true == isAlliance) ? static_cast<size_t>(CURSOR_TEXTURE_INDEX_ALLIANCE_IDLE) : static_cast<size_t>(CURSOR_TEXTURE_INDEX_HORDE_IDLE);
}

void Cursor::setTexture(const CursorType type) noexcept
{
	plog_verbose("Cursor's texture is being set. (type: %" PRId32 ")", static_cast<int32_t>(type));
	switch (type)
	{
		case CursorType::IDLE:
		{
			m_componentContainer[CURSOR_COMPONENT_INDEX].updateTexture(m_textureContainer[CURSOR_TEXTURE_INDEX_ALLIANCE_IDLE + m_textureIndexOffset].getRawTexture());
			break;
		}
		case CursorType::SELECT:
		{
			m_componentContainer[CURSOR_COMPONENT_INDEX].updateTexture(m_textureContainer[CURSOR_TEXTURE_INDEX_ALLIANCE_SELECT + m_textureIndexOffset].getRawTexture());
			break;
		}
		case CursorType::MOVE:
		{
			m_componentContainer[CURSOR_COMPONENT_INDEX].updateTexture(m_textureContainer[CURSOR_TEXTURE_INDEX_ALLIANCE_MOVE + m_textureIndexOffset].getRawTexture());
			break;
		}
		case CursorType::ATTACK:
		{
			m_componentContainer[CURSOR_COMPONENT_INDEX].updateTexture(m_textureContainer[CURSOR_TEXTURE_INDEX_ALLIANCE_ATTACK + m_textureIndexOffset].getRawTexture());
			break;
		}
		default:
		{
			plog_error("Invalid type! (type: %" PRId32 ")", static_cast<int32_t>(type));
			break;
		}
	}
}

} /*< namespace hob */
