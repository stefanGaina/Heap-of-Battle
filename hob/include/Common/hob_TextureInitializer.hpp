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
 * @file hob_TextureInitializer.hpp                                                                   *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added const keywords.                                       *
 * 26.08.2023  Gaina Stefan               Improved logs.                                              *
 * 27.08.2023  Gaina Stefan               Fixed comment.                                              *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * @details This file defines the class and method prototypes and method implementation of the        *
 * texture initializer.                                                                               *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_TEXTURE_INITIALIZER_HPP_
#define HOB_TEXTURE_INITIALIZER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <array>
#include <plog.h>

#include "hob_IDrawable.hpp"
#include "hob_Texture.hpp"
#include "hob_Component.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Initializes a list of textures and components.
*/
template <size_t TEXTURES_COUNT, size_t COMPONENTS_COUNT>
class TextureInitializer : public IDrawable
{
public:
	/**
	 * @brief Loads textures from the specified file paths and initializes components.
	 * @param[in] filePaths: File paths of the images which textures will be loaded.
	 * files which sounds will be loaded from.
	 * @param[in] textureIndexes: Which textures will be assigned to each initialized component.
	 * @param[in] destinations: Positions on the screen and dimensions of the textures.
	 * @param renderer: Rendering context of the window.
	*/
	TextureInitializer(std::array<std::string, TEXTURES_COUNT> filePaths, std::array<size_t, COMPONENTS_COUNT> textureIndexes,
		std::array<SDL_Rect, COMPONENTS_COUNT> destinations, SDL_Renderer* renderer) noexcept;

	/**
	 * @brief Destroys the loaded textures.
	 * @param void
	*/
	virtual ~TextureInitializer(void) = default;

	/**
	 * @brief Draws the components in the order of initialization.
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	virtual void draw(SDL_Renderer* renderer) noexcept override;

protected:
	/**
	 * @brief Holds all the components needed.
	*/
	std::array<Component, COMPONENTS_COUNT> componentContainer;

	/**
	 * @brief Holds all the textures needed.
	*/
	std::array<Texture, TEXTURES_COUNT> textureContainer;
};

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

template <size_t TEXTURES_COUNT, size_t COMPONENTS_COUNT>
TextureInitializer<TEXTURES_COUNT, COMPONENTS_COUNT>::TextureInitializer(const std::array<std::string, TEXTURES_COUNT> filePaths,
	const std::array<size_t, COMPONENTS_COUNT> textureIndexes, const std::array<SDL_Rect, COMPONENTS_COUNT> destinations, SDL_Renderer* const renderer) noexcept
	: componentContainer{}
	, textureContainer  {}
{
	size_t index = 0UL;

	plog_trace("TextureInitializer is being constructed.");
	for (; index < TEXTURES_COUNT; ++index)
	{
		textureContainer[index].load(filePaths[index], renderer);
	}

	for (index = 0UL; index < COMPONENTS_COUNT; ++index)
	{
		componentContainer[index].updateTexture(textureContainer[textureIndexes[index]]);
		componentContainer[index].updatePosition(destinations[index]);
	}
}

template <size_t TEXTURES_COUNT, size_t COMPONENTS_COUNT>
void TextureInitializer<TEXTURES_COUNT, COMPONENTS_COUNT>::draw(SDL_Renderer* const renderer) noexcept
{
	size_t index = 0UL;

	plog_verbose("Textures are being drawn.");
	for (; index < COMPONENTS_COUNT; ++index)
	{
		componentContainer[index].draw(renderer);
	}
}

} /*< namespace hob */

#endif /*< HOB_TEXTURE_INITIALIZER_HPP_ */
