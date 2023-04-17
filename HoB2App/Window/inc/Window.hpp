/** @file Window.hpp
 *  @brief Class definition and method prototypes of the window.
 *
 *  @author Gaina Stefan!
 *  @bug No known bugs.
 */

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

/****************************************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                                 *
 ***************************************************************************************************************************************/

#include "Types.hpp"

/****************************************************************************************************************************************
 * TYPE DEFINITIONS                                                                                                                     *
 ***************************************************************************************************************************************/

namespace Window
{

/**
 * @brief Class used to set up the screen where graphics will be rendered.
*/
class Window final
{
public:
	/**
	 * @brief Low level abstraction layer window.
	*/
	using RawWindow = SDL_Window*;

	/**
	 * @brief Does not create the window implicitly.
	 * @param void
	*/
	Window(void) noexcept;
	
	/**
	 * @brief Destroys the window if it was not already.
	 * @param void
	*/
	~Window(void) noexcept;

	/**
	 * @brief Creates the window and renderer and initializes SDL subsystems(image and mixer).
	 * Throws exception in case of failure.
	 * @param isFullscreen: true - Fullscreen | false - Window
	 * @return void
	*/
	void create(bool isFullscreen) noexcept(false);

	/**
	 * @brief Destroys the window and deinitializes SDL subsystems.
	 * @param  void
	 * @return void
	*/
	void destroy(void) noexcept;

	/**
	 * @brief 
	 * @param void
	 * @return void
	*/
	void checkWindowFocus(void) const noexcept;

private:
	/**
	 * @brief Handle to SDL window object.
	*/
	RawWindow m_windowHandle;
}; /*< class Window */

} /*< namespace Window */

#endif /*< WINDOW_HPP_ */
