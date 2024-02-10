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

/******************************************************************************************************
 * @file hob_Building.cpp                                                                             *
 * @date:      @author:                   Reason for change:                                          *
 * 29.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added const keywords.                                       *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * 20.01.2024  Gaina Stefan               Overloaded changeWeather() method.                          *
 * @details This file implements the class defined in hob_Building.hpp.                               *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Building.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

void Building::init(SDL_Texture* const summerTexture, SDL_Texture* const winterTexture, SDL_Texture* const alternativeSummerTexture,
	SDL_Texture* const alternativeWinterTexture, const SDL_Rect destination) noexcept
{
	plog_trace("Building is being initialized. (destination: %" PRId32 ", %" PRId32 ", %" PRId32 ", %" PRId32 ")",
		destination.x, destination.y, destination.w, destination.h);

	this->summerTexture            = summerTexture;
	this->winterTexture            = winterTexture;
	this->alternativeSummerTexture = alternativeSummerTexture;
	this->alternativeWinterTexture = alternativeWinterTexture;

	component.updateTexture(summerTexture);
	component.updatePosition(destination);
}

void Building::draw(SDL_Renderer* const renderer) noexcept
{
	plog_verbose("Building is being drawn.");
	plog_assert(nullptr != renderer);

	component.draw(renderer);
}

void Building::changeWeather(const bool isWinter) noexcept
{
	plog_trace("Building weather is being changed. (flag: %" PRId32 ")", static_cast<int32_t>(isWinter));
	if (false == isWinter)
	{
		changeWeather(winterTexture, alternativeWinterTexture, summerTexture, alternativeSummerTexture);
		return;
	}
	changeWeather(summerTexture, alternativeSummerTexture, winterTexture, alternativeWinterTexture);
}

void Building::switchTexture(const bool isAlternative) noexcept
{
	plog_trace("Building texture is being switched. (flag: %" PRId32 ")", static_cast<int32_t>(isAlternative));
	if (true == isAlternative)
	{
		changeWeather(summerTexture, winterTexture, alternativeSummerTexture, alternativeWinterTexture);
		return;
	}
	changeWeather(alternativeSummerTexture, alternativeWinterTexture, summerTexture, winterTexture);
}

void Building::changeWeather(SDL_Texture* const weatherTexture1, SDL_Texture* const weatherTexture2,
	SDL_Texture* const weatherTexture3, SDL_Texture* const weatherTexture4) noexcept
{
	SDL_Texture* const currentTexture = component.getRawTexture();

	if (currentTexture == weatherTexture3
	 || currentTexture == weatherTexture4)
	{
		plog_warn("Building weather already changed!");
		return;
	}

	if (currentTexture == weatherTexture1)
	{
		if (nullptr == weatherTexture3)
		{
			plog_warn("Building is not changing weather!");
			return;
		}

		component.updateTexture(weatherTexture3);
		return;
	}

	if (currentTexture == weatherTexture2)
	{
		if (nullptr == weatherTexture4)
		{
			plog_warn("Building is not changing weather!");
			return;
		}

		component.updateTexture(weatherTexture4);
		return;
	}

	plog_error("Building is in an invalid state!");
}

} /*< namespace hob */
