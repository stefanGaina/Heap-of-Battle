#include <plog.h>

#include "hob_Gold.hpp"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief Full file path of an image used by the gold.
 * @param name: The name of the image (without extension).
*/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("game_menu/gold/" name)

namespace hob
{

Gold::Gold(const uint8_t amount) noexcept
	: TextureInitializer
	{
		{
			TEXTURE_FILE_PATH("gold_0"), /*< 0  */
			TEXTURE_FILE_PATH("gold_1"), /*< 1  */
			TEXTURE_FILE_PATH("gold_2"), /*< 2  */
			TEXTURE_FILE_PATH("gold_3"), /*< 3  */
			TEXTURE_FILE_PATH("gold_4"), /*< 4  */
			TEXTURE_FILE_PATH("gold_5"), /*< 5  */
			TEXTURE_FILE_PATH("gold_6"), /*< 6  */
			TEXTURE_FILE_PATH("gold_7"), /*< 7  */
			TEXTURE_FILE_PATH("gold_8"), /*< 8  */
			TEXTURE_FILE_PATH("gold_9"), /*< 9  */
			TEXTURE_FILE_PATH("gold")    /*< 10 */
		},
		{
			0ULL, 0ULL, 0ULL, 10ULL
		},
		{
			{
				{ 15L              , SCALE / 9L, SCALE / 3L, SCALE / 3L },
				{ HSCALE / 2L + 15L, SCALE / 9L, SCALE / 3L, SCALE / 3L },
				{ HSCALE + 15L     , SCALE / 9L, SCALE / 3L, SCALE / 3L },
				{ 2 * HSCALE + 5L  , SCALE / 9L, SCALE / 3L, SCALE / 3L }
			}
		}
	}
	, SoundInitializer
	{
		{
			HOB_SOUNDS_FILE_PATH("gold_received")
		}
	}
	, m_queue         {}
	, m_previousAmount{ amount }
{
	--m_previousAmount;
	update(m_previousAmount + 1U);
}

void Gold::draw(void) noexcept
{
	uint8_t amount = 0U;

	plog_verbose("Gold is being drawn.");
	while (false == m_queue.isEmpty())
	{
		amount = m_queue.get();

		m_componentContainer[2].updateTexture(m_textureContainer[amount % 10]);
		amount /= 10;
		if (0U == amount)
		{
			m_componentContainer[1].updateTexture(NULL);
			m_componentContainer[0].updateTexture(NULL);
			continue;
		}

		m_componentContainer[1].updateTexture(m_textureContainer[amount % 10]);
		amount /= 10;
		if (0U == amount)
		{
			m_componentContainer[0].updateTexture(NULL);
			continue;
		}
		m_componentContainer[0].updateTexture(m_textureContainer[amount % 10]);
	}

	TextureInitializer::draw();
}

void Gold::update(const uint8_t amount) noexcept
{
	plog_trace("Gold is being updated. (amount: %" PRIu8 ")", amount);
	if (amount == m_previousAmount)
	{
		return;
	}

	if (amount > m_previousAmount)
	{
		plog_verbose("Gold increased.");
		m_soundContainer[0].play();
	}
	m_previousAmount = amount;
	m_queue.put(m_previousAmount);
}

} /*< namespace hob */
