#ifndef BUILDINGS1_HPP_
#define BUILDINGS1_HPP_

#include "TextureInitializer.hpp"
#include "BuildingInitializer.hpp"

namespace Game
{

class Buildings1 final : public Common::TextureInitializer<29, 0>
					   , public BuildingInitializer<18>
{
public:
	Buildings1(void) noexcept;

	virtual void draw(void) noexcept override;

	void changeWeather(bool isWinter) noexcept;

private:
	bool m_previousSeason;
}; /*< class Buildings1 */

} /*< namespace Game */

#endif /*< BUILDINGS1_HPP_ */
