/******************************************************************************************************
 * @file hob_Building.hpp                                                                             *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file defines the class and method prototypes of the building.                        *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_BUILDING_HPP_
#define HOB_BUILDING_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_IDrawable.hpp"
#include "hob_Component.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Building supporting textures 2 types of textures each with 2 seasons.
*/
class Building final : public IDrawable
{
public:
	/**
	 * @brief Constructs building not initializing it implicitly.
	 * @param void
	*/
	Building(void) = default;

	/**
	 * @brief Does not destroy the textures.
	 * @param void
	*/
	~Building(void) = default;

	/**
	 * @brief Initializes the building with all textures and destination.
	 * @param[in] summerTexture: Texture that will be drawn during summer, autumn and spring.
	 * @param[in] winterTexture: Texture that will be drawn during winter.
	 * @param[in] alternativeSummerTexture: Alternative texture that will be drawn during summer, autumn and spring.
	 * @param[in] alternativeWinterTexture: Alternative texture that will be drawn during winter.
	 * @param destination: Position on the screen and dimension of the texture.
	 * @return void
	*/
	void init(SDL_Texture* summerTexture, SDL_Texture* winterTexture, SDL_Texture* alternativeSummerTexture,
		SDL_Texture* alternativeWinterTexture, SDL_Rect destination) noexcept;

	/**
	 * @brief Draws the current texture.
	 * @param void
	 * @return void
	*/
	void draw(void) noexcept override;

	/**
	 * @brief Changes the texture that will be drawn (it keeps count if texture is set to alternative).
	 * @param isWinter: true - winter | false - otherwise.
	 * @return void
	*/
	void changeWeather(bool isWinter) noexcept;

	/**
	 * @brief Changes the texture that will be drawn (it keeps count of the current weather).
	 * @param isAlternative: true - is alternative | false - otherwise.
	 * @return void
	*/
	void switchTexture(bool isAlternative) noexcept;

private:
	/**
	 * @brief Texture that is being drawn during summer, autumn and spring.
	*/
	SDL_Texture* m_summerTexture;

	/**
	 * @brief Texture that is being drawn during winter.
	*/
	SDL_Texture* m_winterTexture;

	/**
	 * @brief Alternative texture that is being drawn during summer, autumn and spring.
	*/
	SDL_Texture* m_alternativeSummerTexture;

	/**
	 * @brief Alternative texture that is being drawn during winter.
	*/
	SDL_Texture* m_alternativeWinterTexture;

	/**
	 * @brief The component that is switching textures.
	*/
	Component m_component;
};

} /*< namespace hob */

#endif /*< HOB_BUILDING_HPP_ */
