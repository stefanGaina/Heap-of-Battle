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
 * @file scene_plugin.hpp
 * @author Gaina Stefan
 * @date 18.12.2024
 * @brief This header defines the scene_plugin class.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_ENGINE_INTERNAL_SCENE_PLUGIN_HPP_
#define HOB_ENGINE_INTERNAL_SCENE_PLUGIN_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "scene.hpp"
#include "shared_library.hpp"
#include "details/visibility.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob::engine
{

/** ***************************************************************************************************
 * @brief This class abstracts the loading of the scene plugin's shared library by exposing its API
 * directly.
 *****************************************************************************************************/
class HOB_ENGINE_LOCAL scene_plugin final
{
public:
	/** ***********************************************************************************************
	 * @brief Loads shared library and symbols of create and destroy logging plugin functions from
	 * relative path, LD_LIBRARY_PATH or standard paths.
	 * @param library_path: Path to the plugin's shared library to be loaded.
	 * @param scene_name: The name of the scene, without extension.
	 * @throws std::invalid_argument: If the path to the library is empty.
	 * @throws std::runtime_error: If loading the shared library or loading the symbol from the shared
	 * library fails.
	 * @throws std::bad_alloc: If creating the error message or composing the library path fails.
	 *************************************************************************************************/
	scene_plugin(const std::filesystem::path& library_path, std::string_view scene_name, const std::filesystem::path& configuration) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Gets the name of the scene. It can be called even if there is no instance. It is
	 * thread-safe.
	 * @param void
	 * @returns The name of the scene.
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] const std::string& get_name(void) const noexcept;

	/** ***********************************************************************************************
	 * @brief Gets the scene instance created from the plugin. If there is not an instance, creates it.
	 * It is thread-safe.
	 * @param void
	 * @returns The reference to the scene (can not be nullptr).
	 * @throws std::runtime_error: If the creation of the instance fails.
	 *************************************************************************************************/
	[[nodiscard]] scene* get_instance(void) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Destroys the plugin object by calling the destroy function exposed by the shared library.
	 * It is **not** thread-safe.
	 * @param void
	 * @returns void
	 * @throws N/A.
	 *************************************************************************************************/
	void destroy_scene(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Gets the configuration file associated with this scene. It is thread-safe.
	 * @param void
	 * @returns The configuration file from the game configuration.
	 * @throws N/A.
	 *************************************************************************************************/
	const std::filesystem::path& get_configuration_file_path(void) const noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Gets the library name depending on the platform. It is thread-safe.
	 * @param scene_name: The name of the scene.
	 * @returns Linux: "libscene_name.so".
	 * @returns MacOS: "libscene_name.dylib".
	 * @returns Windows: "scene_name.dll".
	 * @throws std::bad_alloc: If allocating memory for the string fails.
	 *************************************************************************************************/
	[[nodiscard]] static std::string get_library_name(std::string_view scene_name) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Creates a scene plugin object by calling the create function exposed by the shared
	 * library, or gets the already created plugin. It is **not** thread-safe.
	 * @param void
	 * @returns Reference to the created plugin object (destroy_scene() needs to be called).
	 * @throws std::runtime_error: If an invalid plugin address has been returned.
	 *************************************************************************************************/
	[[nodiscard]] scene* create_scene(void) noexcept(false);

private:
	/** ***********************************************************************************************
	 * @brief The library from which the function will be loaded.
	 *************************************************************************************************/
	const shared_library library;

	/** ***********************************************************************************************
	 * @brief The loaded function that will be called to create the scene plugin object.
	 *************************************************************************************************/
	const create_scene_function create_scene_call;

	/** ***********************************************************************************************
	 * @brief The loaded function that will be called to destroy the scene plugin object.
	 *************************************************************************************************/
	const destroy_scene_function destroy_scene_call;

	/** ***********************************************************************************************
	 * @brief The name of the scene.
	 *************************************************************************************************/
	const std::string name;

	/** ***********************************************************************************************
	 * @brief The path of the configuration file associated with this scene.
	 *************************************************************************************************/
	const std::filesystem::path configuration;

	/** ***********************************************************************************************
	 * @brief Reference to the created scene from the shared library.
	 *************************************************************************************************/
	scene* plugin;
};

} /*< namespace hob::engine */

#endif /*< HOB_ENGINE_INTERNAL_SCENE_PLUGIN_HPP_ */
