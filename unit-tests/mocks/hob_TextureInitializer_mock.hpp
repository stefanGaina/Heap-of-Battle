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

#ifndef HOB_TEXTURE_INITIALIZER_MOCK_HPP_
#define HOB_TEXTURE_INITIALIZER_MOCK_HPP_

#ifdef HOB_TEXTURE_INITIALIZER_HPP_
#error "hob_TextureInitializer_mock.hpp is included after hob_TextureInitializer.hpp"
#else
#define HOB_TEXTURE_INITIALIZER_HPP_
#endif /*< HOB_TEXTURE_INITIALIZER_HPP_ */

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <array>
#include <plog.h>
#include <gmock/gmock.h>

#include "hob_IDrawable.hpp"
#include "hob_Texture_mock.hpp"
#include "hob_Component_mock.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

template <size_t TEXTURES_COUNT, size_t COMPONENTS_COUNT>
class TextureInitializer : public hob::IDrawable
{
public:
	TextureInitializer(std::array<std::string, TEXTURES_COUNT> filePaths, std::array<size_t, COMPONENTS_COUNT> textureIndexes,
		std::array<SDL_Rect, COMPONENTS_COUNT> destinations, SDL_Renderer* renderer) noexcept;
	virtual ~TextureInitializer(void) = default;

	virtual void draw(SDL_Renderer* renderer) noexcept override;

protected:
	std::array<hob::Component, COMPONENTS_COUNT> componentContainer;
	std::array<hob::Texture, TEXTURES_COUNT> textureContainer;
};

} /*< namespace hob */

class TextureInitializerDummy
{
public:
	virtual ~TextureInitializerDummy(void) = default;

	virtual void draw(SDL_Renderer* renderer) = 0;
};

class TextureInitializerMock : public TextureInitializerDummy
{
public:
	TextureInitializerMock(void)
	{
		textureInitializerMock = this;
	}

	virtual ~TextureInitializerMock(void)
	{
		textureInitializerMock = nullptr;
	}

	MOCK_METHOD1(draw, void(SDL_Renderer*));

public:
	static TextureInitializerMock* textureInitializerMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

TextureInitializerMock* TextureInitializerMock::textureInitializerMock = nullptr;

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

template <size_t TEXTURES_COUNT, size_t COMPONENTS_COUNT>
TextureInitializer<TEXTURES_COUNT, COMPONENTS_COUNT>::TextureInitializer(const std::array<std::string, TEXTURES_COUNT> filePaths,
	const std::array<size_t, COMPONENTS_COUNT> textureIndexes, const std::array<SDL_Rect, COMPONENTS_COUNT> destinations, SDL_Renderer* const renderer) noexcept
{
}

template <size_t TEXTURES_COUNT, size_t COMPONENTS_COUNT>
void TextureInitializer<TEXTURES_COUNT, COMPONENTS_COUNT>::draw(SDL_Renderer* const renderer) noexcept
{
	ASSERT_NE(nullptr, TextureInitializerMock::textureInitializerMock) << "draw(): nullptr == TextureInitializerMock::textureInitializerMock";
	TextureInitializerMock::textureInitializerMock->draw(renderer);
}

} /*< namespace hob */

#endif /*< HOB_TEXTURE_INITIALIZER_MOCK_HPP_ */
