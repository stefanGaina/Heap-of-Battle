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
 * @file application.cpp
 * @author Gaina Stefan
 * @date 17.12.2024
 * @brief This file implements the class defined in application.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <logger.hpp>

#include "application.hpp"
#include "application_impl.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob::engine
{

application::application(const std::string_view configuration_file) noexcept(false)
	: implementation{ std::make_unique<application_impl>(configuration_file) }
{
	hob_log_default_trace("Application is being constructed. (implementation: \'{:p}\')", reinterpret_cast<void*>(implementation.get()));
}

application::~application(void) noexcept = default;

void application::run(void) noexcept(false)
{
	hob_log_default_assert(nullptr != this);
	hob_log_default_assert(nullptr != implementation);
	hob_log_default_trace("Application is being run. (implementation: \'{:p}\')", reinterpret_cast<void*>(implementation.get()));

	implementation->run();
}

} /*< namespace hob::engine */
