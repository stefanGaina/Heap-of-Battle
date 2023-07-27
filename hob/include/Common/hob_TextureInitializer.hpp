/******************************************************************************************************
 * @file hob_TextureInitializer.hpp                                                                   *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
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
	*/
	TextureInitializer(std::array<std::string, TEXTURES_COUNT> filePaths, std::array<size_t, COMPONENTS_COUNT> textureIndexes,
		std::array<SDL_Rect, COMPONENTS_COUNT> destinations) noexcept;

	/**
	 * @brief Destroys the loaded textures.
	 * @param void
	*/
	virtual ~TextureInitializer(void) = default;

	/**
	 * @brief Draws the components in the order of initialization.
	 * @param param void
	 * @return void
	*/
	virtual void draw(void) noexcept override;

protected:
	/**
	 * @brief Holds all the textures needed.
	*/
	std::array<Texture, TEXTURES_COUNT> m_textureContainer;

	/**
	 * @brief Holds all the components needed.
	*/
	std::array<Component, COMPONENTS_COUNT> m_componentContainer;
};

/***********************************************************************************************************************
 * METHOD DEFINITIONS                                                                                                  *
 **********************************************************************************************************************/

template <size_t TEXTURES_COUNT, size_t COMPONENTS_COUNT>
TextureInitializer<TEXTURES_COUNT, COMPONENTS_COUNT>::TextureInitializer(std::array<std::string, TEXTURES_COUNT> filePaths,
	std::array<size_t, COMPONENTS_COUNT> textureIndexes, std::array<SDL_Rect, COMPONENTS_COUNT> destinations) noexcept
{
	size_t index = 0ULL;

	plog_trace("TextureInitializer is being constructed.");
	for (index = 0ULL; index < TEXTURES_COUNT; ++index)
	{
		m_textureContainer[index].load(filePaths[index]);
	}

	for (index = 0ULL; index < COMPONENTS_COUNT; ++index)
	{
		m_componentContainer[index].updateTexture(m_textureContainer[textureIndexes[index]].getRawTexture());
		m_componentContainer[index].updatePosition(destinations[index]);
	}
}

template <size_t TEXTURES_COUNT, size_t COMPONENTS_COUNT>
void TextureInitializer<TEXTURES_COUNT, COMPONENTS_COUNT>::draw(void) noexcept
{
	size_t index = 0ULL;

	plog_verbose("Textures are being drawn.");
	for (index = 0ULL; index < COMPONENTS_COUNT; ++index)
	{
		m_componentContainer[index].draw();
	}
}

} /*< namespace hob */

#endif /*< HOB_TEXTURE_INITIALIZER_HPP_ */
