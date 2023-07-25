/******************************************************************************************************
 * @file hob_Renderer.hpp                                                                             *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 24.07.2023  Gaina Stefan               Changed it into a singleton.                                *
 * @details This file defines the class and method prototypes of the renderer.                        *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_RENDERER_HPP_
#define HOB_RENDERER_HPP_

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
 * brief Renderer wrapper to be accessible from everywhere.
*/
class Renderer final
{
public:
	/**
	 * @brief Singleton way to get access to the renderer object.
	 * @param void
	 * @return Reference to the renderer instance.
	*/
	static Renderer& getInstance(void) noexcept;

	/**
	 * @brief Sets the renderer for global use.
	 * @param[in] renderer: The rendering context.
	 * @return void
	*/
	void set(SDL_Renderer* renderer) noexcept;

	/**
	 * @brief Getter for the renderer.
	 * @param void
	 * @return The rendering context.
	*/
	SDL_Renderer* get(void) const noexcept;

	/**
	 * @brief Destroys the renderer and invalidates the handle.
	 * @param void
	 * @return void
	*/
	void reset(void) noexcept;

	/**
	 * @brief Prevents the creation of another object.
	 * @param otherRenderer: instance to be copied.
	*/
	Renderer(Renderer& otherRenderer) = delete;

	/**
	 * @brief Prevents the creation of another object.
	 * @param renderer: Instance to be copied.
	*/
	void operator=(const Renderer& renderer) = delete;

private:
	/**
	 * @brief Does not create a renderer implicitly.
	 * @param void
	*/
	Renderer(void) = default;

	/**
	 * @brief Does not destroy the renderer.
	 * @param void
	*/
	~Renderer(void) = default;

private:
	/**
	 * The rendering context.
	*/
	SDL_Renderer* m_renderer;
};

} /*< namespace hob */

#endif /*< HOB_RENDERER_HPP_ */
