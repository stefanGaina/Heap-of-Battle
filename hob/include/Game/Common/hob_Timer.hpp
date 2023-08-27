/******************************************************************************************************
 * @file hob_Timer.hpp                                                                                *
 * @date:      @author:                   Reason for change:                                          *
 * 27.07.2023  Gaina Stefan               Initial version.                                            *
 * 27.08.2023  Gaina Stefan               Added queue.                                                *
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
#include "hob_AsyncQueue.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Encapsulates information about the time.
*/
struct TimeFormat
{
	uint16_t seconds;    /**< How many seconds are left. */
	bool     isAlliance; /**< Whose turn is it.          */
};

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
	 * @param void
	 * @return void
	*/
	void draw(void) noexcept override;

	/**
	 * @brief Updates the time left. This method is safe to be called from other thread than rendering thread.
	 * @param seconds: How many seconds are left.
	 * @param isAlliance: Whose turn is it to use the specific textures.
	 * @return void
	*/
	void update(uint16_t seconds, bool isAlliance) noexcept;

private:
	/**
	 * @brief Thread safe queue for buffering updates.
	*/
	AsyncQueue<TimeFormat> m_queue;
};

} /*< namespace hob */

#endif /*< HOB_TIMER_HPP_ */
