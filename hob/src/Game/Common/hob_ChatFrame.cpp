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
 * @file hob_ChatFrame.cpp                                                                            *
 * @date:      @author:                   Reason for change:                                          *
 * 26.08.2023  Gaina Stefan               Initial version.                                            *
 * 29.08.2023  Gaina Stefan               Updated the use of HOB_TEXTURES_FILE_PATH.                  *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file implements the class defined in hob_ChatFrame.hpp.                              *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_ChatFrame.hpp"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief Full file path of an image used by the chat.
 * @param name: The name of the image (without extension).
 * @return The full file path.
*/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("chat/" name)

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

ChatFrame::ChatFrame(SDL_Renderer* const renderer) noexcept
	: TextureInitializer
	{
		{
			TEXTURE_FILE_PATH("frame")       ,
			TEXTURE_FILE_PATH("core")        ,
			TEXTURE_FILE_PATH("top_frame")   ,
			TEXTURE_FILE_PATH("bottom_frame"),
			TEXTURE_FILE_PATH("left_frame")  ,
			TEXTURE_FILE_PATH("right_frame")
		},
		{
			CHAT_FRAME_TEXTURE_INDEX_FRAME_CORE  ,
			CHAT_FRAME_TEXTURE_INDEX_FRAME_BOTTOM,
			CHAT_FRAME_TEXTURE_INDEX_FRAME_LEFT  ,
			CHAT_FRAME_TEXTURE_INDEX_FRAME_TOP   ,
			CHAT_FRAME_TEXTURE_INDEX_FRAME_RIGHT ,
			CHAT_FRAME_TEXTURE_INDEX_FRAME_INPUT
		},
		{
			{
				{ 8             , 9  * HSCALE + 8, 6 * HSCALE - 16, 5 * HSCALE },
				{ 0             , 14 * HSCALE - 1, 6 * HSCALE     , 8          },
				{ 0             , 9  * HSCALE    , 8              , 5 * HSCALE },
				{ 0             , 9  * HSCALE    , 6 * HSCALE     , 8          },
				{ 6 * HSCALE - 8, 9  * HSCALE    , 8              , 5 * HSCALE },
				{ 0             , 0              , 0              , 0          }
			}
		},
		{ renderer }
	}
{
	plog_trace("ChatFrame is being constructed.");
}

bool ChatFrame::isClickInside(const Coordinate click) const noexcept
{
	plog_verbose("Checking if click is inside chat frame. (click: %" PRId32 ", %" PRId32 ")", click.x, click.y);
	return componentContainer[CHAT_FRAME_COMPONENT_INDEX_FRAME_CORE].isMouseInside(click, { .x = 0, .y = 0, .w = 0, .h = HSCALE - 8 });
}

void ChatFrame::showInputBox(void) noexcept
{
	plog_trace("Input box is being shown.");
	componentContainer[CHAT_FRAME_COMPONENT_INDEX_FRAME_INPUT].updatePosition({ .x = 0, .y = 14 * HSCALE, .w = 6 * HSCALE, .h = HSCALE });
}

void ChatFrame::hideInputBox(void) noexcept
{
	plog_trace("Input box is being hidden.");
	componentContainer[CHAT_FRAME_COMPONENT_INDEX_FRAME_INPUT].updatePosition({ .x = 0, .y = 0, .w = 0, .h = 0 });
}

} /*< namespace hob */
