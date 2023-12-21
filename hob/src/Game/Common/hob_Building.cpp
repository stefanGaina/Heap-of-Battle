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

	if (nullptr == summerTexture || nullptr == alternativeSummerTexture
	 || nullptr == winterTexture || nullptr == alternativeWinterTexture)
	{
		plog_warn("Building is incomplete!");
	}

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
	component.draw(renderer);
}

void Building::changeWeather(const bool isWinter) noexcept
{
	SDL_Texture* const currentTexture = component.getRawTexture();

	plog_trace("Building weather is being changed. (flag: %" PRId32 ")", static_cast<int32_t>(isWinter));
	if (false == isWinter)
	{
		if (currentTexture == summerTexture
		 || currentTexture == alternativeSummerTexture)
		{
			plog_warn("Building weather already changed!");
			return;
		}

		if (currentTexture == winterTexture)
		{
			if (nullptr == summerTexture)
			{
				plog_warn("Building is not changing weather!");
				return;
			}
			component.updateTexture(summerTexture);
		}
		else if (currentTexture == alternativeWinterTexture)
		{
			if (nullptr == alternativeSummerTexture)
			{
				plog_warn("Building is not changing weather!");
				return;
			}
			component.updateTexture(alternativeSummerTexture);
		}
		else
		{
			plog_error("Building is in an invalid state!");
		}
	}
	else
	{
		if (currentTexture == winterTexture
		 || currentTexture == alternativeWinterTexture)
		{
			plog_warn("Building weather already changed!");
			return;
		}

		if (currentTexture == summerTexture)
		{
			if (nullptr == winterTexture)
			{
				plog_warn("Building is not changing weather!");
				return;
			}
			component.updateTexture(winterTexture);
		}
		else if (currentTexture == alternativeSummerTexture)
		{
			if (nullptr == alternativeWinterTexture)
			{
				plog_warn("Building is not changing weather!");
				return;
			}
			component.updateTexture(alternativeWinterTexture);
		}
		else
		{
			plog_error("Building is in an invalid state!");
		}
	}
}

void Building::switchTexture(const bool isAlternative) noexcept
{
	SDL_Texture* const currentTexture = component.getRawTexture();

	plog_trace("Building texture is being switched. (flag: %" PRId32 ")", static_cast<int32_t>(isAlternative));
	if (true == isAlternative)
	{
		if (currentTexture == alternativeSummerTexture
		 || currentTexture == alternativeWinterTexture)
		{
			plog_warn("Building texture already switched!");
			return;
		}

		if (currentTexture == summerTexture)
		{
			if (nullptr == alternativeSummerTexture)
			{
				plog_error("Building is not switching texture!");
				return;
			}
			component.updateTexture(alternativeSummerTexture);
		}
		else if (currentTexture == winterTexture)
		{
			if (nullptr == alternativeWinterTexture)
			{
				plog_error("Building is not switching texture!");
				return;
			}
			component.updateTexture(alternativeWinterTexture);
		}
		else
		{
			plog_error("Building is in an invalid state!");
		}
	}
	else
	{
		if (currentTexture == summerTexture
		 || currentTexture == winterTexture)
		{
			plog_warn("Building texture already switched!");
			return;
		}

		if (currentTexture == alternativeSummerTexture)
		{
			if (nullptr == summerTexture)
			{
				plog_error("Building is not switching texture!");
				return;
			}
			component.updateTexture(summerTexture);
		}
		else if (currentTexture == alternativeWinterTexture)
		{
			if (nullptr == winterTexture)
			{
				plog_error("Building is not switching texture!");
				return;
			}
			component.updateTexture(winterTexture);
		}
		else
		{
			plog_error("Building is in an invalid state!");
		}
	}
}

} /*< namespace hob */
