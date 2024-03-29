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

#ifndef HOB_UNITS_HPP_
#define HOB_UNITS_HPP_

#include <list>

#include "hob_TextureInitializer.hpp"
#include "hob_LoadingScreen.hpp"
#include "hobGame_Game.hpp"

namespace hob
{

class Units final : public TextureInitializer<268UL, 0UL>
{
public:
	Units(SDL_Renderer* renderer, LoadingScreen& loadingScreen) noexcept;

	void draw(SDL_Renderer* renderer) noexcept override;

	void add(hobGame::Unit unit, bool isAlliance) noexcept(false);

private:
	std::list<Component> components;
};

} /*< namespace hob */

#endif /*< HOB_UNITS_HPP_ */
