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

/******************************************************************************************************
 * @file hob_Texture.cpp                                                                              *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 24.07.2023  Gaina Stefan               Updated the renderer get.                                   *
 * 25.08.2023  Gaina Stefan               Added const keyword.                                        *
 * 26.08.2023  Gaina Stefan               Improved logs.                                              *
 * 27.08.2023  Gaina Stefan               Added comment.                                              *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file implements the class defined in hob_Texture.hpp.                                *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <SDL_image.h>
#include <plog.h>

#include "hob_Texture.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Texture::Texture(void) noexcept
	: rawTexture{ nullptr }
{
	plog_trace("Texture is being default constructed.");
}

Texture::Texture(std::string filePath, SDL_Renderer* const renderer) noexcept
	: rawTexture{ nullptr }
{
	plog_trace("Texture is being constructed.");
	load(filePath, renderer);
}

Texture::~Texture(void) noexcept
{
	plog_trace("Texture is being destructed.");
	destroy();
}

void Texture::load(const std::string& filePath, SDL_Renderer* const renderer) noexcept
{
	SDL_Surface* temporarySurface = nullptr;

	plog_trace("Texture is being loaded. (file path: %s)", filePath.c_str());
	if (nullptr != rawTexture)
	{
		plog_warn("Texture was already loaded!");
		return;
	}

	temporarySurface = IMG_Load(filePath.c_str());
	if (nullptr == temporarySurface)
	{
		plog_error("Image failed to be loaded! (file path: %s) (SDL error message: %s)", filePath.c_str(), SDL_GetError());
		return;
	}

	rawTexture = SDL_CreateTextureFromSurface(renderer, temporarySurface);
	if (nullptr == rawTexture)
	{
		plog_error("Texture failed to be created! (file path: %s) (SDL error message: %s)", filePath.c_str(), SDL_GetError());
	}
	SDL_FreeSurface(temporarySurface);
}

Coordinate Texture::create(const std::string text, TTF_Font* const font, const SDL_Color color, SDL_Renderer* const renderer) noexcept
{
	SDL_Surface* temporarySurface = nullptr;
	Coordinate   dimension        = {};

	plog_verbose("Text texture is being created. (text: %s)", text.c_str());
	// if (nullptr != rawTexture) <- It is okay not to check for that.

	if (nullptr == font)
	{
		plog_error("Invalid font!");
		return dimension;
	}

	temporarySurface = TTF_RenderText_Blended(font, text.c_str(), color);
	if (nullptr == temporarySurface)
	{
		plog_error("Text texture failed to be loaded! (text: %s) (TTF error message: %s)", text.c_str(), TTF_GetError());
		return dimension;
	}

	rawTexture = SDL_CreateTextureFromSurface(renderer, temporarySurface);
	if (nullptr == rawTexture)
	{
		plog_error("Text texture failed to be created! (TTF error message: %s)", TTF_GetError());
	}

	dimension.x = temporarySurface->w;
	dimension.y = temporarySurface->h;
	SDL_FreeSurface(temporarySurface);

	return dimension;
}

void Texture::destroy(void) noexcept
{
	plog_trace("Texture is being destroyed.");
	if (nullptr == rawTexture)
	{
		plog_warn("Texture is not loaded!");
		return;
	}
	SDL_DestroyTexture(rawTexture);
	rawTexture = nullptr;
}

SDL_Texture* Texture::getRawTexture(void) const noexcept
{
	plog_verbose("Texture data is being got.");
	return rawTexture;
}

} /*< namespace hob */
