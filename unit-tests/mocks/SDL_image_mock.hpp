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

#ifndef SDL_IMAGE_MOCK_HPP_
#define SDL_IMAGE_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>
#include <SDL2/SDL_image.h>

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

class IMG
{
public:
	virtual ~IMG(void) = default;

	virtual const SDL_version* IMG_Linked_Version(void)	  = 0;
	virtual int				   IMG_Init(int flags)		  = 0;
	virtual void			   IMG_Quit(void)			  = 0;
	virtual SDL_Surface*	   IMG_Load(const char* file) = 0;
};

class IMGMock : public IMG
{
public:
	IMGMock(void)
	{
		imgMock = this;
	}

	virtual ~IMGMock(void)
	{
		imgMock = nullptr;
	}

	MOCK_METHOD0(IMG_Linked_Version, const SDL_version*(void));
	MOCK_METHOD1(IMG_Init, int(int));
	MOCK_METHOD0(IMG_Quit, void(void));
	MOCK_METHOD1(IMG_Load, SDL_Surface*(const char*));

public:
	static IMGMock* imgMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

IMGMock* IMGMock::imgMock = nullptr;

/******************************************************************************************************
 * FUNCTION DEFINITIONS
 *****************************************************************************************************/

extern "C" {

const SDL_version* IMG_Linked_Version(void)
{
	if (nullptr == IMGMock::imgMock)
	{
		ADD_FAILURE() << "IMG_Linked_Version(): nullptr == IMGMock::imgMock";
		return nullptr;
	}
	return IMGMock::imgMock->IMG_Linked_Version();
}

int IMG_Init(const int flags)
{
	if (nullptr == IMGMock::imgMock)
	{
		ADD_FAILURE() << "IMG_Init(): nullptr == IMGMock::imgMock";
		return -1;
	}
	return IMGMock::imgMock->IMG_Init(flags);
}

void IMG_Quit(void)
{
	ASSERT_NE(nullptr, IMGMock::imgMock) << "IMG_Quit(): nullptr == IMGMock::imgMock";
	IMGMock::imgMock->IMG_Quit();
}

SDL_Surface* IMG_Load(const char* const file)
{
	if (nullptr == IMGMock::imgMock)
	{
		ADD_FAILURE() << "IMG_Load(): nullptr == IMGMock::imgMock";
		return nullptr;
	}
	return IMGMock::imgMock->IMG_Load(file);
}
}

#endif /*< SDL_IMAGE_MOCK_HPP_ */
