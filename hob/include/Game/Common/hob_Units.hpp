#ifndef HOB_UNITS_HPP_
#define HOB_UNITS_HPP_

#include <list>

#include "hob_TextureInitializer.hpp"
#include "hobGame_Game.hpp"


namespace hob
{

class Units final : public TextureInitializer<2ULL, 0ULL>
{
public:
	Units(void) noexcept;

	~Units(void) = default;

	void draw(void) noexcept override;

	void add(hobGame::Unit unit) noexcept;

private:
	std::list<Component> m_components;
};

} /*< namespace hob */


#endif /*< HOB_UNITS_HPP_ */
