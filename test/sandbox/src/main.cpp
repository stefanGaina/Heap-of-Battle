#include <cstdlib>
#include <cstdint>
#include <cassert>

// #include "application.hpp"
#include "logger.hpp"

std::int32_t main(const std::int32_t argument_count, char** const arguments)
{
	// std::unique_ptr<hob::engine::application> application = nullptr;

	assert(0 < argument_count);
	assert(nullptr != arguments);

	try
	{
		hob::log::initialize("TODO");
		HOB_LOG_FATAL("terminal", "test");

		// application = std::make_unique<hob::engine::application>(1 < argument_count ? arguments[1] : "conf.json");
		// application->run();

		return EXIT_SUCCESS;
	}
	catch (const std::exception& exception)
	{
		return EXIT_FAILURE;
	}
}
