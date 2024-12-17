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
 * @file shared_library.cpp
 * @author Gaina Stefan
 * @date 17.12.2024
 * @brief This file implements the class defined in shared_library.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <stdexcept>
#include <format>
#include <dlfcn.h>
#include <logger.hpp>

#include "shared_library.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob::engine
{

shared_library::shared_library(const std::filesystem::path& library_path) noexcept(false)
	: handle{ false == library_path.empty() ? load_library(library_path) : throw std::invalid_argument{ "Scene name is empty!" } }
{
	hob_log_default_assert(nullptr != handle);
	hob_log_default_trace("Shared library is being constructed. (library path: \"{}\") (handle: {:p})", library_path.string(), handle);
}

shared_library::~shared_library(void) noexcept
{
	hob_log_default_assert(nullptr != handle);
	hob_log_default_trace("Shared library is being destructed. (handle: {:p})", handle);

	if (0 != dlclose(handle))
	{
		hob_log_default_warn("Failed to close opened shared library! (error message: \"{}\")", dlerror());
	}
}

void* shared_library::get_symbol(const std::string_view symbol_name) const noexcept(false)
{
	void* const symbol = dlsym(handle, symbol_name.data());

	hob_log_default_assert(nullptr != this);
	hob_log_default_assert(nullptr != handle);
	hob_log_default_assert(false == symbol_name.empty());

	return nullptr != symbol ? symbol : throw std::runtime_error{ std::format("Failed to load \"{}\" symbol! (error message: \"{}\")", symbol_name, dlerror()) };
}

void* shared_library::load_library(const std::filesystem::path& library_path) noexcept(false)
{
	void* const handle = dlopen(library_path.string().c_str(), RTLD_LAZY);

	hob_log_default_trace("Library is being loaded. (library path: \"{}\")", library_path.string());
	return nullptr != handle
			   ? handle
			   : throw std::runtime_error{ std::format("Failed to open \"{}\" shared library! (error message: \"{}\")", library_path.string(), dlerror()) };
}

} /*< namespace hob::engine */
