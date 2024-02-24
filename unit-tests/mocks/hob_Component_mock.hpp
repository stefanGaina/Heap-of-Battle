/******************************************************************************************************
 * Heap of Battle Copyright (C) 2024
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the
 * authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
 *    original software. If you use this software in a product, an acknowledgment in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being
 *    the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *****************************************************************************************************/

#ifndef HOB_COMPONENT_MOCK_HPP_
#define HOB_COMPONENT_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>

#include "hob_Component.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

class ComponentDummy
{
public:
	virtual ~ComponentDummy(void) = default;

	virtual void		 updateTexture(SDL_Texture* texture)						= 0;
	virtual void		 updateTexture(const hob::Texture& texture)					= 0;
	virtual void		 updatePosition(SDL_Rect destination)						= 0;
	virtual void		 correctPosition(SDL_Rect corrections)						= 0;
	virtual bool		 isMouseInside(hob::Coordinate mouse, SDL_Rect corrections) = 0;
	virtual SDL_Texture* getRawTexture(void)										= 0;
};

class ComponentMock : public ComponentDummy
{
public:
	ComponentMock(void)
	{
		componentMock = this;
	}

	virtual ~ComponentMock(void)
	{
		componentMock = nullptr;
	}

	MOCK_METHOD1(draw, void(SDL_Renderer*));
	MOCK_METHOD1(updateTexture, void(SDL_Texture*));
	MOCK_METHOD1(updateTexture, void(const hob::Texture&));
	MOCK_METHOD1(updatePosition, void(SDL_Rect));
	MOCK_METHOD1(correctPosition, void(SDL_Rect));
	MOCK_METHOD2(isMouseInside, bool(hob::Coordinate, SDL_Rect));
	MOCK_METHOD0(getRawTexture, SDL_Texture*(void));

public:
	static ComponentMock* componentMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

ComponentMock* ComponentMock::componentMock = nullptr;

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

Component::Component(SDL_Texture* const texture, const SDL_Rect destination) noexcept
{
}

void Component::draw(SDL_Renderer* const renderer) noexcept
{
	ASSERT_NE(nullptr, ComponentMock::componentMock) << "draw(): nullptr == ComponentMock::componentMock";
	ComponentMock::componentMock->draw(renderer);
}

void Component::updateTexture(SDL_Texture* const texture) noexcept
{
	ASSERT_NE(nullptr, ComponentMock::componentMock) << "updateTexture(): nullptr == ComponentMock::componentMock";
	ComponentMock::componentMock->updateTexture(texture);
}

void Component::updateTexture(const Texture& texture) noexcept
{
	ASSERT_NE(nullptr, ComponentMock::componentMock) << "updateTexture(): nullptr == ComponentMock::componentMock";
	ComponentMock::componentMock->updateTexture(texture);
}

void Component::updatePosition(const SDL_Rect destination) noexcept
{
	ASSERT_NE(nullptr, ComponentMock::componentMock) << "updatePosition(): nullptr == ComponentMock::componentMock";
	ComponentMock::componentMock->updatePosition(destination);
}

void Component::correctPosition(const SDL_Rect corrections) noexcept
{
	ASSERT_NE(nullptr, ComponentMock::componentMock) << "correctPosition(): nullptr == ComponentMock::componentMock";
	ComponentMock::componentMock->correctPosition(corrections);
}

bool Component::isMouseInside(const Coordinate mouse, const SDL_Rect corrections) const noexcept
{
	if (nullptr == ComponentMock::componentMock)
	{
		ADD_FAILURE() << "isMouseInside(): nullptr == ComponentMock::componentMock";
		return false;
	}
	return ComponentMock::componentMock->isMouseInside(mouse, corrections);
}

SDL_Texture* Component::getRawTexture(void) const noexcept
{
	if (nullptr == ComponentMock::componentMock)
	{
		ADD_FAILURE() << "getRawTexture(): nullptr == ComponentMock::componentMock";
		return nullptr;
	}
	return ComponentMock::componentMock->getRawTexture();
}

bool Component::operator==(const Texture& texture) const noexcept
{
	return false;
}

} /*< namespace hob */

#endif /*< HOB_COMPONENT_MOCK_HPP_ */
