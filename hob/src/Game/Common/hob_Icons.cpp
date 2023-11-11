#include <plog.h>

#include "hob_Icons.hpp"
#include "hob_Faction.hpp"

/**
 * @brief Full file path of an image used by the icons.
 * @param name: The name of the image (without extension).
*/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("game_menu/icons/" name)

namespace hob
{

Icons::Icons(void) noexcept
	: TextureInitializer
	{
		{
			TEXTURE_FILE_PATH("footman_icon")      , /*< 0  */
			TEXTURE_FILE_PATH("elf_icon")          , /*< 1  */
			TEXTURE_FILE_PATH("knight_icon")       , /*< 2  */
			TEXTURE_FILE_PATH("gryphon_rider_icon"), /*< 3  */
			TEXTURE_FILE_PATH("mage_icon")         , /*< 4  */
			TEXTURE_FILE_PATH("castle_icon")       , /*< 5  */
			TEXTURE_FILE_PATH("keep_icon")         , /*< 6  */
			TEXTURE_FILE_PATH("grunt_icon")        , /*< 7  */
			TEXTURE_FILE_PATH("troll_icon")        , /*< 8  */
			TEXTURE_FILE_PATH("death_rider_icon")  , /*< 9  */
			TEXTURE_FILE_PATH("dragon_icon")       , /*< 10 */
			TEXTURE_FILE_PATH("ogre_icon")         , /*< 11 */
			TEXTURE_FILE_PATH("stronghold_icon")   , /*< 12 */
			TEXTURE_FILE_PATH("hall_icon")           /*< 13 */
		},
		{
			0ULL,
			0ULL,
			0ULL,
			0ULL,
			0ULL
		},
		{
			{
				{ 0L, 0L, 0L, 0L },
				{ 0L, 0L, 0L, 0L },
				{ 0L, 0L, 0L, 0L },
				{ 0L, 0L, 0L, 0L },
				{ 0L, 0L, 0L, 0L }
			}
		}
	}
{

}

void Icons::hide(void) noexcept
{

}

void Icons::setAllianceKeep(void) noexcept
{
	if (true == Faction::getInstance().getFaction())
	{
		m_componentContainer[0ULL].updateTexture(m_textureContainer[0ULL]);
		m_componentContainer[0ULL].updatePosition({ .x = 8L, .y = HSCALE + HSCALE / 2L + 4L, .w = HSCALE - 8L, .h = HSCALE - 8L });

		m_componentContainer[1ULL].updateTexture(m_textureContainer[1ULL]);
		m_componentContainer[1ULL].updatePosition({ .x = 8L, .y = 3L * HSCALE + 4L, .w = HSCALE - 8L, .h = HSCALE - 8L });

		m_componentContainer[2ULL].updateTexture(m_textureContainer[2ULL]);
		m_componentContainer[2ULL].updatePosition({ .x = 8L, .y = 4L * HSCALE + HSCALE / 2L + 4L, .w = HSCALE - 8L, .h = HSCALE - 8L });

		m_componentContainer[3ULL].updateTexture(m_textureContainer[3ULL]);
		m_componentContainer[3ULL].updatePosition({ .x = 8L, .y = 6L * HSCALE + 4L, .w = HSCALE - 8L, .h = HSCALE - 8L });

		m_componentContainer[4ULL].updateTexture(m_textureContainer[4ULL]);
		m_componentContainer[4ULL].updatePosition({ .x = 8L, .y = 7L * HSCALE + HSCALE / 2L + 4L, .w = HSCALE - 8L, .h = HSCALE - 8L });
	}
}

} /*< namespace hob */
