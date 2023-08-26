/******************************************************************************************************
 * @file hob_Window.hpp                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 26.08.2023  Gaina Stefan               Added constructor and destructor.                           *
 * @details This file defines the class and method prototypes of the window.                          *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_WINDOW_HPP_
#define HOB_WINDOW_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "hob_Types.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Class used to set up the screen where graphics will be rendered.
*/
class Window final
{
public:
	/**
	 * @brief Makes the terminal not visible.
	 * @param void
	 * @return void
	*/
	static void hideTerminal(void) noexcept;

	/**
	 * @brief Does not create the window implicitly.
	 * @param void
	*/
	Window(void) noexcept;

	/**
	 * @brief Does not destroy the window implicitly.
	 * @param void
	*/
	~Window(void) = default;

	/**
	 * @brief Creates the window where the textures will be renderer.
	 * @param void
	 * @return void
	*/
	void create(void) noexcept(false);

	/**
	 * @brief Destroys the created window and renderer.
	 * @param void
	 * @return void
	*/
	void destroy(void) noexcept;

	/**
	 * @brief Sets the icon of the window.
	 * @param void
	 * @return void
	*/
	void setIcon(void) const noexcept;

#ifdef DEVEL_BUILD
	/**
	 * @brief Logs information about renderer and power for debugging purposes.
	 * @param void
	 * @return void
	*/
	void logInfo(void) const noexcept;
#endif /*< DEVEL_BUILD */

private:
	/**
	 * @brief The SDL window handle.
	*/
	SDL_Window* m_window;
};

} /*< namespace hob */

#endif /*< HOB_WINDOW_HPP_ */
