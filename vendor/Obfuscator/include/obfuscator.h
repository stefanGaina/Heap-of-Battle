/******************************************************************************************************
 * Heap of Battle Copyright (C) 2024
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the
 * authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
 *    original software. If you use this software in a product, an acknowledgment in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being
 *    the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @file obfuscator.h
 * @author Gaina Stefan
 * @date 08.08.2023
 * @brief This file defines the public interface of <i>Obfuscator</i>.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef OBFUSCATOR_H_
#define OBFUSCATOR_H_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <stdint.h>

/******************************************************************************************************
 * FUNCTION PROTOTYPES
 *****************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/** ***************************************************************************************************
 * @brief Obfuscates a string based on a 64-bit key.
 * @param[in, out] message: Buffer of message that will be obfuscated.
 * @param key: The key used for obfuscating.
 * @return void
 *****************************************************************************************************/
extern void obfuscate_string(char* message, uint64_t key);

/** ***************************************************************************************************
 * @brief Deobfuscates a string based on a 64-bit key.
 * @param[in, out] message: Buffer of message that will be deobfuscated.
 * @param key: The key used for obfuscating.
 * @return void
 *****************************************************************************************************/
extern void deobfuscate_string(char* message, uint64_t key);

/** ***************************************************************************************************
 * @brief Changes the key to mitigate having the same characters obfuscated the same.
 * @param[in, out] key: The key used for obfuscating.
 * @return void
 *****************************************************************************************************/
extern void obfuscator_update_key(uint64_t* key);

/** ***************************************************************************************************
 * @brief Gets the prime modulus for the Diffie-Hellman algorithm. It is wrapped inside a function so
 * the value remains hidden.
 * @param void
 * @return Hard coded prime modulus.
 *****************************************************************************************************/
extern uint64_t obfuscator_get_prime_modulus(void);

/** ***************************************************************************************************
 * @brief Gets the base for the Diffie-Hellman algorithm. It is wrapped inside a function so the value
 * remains hidden.
 * @param void
 * @return Hard coded base.
 *****************************************************************************************************/
extern uint64_t obfuscator_get_base(void);

#ifdef __cplusplus
}
#endif

#endif /*< OBFUSCATOR_H_ */
