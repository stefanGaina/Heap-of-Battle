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

#ifndef STL_STRING_MOCK_HPP_
#define STL_STRING_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>

#include "stl_string_begin.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace std
{

class string
{
public:
	string(void)			 = default;
	string(string&& string_) = default;

	string(string& string_) noexcept(false);
	void operator=(const string& string_) noexcept(false);
};

string operator+(const string& string_, const char* cstring) noexcept(false);

string to_string(int __val) noexcept;

} /*< namespace std */

class StlStringDummy
{
public:
	virtual ~StlStringDummy(void) = default;

	virtual void		copyConstructor(std::string& string_)						  = 0;
	virtual std::string operatorPlus(const std::string& string_, const char* cstring) = 0;
	virtual void		operatorEqual(const std::string& string_)					  = 0;
	virtual std::string to_string(int __val)										  = 0;
};

class StlStringMock : public StlStringDummy
{
public:
	StlStringMock(void)
	{
		stlStringMock = this;
	}

	virtual ~StlStringMock(void)
	{
		stlStringMock = nullptr;
	}

	MOCK_METHOD1(copyConstructor, void(std::string&));
	MOCK_METHOD2(operatorPlus, std::string(const std::string&, const char*));
	MOCK_METHOD1(operatorEqual, void(const std::string&));
	MOCK_METHOD1(to_string, std::string(int));

public:
	static StlStringMock* stlStringMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

StlStringMock* StlStringMock::stlStringMock = nullptr;

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace std
{

string::string(string& string_) noexcept(false)
{
	if (nullptr == StlStringMock::stlStringMock)
	{
		ADD_FAILURE() << "copyConstructor(): nullptr == StlStringMock::stlStringMock";
		return;
	}
	StlStringMock::stlStringMock->copyConstructor(string_);
}

void string::operator=(const string& string_) noexcept(false)
{
	ASSERT_NE(nullptr, StlStringMock::stlStringMock) << "operatorEqual(): nullptr == StlStringMock::stlStringMock";
	return StlStringMock::stlStringMock->operatorEqual(string_);
}

string operator+(const string& string_, const char* const cstring) noexcept(false)
{
	if (nullptr == StlStringMock::stlStringMock)
	{
		ADD_FAILURE() << "operatorPlus(): nullptr == StlStringMock::stlStringMock";
		return (string){};
	}
	return StlStringMock::stlStringMock->operatorPlus(string_, cstring);
}

string to_string(const int __val) noexcept
{
	if (nullptr == StlStringMock::stlStringMock)
	{
		ADD_FAILURE() << "to_string(): nullptr == StlStringMock::stlStringMock";
		return (string){};
	}
	return StlStringMock::stlStringMock->to_string(__val);
}

} /*< namespace std */

#include "stl_string_end.hpp"

#endif /*< STL_STRING_MOCK_HPP_ */
