/******************************************************************************************************
 * Copyright (C) 2024 Gaina Stefan
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
 * OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @file scene_plugin.cpp
 * @author Gaina Stefan
 * @date 18.12.2024
 * @brief This file implements the class defined in scene_plugin.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <stdexcept>
#include <logger.hpp>

#include "scene_plugin.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob::engine
{

scene_plugin::scene_plugin(const std::filesystem::path& library_path, const std::string_view scene_name, const std::filesystem::path& configuration) noexcept(false)
	: library{ true == library_path.empty() ? std::filesystem::path{ get_library_name(scene_name) } : library_path / get_library_name(scene_name) }
	, create_scene_call{ reinterpret_cast<create_scene_function>(library.get_symbol(CREATE_SCENE_FUNCTION_NAME)) }
	, destroy_scene_call{ reinterpret_cast<destroy_scene_function>(library.get_symbol(DESTROY_SCENE_FUNCTION_NAME)) }
	, name{ scene_name }
	, configuration{ configuration }
	, plugin{ nullptr }
{
	hob_log_default_assert(nullptr != create_scene_call);
	hob_log_default_assert(nullptr != destroy_scene_call);
	hob_log_default_trace("Scene plugin is being constructed. (path: \"{}\") (name: \"{}\") (configuration: \"{}\")", library_path.string(), scene_name,
						  configuration.string());
}

const std::string& scene_plugin::get_name(void) const noexcept
{
	hob_log_default_assert(nullptr != this);
	hob_log_default_trace("Scene name is being got. (name: \"{}\")", name);

	return name;
}

scene* scene_plugin::get_instance(void) noexcept(false)
{
	hob_log_default_trace("Scene instance is being got.");
	return nullptr != plugin ? plugin : create_scene();
}

void scene_plugin::destroy_scene(void) noexcept
{
	hob_log_default_assert(nullptr != this);
	hob_log_default_assert(nullptr != destroy_scene_call);
	hob_log_default_expect(nullptr != plugin);
	hob_log_default_debug("Scene instance is being destroyed. (destroy function: \'{:p}\')", reinterpret_cast<void*>(destroy_scene_call));

	(*destroy_scene_call)(plugin);
	plugin = nullptr;
}

const std::filesystem::path& scene_plugin::get_configuration_file_path(void) const noexcept
{
	hob_log_default_assert(nullptr != this);
	hob_log_default_trace("Configuration is being got. (file path: \"{}\")", configuration.string());

	return configuration;
}

std::string scene_plugin::get_library_name(const std::string_view scene_name) noexcept(false)
{
	hob_log_default_assert(false == scene_name.empty());
	hob_log_default_trace("Library name is being got. (scene name: \"{}\")", scene_name);

#ifdef __linux__
	return "lib" + std::string{ scene_name } + ".so";
#elif __APPLE__
	return "lib" + std::string{ scene_name } + ".dylib";
#elif _WIN32
	return std::string{ scene_name } + ".dll";
#else
#error "Unsupported platform detected!"
#endif
}

scene* scene_plugin::create_scene(void) noexcept(false)
{
	hob_log_default_assert(nullptr != this);
	hob_log_default_assert(nullptr != create_scene_call);
	hob_log_default_assert(nullptr == plugin);
	hob_log_default_debug("Scene instance is being created. (create function: \'{:p}\')", reinterpret_cast<void*>(create_scene_call));

	plugin = (*create_scene_call)();
	return nullptr != plugin ? plugin : throw std::runtime_error{ "Invalid address returned from the plugin!" };
}

} /*< namespace hob::engine */
