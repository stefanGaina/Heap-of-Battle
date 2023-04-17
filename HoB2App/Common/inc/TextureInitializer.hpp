/** @file TextureInitializes.hpp
 *  @brief Class definition, method prototypes and method implementations of the texture initializer.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

#ifndef TEXTURE_INITIALIZER_HPP_
#define TEXTURE_INITIALIZER_HPP_

/****************************************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                                 *
 ***************************************************************************************************************************************/

#include <string>
#include <array>
#include <plog.h>

#include "IDrawable.hpp"
#include "Texture.hpp"
#include "Component.hpp"

/****************************************************************************************************************************************
 * TYPE DEFINITIONS                                                                                                                     *
 ***************************************************************************************************************************************/

namespace Common
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
	 * @param[in] filePaths: file paths of the images which textures will be loaded.
	 * files which sounds will be loaded from.
	 * @param[in] textureIndexes: which textures will be assigned to each initialized component.
	 * @param[in] destinations: positions on the screen and dimensions of the textures.
	*/
	TextureInitializer(std::array<std::string, TEXTURES_COUNT> filePaths, std::array<size_t, COMPONENTS_COUNT> textureIndexes,
		std::array<SDL_Rect, COMPONENTS_COUNT> destinations) noexcept;

	/**
	 * @brief Frees the loaded textures.
	 * @param void
	*/
	virtual ~TextureInitializer(void) noexcept;

	/**
	 * @brief Draws the components in the order of initialization.
	 * @param void
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
}; /*< class TextureInitializer */

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
TextureInitializer<TEXTURES_COUNT, COMPONENTS_COUNT>::~TextureInitializer(void) noexcept
{
	plog_trace("TextureInitializer is being deconstructed.");
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

} /*< namespace Common */

#endif /*< TEXTURE_INITIALIZER_HPP_ */
