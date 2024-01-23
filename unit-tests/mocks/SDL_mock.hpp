/******************************************************************************************************
 * Heap of Battle Copyright (C) 2024                                                                  *
 *                                                                                                    *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the   *
 * authors be held liable for any damages arising from the use of this software.                      *
 *                                                                                                    *
 * Permission is granted to anyone to use this software for any purpose, including commercial         *
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:   *
 *                                                                                                    *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the   *
 *    original software. If you use this software in a product, an acknowledgment in the product      *
 *    documentation would be appreciated but is not required.                                         *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being *
 *    the original software.                                                                          *
 * 3. This notice may not be removed or altered from any source distribution.                         *
******************************************************************************************************/

#ifndef SDL_MOCK_HPP_
#define SDL_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <gmock/gmock.h>
#include <SDL2/SDL.h>

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

class SDL
{
public:
	virtual ~SDL(void) = default;

	virtual void SDL_GetVersion(SDL_version* ver) = 0;
	virtual int SDL_Init(Uint32 flags) = 0;
	virtual const char* SDL_GetError(void) = 0;
	virtual void SDL_DestroyRenderer(SDL_Renderer* renderer) = 0;
	virtual SDL_Window* SDL_CreateWindow(const char* title, int x, int y, int w, int h, Uint32 flags) = 0;
	virtual SDL_Renderer* SDL_CreateRenderer(SDL_Window* window, int index, Uint32 flags) = 0;
	virtual int SDL_SetRenderDrawBlendMode(SDL_Renderer* renderer, SDL_BlendMode blendMode) = 0;
	virtual int SDL_SetRenderDrawColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) = 0;
	virtual void SDL_DestroyWindow(SDL_Window* window) = 0;
	virtual SDL_Texture* SDL_CreateTextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface) = 0;
	virtual void SDL_FreeSurface(SDL_Surface* surface) = 0;
	virtual void SDL_DestroyTexture(SDL_Texture* texture) = 0;
	virtual SDL_RWops* SDL_RWFromFile(const char* file, const char* mode) = 0;
	virtual int SDL_RenderCopy(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect) = 0;
	virtual int SDL_ShowCursor(int toggle) = 0;
};

class SDLMock : public SDL
{
public:
	SDLMock(void)
	{
		sdlMock = this;
	}

	virtual ~SDLMock(void)
	{
		sdlMock = nullptr;
	}

	MOCK_METHOD1(SDL_GetVersion, void(SDL_version*));
	MOCK_METHOD1(SDL_Init, int(Uint32));
	MOCK_METHOD0(SDL_GetError, const char*(void));
	MOCK_METHOD1(SDL_DestroyRenderer, void(SDL_Renderer*));
	MOCK_METHOD6(SDL_CreateWindow, SDL_Window*(const char*, int, int, int, int, Uint32));
	MOCK_METHOD3(SDL_CreateRenderer, SDL_Renderer*(SDL_Window*, int, Uint32));
	MOCK_METHOD2(SDL_SetRenderDrawBlendMode, int(SDL_Renderer*, SDL_BlendMode));
	MOCK_METHOD5(SDL_SetRenderDrawColor, int(SDL_Renderer*, Uint8, Uint8, Uint8, Uint8));
	MOCK_METHOD1(SDL_DestroyWindow, void(SDL_Window*));
	MOCK_METHOD2(SDL_CreateTextureFromSurface, SDL_Texture*(SDL_Renderer*, SDL_Surface*));
	MOCK_METHOD1(SDL_FreeSurface, void(SDL_Surface*));
	MOCK_METHOD1(SDL_DestroyTexture, void(SDL_Texture*));
	MOCK_METHOD2(SDL_RWFromFile, SDL_RWops*(const char*, const char*));
	MOCK_METHOD4(SDL_RenderCopy, int(SDL_Renderer*, SDL_Texture*, const SDL_Rect*, const SDL_Rect*));
	MOCK_METHOD1(SDL_ShowCursor, int(int));

public:
	static SDLMock* sdlMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES                                                                                    *
 *****************************************************************************************************/

SDLMock* SDLMock::sdlMock = nullptr;

/******************************************************************************************************
 * FUNCTION DEFINITIONS                                                                               *
 *****************************************************************************************************/

extern "C" {

void SDL_GetVersion(SDL_version* const ver)
{
	ASSERT_NE(nullptr, SDLMock::sdlMock) << "SDL_GetVersion(): nullptr == SDLMock::sdlMock";
	SDLMock::sdlMock->SDL_GetVersion(ver);
}

int SDL_Init(const Uint32 flags)
{
	if (nullptr == SDLMock::sdlMock)
	{
		ADD_FAILURE() << "SDL_Init(): nullptr == SDLMock::sdlMock";
		return -1;
	}
	return SDLMock::sdlMock->SDL_Init(flags);
}

const char* SDL_GetError(void)
{
	if (nullptr == SDLMock::sdlMock)
	{
		ADD_FAILURE() << "SDL_GetError(): nullptr == SDLMock::sdlMock";
		return nullptr;
	}
	return SDLMock::sdlMock->SDL_GetError();
}

void SDL_DestroyRenderer(SDL_Renderer* const renderer)
{
	ASSERT_NE(nullptr, SDLMock::sdlMock) << "SDL_DestroyRenderer(): nullptr == SDLMock::sdlMock";
	SDLMock::sdlMock->SDL_DestroyRenderer(renderer);
}

SDL_Window* SDL_CreateWindow(const char* const title, const int x, const int y, const int w, const int h, const Uint32 flags)
{
	if (nullptr == SDLMock::sdlMock)
	{
		ADD_FAILURE() << "SDL_CreateWindow(): nullptr == SDLMock::sdlMock";
		return nullptr;
	}
	return SDLMock::sdlMock->SDL_CreateWindow(title, x, y, w, h, flags);
}

SDL_Renderer* SDL_CreateRenderer(SDL_Window* const window, const int index, const Uint32 flags)
{
	if (nullptr == SDLMock::sdlMock)
	{
		ADD_FAILURE() << "SDL_CreateRenderer(): nullptr == SDLMock::sdlMock";
		return nullptr;
	}
	return SDLMock::sdlMock->SDL_CreateRenderer(window, index, flags);
}

int SDL_SetRenderDrawBlendMode(SDL_Renderer* const renderer, const SDL_BlendMode blendMode)
{
	if (nullptr == SDLMock::sdlMock)
	{
		ADD_FAILURE() << "SDL_SetRenderDrawBlendMode(): nullptr == SDLMock::sdlMock";
		return -1;
	}
	return SDLMock::sdlMock->SDL_SetRenderDrawBlendMode(renderer, blendMode);
}

int SDL_SetRenderDrawColor(SDL_Renderer* const renderer, const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
	if (nullptr == SDLMock::sdlMock)
	{
		ADD_FAILURE() << "SDL_SetRenderDrawColor(): nullptr == SDLMock::sdlMock";
		return -1;
	}
	return SDLMock::sdlMock->SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void SDL_DestroyWindow(SDL_Window* const window)
{
	ASSERT_NE(nullptr, SDLMock::sdlMock) << "SDL_DestroyWindow(): nullptr == SDLMock::sdlMock";
	SDLMock::sdlMock->SDL_DestroyWindow(window);
}

SDL_Texture* SDL_CreateTextureFromSurface(SDL_Renderer* const renderer, SDL_Surface* const surface)
{
	if (nullptr == SDLMock::sdlMock)
	{
		ADD_FAILURE() << "SDL_CreateTextureFromSurface(): nullptr == SDLMock::sdlMock";
		return nullptr;
	}
	return SDLMock::sdlMock->SDL_CreateTextureFromSurface(renderer, surface);
}

void SDL_FreeSurface(SDL_Surface* const surface)
{
	ASSERT_NE(nullptr, SDLMock::sdlMock) << "SDL_FreeSurface(): nullptr == SDLMock::sdlMock";
	SDLMock::sdlMock->SDL_FreeSurface(surface);
}

void SDL_DestroyTexture(SDL_Texture* const texture)
{
	ASSERT_NE(nullptr, SDLMock::sdlMock) << "SDL_DestroyTexture(): nullptr == SDLMock::sdlMock";
	SDLMock::sdlMock->SDL_DestroyTexture(texture);
}

SDL_RWops* SDL_RWFromFile(const char* const file, const char* const mode)
{
	if (nullptr == SDLMock::sdlMock)
	{
		ADD_FAILURE() << "SDL_RWFromFile(): nullptr == SDLMock::sdlMock";
		return nullptr;
	}
	return SDLMock::sdlMock->SDL_RWFromFile(file, mode);
}

int SDL_RenderCopy(SDL_Renderer* const renderer, SDL_Texture* const texture, const SDL_Rect* const srcrect, const SDL_Rect* const dstrect)
{
	if (nullptr == SDLMock::sdlMock)
	{
		ADD_FAILURE() << "SDL_RenderCopy(): nullptr == SDLMock::sdlMock";
		return -1;
	}
	return SDLMock::sdlMock->SDL_RenderCopy(renderer, texture, srcrect, dstrect);
}

int SDL_ShowCursor(const int toggle)
{
	if (nullptr == SDLMock::sdlMock)
	{
		ADD_FAILURE() << "SDL_ShowCursor(): nullptr == SDLMock::sdlMock";
		return -1;
	}
	return SDLMock::sdlMock->SDL_ShowCursor(toggle);
}

}

#endif /*< SDL_MOCK_HPP_ */
