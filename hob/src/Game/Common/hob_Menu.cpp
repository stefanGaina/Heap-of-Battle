/******************************************************************************************************
 * @file hob_Menu.cpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * 29.08.2023  Gaina Stefan               Refactored.                                                 *
 * @details This file implements the class defined in hob_Menu.hpp.                                   *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Menu.hpp"
#include "hob_Faction.hpp"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief Full file path of an image of a building.
 * @param name: The name of the image (without extension).
*/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("game_menu/" name)

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Menu::Menu(void) noexcept
	: TextureInitializer
	{
		{
			true == Faction::getInstance().getFaction() ? TEXTURE_FILE_PATH("alliance_stone")   : TEXTURE_FILE_PATH("horde_stone"),
			true == Faction::getInstance().getFaction() ? TEXTURE_FILE_PATH("alliance_stone_1") : TEXTURE_FILE_PATH("horde_stone_1")
		},
		{
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,

			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,

			MENU_TEXTURE_INDEX_STONE,
			MENU_TEXTURE_INDEX_STONE,
			MENU_TEXTURE_INDEX_STONE,
			MENU_TEXTURE_INDEX_STONE,
			MENU_TEXTURE_INDEX_STONE,
			MENU_TEXTURE_INDEX_STONE,

			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,

			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,

			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,

			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,

			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,

			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE_VAR,

			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
			MENU_TEXTURE_INDEX_STONE_VAR,
			MENU_TEXTURE_INDEX_STONE    ,
		},
		{
			{
				{ 0L                     , 0L, SCALE / 2L, SCALE / 2L },
				{ SCALE /2L              , 0L, SCALE / 2L, SCALE / 2L },
				{ SCALE                  , 0L, SCALE / 2L, SCALE / 2L },
				{ SCALE + SCALE / 2L     , 0L, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE             , 0L, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE + SCALE / 2L, 0L, SCALE / 2L, SCALE / 2L },

				{ 0L                     , SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE /2L              , SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE                  , SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE + SCALE / 2L     , SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE             , SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L, SCALE / 2L },

				{ 0L                     , SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE /2L              , SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE                  , SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE + SCALE / 2L     , SCALE, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE             , SCALE, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE + SCALE / 2L, SCALE, SCALE / 2L, SCALE / 2L },

				{ 0L                     , SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE /2L              , SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE                  , SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE + SCALE / 2L     , SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE             , SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE + SCALE / 2L, SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },

				{ 0L                     , 2L * SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE /2L              , 2L * SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE                  , 2L * SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE + SCALE / 2L     , 2L * SCALE, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE             , 2L * SCALE, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE + SCALE / 2L, 2L * SCALE, SCALE / 2L, SCALE / 2L },

				{ 0L                     , 2L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE /2L              , 2L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE                  , 2L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE + SCALE / 2L     , 2L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE             , 2L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE + SCALE / 2L, 2L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },

				{ 0L                     , 3L * SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE /2L              , 3L * SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE                  , 3L * SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE + SCALE / 2L     , 3L * SCALE, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE             , 3L * SCALE, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE + SCALE / 2L, 3L * SCALE, SCALE / 2L, SCALE / 2L },

				{ 0L                     , 3L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE /2L              , 3L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE                  , 3L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE + SCALE / 2L     , 3L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE             , 3L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE + SCALE / 2L, 3L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },

				{ 0L                     , 4L * SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE /2L              , 4L * SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE                  , 4L * SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE + SCALE / 2L     , 4L * SCALE, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE             , 4L * SCALE, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE + SCALE / 2L, 4L * SCALE, SCALE / 2L, SCALE / 2L },

				{ 0L                     , 4L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE /2L              , 4L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE                  , 4L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE + SCALE / 2L     , 4L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE             , 4L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE + SCALE / 2L, 4L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },

				{ 0L                     , 5L * SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE /2L              , 5L * SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE                  , 5L * SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE + SCALE / 2L     , 5L * SCALE, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE             , 5L * SCALE, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE + SCALE / 2L, 5L * SCALE, SCALE / 2L, SCALE / 2L },

				{ 0L                     , 5L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE /2L              , 5L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE                  , 5L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE + SCALE / 2L     , 5L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE             , 5L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE + SCALE / 2L, 5L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },

				{ 0L                     , 6L * SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE /2L              , 6L * SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE                  , 6L * SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE + SCALE / 2L     , 6L * SCALE, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE             , 6L * SCALE, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE + SCALE / 2L, 6L * SCALE, SCALE / 2L, SCALE / 2L },

				{ 0L                     , 6L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE /2L              , 6L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE                  , 6L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ SCALE + SCALE / 2L     , 6L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE             , 6L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE + SCALE / 2L, 6L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },

				{ 0L                     , 7L * SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE /2L              , 7L * SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE                  , 7L * SCALE, SCALE / 2L, SCALE / 2L },
				{ SCALE + SCALE / 2L     , 7L * SCALE, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE             , 7L * SCALE, SCALE / 2L, SCALE / 2L },
				{ 2L * SCALE + SCALE / 2L, 7L * SCALE, SCALE / 2L, SCALE / 2L },

				{ 0L                     , 15L * HSCALE, HSCALE, HSCALE },
				{ SCALE /2L              , 15L * HSCALE, HSCALE, HSCALE },
				{ SCALE                  , 15L * HSCALE, HSCALE, HSCALE },
				{ SCALE + SCALE / 2L     , 15L * HSCALE, HSCALE, HSCALE },
				{ 2L * SCALE             , 15L * HSCALE, HSCALE, HSCALE },
				{ 2L * SCALE + SCALE / 2L, 15L * HSCALE, HSCALE, HSCALE },

				{ 0L                     , 16L * HSCALE, HSCALE, HSCALE },
				{ SCALE /2L              , 16L * HSCALE, HSCALE, HSCALE },
				{ SCALE                  , 16L * HSCALE, HSCALE, HSCALE },
				{ SCALE + SCALE / 2L     , 16L * HSCALE, HSCALE, HSCALE },
				{ 2L * SCALE             , 16L * HSCALE, HSCALE, HSCALE },
				{ 2L * SCALE + SCALE / 2L, 16L * HSCALE, HSCALE, HSCALE },

				{ 0L                     , 17L * HSCALE, HSCALE, HSCALE },
				{ SCALE /2L              , 17L * HSCALE, HSCALE, HSCALE },
				{ SCALE                  , 17L * HSCALE, HSCALE, HSCALE },
				{ SCALE + SCALE / 2L     , 17L * HSCALE, HSCALE, HSCALE },
				{ 2L * SCALE             , 17L * HSCALE, HSCALE, HSCALE },
				{ 2L * SCALE + SCALE / 2L, 17L * HSCALE, HSCALE, HSCALE },

				{ 6L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 6L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 6L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
				{ 7L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 7L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 7L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

				{ 8L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 8L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 8L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
				{ 9L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 9L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 9L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

				{ 10L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 10L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 10L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
				{ 11L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 11L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 11L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

				{ 12L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 12L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 12L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
				{ 13L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 13L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 13L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

				{ 14L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 14L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 14L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
				{ 15L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 15L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 15L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

				{ 16L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 16L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 16L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
				{ 17L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 17L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 17L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

				{ 18L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 18L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 18L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
				{ 19L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 19L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 19L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

				{ 20L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 20L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 20L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
				{ 21L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 21L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 21L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

				{ 22L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 22L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 22L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
				{ 23L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 23L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 23L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

				{ 24L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 24L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 24L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
				{ 25L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 25L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 25L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

				{ 26L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 26L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 26L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
				{ 27L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 27L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 27L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

				{ 28L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 28L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 28L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
				{ 29L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 29L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 29L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

				{ 30L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 30L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 30L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
				{ 31L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 31L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 31L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

				{ 32L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 32L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 32L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
				{ 33L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 33L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 33L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

				{ 34L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 34L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 34L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
				{ 35L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
				{ 35L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
				{ 35L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
			}
		}
	}
{
	plog_trace("Game menu is being constructed.");
}

} /*< namespace hob */
