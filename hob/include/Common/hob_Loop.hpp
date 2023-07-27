/******************************************************************************************************
 * @file hob_Loop.hpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 24.07.2023  Gaina Stefan               Remove frames per second.                                   *
 * @details This file defines the class and method prototypes of the loop.                            *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_LOOP_HPP_
#define HOB_LOOP_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_FramesPerSecond.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Abstract class that provides the inherited mechanism to keeping up a scene.
*/
class Loop
{
public:
	/**
	 * @brief Loop state is set to not started.
	 * @param void
	*/
	Loop(void) noexcept;

	/**
	 * @brief Default destructor.
	 * @param void
	*/
	virtual ~Loop(void) = default;

	/**
	 * @brief Blocks until an event to quit or move to another scene is given.
	 * @param void
	 * @return Next scene that will take place.
	*/
	Scene start(void) noexcept;

protected:
	/**
	 * @brief Stops the loop.
	 * @param nextScene: Scene that will be returned after loop stops.
	 * @return void
	*/
	void stop(Scene nextScene) noexcept;

private:
	/**
	 * @brief Handles all pending events.
	 * @param void
	 * @return void
	*/
	void handleEvents(void) noexcept;

	/**
	 * @brief Clears renderer buffer and presents it to the screen after it draws desired objects.
	 * @param void
	 * @return void
	*/
	void render(void) noexcept(false);

	/**
	 * @brief Abstract method, handling an event.
	 * @param void
	 * @return void
	*/
	virtual void handleEvent(const SDL_Event& event) noexcept = 0;

	/**
	 * @brief Abstract method drawing to the renderer the updated scene.
	 * @param void
	 * @return void
	*/
	virtual void draw(void) noexcept = 0;

private:
	/**
	 * @brief Flag indicating if the loop is running or is stopped.
	*/
	bool m_isRunning;

	/**
	 * @brief The scene that will follow after the current one is finished.
	*/
	Scene m_nextScene;
};

} /*< namespace hob */

#endif /*< HOB_LOOP_HPP_ */
