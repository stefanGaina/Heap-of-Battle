/******************************************************************************************************
 * @file hobM_Renderer.hpp                                                                            *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file defines the class and method prototypes of the renderer.                        *
 * @todo Make it a singleton.                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_RENDERER_HPP_
#define HOB_RENDERER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <SDL.h>

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * brief Renderer wrapper to be accessible from everywhere.
*/
class Renderer final
{
public:
	/**
	 * @brief Sets the renderer for global use.
	 * @param[in] renderer: The rendering context.
	 * @return void
	*/
	static void set(SDL_Renderer* renderer);

	/**
	 * @brief Getter for the renderer.
	 * @param void
	 * @return The rendering context.
	*/
	static SDL_Renderer* get(void);

	/**
	 * @brief Destroys the renderer and invalidates the handle.
	 * @param void
	 * @return void
	*/
	static void reset(void);

private:
	/**
	 * The rendering context.
	*/
	static SDL_Renderer* s_renderer;
};

} /*< namespace hob */

#endif /*< HOB_RENDERER_HPP_ */
