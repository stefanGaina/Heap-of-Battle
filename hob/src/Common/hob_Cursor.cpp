/******************************************************************************************************
 * @file hob_Cursor.cpp                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added const keywords.                                       *
 * 26.08.2023  Gaina Stefan               Improved logs.                                              *
 * 29.08.2023  Gaina Stefan               Removed the use of hob:: and getRawTexture().               *
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
 * @param name: The name of the image (without extension).
*/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("cursor/" name)

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
			{ SCREEN_WIDTH, SCREEN_HEIGHT, SCALE / 3L, SCALE / 3L }
		}
	}
	, m_textureIndexOffset{ CURSOR_TEXTURE_INDEX_ALLIANCE_IDLE }
	, m_enabled           { false }
{
	int32_t errorCode = 0L;

	plog_trace("Cursor is being constructed. (size: %" PRIu64 ") (1: %" PRIu64 ") (2: %" PRIu64 ")", sizeof(*this), sizeof(m_textureIndexOffset), sizeof(m_enabled));

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

void Cursor::updatePosition(const Coordinate& mouse) noexcept
{
	SDL_Rect destination = { .x = 0L, .y = 0L, .w = SCALE / 3L, .h = SCALE / 3L };

	plog_verbose("Cursor position is being updated. (coordinates: %" PRId32 ", %" PRId32 ")", mouse.x, mouse.y);
	if (0L >= mouse.x || 0L >= mouse.y)
	{
		destination.x = SCREEN_WIDTH;
		destination.y = SCREEN_HEIGHT;
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

void Cursor::setTexture(const hobGame::CursorType type) noexcept
{
	plog_verbose("Cursor's texture is being set. (type: %" PRId32 ")", static_cast<int32_t>(type));
	switch (type)
	{
		case hobGame::CursorType::IDLE:
		{
			m_componentContainer[CURSOR_COMPONENT_INDEX].updateTexture(m_textureContainer[CURSOR_TEXTURE_INDEX_ALLIANCE_IDLE + m_textureIndexOffset]);
			break;
		}
		case hobGame::CursorType::SELECT:
		{
			m_componentContainer[CURSOR_COMPONENT_INDEX].updateTexture(m_textureContainer[CURSOR_TEXTURE_INDEX_ALLIANCE_SELECT + m_textureIndexOffset]);
			break;
		}
		case hobGame::CursorType::MOVE:
		{
			m_componentContainer[CURSOR_COMPONENT_INDEX].updateTexture(m_textureContainer[CURSOR_TEXTURE_INDEX_ALLIANCE_MOVE + m_textureIndexOffset]);
			break;
		}
		case hobGame::CursorType::ATTACK:
		{
			m_componentContainer[CURSOR_COMPONENT_INDEX].updateTexture(m_textureContainer[CURSOR_TEXTURE_INDEX_ALLIANCE_ATTACK + m_textureIndexOffset]);
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
