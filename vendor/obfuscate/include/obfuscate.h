#ifndef OBFUSCATE_H_
#define OBFUSCATE_H_

/***********************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                *
 **********************************************************************************************************************/

#include <stdint.h>

/***********************************************************************************************************************
 * FUNCTION PROTOTYPES                                                                                                 *
 **********************************************************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Obfuscates a string based on the hour and minute when the message will be sent.
 * @param[in|out] out_message: buffer of message that will be obfuscated.
 * @param hour: hour when the message will be sent.
 * @param minute: minute when the message will be sent.
 * @return void
 */
extern void obfuscate_string(char* out_message, uint8_t hour, uint8_t minute);

/**
 * @brief Obfuscates a string based on the hour and minute when the message was sent.
 * @param[in|out] out_message: buffer of message that will be deobfuscated.
 * @param hour: hour when the message was sent.
 * @param minute: minute when the message was sent.
 * @return void
 */
extern void deobfuscate_string(char* out_message, uint8_t hour, uint8_t minute);

#ifdef __cplusplus
}
#endif

#endif /*< OBFUSCATE_H_ */
