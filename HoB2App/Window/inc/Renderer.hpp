/** @file Renderer.hpp
 *  @brief Class definition and method prototypes of the renderer.
 *
 *  @author Gaina Stefan!
 *  @bug No known bugs.
 */

#ifndef RENDERER_HPP_
#define RENDERER_HPP_

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
 * @brief Provides a way to draw grapchis to the screen in a non replicable way.
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
	 * @brief Queries for the raw renderer.
	 * @param void
	 * @return Handle to SDL window object (can be null if window is not initialized).
	*/
	RawRenderer load(void) const noexcept;

	/**
	 * @brief Stores data that will be used to render graphics.
	 * @param rendererHandle - Handle to SDL window object.
	 * @return void
	*/
	void store(RawRenderer rendererHandle) noexcept;

	/**
	 * @brief Clears the renderer buffer of everything that was previously drawn. Can fail throwing an exception.
	 * @param void
	 * @return void
	*/
	void clear(void) const noexcept(false);

	/**
	 * @brief Presents to the screen everything drawn.
	 * @param void
	 * @return void
	*/
	void present(void) const noexcept;

	/**
	 * @brief Destroys the renderer.
	 * @param void 
	 * @return void
	*/
	void destroy(void) noexcept;

	/**
	 * @brief Prevents the creation of another object.
	 * @param otherRenderer: instance to be copied.
	*/
	Renderer(Renderer& otherRenderer) = delete;

	/**
	 * @brief Prevents the creation of another object.
	 * @param renderer: instance to be copied.
	 * @return void
	*/
	void operator=(const Renderer& renderer) = delete;

private:
	/**
	 * @brief Does not create the renderer implicitly.
	 * @param void
	*/
	Renderer(void) noexcept;

	/**
	 * @brief Destroys the renderer if it was not already.
	 * @param void
	*/
	~Renderer(void) noexcept;

private:
	/**
	 * @brief Handle to SDL window object.
	*/
	RawRenderer m_rendererHandle;
}; /*< class Renderer */

} /*< namespace Window */

#endif /*< RENDERER_HPP_ */
