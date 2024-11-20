#ifndef HOB_LOG_INTERNAL_SINK_MANAGER_HPP_
#define HOB_LOG_INTERNAL_SINK_MANAGER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <vector>
#include <memory>
#include <cassert>

#include "types.hpp"

/******************************************************************************************************
 * CONSTANTS
 *****************************************************************************************************/

namespace hob::log
{

/** ***************************************************************************************************
 * @brief The message that is attached to the exception thrown when a sink that does not support an
 * operation is about to be used.
 *****************************************************************************************************/
inline constexpr const char* OPERATION_NOT_SUPPORTED_MESSAGE = "The sink does not support this operation!";

/******************************************************************************************************
 * FORWARD DECLARATIONS
 *****************************************************************************************************/

class sink;

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief This class manages the instances of the sinks offering methods to add, remove or modify them.
 *****************************************************************************************************/
class sink_manager final
{
public:
	/** ***********************************************************************************************
	 * @brief TODO
	 * @param configuration_file_path: TODO
	 * @throws TODO
	 *************************************************************************************************/
	sink_manager(std::string_view configuration_file_path) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Removes all the sinks and writes configuration changes to the file.
	 * @param void
	 *************************************************************************************************/
	~sink_manager(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Adds the terminal sink to the logger. It is **not** thread-safe.
	 * @param sink_name: TODO
	 * @param configuration: The parameters that will be configured with.
	 * @returns void
	 * @throws std::logic_error: If the terminal sink has already been added.
	 * @throws std::invalid_argument: If the stream is **not** stdout or stderr or severity level is
	 * not in the [0, 63] interval.
	 * @throws std::bad_alloc: If the memory allocation of the sink or making the copy of the name
	 * fails.
	 *************************************************************************************************/
	void add_sink(std::string_view sink_name, const sink_terminal_configuration& configuration) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Removes a sink, making it not usable anymore. This function does not fail if the sink
	 * has not been added. It is **not** thread-safe.
	 * @param sink_name: The name of the sink to be removed.
	 * @returns void
	 * @throws N/A.
	 *************************************************************************************************/
	void remove_sink(std::string_view sink_name) noexcept;

	/** ***********************************************************************************************
	 * @brief Checks if the name of a sink is valid. It is thread-safe.
	 * @param sink_name: The name of the sink to be checked.
	 * @returns true - the sink name is valid, this can be used.
	 * @returns false - the sink name is invalid, using this will result in errors.
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] bool is_sink_valid(std::string_view sink_name) const noexcept;

	/** ***********************************************************************************************
	 * @brief Sets the name of the default sink that will be used when logging with default macros. It
	 * is **not** thread-safe.
	 * @param sink_name: The name of the default sink (empty string to invalidate the logging macro
	 * calls).
	 * @returns void
	 * @throws std::bad_alloc: If making the copy of the name fails.
	 *************************************************************************************************/
	void set_default_sink_name(std::string_view sink_name) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Gets the name of the sink that is used when logging with default macros. It is
	 * thread-safe.
	 * @param void
	 * @returns The name of the default sink.
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] std::string_view get_default_sink_name(void) const noexcept;

	/** ***********************************************************************************************
	 * @brief Finds the sink object by its name. It is thread-safe.
	 * @param sink_name: The name of the searched sink.
	 * @returns Reference to the sink.
	 * @throws std::invalid_argument: If the sink has not been found or the operation is not supported.
	 *************************************************************************************************/
	template<typename TYPE>
	[[nodiscard]] TYPE& get_sink(std::string_view sink_name) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Finds the sink object by its name. It is thread-safe.
	 * @param sink_name: The name of the searched sink.
	 * @returns Const reference to the sink.
	 * @throws std::invalid_argument: If the sink has not been found or the operation is not supported.
	 *************************************************************************************************/
	template<typename TYPE>
	[[nodiscard]] const TYPE& get_sink(std::string_view sink_name) const noexcept(false);

private:
	/** ***********************************************************************************************
	 * @brief Throws an exception if the sink name is not a correct one to be added.
	 * @param sink_name: The name of the queried sink.
	 * @returns void
	 * @throws std::logic_error: If the sink has already been added.
	 * @throws std::invalid_argument: If the sink name is reserved (e.g. terminal sink name).
	 *************************************************************************************************/
	void throw_if_sink_name_invalid(std::string_view sink_name) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Finds the sink object by its name. It is thread-safe.
	 * @param sink_name: The name of the searched sink.
	 * @returns Reference to the generic sink.
	 * @throws std::invalid_argument: If the sink has not been found.
	 *************************************************************************************************/
	[[nodiscard]] std::shared_ptr<sink>& get_sink(std::string_view sink_name) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Finds the sink object by its name. It is thread-safe.
	 * @param sink_name: The name of the searched sink.
	 * @returns Const reference to the generic sink.
	 * @throws std::invalid_argument: If the sink has not been found.
	 *************************************************************************************************/
	[[nodiscard]] const std::shared_ptr<sink>& get_sink(std::string_view sink_name) const noexcept(false);

private:
	/** ***********************************************************************************************
	 * @brief The path to the configuration file, this is needed in case an update of the
	 * configuration needs to be written at destruction.
	 *************************************************************************************************/
	const std::string configuration_file_path;

	/** ***********************************************************************************************
	 * @brief The name of the sink that will be used in the default macros.
	 *************************************************************************************************/
	std::string default_sink_name;

	/** ***********************************************************************************************
	 * @brief The collection of the different type of sinks.
	 *************************************************************************************************/
	std::vector<std::shared_ptr<sink>> sinks;
};

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

template<typename TYPE>
TYPE& sink_manager::get_sink(const std::string_view sink_name) noexcept(false)
{
	const std::shared_ptr<TYPE> sink = std::dynamic_pointer_cast<TYPE>(get_sink(sink_name));

	assert(nullptr != this);
	return nullptr != sink ? *sink : throw std::invalid_argument{ OPERATION_NOT_SUPPORTED_MESSAGE };
}

template<typename TYPE>
const TYPE& sink_manager::get_sink(const std::string_view sink_name) const noexcept(false)
{
	const std::shared_ptr<TYPE> sink = std::dynamic_pointer_cast<TYPE>(get_sink(sink_name));

	assert(nullptr != this);
	return nullptr != sink ? *sink : throw std::invalid_argument{ OPERATION_NOT_SUPPORTED_MESSAGE };
}

} /*< namespace hob::log */

#endif /*< HOB_LOG_INTERNAL_SINK_MANAGER_HPP_ */
