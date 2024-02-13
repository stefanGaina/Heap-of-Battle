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

#ifndef SDL_TTF_MOCK_HPP_
#define SDL_TTF_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>
#include <SDL2/SDL_ttf.h>

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

class TTF
{
public:
	virtual ~TTF(void)																				  = default;

	virtual const SDL_version* TTF_Linked_Version(void)												  = 0;
	virtual int				   TTF_Init(void)														  = 0;
	virtual void			   TTF_Quit(void)														  = 0;
	virtual SDL_Surface*	   TTF_RenderText_Blended(TTF_Font* font, const char* text, SDL_Color fg) = 0;
};

class TTFMock : public TTF
{
public:
	TTFMock(void)
	{
		ttfMock = this;
	}

	virtual ~TTFMock(void)
	{
		ttfMock = nullptr;
	}

	MOCK_METHOD0(TTF_Linked_Version, const SDL_version*(void));
	MOCK_METHOD0(TTF_Init, int(void));
	MOCK_METHOD0(TTF_Quit, void(void));
	MOCK_METHOD3(TTF_RenderText_Blended, SDL_Surface*(TTF_Font*, const char*, SDL_Color));

public:
	static TTFMock* ttfMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

TTFMock* TTFMock::ttfMock = nullptr;

/******************************************************************************************************
 * FUNCTION DEFINITIONS
 *****************************************************************************************************/

extern "C"
{

	const SDL_version* TTF_Linked_Version(void)
	{
		if (nullptr == TTFMock::ttfMock)
		{
			ADD_FAILURE() << "TTF_Linked_Version(): nullptr == TTFMock::ttfMock";
			return nullptr;
		}
		return TTFMock::ttfMock->TTF_Linked_Version();
	}

	int TTF_Init(void)
	{
		if (nullptr == TTFMock::ttfMock)
		{
			ADD_FAILURE() << "TTF_Init(): nullptr == TTFMock::ttfMock";
			return -1;
		}
		return TTFMock::ttfMock->TTF_Init();
	}

	void TTF_Quit(void)
	{
		ASSERT_NE(nullptr, TTFMock::ttfMock) << "TTF_Quit(): nullptr == TTFMock::ttfMock";
		TTFMock::ttfMock->TTF_Quit();
	}

	SDL_Surface* TTF_RenderText_Blended(TTF_Font* const font, const char* const text, const SDL_Color fg)
	{
		if (nullptr == TTFMock::ttfMock)
		{
			ADD_FAILURE() << "TTF_RenderText_Blended(): nullptr == TTFMock::ttfMock";
			return nullptr;
		}
		return TTFMock::ttfMock->TTF_RenderText_Blended(font, text, fg);
	}
}

#endif /*< SDL_TTF_MOCK_HPP_ */
