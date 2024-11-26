/******************************************************************************************************
 * Copyright (C) 2024 Ploae Radu
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

#ifndef HOB_LOG_INTERNAL_SINK_FILE_HPP_
#define HOB_LOG_INTERNAL_SINK_FILE_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "sink_base.hpp"
#include "fstream"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob::log {

class HOB_LOG_LOCAL sink_file final : public sink_base 
{
public:
    sink_file(std::string_view name, const sink_file_configuration& configuration) noexcept(false);
    
    void set_file(const std::filesystem::path& file) noexcept(false);

    [[nodiscard]] std::filesystem::path get_file(void) const noexcept;

    void set_append_mode(bool append_mode) noexcept(false);

    [[nodiscard]] bool get_append_mode(void) const noexcept;

private:
    [[nodiscard]] bool log(std::uint8_t severity_bit, std::string_view message) noexcept override;

private:
    std::ofstream file;
    std::filesystem::path current_file_path;
    bool append_mode;
}







}