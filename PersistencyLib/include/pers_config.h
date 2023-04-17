/** @file pers_config.h
 *  @brief Part of the persistency lib's public API consisting of function prototypes that involve operations over the configuration
 * file.
 *
 *  @author Gaina Stefan!
 *  @bug No known bugs.
 */

#ifndef PERS_CONFIG_H_
#define PERS_CONFIG_H_

/***********************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                *
 **********************************************************************************************************************/

#include "stdint.h"

/***********************************************************************************************************************
 * FUNCTION PROTOTYPES                                                                                                 *
 **********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Reads from the configuration file (pers/config).
 * @param void
 * @return void
*/
extern void pers_config_read(void);

/**
 * @brief Writes the updates to the configuration file (pers/config).
 * @param void
 * @return void
*/
extern void pers_config_write(void);

/**
 * @brief Queries the fullscreen mode.
 * @param void
 * @return 0 - Window mode | otherwise - Fullscreen mode.
*/
extern int32_t pers_config_get_is_fullscreen(void);

/**
 * @brief Sets the fullscreen mode.
 * @param is_fullscreen_to_be_set: 0 - Window mode | otherwise - Fullscreen mode.
 * @return void
*/
extern void pers_config_set_is_fullscreen(int32_t is_fullscreen_to_be_set);

/**
 * @brief Queries the music volume.
 * @param void
 * @return The volume at which the music should be playing (values between 0 - muted and 5 - maximum).
*/
extern int32_t pers_config_get_music_volume(void);

/**
 * @brief Sets the music volume.
 * @param music_volume_to_be_set: the volume at which the music should be playing (values between 0 - muted and 5 - maximum).
 * @return void
*/
extern void pers_config_set_music_volume(int32_t music_volume_to_be_set);

/**
 * @brief Queries the sound effects volume.
 * @param void
 * @return The volume at which the sound effects should be playing (values between 0 - muted and 5 - maximum).
*/
extern int32_t pers_config_get_sound_fx_volume(void);

/**
 * @brief Sets the sound effects volume.
 * @param sound_effects_volume_to_be_set - the desired volume at which the sound effects will be played (values between 0 - muted 
 * and 5 - maximum).
 * @return void
*/
extern void pers_config_set_sound_fx_volume(int32_t sound_fx_volume_to_be_set);

#ifdef __cplusplus
}
#endif

#endif /*< PERS_CONFIG_H_ */
