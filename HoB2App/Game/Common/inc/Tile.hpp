/** @file Tile.hpp
 *  @brief Class definition and method prototypes of the tile.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

#ifndef TILE_HPP_
#define TILE_HPP_

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
 * @brief TODO
*/
enum class Season
{
	SUMMER = 0, /**< */
	AUTUMN = 1, /**< */
	WINTER = 2, /**< */
	SPRING = 3  /**< */
};

/**
 * @brief 
*/
class Tile final : public Common::IDrawable
{
public:
	/**
	 * @brief 
	 * @param  
	 * @return 
	*/
	Tile(void) noexcept;

	/**
	 * @brief Does not destroy the textures.
	*/
	~Tile(void) noexcept;

	/**
	 * @brief 
	 * @return void
	*/
	void init(RawTexture summerTexture, RawTexture autumnTexture, RawTexture winterTexture, RawTexture springTexture, Coordinate position) noexcept;

	/**
	 * @brief Draws the active texture of the tile.
	 * @param void
	 * @return void
	*/
	virtual void draw(void) noexcept override final;

	/**
	 * @brief 
	 * @param season
	 * @return void
	*/
	void changeTexture(Season season) noexcept;

private:
	/**
	 * @brief Texture that will be drawn when season is set to summer.
	*/
	RawTexture m_summerTexture;

	/**
	 * @brief Texture that will be drawn when season is set to autumn.
	*/
	RawTexture m_autumnTexture;

	/**
	 * @brief Texture that will be drawn when season is set to winter.
	*/
	RawTexture m_winterTexture;

	/**
	 * @brief Texture that will be drawn when season is set to spring.
	*/
	RawTexture m_springTexture;

	/**
	 * @brief Component used to draw the tile.
	*/
	Common::Component m_component;
}; /*< class Tile */

} /*< namespace Game */

#endif /*< TILE_HPP_ */
