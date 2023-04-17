/** @file Component.hpp
 *  @brief Class definition and method prototypes of the component.
 *
 *  @author Gaina Stefan!
 *  @bug No known bugs.
 */

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

/****************************************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                                 *
 ***************************************************************************************************************************************/

#include "IDrawable.hpp"
#include "Types.hpp"

/****************************************************************************************************************************************
 * TYPE DEFINITIONS                                                                                                                     *
 ***************************************************************************************************************************************/

namespace Common
{

/**
 * @brief Packs texture and dimension/position on screen.
*/
class Component final : public IDrawable
{
public:
	/**
	 * @brief Initializes component.
	 * @param[in] texture: texture of the component.
	 * @param destination: position on the screen and dimension of the texture.
	*/
	Component(RawTexture texture = nullptr, Rect destination = { 0L, 0L, 0L, 0L }) noexcept;

	/**
	 * @brief Does not destroy the texture.
	 * @param void
	*/
	~Component(void) = default;

	/**
	 * @brief Draws the texture at the destination.
	 * @param void
	 * @return void
	*/
	virtual void draw(void) noexcept override final;

	/**
	 * @brief Changes the texture of the component or sets it if not already. Does not destroy the old one.
	 * @param[in] texture: texture of the component.
	 * @return void
	*/
	void updateTexture(RawTexture texture) noexcept;

	/**
	 * @brief Changes the destination of the component or sets it if not already.
	 * @param destination: position on the screen and dimension of the texture.
	 * @return void
	*/
	void updatePosition(Rect destination) noexcept;
	
	/**
	 * @brief Update position and dimension based on current information.
	 * @param corrections: values to be added to the destination.
	 * @return void
	*/
	void correctPosition(Rect corrections) noexcept;

	/**
	 * @brief Checks if coordinates are inside the component's rectangle destination area.
	 * @param mouse: coordinates of the mouse.
	 * @param corrections: values added for textures that are loaded from images with blank space.
	 * @return true - it is inside area | false - it is not inside area.
	*/
	bool isMouseInside(Coordinate mouse, Rect corrections = { 0L, 0L, 0L, 0L }) const noexcept;

	/**
	 * @brief Queries for the texture that is used for the drawing.
	 * @param void
	 * @return Texture that is being drawn.
	*/
	RawTexture getRawTexture(void) const noexcept;

private:
	/**
	 * @brief Texture that will be drawn. This class does not have ownership over it.
	*/
	RawTexture m_texture;

	/**
	 * @brief Position on the screen and dimension of the texture.
	*/
	Rect m_destination;
}; /*< class Component */

} /*< namespace Common */

#endif /*< COMPONENT_HPP_ */
