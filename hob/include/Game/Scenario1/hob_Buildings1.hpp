/******************************************************************************************************
 * @file hob_Buildings1.hpp                                                                           *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file defines the class and method prototypes of the buildings of the first scenario. *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_BUILDINGS1_HPP_
#define HOB_BUILDINGS1_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_TextureInitializer.hpp"
#include "hob_BuildingInitializer.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Graphical representation of all the buildings used in scenario 1.
*/
class Buildings1 final : public TextureInitializer<29, 0>
					   , public BuildingInitializer<18>
{
public:
	/**
	 * @brief Loads the textures and initializes the buildings.
	 * @param void
	*/
	Buildings1(void) noexcept;

	/**
	 * @brief Destroys the loaded textures.
	 * @param void
	*/
	~Buildings1(void) = default;

	/**
	 * @brief Calls the draw method of each building.
	 * @param void
	 * @return void
	*/
	void draw(void) noexcept override;

	/**
	 * @brief Changes the textures of the buildings.
	 * @param isWinter: true - winter | false - otherwise.
	 * @return void
	*/
	void changeWeather(bool isWinter) noexcept;

private:
	/**
	 * @brief The season that the textures are set to.
	*/
	bool m_previousSeason;
};

} /*< namespace hob */

#endif /*< HOB_BUILDINGS1_HPP_ */
