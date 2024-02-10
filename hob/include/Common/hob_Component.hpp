/******************************************************************************************************
 * Heap of Battle Copyright (C) 2024
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the
 * authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
 *    original software. If you use this software in a product, an acknowledgment in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being
 *    the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @file hob_Component.hpp
 * @author Gaina Stefan
 * @date 23.08.2023
 * @brief This file defines the class and method prototypes of the component.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_COMPONENT_HPP_
#define HOB_COMPONENT_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "hob_IDrawable.hpp"
#include "hob_Texture.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

/** ***************************************************************************************************
 * @brief Packs texture and dimension/position on screen.
 * @details The component does not take ownership of the texture so it is not destroyed.
 *****************************************************************************************************/
class Component final : public IDrawable
{
public:
	/** ***********************************************************************************************
	 * @brief Initializes component.
	 * @param texture: Texture of the component.
	 * @param destination: Position on the screen and dimension of the texture.
	 *************************************************************************************************/
	Component(SDL_Texture* texture = nullptr, SDL_Rect destination = { .x = 0, .y = 0, .w = 0, .h = 0 }) noexcept;

	/** ***********************************************************************************************
	 * @brief Draws the texture at the destination.
	 * @param renderer: Rendering context of the window.
	 * @return void
	 *************************************************************************************************/
	void draw(SDL_Renderer* renderer) noexcept override;

	/** ***********************************************************************************************
	 * @brief Changes the texture of the component or sets it if not already. Does not destroy the old
	 * one.
	 * @param texture: Texture of the component.
	 * @return void
	 *************************************************************************************************/
	void updateTexture(SDL_Texture* texture) noexcept;

	/** ***********************************************************************************************
	 * @brief Changes the texture of the component or sets it if not already. Does not destroy the old
	 * one.
	 * @param texture: Texture of the component.
	 * @return void
	 *************************************************************************************************/
	void updateTexture(const Texture& texture) noexcept;

	/** ***********************************************************************************************
	 * @brief Changes the destination of the component or sets it if not already.
	 * @param destination: Position on the screen and dimension of the texture.
	 * @return void
	 *************************************************************************************************/
	void updatePosition(SDL_Rect destination) noexcept;

	/** ***********************************************************************************************
	 * @brief Update position and dimension based on current information.
	 * @param corrections: Values to be added to the destination.
	 * @return void
	 *************************************************************************************************/
	void correctPosition(SDL_Rect corrections) noexcept;

	/** ***********************************************************************************************
	 * @brief Checks if coordinates are inside the component's rectangle destination area.
	 * @param mouse: Coordinates of the mouse.
	 * @param corrections: Values added for textures that are loaded from images with blank space.
	 * @return true - it is inside area.
	 * @return false - it is not inside area.
	 *************************************************************************************************/
	bool isMouseInside(Coordinate mouse, SDL_Rect corrections = { .x = 0, .y = 0, .w = 0, .h = 0 }) const noexcept;

	/** ***********************************************************************************************
	 * @brief Queries for the texture that is used for the drawing.
	 * @param void
	 * @return Texture that is being drawn.
	 *************************************************************************************************/
	SDL_Texture* getRawTexture(void) const noexcept;

	/** ***********************************************************************************************
	 * @brief Checks if the raw textures are the same.
	 * @param texture: A texture object.
	 * @return true - the objects have the same raw texture
	 * @return false - the object does not have the same raw texture.
	 *************************************************************************************************/
	bool operator ==(const Texture& texture) const noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Position on the screen and dimension of the texture.
	 *************************************************************************************************/
	SDL_Rect destination;

	/** ***********************************************************************************************
	 * @brief Texture that will be drawn. The component does not have ownership over it.
	 *************************************************************************************************/
	SDL_Texture* texture;
};

} /*< namespace hob */

#endif /*< HOB_COMPONENT_HPP_ */
