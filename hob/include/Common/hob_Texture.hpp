/******************************************************************************************************
 * @file hob_Texture.hpp                                                                              *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
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
#include <SDL_ttf.h>

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
	Texture(void) noexcept;
	
	/**
	 * @brief Loads texture from an image file.
	 * @param filePath: Relative path to the image file.
	*/
	Texture(std::string filePath) noexcept;

	/**
	 * @brief Destroys the loaded texture.
	 * @param void
	*/
	~Texture(void) noexcept;

	/**
	 * @brief Loads texture from an image file.
	 * @param filePath: Relative path to the image file.
	 * @return void
	*/
	void load(const std::string& filePath) noexcept;

	/**
	 * @brief Creates a texture from a text.
	 * @param text: The text that represents the texture.
	 * @param[in] font: The font from which the texture will be created.
	 * @param color: Color of the text.
	 * @return The dimension of the created texture (0 and 0 in case of error).
	*/
	Coordinate create(std::string text, TTF_Font* font, SDL_Color color) noexcept;

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
	SDL_Texture* m_rawTexture;
};

} /*< namespace hob */

#endif /*< HOB_TEXTURE_HPP_ */
