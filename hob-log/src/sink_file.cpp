
#include <stdexcept>

#include "sink_file.hpp"
#include "utility.hpp"


namespace hob::log
{
    
sink_file::sink_file(std::string_view name, const sink_file_configuration& configuration) noexcept(false)
    : sink_base{ name, configuration.base }
    , current_file_path{}
    , append_mode{ false }
{
    set_file(configuration.file_path);
    set_append_mode(configuration.append_mode);
}

void sink_file::set_file(const std::filesystem::path& file_path) noexcept(false) {

    assert(this != nullptr);

    if (file_path.empty()) {
        throw std::invalid_argument{"File path cannot be empty"};
    }

    current_file_path = file_path;

    std::ios_base::openmode mode = std::ios_base::out;
    mode |= append_mode ? std::ios_base::app : std::ios_base::trunc;

    file.close(); // Close any previously opened file.
    file.open(current_file_path, mode);

    if (!file.is_open()) {
        throw std::ios_base::failure{"Failed to open the log file"};
    }
}

std::filesystem::path sink_file::get_file(void) const noexcept {
    return current_file_path;
}

void sink_file::set_append_mode(bool append_mode) noexcept(false) {
    if (this->append_mode != append_mode) {
        this->append_mode = append_mode;
        set_file(current_file_path); // Reopen file with new mode.
    }
}

bool sink_file::get_append_mode(void) const noexcept {
    return append_mode;
}

bool sink_file::log(std::uint8_t severity_bit, std::string_view message) noexcept {
    
    assert(this != nullptr);

    try {
        // Check if the file stream is open.
        if (!file.is_open()) {
            return false; // Log is lost if the file is not open.
        }

        // Write the log message to the file.
        file << "[" << severity_to_string(severity_bit) << "] " << message << '\n';

        // Ensure the output buffer is flushed to the file.
        file.flush();

        return true; // Log written successfully.
    } catch (const std::exception& e) {
        // Handle any exceptions thrown during logging.
        DEBUG_PRINT("Exception while logging to file: {}", e.what());
        return false; // Log is lost due to an error.
    }
}




}