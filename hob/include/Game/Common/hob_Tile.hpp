/******************************************************************************************************
 * @file hob_Tile.hpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file defines the class and method prototypes of the tile.                            *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_TILE_HPP_
#define HOB_TILE_HPP_

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
 * @brief Enumerates the seasons.
*/
enum class Season
{
	SUMMER = 0, /**< Summer season. */
	AUTUMN = 1, /**< Autumn season. */
	WINTER = 2, /**< Winter season. */
	SPRING = 3  /**< Spring season. */
};

/**
 * @brief HSCALE by HSCALE tile supporting texture for each season.
*/
class Tile final : public IDrawable
{
public:
	/**
	 * @brief Does not initialize the tile implicitly.
	 * @param void
	*/
	Tile(void) noexcept;

	/**
	 * @brief Does not destroy the textures.
	 * @param void
	*/
	~Tile(void) = default;

	/**
	 * @brief Initializes the tile with textures for all seasons and its position.
	 * @param[in] summerTexture: Texture that will be drawn when season is set to summer.
	 * @param[in] autumnTexture: Texture that will be drawn when season is set to autumn.
	 * @param[in] winterTexture: Texture that will be drawn when season is set to winter.
	 * @param[in] springTexture: Texture that will be drawn when season is set to spring.
	 * @param position: Indexes of the playing board matrix.
	 * @return void
	*/
	void init(SDL_Texture* summerTexture, SDL_Texture* autumnTexture, SDL_Texture* winterTexture, SDL_Texture* springTexture, Coordinate position) noexcept;

	/**
	 * @brief Draws the active texture of the tile.
	 * @param void
	 * @return void
	*/
	void draw(void) noexcept override;

	/**
	 * @brief Changes the texture that will be drawn.
	 * @param season: What season will the tile's texture be changed to.
	 * @return void
	*/
	void changeTexture(Season season) noexcept;

private:
	/**
	 * @brief Texture that will be drawn when season is set to summer.
	*/
	SDL_Texture* m_summerTexture;

	/**
	 * @brief Texture that will be drawn when season is set to autumn.
	*/
	SDL_Texture* m_autumnTexture;

	/**
	 * @brief Texture that will be drawn when season is set to winter.
	*/
	SDL_Texture* m_winterTexture;

	/**
	 * @brief Texture that will be drawn when season is set to spring.
	*/
	SDL_Texture* m_springTexture;

	/**
	 * @brief Component used to draw the tile.
	*/
	Component m_component;
};

} /*< namespace hob */

#endif /*< HOB_TILE_HPP_ */
