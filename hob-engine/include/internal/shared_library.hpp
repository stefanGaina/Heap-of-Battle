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
 * @file shared_library.hpp
 * @author Gaina Stefan
 * @date 17.12.2024
 * @brief This header defines the shared_library class.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_ENGINE_INTERNAL_SHARED_LIBRARY_HPP_
#define HOB_ENGINE_INTERNAL_SHARED_LIBRARY_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <string>
#include <vector>
#include <filesystem>

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob::engine
{

/** ***************************************************************************************************
 * @brief This class abstracts the shared library lazy loading using RAII.
 * @details This class relies on the default copy constructor so in case a copy is done the handle and
 * the returned symbols will be dangling.
 *****************************************************************************************************/
class shared_library final
{
public:
	/** ***********************************************************************************************
	 * @brief Loads shared library from the given path.
	 * @param library_path: Path to the shared library to be loaded.
	 * @throws std::invalid_argument: If the path to the library is empty.
	 * @throws std::runtime_error: If loading the shared library fails.
	 * @throws std::bad_alloc: If creating the error message fails.
	 *************************************************************************************************/
	shared_library(const std::filesystem::path& library_path) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Closes the loaded achieving RAII.
	 * @param void
	 * @throws N/A.
	 *************************************************************************************************/
	~shared_library(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Loads a symbol from the loaded shared library.
	 * @param symbol_name: The name of the symbol to be loaded (can **not** be empty).
	 * @returns The address of the symbol (can not be nullptr).
	 * @throws std::runtime_error: If loading the symbol from the shared library fails.
	 *************************************************************************************************/
	[[nodiscard]] void* get_symbol(std::string_view symbol_name) const noexcept(false);

private:
	/** ***********************************************************************************************
	 * @brief Loads shared library from relative path, LD_LIBRARY_PATH or standard paths.
	 * @param library_path: Path to the shared library to be loaded (can **not** be empty).
	 * @returns Handle to the loaded shared library or nullptr if the operation failed.
	 * @throws std::runtime_error: If loading the shared library fails.
	 * @throws std::bad_alloc: If creating the error message or composing the library paths fails.
	 *************************************************************************************************/
	[[nodiscard]] static void* load_library(const std::filesystem::path& library_path) noexcept(false);

private:
	/** ***********************************************************************************************
	 * @brief The handle needed to load symbols after the loading has succeeded.
	 *************************************************************************************************/
	void* const handle;
};

} /*< namespace hob::engine */

#endif /*< HOB_ENGINE_INTERNAL_SHARED_LIBRARY_HPP_ */
