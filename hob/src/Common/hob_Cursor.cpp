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
 * @file hob_Cursor.cpp                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added const keywords.                                       *
 * 26.08.2023  Gaina Stefan               Improved logs.                                              *
 * 29.08.2023  Gaina Stefan               Removed the use of hob:: and getRawTexture().               *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
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
 * @return The full file path.
*/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("cursor/" name)

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Cursor::Cursor(SDL_Renderer* const renderer) noexcept
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
			{ SCREEN_WIDTH, SCREEN_HEIGHT, SCALE / 3, SCALE / 3 }
		},
		renderer
	}
	, textureIndexOffset{ CURSOR_TEXTURE_INDEX_ALLIANCE_IDLE }
	, enabled           { false }
{
	int32_t errorCode = 0;

	plog_trace("Cursor is being constructed.");

	errorCode = SDL_ShowCursor(SDL_QUERY);
	if (0 > errorCode)
	{
		plog_error("SDL Cursor failed to be queried! (SDL error message: %s)", SDL_GetError());
		return;
	}

	if (SDL_ENABLE == errorCode)
	{
		if (0 > SDL_ShowCursor(SDL_DISABLE))
		{
			plog_error("SDL Cursor failed to be hidden! (SDL error message: %s)", SDL_GetError());
			return;
		}
	}
	else
	{
		plog_debug("SDL Cursor is already hidden.");
	}
	enabled = true;
}

void Cursor::updatePosition(const Coordinate& mouse) noexcept
{
	SDL_Rect destination = { .x = 0, .y = 0, .w = SCALE / 3, .h = SCALE / 3 };

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
	componentContainer[CURSOR_COMPONENT_INDEX].updatePosition(destination);
}

void Cursor::draw(SDL_Renderer* const renderer) noexcept
{
	plog_verbose("Cursor is being drawn.");
	if (true == enabled)
	{
		TextureInitializer::draw(renderer);
	}
}

void Cursor::setFaction(const bool isAlliance) noexcept
{
	plog_info("Cursor's faction is being set! (faction: %" PRId16 ")", static_cast<int16_t>(isAlliance));
	textureIndexOffset = (true == isAlliance) ? static_cast<size_t>(CURSOR_TEXTURE_INDEX_ALLIANCE_IDLE) : static_cast<size_t>(CURSOR_TEXTURE_INDEX_HORDE_IDLE);
}

void Cursor::setTexture(const hobGame::CursorType type) noexcept
{
	plog_verbose("Cursor's texture is being set. (type: %" PRId32 ")", static_cast<int32_t>(type));
	switch (type)
	{
		case hobGame::CursorType::IDLE:
		{
			componentContainer[CURSOR_COMPONENT_INDEX].updateTexture(textureContainer[CURSOR_TEXTURE_INDEX_ALLIANCE_IDLE + textureIndexOffset]);
			break;
		}
		case hobGame::CursorType::SELECT:
		{
			componentContainer[CURSOR_COMPONENT_INDEX].updateTexture(textureContainer[CURSOR_TEXTURE_INDEX_ALLIANCE_SELECT + textureIndexOffset]);
			break;
		}
		case hobGame::CursorType::MOVE:
		{
			componentContainer[CURSOR_COMPONENT_INDEX].updateTexture(textureContainer[CURSOR_TEXTURE_INDEX_ALLIANCE_MOVE + textureIndexOffset]);
			break;
		}
		case hobGame::CursorType::ATTACK:
		{
			componentContainer[CURSOR_COMPONENT_INDEX].updateTexture(textureContainer[CURSOR_TEXTURE_INDEX_ALLIANCE_ATTACK + textureIndexOffset]);
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
