/** @file Settings.cpp
 *  @brief Method implementation for the settings.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

/***********************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                *
 **********************************************************************************************************************/

#include <plog.h>

#include "Settings.hpp"
#include "MenuCommon.h"

namespace Menu
{

/***********************************************************************************************************************
 * LOCAL VARIABLES                                                                                                     *
 **********************************************************************************************************************/

static std::array<std::string, SETTINGS_TEXTURES_COUNT> textureFilePaths =
{
	MENU_TEXTURE_PATH_BACKGROUND                   ,
	MENU_TEXTURE_PATH_BUTTON_IDLE                  ,
	MENU_TEXTURE_PATH_BUTTON_ACTIVE                ,
	MENU_TEXTURE_PATH_BUTTON_PRESSED               ,
	"assets/textures/main_menu/start_game_text.png",
	"assets/textures/main_menu/settings_text.png"  ,
	"assets/textures/main_menu/exit_text.png"
};

static std::array<size_t, SETTINGS_COMPONENTS_COUNT> textureIndexes =
{
	0     ,
	0           ,
	0      ,
	0        ,
	0    ,
	0         ,
	0    ,
	0    ,
	0    ,
	0,
	0  ,
	0
};

static std::array<SDL_Rect, SETTINGS_COMPONENTS_COUNT> destinations =
{
	{
		{ 0L                                          , 0L                                       , SCREEN_WIDTH       , SCREEN_HEIGHT      },
		{ 4L * SCALE                                  , 0L                                       , 2L * BAR_WIDTH     , 2L * BAR_HEIGHT    },
		{ 4L * SCALE + SCALE / 2L + SCALE / 4L        , SCALE + SCALE / 2L                       , 3L * SCALE         , SCALE + SCALE / 2L },
		{ 7L * SCALE + SCALE / 2L                     , 2L * SCALE                               , SCALE              , SCALE + SCALE / 2L },
		{ 8L * SCALE + SCALE / 3L                     , SCALE + SCALE / 2L                       , 3L * SCALE         , SCALE + SCALE / 2L },
		{ 7L * SCALE + SCALE / 2L - 2L                , SCALE / 2L - 8L                          , SCALE              , SCALE + SCALE / 2L },
		{ BAR_HORIZONTAL_CENTERED                     , 3L * SCALE + SCALE / 2L                  , BAR_WIDTH          , BAR_HEIGHT         },
		{ BAR_HORIZONTAL_CENTERED                     , 3L * SCALE + SCALE / 2L + 4L * SCALE / 3L, BAR_WIDTH          , BAR_HEIGHT         },
		{ BAR_HORIZONTAL_CENTERED                     , 3L * SCALE + SCALE / 2L + 8L * SCALE / 3L, BAR_WIDTH          , BAR_HEIGHT         },
		{ BAR_HORIZONTAL_CENTERED + SCALE             , 4L * SCALE + SCALE / 4L                  , BAR_TEXT_WIDTH     , BAR_TEXT_HEIGHT    },
		{ BAR_HORIZONTAL_CENTERED + SCALE             , 4L * SCALE + SCALE / 4L + 4L * SCALE / 3L, BAR_TEXT_WIDTH     , BAR_TEXT_HEIGHT    },
		{ BAR_HORIZONTAL_CENTERED + SCALE + SCALE / 2L, 6L * SCALE + 2L * SCALE / 3L + SCALE / 4L, BAR_TEXT_WIDTH / 2L, BAR_TEXT_HEIGHT    }
	}
};

static std::array<std::string, 1> soundFilePaths =
{
	MENU_SOUND_PATH_CLICK
};

/***********************************************************************************************************************
 * METHOD DEFINITIONS                                                                                                  *
 **********************************************************************************************************************/

Settings::Settings(void)
	: Loop              {}
	, TextureInitializer{ textureFilePaths, textureIndexes, destinations }
	, SoundInitializer  { soundFilePaths }
{
	plog_trace("Settings is being constructed.");
}

Settings::~Settings(void)
{
	plog_trace("Settings is being deconstructed.");
}

void Settings::draw(void) noexcept
{
	plog_verbose("Settings is being drawn.");
	TextureInitializer::draw();
}

void Settings::handleEvent(const SDL_Event& event) noexcept
{

}

} /*< namespace Menu */
