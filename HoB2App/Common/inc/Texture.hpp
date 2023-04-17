/** @file Texture.hpp
 *  @brief Class definition and method prototypes of the texture.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

/****************************************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                                 *
 ***************************************************************************************************************************************/

#include <string>

#include "Types.hpp"

/****************************************************************************************************************************************
 * TYPE DEFINITIONS                                                                                                                     *
 ***************************************************************************************************************************************/

namespace Common
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
	 * @param filePath: relative path to the image file.
	*/
	Texture(std::string filePath) noexcept;

	/**
	 * @brief Destroys the loaded texture.
	 * @param void
	*/
	~Texture(void) noexcept;

	/**
	 * @brief Loads texture from an image file.
	 * @param filePath: relative path to the image file.
	*/
	void load(const std::string& filePath) noexcept;

	/**
	 * @brief Destroys the loaded texture.
	 * @param void
	*/
	void destroy(void) noexcept;

	/**
	 * @brief Queries for the loaded texture.
	 * @param void
	 * @return Handle to SDL texture object.
	*/
	RawTexture getRawTexture(void) const noexcept;

private:
	/**
	 * @brief Handle to SDL texture object.
	*/
	RawTexture m_rawTexture;
}; /*< class Texture */

} /*< namespace Common */

#endif /*< TEXTURE_HPP_ */
