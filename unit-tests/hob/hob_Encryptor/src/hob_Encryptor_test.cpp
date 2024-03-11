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
 * @file hob_Encryptor_test.cpp
 * @author Gaina Stefan
 * @date 10.02.2024
 * @brief This file unit-tests hob_Encryptor.cpp.
 * @details Current coverage report:
 * <ul>
 * <li> Line coverage: 100.0% (25/26) </li>
 * <li> Functions:     100.0% (5/5)   </li>
 * <li> Branches:      100.0% (3/4)   </li>
 * </ul>
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "hob_Socket_mock.hpp"
#include "obfuscator_mock.hpp"
#include "hob_Encryptor.hpp"

/******************************************************************************************************
 * TEST CLASS
 *****************************************************************************************************/

class EncryptorTest : public testing::Test
{
public:
	EncryptorTest(void)
		: socketMock{}
		, obfuscatorMock{}
	{
	}

public:
	SocketMock	   socketMock;
	ObfuscatorMock obfuscatorMock;
};

/******************************************************************************************************
 * receivedKey
 *****************************************************************************************************/

TEST_F(EncryptorTest, receivedKey_success)
{
	hob::Encryptor encryptor = {};
	hob::Socket	   socket	 = {};

	EXPECT_CALL(obfuscatorMock, obfuscator_get_base()) /**/
		.WillOnce(testing::Return(2UL));
	EXPECT_CALL(obfuscatorMock, obfuscator_get_prime_modulus()) /**/
		.Times(3)
		.WillRepeatedly(testing::Return(2UL));
	EXPECT_CALL(socketMock, sendUpdate(testing::_));
	EXPECT_CALL(obfuscatorMock, obfuscator_update_key(testing::_)) /**/
		.Times(2);

	encryptor.receivedKey(0UL, socket);
	encryptor.receivedKey(0UL, socket);
}

/******************************************************************************************************
 * encryptMessage
 *****************************************************************************************************/

TEST_F(EncryptorTest, encryptMessage_success)
{
	hob::Encryptor encryptor = {};
	char		   message[] = "dummy";

	EXPECT_CALL(obfuscatorMock, obfuscate_string(testing::_, testing::_));
	EXPECT_CALL(obfuscatorMock, obfuscator_update_key(testing::_));

	encryptor.encryptMessage(message);
}

/******************************************************************************************************
 * decryptMessage
 *****************************************************************************************************/

TEST_F(EncryptorTest, decryptMessage_success)
{
	hob::Encryptor encryptor = {};
	char		   message[] = "dummy";

	EXPECT_CALL(obfuscatorMock, deobfuscate_string(testing::_, testing::_));
	EXPECT_CALL(obfuscatorMock, obfuscator_update_key(testing::_));

	encryptor.decryptMessage(message);
}
