#ifndef HOB_ENGINE_INTERNAL_APPLICATION_IMPL_HPP_
#define HOB_ENGINE_INTERNAL_APPLICATION_IMPL_HPP_

#include "SFML/Graphics.hpp"

namespace hob::engine
{

class application_impl final
{
public:
	application_impl(const std::string_view configuration_file) noexcept(false);

	void run(void) noexcept(false);

private:
	void draw(void) noexcept;

	void handle_events(void) noexcept;

private:
	sf::RenderWindow window;
};

} /*< namespace hob::engine */

#endif /*< HOB_ENGINE_INTERNAL_APPLICATION_IMPL_HPP_ */
