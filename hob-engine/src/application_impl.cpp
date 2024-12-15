
#include <logger.hpp>

#include "application_impl.hpp"
#include "test.hpp"

namespace hob::engine
{

application_impl::application_impl(const std::string_view configuration_file) noexcept(false)
	: window{ { 1280, 720 }, "heap-of-battle", sf::Style::Titlebar | sf::Style::Close }
{
	hob_log_default_trace("Application is constructed. (configuration file: {})", configuration_file);

	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);
}

void application_impl::run(void) noexcept(false)
{
	hob_log_default_assert(nullptr != this);
	hob_log_default_assert(true == window.isOpen());
	hob_log_default_trace("Application is being run.");

	while (true == window.isOpen())
	{
		draw();
		handle_events();
	}
}

void application_impl::draw(void) noexcept
{
	hob_log_default_assert(nullptr != this);
	hob_log_default_assert(true == window.isOpen());
	hob_log_default_trace("Graphics are being drawn.");

	window.clear();

	window.display();
}

void application_impl::handle_events(void) noexcept
{
	sf::Event event = {};

	hob_log_default_assert(nullptr != this);
	hob_log_default_assert(true == window.isOpen());
	hob_log_default_trace("Events are being handled.");

	while (true == hob_engine_poll_event(window, event))
	{
	}
}

// json -> "name": .so + json | starting scene | window conf
// init all
// load scene
// draw handle event
// unload scene
// load new scene

} /*< namespace hob::engine */
