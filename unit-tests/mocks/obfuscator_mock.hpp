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

#ifndef OBFUSCATOR_MOCK_HPP_
#define OBFUSCATOR_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>
#include <obfuscator.h>

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

class Obfuscator
{
public:
	virtual ~Obfuscator(void) = default;

	virtual void obfuscate_string(char* message, uint64_t key) = 0;
	virtual void deobfuscate_string(char* message, uint64_t key) = 0;
	virtual void obfuscator_update_key(uint64_t* key) = 0;
	virtual uint64_t obfuscator_get_prime_modulus(void) = 0;
	virtual uint64_t obfuscator_get_base(void) = 0;
};

class ObfuscatorMock : public Obfuscator
{
public:
	ObfuscatorMock(void)
	{
		obfuscatorMock = this;
	}

	virtual ~ObfuscatorMock(void)
	{
		obfuscatorMock = nullptr;
	}

	MOCK_METHOD2(obfuscate_string, void(char*, uint64_t));
	MOCK_METHOD2(deobfuscate_string, void(char*, uint64_t));
	MOCK_METHOD1(obfuscator_update_key, void(uint64_t*));
	MOCK_METHOD0(obfuscator_get_prime_modulus, uint64_t(void));
	MOCK_METHOD0(obfuscator_get_base, uint64_t(void));

public:
	static ObfuscatorMock* obfuscatorMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

ObfuscatorMock* ObfuscatorMock::obfuscatorMock = nullptr;

/******************************************************************************************************
 * FUNCTION DEFINITIONS
 *****************************************************************************************************/

extern "C" {

void obfuscate_string(char* const message, const uint64_t key)
{
	ASSERT_NE(nullptr, ObfuscatorMock::obfuscatorMock) << "obfuscate_string(): nullptr == ObfuscatorMock::obfuscatorMock";
	ObfuscatorMock::obfuscatorMock->obfuscate_string(message, key);
}

void deobfuscate_string(char* const message, const uint64_t key)
{
	ASSERT_NE(nullptr, ObfuscatorMock::obfuscatorMock) << "deobfuscate_string(): nullptr == ObfuscatorMock::obfuscatorMock";
	ObfuscatorMock::obfuscatorMock->deobfuscate_string(message, key);
}

void obfuscator_update_key(uint64_t* const key)
{
	ASSERT_NE(nullptr, ObfuscatorMock::obfuscatorMock) << "obfuscator_update_key(): nullptr == ObfuscatorMock::obfuscatorMock";
	ObfuscatorMock::obfuscatorMock->obfuscator_update_key(key);
}

uint64_t obfuscator_get_prime_modulus(void)
{
	if (nullptr == ObfuscatorMock::obfuscatorMock)
	{
		ADD_FAILURE() << "obfuscator_get_prime_modulus(): nullptr == ObfuscatorMock::obfuscatorMock";
		return 0UL;
	}
	return ObfuscatorMock::obfuscatorMock->obfuscator_get_prime_modulus();
}

uint64_t obfuscator_get_base(void)
{
	if (nullptr == ObfuscatorMock::obfuscatorMock)
	{
		ADD_FAILURE() << "obfuscator_get_base(): nullptr == ObfuscatorMock::obfuscatorMock";
		return 0UL;
	}
	return ObfuscatorMock::obfuscatorMock->obfuscator_get_base();
}

}

#endif /*< OBFUSCATOR_MOCK_HPP_ */
