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
 * @file hob_Encryptor.cpp
 * @author Gaina Stefan
 * @date 09.02.2024
 * @brief This file implements the class defined in hob_Encryptor.hpp.
 * @todo Consider changing the clock_gettime() call which can return an error to a C++ way of getting
 * a random number.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <ctime>
#include <cmath>
#include <plog.h>
#include <obfuscator.h>

#include "hob_Encryptor.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

void Encryptor::sendKey(const Socket& socket) noexcept
{
	const uint64_t     base       = obfuscator_get_base();
	hobServer::Message keyMessage = { .type = hobServer::MessageType::ENCRYPT_KEY, .payload = {} };
	struct timespec    time       = {};

	plog_debug("The public key is being sent.");
	plog_assert(0UL == privateKey);
	plog_assert(0UL == exponent);

	if (0 != clock_gettime(CLOCK_MONOTONIC, &time))
	{
		plog_warn("Failed to get random exponent! (error message: %s)", strerror(errno));
		time.tv_nsec = 0x0123456789ABCDEFL;
	}

	exponent                      = static_cast<uint64_t>(time.tv_nsec) % base;
	keyMessage.payload.encryptKey = diffieHellmanKey(base);
	socket.sendUpdate(keyMessage);
}

void Encryptor::receivedKey(const uint64_t enemyKey, const Socket& socket) noexcept
{
	plog_debug("Received the enemy key. (key: %" PRIu64 ")", enemyKey);
	if (0UL == exponent)
	{
		sendKey(socket);
	}

	privateKey = diffieHellmanKey(enemyKey);
	obfuscator_update_key(&privateKey);
}

void Encryptor::encryptMessage(char* const message) noexcept
{
	plog_trace("Encrypting the message. (message: %s)", message);
	plog_assert(nullptr != message);
	plog_assert(0UL != privateKey);

	obfuscate_string(message, privateKey);
	obfuscator_update_key(&privateKey);
}

void Encryptor::decryptMessage(char* const message) noexcept
{
	plog_trace("Decrypting the message. (message: %s)", message);
	plog_assert(nullptr != message);
	plog_assert(0UL != privateKey);

	deobfuscate_string(message, privateKey);
	obfuscator_update_key(&privateKey);
}

uint64_t Encryptor::diffieHellmanKey(const uint64_t base) const noexcept
{
	plog_verbose("Getting the Diffie-Hellan key. (base: %" PRIu64 ")", base);
	return static_cast<uint64_t>(pow(static_cast<double>(base), static_cast<double>(exponent))) % obfuscator_get_prime_modulus();
}

} /*< namespace hob */
