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
 * @file hob_Building.hpp
 * @author Gaina Stefan
 * @date 29.07.2023
 * @brief This file defines the class and method prototypes of the building.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_BUILDING_HPP_
#define HOB_BUILDING_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "hob_IDrawable.hpp"
#include "hob_Component.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

/** ***************************************************************************************************
 * @brief Building supporting textures 2 types of textures each with 2 seasons.
 *****************************************************************************************************/
class Building final : public IDrawable
{
public:
	/** ***********************************************************************************************
	 * @brief Initializes the building with all textures and destination.
	 * @param summerTexture: Texture that will be drawn during summer, autumn and spring.
	 * @param winterTexture: Texture that will be drawn during winter.
	 * @param alternativeSummerTexture: Alternative texture that will be drawn during summer, autumn and spring.
	 * @param alternativeWinterTexture: Alternative texture that will be drawn during winter.
	 * @param destination: Position on the screen and dimension of the texture.
	 * @return void
	 *************************************************************************************************/
	void init(SDL_Texture* summerTexture,
			  SDL_Texture* winterTexture,
			  SDL_Texture* alternativeSummerTexture,
			  SDL_Texture* alternativeWinterTexture,
			  SDL_Rect	   destination) noexcept;

	/** ***********************************************************************************************
	 * @brief Draws the current texture.
	 * @param renderer: Rendering context of the window.
	 * @return void
	 *************************************************************************************************/
	void draw(SDL_Renderer* renderer) noexcept override;

	/** ***********************************************************************************************
	 * @brief Changes the texture that will be drawn (it keeps count if texture is set to alternative).
	 * @param isWinter: true - winter, false - otherwise.
	 * @return void
	 *************************************************************************************************/
	void changeWeather(bool isWinter) noexcept;

	/** ***********************************************************************************************
	 * @brief Changes the texture that will be drawn (it keeps count of the current weather).
	 * @param isAlternative: true - alternative, false - otherwise.
	 * @return void
	 *************************************************************************************************/
	void switchTexture(bool isAlternative) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Changes the weather that will be drawn.
	 * @param weatherTexture1: The undesired weather texture variation 1.
	 * @param weatherTexture2: The undesired weather texture variation 2.
	 * @param weatherTexture3: The desired weather texture variation 1.
	 * @param weatherTexture4: The desired weather texture variation 2.
	 * @return void
	 *************************************************************************************************/
	void changeWeather(SDL_Texture* weatherTexture1, SDL_Texture* weatherTexture2, SDL_Texture* weatherTexture3, SDL_Texture* weatherTexture4) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Texture that is being drawn during summer, autumn and spring.
	 *************************************************************************************************/
	SDL_Texture* summerTexture;

	/** ***********************************************************************************************
	 * @brief Texture that is being drawn during winter.
	 *************************************************************************************************/
	SDL_Texture* winterTexture;

	/** ***********************************************************************************************
	 * @brief Alternative texture that is being drawn during summer, autumn and spring.
	 *************************************************************************************************/
	SDL_Texture* alternativeSummerTexture;

	/** ***********************************************************************************************
	 * @brief Alternative texture that is being drawn during winter.
	 *************************************************************************************************/
	SDL_Texture* alternativeWinterTexture;

	/** ***********************************************************************************************
	 * @brief The component that is switching textures.
	 *************************************************************************************************/
	Component component;
};

} /*< namespace hob */

#endif /*< HOB_BUILDING_HPP_ */
