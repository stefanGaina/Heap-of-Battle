/** @file pers_config.c
 *  @brief Implementation of the functions involved in operations over the configuration file.
 *
 *  @author Gaina Stefan!
 *  @bug No known bugs.
 */

/***********************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                *
 **********************************************************************************************************************/

#include <stdio.h>
#include <inttypes.h>
#include <plog.h>

#include "pers_config.h"

/***********************************************************************************************************************
 * MACROS                                                                                                              *
 **********************************************************************************************************************/

/**
 * @brief Tag that is attached at the beginning of logs.
*/
#define LOG_PREFIX "[PERS] "

/***********************************************************************************************************************
 * LOCAL VARIABLES                                                                                                     *
 **********************************************************************************************************************/

/**
 * @brief Name of the file where the configuration will be read/written.
*/
static const char* const CONFIG_FILE_NAME = "pers/config";

/**
 * @brief Buffer for the content of the file. Format: is_fullscreen space music_volume space sound_effects_volume EOF.
*/
static char config_buffer[] = "0 5 5";

/**
 * @brief Flag detemining if the application is in window mode or not.
*/
static int32_t is_fullscreen = 0L;

/**
 * @brief Volume at which the music will be played.
*/
static int32_t music_volume = 5L;

/**
 * @brief Volume at which the sound effects will be played.
*/
static int32_t sound_fx_volume = 5L;

/***********************************************************************************************************************
 * FUNCTION DEFINITIONS                                                                                                *
 **********************************************************************************************************************/

void pers_config_read(void)
{
	FILE*   file       = NULL;
	errno_t error_code = 0L;

	plog_debug(LOG_PREFIX "Reading from \"%s\". (default config buffer: %s).", CONFIG_FILE_NAME, config_buffer);

	error_code = fopen_s(&file, CONFIG_FILE_NAME, "r");
	if (0L != error_code)
	{
		plog_error(LOG_PREFIX "Failed to open \"%s\" in read mode! (error code: %" PRId32 ")", CONFIG_FILE_NAME, error_code);
		return;
	}

	fgets(config_buffer, sizeof(config_buffer), file);

	error_code = fclose(file);
	if (0L != error_code)
	{
		plog_warn(LOG_PREFIX "Failed to close \"%s\"! (error code: %" PRId32 ")", CONFIG_FILE_NAME, error_code);
	}

	if ('1' < config_buffer[0] || '0' > config_buffer[0])
	{
		plog_warn(LOG_PREFIX "Fullscreen mode from \"%s\" is not a valid value! (fullscreen mode: %" PRId32 ")", CONFIG_FILE_NAME, (int32_t)config_buffer[0]);
		config_buffer[0] = '0';
	}
	is_fullscreen = config_buffer[0] - '0';

	if ('5' < config_buffer[2] || '0' > config_buffer[2])
	{
		plog_warn(LOG_PREFIX "Music volume from \"%s\" is not a valid value! (music volume: %" PRId32 ")", CONFIG_FILE_NAME, (int32_t)config_buffer[2]);
		config_buffer[1] = '5';
	}
	music_volume = config_buffer[2] - '0';

	if ('5' < config_buffer[4] || '0' > config_buffer[4])
	{
		plog_warn(LOG_PREFIX "Sound effects volume from \"%s\" is not a valid value! (sound effects volume: %" PRId32 ")", CONFIG_FILE_NAME, (int32_t)config_buffer[4]);
		config_buffer[4] = '5';
	}
	sound_fx_volume = config_buffer[4] - '0';

	plog_info(LOG_PREFIX "Config buffer read! (config buffer: %s)", config_buffer);
}

void pers_config_write(void)
{
	FILE*   file       = NULL;
	errno_t error_code = 0L;

	plog_debug(LOG_PREFIX "Writing in \"%s\". (config buffer: %s)", CONFIG_FILE_NAME, config_buffer);

	error_code = fopen_s(&file, CONFIG_FILE_NAME, "w");
	if (0L != error_code)
	{
		plog_error(LOG_PREFIX "Failed to open %s in write mode! (error code: %" PRId32 ")", CONFIG_FILE_NAME, error_code);
		return;
	}

	error_code = fputs(config_buffer, file);
	if (0 > error_code)
	{
		plog_error(LOG_PREFIX "Failed to write in \"%s\"! (error code: %" PRId32 ")", CONFIG_FILE_NAME, error_code);
	}

	error_code = fclose(file);
	if (0L != error_code)
	{
		plog_warn(LOG_PREFIX "Failed to close \"%s\"! (error code: %" PRId32 ")", CONFIG_FILE_NAME, error_code);
	}
}

int32_t pers_config_get_is_fullscreen(void)
{
	plog_debug(LOG_PREFIX "Getting fullscreen mode. (fullscreen mode: %" PRId32 ")", is_fullscreen);
	return is_fullscreen;
}

void pers_config_set_is_fullscreen(int32_t is_fullscreen_to_be_set)
{
	plog_trace(LOG_PREFIX "Setting fullscreen mode! (fullscreen mode: %" PRId32 ")", is_fullscreen_to_be_set);
	if (0L == is_fullscreen_to_be_set)
	{
		config_buffer[0] = '0';
	}
	else
	{
		config_buffer[0] = '1';
	}
	plog_info(LOG_PREFIX "Fullscreen mode set! (fullscreen mode: %" PRId32 ")", is_fullscreen_to_be_set);
	is_fullscreen = is_fullscreen_to_be_set;
}

int32_t pers_config_get_music_volume(void)
{
	plog_debug(LOG_PREFIX "Getting music volume. (music volume: %" PRId32 ")", music_volume);
	return music_volume;
}

void pers_config_set_music_volume(int32_t music_volume_to_be_set)
{
	plog_trace(LOG_PREFIX "Setting music volume! (music volume: %" PRId32 ")", music_volume_to_be_set);
	if (0L > music_volume_to_be_set || 5L < music_volume_to_be_set)
	{
		plog_error(LOG_PREFIX "Invalid volume! (music volume: %" PRId32 ")", music_volume_to_be_set);
		return;
	}

	plog_info(LOG_PREFIX "Music volume set! (music volume: %" PRId32 ")", music_volume_to_be_set);
	config_buffer[2] = music_volume_to_be_set + '0';
	music_volume     = music_volume_to_be_set;
}

int32_t pers_config_get_sound_fx_volume(void)
{
	plog_debug(LOG_PREFIX "Getting sound effects volume. (sound effects volume: %" PRId32 ")", sound_fx_volume);
	return sound_fx_volume;
}

void pers_config_set_sound_fx_volume(int32_t sound_fx_volume_to_be_set)
{
	plog_trace(LOG_PREFIX "Setting sound effects volume! (sound effects volume: %" PRId32 ")", sound_fx_volume_to_be_set);
	if (0L > sound_fx_volume_to_be_set || 5L < sound_fx_volume_to_be_set)
	{
		plog_error(LOG_PREFIX "Invalid volume! (sound effects volume: %" PRId32 ")", sound_fx_volume_to_be_set);
		return;
	}

	plog_info(LOG_PREFIX "Sound effects volume set! (sound effects volume: %" PRId32 ")", sound_fx_volume_to_be_set);
	config_buffer[4] = sound_fx_volume_to_be_set + '0';
	sound_fx_volume  = sound_fx_volume_to_be_set;
}
