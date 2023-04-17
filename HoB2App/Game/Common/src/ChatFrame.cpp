/** @file ChatFrame.cpp
 *  @brief Method implementation for the chat frame.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

/***********************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                *
 **********************************************************************************************************************/

#include <plog.h>

#include "ChatFrame.hpp"

/***********************************************************************************************************************
 * MACROS                                                                                                              *
 **********************************************************************************************************************/

/**
 * @brief TODO
*/
#define TEXTURE_FILE_PATH(name) "assets/textures/chat/" name ".png"

/***********************************************************************************************************************
 * METHOD DEFINITIONS                                                                                                  *
 **********************************************************************************************************************/

namespace Game
{

ChatFrame::ChatFrame(void) noexcept
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
				{ 8L             , 4L * SCALE + SCALE / 2L + 8L, 3L * SCALE - 16L, 3L * SCALE - SCALE / 2L },
				{ 0L             , 7L * SCALE - 1L             , 3L * SCALE      , 8L                      },
				{ 0L             , 4L * SCALE + SCALE / 2L     , 8L              , 3L * SCALE - SCALE / 2L },
				{ 0L             , 4L * SCALE + SCALE / 2L     , 3L * SCALE      , 8L                      },
				{ 3L * SCALE - 8L, 4L * SCALE + SCALE / 2L     , 8L              , 3L * SCALE - SCALE / 2L },
				{ 0L             , 0L                          , 0L              , 0L                      }
			}
		}
	}
{
	plog_trace("ChatFrame is being constructed.");
}

ChatFrame::~ChatFrame(void) noexcept
{
	plog_trace("ChatFrame is being destructed.");
}

bool ChatFrame::isClickInside(Coordinate click) const noexcept
{
	plog_verbose("Checking if click is inside chat frame. (click: %" PRId32 ", % " PRId32 ")", click.x, click.y);
	return m_componentContainer[CHAT_FRAME_COMPONENT_INDEX_FRAME_CORE].isMouseInside(click, { 0L, 0L, 0L, SCALE / 2L - 8L });
}

void ChatFrame::showInputBox(void) noexcept
{
	plog_trace("Input box is being shown.");
	m_componentContainer[CHAT_FRAME_COMPONENT_INDEX_FRAME_INPUT].updatePosition({ 0L, 7L * SCALE, 3L * SCALE, SCALE / 2L });
}

void ChatFrame::hideInputBox(void) noexcept
{
	plog_trace("Input box is being hidden.");
	m_componentContainer[CHAT_FRAME_COMPONENT_INDEX_FRAME_INPUT].updatePosition({ 0L, 0L, 0L, 0L });
}

} /*< namespace Game */
