/******************************************************************************************************
 * @file hob_Component.hpp                                                                            *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 26.08.2023  Gaina Stefan               Changed order of members.                                   *
 * 29.08.2023  Gaina Stefan               Overloaded updateTexture and == operator.                   *
 * @details This file defines the class and method prototypes of the component.                       *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_COMPONENT_HPP_
#define HOB_COMPONENT_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_IDrawable.hpp"
#include "hob_Texture.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Packs texture and dimension/position on screen.
*/
class Component final : public IDrawable
{
public:
	/**
	 * @brief Initializes component.
	 * @param[in] texture: Texture of the component.
	 * @param destination: Position on the screen and dimension of the texture.
	*/
	Component(SDL_Texture* texture = NULL, SDL_Rect destination = { 0L, 0L, 0L, 0L }) noexcept;

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
	void draw(void) noexcept override;

	/**
	 * @brief Changes the texture of the component or sets it if not already. Does not destroy the old one.
	 * @param[in] texture: Texture of the component.
	 * @return void
	*/
	void updateTexture(SDL_Texture* texture) noexcept;

	/**
	 * @brief Changes the texture of the component or sets it if not already. Does not destroy the old one.
	 * @param[in] texture: Texture of the component.
	 * @return void
	*/
	void updateTexture(const Texture& texture) noexcept;

	/**
	 * @brief Changes the destination of the component or sets it if not already.
	 * @param destination: Position on the screen and dimension of the texture.
	 * @return void
	*/
	void updatePosition(SDL_Rect destination) noexcept;
	
	/**
	 * @brief Update position and dimension based on current information.
	 * @param corrections: Values to be added to the destination.
	 * @return void
	*/
	void correctPosition(SDL_Rect corrections) noexcept;

	/**
	 * @brief Checks if coordinates are inside the component's rectangle destination area.
	 * @param mouse: Coordinates of the mouse.
	 * @param corrections: Values added for textures that are loaded from images with blank space.
	 * @return true - it is inside area | false - it is not inside area.
	*/
	bool isMouseInside(Coordinate mouse, SDL_Rect corrections = { .x = 0L, .y = 0L, .w = 0L, .h = 0L }) const noexcept;

	/**
	 * @brief Queries for the texture that is used for the drawing.
	 * @param void
	 * @return Texture that is being drawn.
	*/
	SDL_Texture* getRawTexture(void) const noexcept;

	/**
	 * @brief Checks if the raw textures are the same.
	 * @param texture: A texture object.
	 * @return true - the objects have the same raw texture | false - otherwise.
	*/
	bool operator ==(const Texture& texture) const noexcept;

private:
	/**
	 * @brief Position on the screen and dimension of the texture.
	*/
	SDL_Rect m_destination;

	/**
	 * @brief Texture that will be drawn. This class does not have ownership over it.
	*/
	SDL_Texture* m_texture;
};

} /*< namespace hob */

#endif /*< HOB_COMPONENT_HPP_ */
