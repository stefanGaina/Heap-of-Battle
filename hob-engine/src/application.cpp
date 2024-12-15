#include <logger.hpp>

#include "application.hpp"
#include "application_impl.hpp"

namespace hob::engine
{

application::application(const std::string_view configuration_file) noexcept(false)
	: implementation{ std::make_unique<application_impl>(configuration_file) }
{
}

application::~application(void) noexcept = default;

void application::run(void) noexcept(false)
{
	hob_log_default_assert(nullptr != this);
	hob_log_default_assert(nullptr != implementation);

	implementation->run();
}

} /*< namespace hob::engine */
