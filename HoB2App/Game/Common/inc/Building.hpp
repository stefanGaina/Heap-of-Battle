/** @file Building.hpp
 *  @brief Class definition and method prototypes of the building.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

#ifndef BUILDING_HPP_
#define BUILDING_HPP_

/****************************************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                                 *
 ***************************************************************************************************************************************/

#include "IDrawable.hpp"
#include "Component.hpp"

/****************************************************************************************************************************************
 * TYPE DEFINITIONS                                                                                                                     *
 ***************************************************************************************************************************************/

namespace Game
{

/**
 * @brief 
*/
class Building final : public Common::IDrawable
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
	 * @brief 
	 * @param[in] summerTexture 
	 * @param[in] winterTexture 
	 * @param[in] alternativeSummerTexture 
	 * @param[in] alternativeWinterTexture 
	 * @param destination 
	 * @return 
	*/
	void init(RawTexture summerTexture, RawTexture winterTexture, RawTexture alternativeSummerTexture,
		RawTexture alternativeWinterTexture, Rect destination) noexcept;

	/**
	 * @brief 
	 * @param void
	 * @return void
	*/
	virtual void draw(void) noexcept override final;

	/**
	 * @brief 
	 * @param isWinter
	 * @return void
	*/
	void changeWeather(bool isWinter) noexcept;

	/**
	 * @brief 
	 * @param isAlternative 
	 * @return void
	*/
	void switchTexture(bool isAlternative) noexcept;

private:
	/**
	 * @brief 
	*/
	RawTexture m_summerTexture;

	/**
	 * @brief 
	*/
	RawTexture m_winterTexture;

	/**
	 * @brief 
	*/
	RawTexture m_alternativeSummerTexture;

	/**
	 * @brief 
	*/
	RawTexture m_alternativeWinterTexture;

	/**
	 * @brief 
	*/
	Common::Component m_component;
}; /*< class Building */

} /*< namespace Game */

#endif /*< BUILDING_HPP_ */
