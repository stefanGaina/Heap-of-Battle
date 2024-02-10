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
 * @file hob_Texture.hpp                                                                              *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * 17.01.2024  Gaina Stefan               Changed comment.                                            *
 * 19.01.2024  Gaina Stefan               Changed SDL_ttf include.                                    *
 * @details This file defines the class and method prototypes of the texture.                         *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_TEXTURE_HPP_
#define HOB_TEXTURE_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <string>
#include <SDL2/SDL_ttf.h>

#include "hob_Types.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Texture wrapper.
*/
class Texture final
{
public:
	/**
	 * @brief Default constructor not loading implicitly the texture.
	 * @param void
	*/
	Texture(void) = default;

	/**
	 * @brief Loads texture from an image file.
	 * @param filePath: Relative path to the image file.
	 * @param renderer: Rendering context of the window.
	*/
	Texture(std::string filePath, SDL_Renderer* renderer) noexcept;

	/**
	 * @brief Destroys the loaded texture.
	 * @param void
	*/
	~Texture(void) noexcept;

	/**
	 * @brief Loads texture from an image file.
	 * @param filePath: Relative path to the image file.
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	void load(const std::string& filePath, SDL_Renderer* renderer) noexcept;

	/**
	 * @brief Creates a texture from a text.
	 * @param text: The text that represents the texture.
	 * @param font: The font from which the texture will be created.
	 * @param color: Color of the text.
	 * @param renderer: Rendering context of the window.
	 * @return The dimension of the created texture (0 and 0 in case of error).
	*/
	Coordinate create(std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) noexcept;

	/**
	 * @brief Destroys the loaded texture.
	 * @param void
	 * @return void
	*/
	void destroy(void) noexcept;

	/**
	 * @brief Queries for the loaded texture.
	 * @param void
	 * @return Handle to SDL texture object.
	*/
	SDL_Texture* getRawTexture(void) const noexcept;

private:
	/**
	 * @brief Handle to SDL texture object.
	*/
	SDL_Texture* rawTexture;
};

} /*< namespace hob */

#endif /*< HOB_TEXTURE_HPP_ */
