/** @file Texture.cpp
 *  @brief Method implementation for the texture.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

/****************************************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                                 *
 ***************************************************************************************************************************************/

#include <SDL_image.h>
#include <plog.h>

#include "Texture.hpp"
#include "Renderer.hpp"

/****************************************************************************************************************************************
 * METHOD DEFINITIONS                                                                                                                   *
 ***************************************************************************************************************************************/

namespace Common
{

Texture::Texture(void) noexcept
	: m_rawTexture{ nullptr }
{
	plog_trace("Texture is being default constructed.");
}

Texture::Texture(std::string filePath) noexcept
	: m_rawTexture{ nullptr }
{
	plog_trace("Texture is being constructed. (file path: %s)", filePath.c_str());
	load(filePath);
}

Texture::~Texture(void) noexcept
{
	plog_trace("Texture is being destructed.");
	destroy();
}

void Texture::load(const std::string& filePath) noexcept
{
	Surface temporarySurface = nullptr;

	plog_trace("Texture is being loaded. (file path: %s)", filePath.c_str());

	if (nullptr != m_rawTexture)
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
	if (nullptr == temporarySurface)
	{
		plog_error("Image failed to be loaded! (file path: %s) (SDL error message: %s)", filePath.c_str(), SDL_GetError());
		return;
	}

	m_rawTexture = SDL_CreateTextureFromSurface(Window::Renderer::getInstance().load(), temporarySurface);
	if (nullptr == m_rawTexture)
	{
		plog_error("Texture failed to be created! (file path: %s) (SDL error message: %s)", filePath.c_str(), SDL_GetError());
	}
	SDL_FreeSurface(temporarySurface);
}

void Texture::destroy(void) noexcept
{
	plog_trace("Texture is being destroyed.");
	if (nullptr == m_rawTexture)
	{
		plog_warn("Texture is not loaded!");
		return;
	}

	SDL_DestroyTexture(m_rawTexture);
	m_rawTexture = nullptr;
}

RawTexture Texture::getRawTexture(void) const noexcept
{
	plog_verbose("Texture data is being got.");
	return m_rawTexture;
}

} /*< namespace Common */
