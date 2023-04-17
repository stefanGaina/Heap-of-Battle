/** @file Loop.hpp
 *  @brief Class definition and method prototypes and method implementation of the loop.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

#ifndef LOOP_HPP_
#define LOOP_HPP_

/****************************************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                                 *
 ***************************************************************************************************************************************/

#include "Types.hpp"

/****************************************************************************************************************************************
 * TYPE DEFINITIONS                                                                                                                     *
 ***************************************************************************************************************************************/

namespace Common
{

/**
 * @brief Abstract class that provides the inherited mechanism to keeping up a scene.
*/
class Loop
{
public:
	/**
	 * @brief Loop state is set to not started.
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
	Scene startLoop(void) noexcept;

protected:
	/**
	 * @brief Stops the loop.
	 * @param nextScene: scene that will be returned after loop stops.
	 * @return void
	*/
	void stopLoop(Scene nextScene) noexcept;

	/**
	 * @brief Abstract method, handling an event.
	 * @param void
	 * @return void
	*/
	virtual void handleEvent(const Event& event) = 0;

	/**
	 * @brief Abstract method drawing to the renderer the updated scene.
	 * @param void
	 * @return void
	*/
	virtual void draw(void) noexcept = 0;

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

private:
	/**
	 * @brief Flag indicating if the loop is running or is stopped.
	*/
	bool m_isRunning;

	/**
	 * @brief The scene that will follow after the current one is finished.
	*/
	Scene m_nextScene;
}; /*< class Loop */

} /*< namespace Common */

#endif /*< LOOP_HPP_ */
