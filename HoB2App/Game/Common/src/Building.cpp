/** @file Building.cpp
 *  @brief Method implementation for the building.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

/****************************************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                                 *
 ***************************************************************************************************************************************/

#include <plog.h>

#include "Building.hpp"

/****************************************************************************************************************************************
 * METHOD DEFINITIONS                                                                                                                   *
 ***************************************************************************************************************************************/

namespace Game
{

void Building::init(RawTexture summerTexture, RawTexture winterTexture, RawTexture alternativeSummerTexture,
		RawTexture alternativeWinterTexture, Rect destination) noexcept
{
	plog_trace("Building is being initialized. (destination: %" PRId32 ", %" PRId32 ", %" PRId32 ", %" PRId32 ")",
		destination.x, destination.y, destination.w, destination.h);

	if (nullptr == summerTexture || nullptr == alternativeSummerTexture
	 || nullptr == winterTexture || nullptr == alternativeWinterTexture)
	{
		plog_warn("Building is incomplete!");
	}

	m_summerTexture            = summerTexture;
	m_winterTexture            = winterTexture;
	m_alternativeSummerTexture = alternativeSummerTexture;
	m_alternativeWinterTexture = alternativeWinterTexture;

	m_component.updateTexture(m_summerTexture);
	m_component.updatePosition(destination);
}

void Building::draw(void) noexcept
{
	plog_verbose("Building is being drawn.");
	m_component.draw();
}

void Building::changeWeather(bool isWinter) noexcept
{
	RawTexture currentTexture = m_component.getRawTexture();

	plog_trace("Building weather is being changed. (flag: %" PRId32 ")", static_cast<int32_t>(isWinter));
	if (false == isWinter)
	{
		if (currentTexture == m_summerTexture
		 || currentTexture == m_alternativeSummerTexture)
		{
			plog_warn("Building weather already changed!");
			return;
		}

		if (currentTexture == m_winterTexture)
		{
			if (nullptr == m_summerTexture)
			{
				plog_warn("Building is not changing weather!");
				return;
			}
			m_component.updateTexture(m_summerTexture);
		}
		else if (currentTexture == m_alternativeWinterTexture)
		{
			if (nullptr == m_alternativeSummerTexture)
			{
				plog_warn("Building is not changing weather!");
				return;
			}
			m_component.updateTexture(m_alternativeSummerTexture);
		}
		else
		{
			plog_error("Building is in an invalid state!");
		}
	}
	else
	{
		if (currentTexture == m_winterTexture
		 || currentTexture == m_alternativeWinterTexture)
		{
			plog_warn("Building weather already changed!");
			return;
		}

		if (currentTexture == m_summerTexture)
		{
			if (nullptr == m_winterTexture)
			{
				plog_warn("Building is not changing weather!");
				return;
			}
			m_component.updateTexture(m_winterTexture);
		}
		else if (currentTexture == m_alternativeSummerTexture)
		{
			if (nullptr == m_alternativeWinterTexture)
			{
				plog_warn("Building is not changing weather!");
				return;
			}
			m_component.updateTexture(m_alternativeWinterTexture);
		}
		else
		{
			plog_error("Building is in an invalid state!");
		}
	}
}

void Building::switchTexture(bool isAlternative) noexcept
{
	RawTexture currentTexture = m_component.getRawTexture();

	plog_trace("Building texture is being switched. (flag: %" PRId32 ")", static_cast<int32_t>(isAlternative));
	if (true == isAlternative)
	{
		if (currentTexture == m_alternativeSummerTexture
		 || currentTexture == m_alternativeWinterTexture)
		{
			plog_warn("Building texture already switched!");
			return;
		}

		if (currentTexture == m_summerTexture)
		{
			if (nullptr == m_alternativeSummerTexture)
			{
				plog_error("Building is not switching texture!");
				return;
			}
			m_component.updateTexture(m_alternativeSummerTexture);
		}
		else if (currentTexture == m_winterTexture)
		{
			if (nullptr == m_alternativeWinterTexture)
			{
				plog_error("Building is not switching texture!");
				return;
			}
			m_component.updateTexture(m_alternativeWinterTexture);
		}
		else
		{
			plog_error("Building is in an invalid state!");
		}
	}
	else
	{
		if (currentTexture == m_summerTexture
		 || currentTexture == m_winterTexture)
		{
			plog_warn("Building texture already switched!");
			return;
		}

		if (currentTexture == m_alternativeSummerTexture)
		{
			if (nullptr == m_summerTexture)
			{
				plog_error("Building is not switching texture!");
				return;
			}
			m_component.updateTexture(m_summerTexture);
		}
		else if (currentTexture == m_alternativeWinterTexture)
		{
			if (nullptr == m_winterTexture)
			{
				plog_error("Building is not switching texture!");
				return;
			}
			m_component.updateTexture(m_winterTexture);
		}
		else
		{
			plog_error("Building is in an invalid state!");
		}
	}
}

} /*< namespace Game */
