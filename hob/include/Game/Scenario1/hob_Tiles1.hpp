/******************************************************************************************************
 * @file hob_Tiles1.hpp                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file defines the class and method prototypes of the tiles of the first scenario.     *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_TILES1_HPP_
#define HOB_TILES1_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_TextureInitializer.hpp"
#include "hob_TileInitializer.hpp"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

namespace hob
{

/*
 * @brief How many times of tiles are being used.
 */
static constexpr const size_t TILES1_COUNT = 13ULL;

/**
 * @brief How many textures scenario 1 tiles loads.
*/
static constexpr const size_t TILES1_TEXTURES_COUNT = 34ULL;

/**
 * @brief How many components the tiles of scenario 1 uses.
*/
static constexpr const size_t TILES1_COMPONENTS_COUNT = 0ULL;

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

/**
 * @brief
*/
class Tiles1 final : public TextureInitializer<TILES1_TEXTURES_COUNT, TILES1_COMPONENTS_COUNT>
				   , public TileInitializer<TILES1_COUNT>
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
	~Tiles1(void) = default;

	/**
	 * @brief Draws the tiles.
	 * @param void
	 * @return void
	*/
	void draw(void) noexcept override;
};

} /*< namespace hob */

#endif /*< HOB_TILES1_HPP_ */
