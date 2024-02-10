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
 * @file hob_Encryptor.hpp
 * @author Gaina Stefan
 * @date 09.02.2024
 * @brief This file defines the class and method prototypes of the encryptor.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_ENCRYPTOR_HPP_
#define HOB_ENCRYPTOR_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "hob_Socket.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

/** ***************************************************************************************************
 * @brief Common class allowing for messages to be encrypted and decrypted.
 * @details This feature is associated to the chat. The host (or the Alliance player) sends its
 * private key and the other player sends one back. With the help of the Diffie-Hellman key
 * exchange (https://en.wikipedia.org/wiki/Diffie%E2%80%93Hellman_key_exchange) both players now
 * have a common key (not known to a middle man) which is used by libobfuscator.so (private
 * internal HOB library).
 *****************************************************************************************************/
class Encryptor
{
public:
	/** ***********************************************************************************************
	 * @brief Produces a random exponent and generates a private key.
	 * @param socket: Sends the private key to the other player.
	 * @return void
	 *************************************************************************************************/
	void sendKey(const Socket& socket) noexcept;

	/** ***********************************************************************************************
	 * @brief Uses the private key and the key received from the other player and produces the common
	 * key. In the case this is received without sending one generates one first.
	 * @param enemyKey: The key received from the other player.
	 * @param socket: In the case this is received first send the private key back.
	 * @return void
	 *************************************************************************************************/
	void receivedKey(uint64_t enemyKey, const Socket& socket) noexcept;

	/** ***********************************************************************************************
	 * @brief Encrypts a message before sending to the opponent.
	 * @param message: The message to be encrypted.
	 * @return void
	 *************************************************************************************************/
	void encryptMessage(char* message) noexcept;

	/** ***********************************************************************************************
	 * @brief Decrypts a message received from the opponent.
	 * @param message: The message to be decrypted.
	 * @return void
	 *************************************************************************************************/
	void decryptMessage(char* message) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Determines a private key according to Diffie-Hellman key exchange.
	 * @param base: The base which gets raised to the power of exponent and then divided by modulus.
	 * @return The private key.
	 *************************************************************************************************/
	uint64_t diffieHellmanKey(const uint64_t base) const noexcept;

private:
	/** ***********************************************************************************************
	 * @brief The common key resulted from the user private key and the other player private key.
	 *************************************************************************************************/
	uint64_t privateKey;

	/** ***********************************************************************************************
	 * @brief Random number used for generating the private key.
	 *************************************************************************************************/
	uint64_t exponent;
};

} /*< namespace hob */

#endif /*< HOB_ENCRYPTOR_HPP_ */
