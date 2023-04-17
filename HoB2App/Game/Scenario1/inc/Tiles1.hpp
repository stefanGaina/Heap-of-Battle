/** @file Chat.hpp
 *  @brief Class definition and method prototypes of the tiles of scenario number 1.
 *
 *  @author Gaina Stefan!
 *  @bug No known bugs.
 */

#ifndef TILES1_HPP_
#define TILES1_HPP_

/****************************************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                                 *
 ***************************************************************************************************************************************/

#include "TextureInitializer.hpp"
#include "TileInitializer.hpp"

/****************************************************************************************************************************************
 * MACROS                                                                                                                               *
 ***************************************************************************************************************************************/

/*
 * @brief How many times of tiles are being used.
 */
#define TILES_COUNT 13ULL

/****************************************************************************************************************************************
 * TYPE DEFINITIONS                                                                                                                     *
 ***************************************************************************************************************************************/

namespace Game
{

/*
 * @brief Enumerates scenario 1 tiles' textures index.
 */
enum Tiles1TextureIndex
{
	TILES1_TEXTURES_COUNT = 34 /**< How many textures scenario 1 tiles loads. */
};

/*
 * @brief Enumerates scenario 1 tiles' changeable components index.
 */
enum Tiles1ComponentIndex
{
	TILES1_COMPONENTS_COUNT = 0 /**< How many components the tiles of scenario 1 uses. */
};

class Tiles1 final : public Common::TextureInitializer<TILES1_TEXTURES_COUNT, TILES1_COMPONENTS_COUNT>
				   , public TileInitializer<TILES_COUNT>
{
public:
	/**
	 * @brief Loads the textures and initializes the tiles.
	 * @param void
	*/
	Tiles1(void);

	/**
	 * @brief Destroys the loaded textures.
	 * @param void
	*/
	~Tiles1(void);

	/**
	 * @brief Draws the tiles.
	 * @param void
	 * @return void
	*/
	virtual void draw(void) noexcept override;
}; /*< class Tiles1 */

} /*< namespace Game */

#endif /*< TILES1_HPP_ */
