/******************************************************************************************************
 * @file hob_Timer.hpp                                                                                *
 * @date:      @author:                   Reason for change:                                          *
 * 27.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file defines the class and method prototypes of the timer.                           *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_TIMER_HPP_
#define HOB_TIMER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_TextureInitializer.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Graphical representation of the time left.
*/
class Timer final : public TextureInitializer<22ULL, 4ULL>
{
public:
	/**
	 * @brief Loads the textures needed for drawing the timer.
	 * @param void
	*/
	Timer(void) noexcept;

	/**
	 * @brief Destroys the loaded textures.
	 * @param void
	*/
	~Timer(void) = default;

	/**
	 * @brief Draws the time left.
	 * @param seconds: How many seconds are left.
	 * @param isAlliance: Whose turn is it to use the specific textures.
	 * @return void
	*/
	void update(uint16_t seconds, bool isAlliance) noexcept;
};

} /*< namespace hob */

#endif /*< HOB_TIMER_HPP_ */
