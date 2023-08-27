/******************************************************************************************************
 * @file hob_Texture.cpp                                                                              *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 24.07.2023  Gaina Stefan               Updated the renderer get.                                   *
 * 25.08.2023  Gaina Stefan               Added const keyword.                                        *
 * 26.08.2023  Gaina Stefan               Improved logs.                                              *
 * 27.08.2023  Gaina Stefan               Added comment.                                              *
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
#include "hob_Renderer.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Texture::Texture(void) noexcept
	: m_rawTexture{ NULL }
{
	plog_trace("Texture is being default constructed. (size: %" PRIu64 ") (1: %" PRIu64 ")", sizeof(*this), sizeof(m_rawTexture));
}

Texture::Texture(std::string filePath) noexcept
	: m_rawTexture{ NULL }
{
	plog_trace("Texture is being constructed. (file path: %s) (size: %" PRIu64 ") (1: %" PRIu64 ")", filePath.c_str(), sizeof(*this), sizeof(m_rawTexture));
	load(filePath);
}

Texture::~Texture(void) noexcept
{
	plog_trace("Texture is being destructed.");
	destroy();
}

void Texture::load(const std::string& filePath) noexcept
{
	SDL_Surface* temporarySurface = NULL;

	plog_trace("Texture is being loaded. (file path: %s)", filePath.c_str());
	if (NULL != m_rawTexture)
	{
		plog_warn("Texture was already loaded!");
		return;
	}

	if ("" == filePath)
	{
		plog_error("Invalid texture file path!");
		return;
	}

	temporarySurface = IMG_Load(filePath.c_str());
	if (NULL == temporarySurface)
	{
		plog_error("Image failed to be loaded! (file path: %s) (SDL error message: %s)", filePath.c_str(), SDL_GetError());
		return;
	}

	m_rawTexture = SDL_CreateTextureFromSurface(Renderer::getInstance().get(), temporarySurface);
	if (NULL == m_rawTexture)
	{
		plog_error("Texture failed to be created! (file path: %s) (SDL error message: %s)", filePath.c_str(), SDL_GetError());
	}
	SDL_FreeSurface(temporarySurface);
}

Coordinate Texture::create(const std::string text, TTF_Font* const font, const SDL_Color color) noexcept
{
	SDL_Surface* temporarySurface = NULL;
	Coordinate   dimension        = {};

	plog_verbose("Text texture is being created. (text: %s)", text.c_str());
	// if (NULL != m_rawTexture) <- It is okay not to check for that

	if ("" == text)
	{
		plog_error("Invalid texture text!");
		return dimension;
	}

	if (NULL == font)
	{
		plog_error("Invalid font!");
		return dimension;
	}

	temporarySurface = TTF_RenderText_Blended(font, text.c_str(), color);
	if (NULL == temporarySurface)
	{
		plog_error("Text texture failed to be loaded! (text: %s) (TTF error message: %s)", text.c_str(), TTF_GetError());
		return dimension;
	}

	m_rawTexture = SDL_CreateTextureFromSurface(Renderer::getInstance().get(), temporarySurface);
	if (NULL == m_rawTexture)
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
	if (NULL == m_rawTexture)
	{
		plog_warn("Texture is not loaded!");
		return;
	}
	SDL_DestroyTexture(m_rawTexture);
	m_rawTexture = NULL;
}

SDL_Texture* Texture::getRawTexture(void) const noexcept
{
	plog_verbose("Texture data is being got.");
	return m_rawTexture;
}

} /*< namespace hob */
