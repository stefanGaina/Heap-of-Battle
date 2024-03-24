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
 * @file hob_Texture_test.cpp
 * @author Gaina Stefan
 * @date 21.01.2024
 * @brief This file unit-tests hob_Texture.cpp.
 * @details Current coverage report:
 * <ul>
 * <li> Line coverage: 100.0% (36/36) </li>
 * <li> Functions:     100.0% (6/6)   </li>
 * <li> Branches:      100.0% (8/8)   </li>
 * </ul>
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "SDL_mock.hpp"
#include "SDL_image_mock.hpp"
#include "SDL_ttf_mock.hpp"
#include "hob_Texture.hpp"

/******************************************************************************************************
 * CONSTANTS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Dummy address to pass the != nulllptr check.
 *****************************************************************************************************/
static constexpr size_t not_nullptr = 0x1UL;

/******************************************************************************************************
 * TEST CLASS
 *****************************************************************************************************/

class TextureTest : public testing::Test
{
public:
	TextureTest(void)
		: sdlMock{}
		, imgMock{}
		, ttfMock{}
	{
	}

public:
	SDLMock sdlMock;
	IMGMock imgMock;
	TTFMock ttfMock;
};

/******************************************************************************************************
 * load
 *****************************************************************************************************/

TEST_F(TextureTest, load_imgLoad_fail)
{
	EXPECT_CALL(imgMock, IMG_Load(testing::_)) /**/
		.WillOnce(testing::Return(nullptr));

	hob::Texture texture = { "test", nullptr };
	EXPECT_EQ(nullptr, texture.getRawTexture()) << "Raw texture is valid even though the loading failed!";
}

TEST_F(TextureTest, load_success)
{
	hob::Texture	  texture = {};
	const std::string string  = "test";

	EXPECT_CALL(imgMock, IMG_Load(testing::_)) /**/
		.WillOnce(testing::Return((SDL_Surface*)not_nullptr));
	EXPECT_CALL(sdlMock, SDL_CreateTextureFromSurface(testing::_, testing::_)) /**/
		.WillOnce(testing::Return((SDL_Texture*)not_nullptr));
	EXPECT_CALL(sdlMock, SDL_FreeSurface(testing::_));

	texture.load("test", nullptr);
	EXPECT_NE(nullptr, texture.getRawTexture()) << "Raw texture is invalid even though the loading succeeded!";

	EXPECT_CALL(sdlMock, SDL_DestroyTexture(testing::_));
}

/******************************************************************************************************
 * create
 *****************************************************************************************************/

TEST_F(TextureTest, create_font_fail)
{
	hob::Texture	texture	  = {};
	hob::Coordinate dimension = {};

	dimension = texture.create("test", nullptr, { .r = 0, .g = 0, .b = 0, .a = 0 }, nullptr);
	EXPECT_EQ(0, dimension.x) << "Invalid dimension returned!";
	EXPECT_EQ(0, dimension.y) << "Invalid dimension returned!";
	EXPECT_EQ(nullptr, texture.getRawTexture()) << "Raw texture is valid even though the creation failed!";
}

TEST_F(TextureTest, create_renderText_fail)
{
	hob::Texture	texture	  = {};
	hob::Coordinate dimension = {};

	EXPECT_CALL(ttfMock, TTF_RenderText_Blended(testing::_, testing::_, testing::_)) /**/
		.WillOnce(testing::Return(nullptr));

	dimension = texture.create("test", (TTF_Font*)not_nullptr, { .r = 0, .g = 0, .b = 0, .a = 0 }, nullptr);
	EXPECT_EQ(0, dimension.x) << "Invalid dimension returned!";
	EXPECT_EQ(0, dimension.y) << "Invalid dimension returned!";
	EXPECT_EQ(nullptr, texture.getRawTexture()) << "Raw texture is valid even though the creation failed!";
}

TEST_F(TextureTest, create_success)
{
	static constexpr int32_t SURFACE_WIDTH	= 10;
	static constexpr int32_t SURFACE_HEIGHT = 10;

	hob::Texture	texture	  = {};
	hob::Coordinate dimension = {};
	SDL_Surface		surface	  = {};

	surface.w = SURFACE_WIDTH;
	surface.h = SURFACE_HEIGHT;

	EXPECT_CALL(ttfMock, TTF_RenderText_Blended(testing::_, testing::_, testing::_)) /**/
		.WillOnce(testing::Return(&surface));
	EXPECT_CALL(sdlMock, SDL_CreateTextureFromSurface(testing::_, testing::_)) /**/
		.WillOnce(testing::Return((SDL_Texture*)not_nullptr));
	EXPECT_CALL(sdlMock, SDL_FreeSurface(testing::_));

	dimension = texture.create("test", (TTF_Font*)not_nullptr, { .r = 0, .g = 0, .b = 0, .a = 0 }, nullptr);
	EXPECT_EQ(SURFACE_WIDTH, dimension.x) << "Invalid dimension returned!";
	EXPECT_EQ(SURFACE_WIDTH, dimension.y) << "Invalid dimension returned!";
	EXPECT_NE(nullptr, texture.getRawTexture()) << "Raw texture is invalid even though the creation succeeded!";

	EXPECT_CALL(sdlMock, SDL_DestroyTexture(testing::_));
}
