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
 *****************************************************************************************************/

#ifndef HOB_TEXTURE_MOCK_HPP_
#define HOB_TEXTURE_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <gmock/gmock.h>

#include "hob_Texture.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

class TextureDummy
{
public:
	virtual ~TextureDummy(void) = default;

	virtual void load(const std::string& filePath, SDL_Renderer* renderer) = 0;
	virtual hob::Coordinate create(std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) = 0;
	virtual void destroy(void) = 0;
	virtual SDL_Texture* getRawTexture(void) = 0;
};

class TextureMock : public TextureDummy
{
public:
	TextureMock(void)
	{
		textureMock = this;
	}

	virtual ~TextureMock(void)
	{
		textureMock = nullptr;
	}

	MOCK_METHOD2(load, void(const std::string&, SDL_Renderer*));
	MOCK_METHOD4(create, hob::Coordinate(std::string, TTF_Font*, SDL_Color, SDL_Renderer*));
	MOCK_METHOD0(destroy, void(void));
	MOCK_METHOD0(getRawTexture, SDL_Texture*(void));

public:
	static TextureMock* textureMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES                                                                                    *
 *****************************************************************************************************/

TextureMock* TextureMock::textureMock = nullptr;

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Texture::Texture(void) noexcept
	: rawTexture{ nullptr }
{
}

Texture::Texture(const std::string filePath, SDL_Renderer* const renderer) noexcept
	: rawTexture{ nullptr }
{
}

Texture::~Texture(void) noexcept
{
}

void Texture::load(const std::string& filePath, SDL_Renderer* const renderer) noexcept
{
	ASSERT_NE(nullptr, TextureMock::textureMock) << "load(): nullptr == TextureMock::textureMock";
	TextureMock::textureMock->load(filePath, renderer);
}

Coordinate Texture::create(const std::string text, TTF_Font* const font, const SDL_Color color, SDL_Renderer* const renderer) noexcept
{
	if (nullptr == TextureMock::textureMock)
	{
		ADD_FAILURE() << "create(): nullptr == TextureMock::textureMock";
		return (Coordinate){ 0, 0 };
	}
	return TextureMock::textureMock->create(text, font, color, renderer);
}

void Texture::destroy(void) noexcept
{
	ASSERT_NE(nullptr, TextureMock::textureMock) << "destroy(): nullptr == TextureMock::textureMock";
	TextureMock::textureMock->destroy();
}

SDL_Texture* Texture::getRawTexture(void) const noexcept
{
	if (nullptr == TextureMock::textureMock)
	{
		ADD_FAILURE() << "getRawTexture(): nullptr == TextureMock::textureMock";
		return nullptr;
	}
	return TextureMock::textureMock->getRawTexture();
}

}

#endif /*< HOB_TEXTURE_MOCK_HPP_ */
