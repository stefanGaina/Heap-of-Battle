/******************************************************************************************************
 * Heap of Battle Copyright (C) 2024                                                                  *
 *                                                                                                    *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the   *
 * authors be held liable for any damages arising from the use of this software.                      *
 *                                                                                                    *
 * Permission is granted to anyone to use this software for any purpose, including commercial         *
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:   *
 *                                                                                                    *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the   *
 *    original software. If you use this software in a product, an acknowledgment in the product      *
 *    documentation would be appreciated but is not required.                                         *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being *
 *    the original software.                                                                          *
 * 3. This notice may not be removed or altered from any source distribution.                         *
******************************************************************************************************/

#ifndef HOB_GOLD_HPP_
#define HOB_GOLD_HPP_

#include "hob_TextureInitializer.hpp"
#include "hob_SoundInitializer.hpp"
#include "hob_AsyncQueue.hpp"

namespace hob
{

/**
 * @brief TODO
*/
class Gold final : public TextureInitializer<11UL, 4UL>
				 , public SoundInitializer<1UL>
{
public:
	/**
	 * @brief TODO
	 * @param renderer: Rendering context of the window.
	 * @param amount: TODO
	*/
	Gold(SDL_Renderer* renderer, uint8_t amount) noexcept;

	/**
	 * @brief TODO
	 * @param renderer: Rendering context of the window.
	 * @return void
	*/
	void draw(SDL_Renderer* renderer) noexcept override;

	/**
	 * @brief TODO
	 * @param amount: TODO
	 * @return void
	*/
	void update(uint8_t amount) noexcept;

private:
	/**
	 * @brief TODO
	*/
	AsyncQueue<uint8_t> queue;

	/**
	 * @brief TODO
	*/
	uint8_t previousAmount;
};

} /*< namespace hob */

#endif /*< HOB_GOLD_HPP_ */
