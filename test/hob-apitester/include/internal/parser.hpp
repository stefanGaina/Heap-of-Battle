#ifndef APITEST_INTERNAL_PARSER_HPP_
#define APITEST_INTERNAL_PARSER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <map>

#include "internal.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob::apitester
{

/**
 * @brief 
 */
struct function_data
{
	details::function_prototype function;		 /**<  */
	std::size_t					arguments_count; /**<  */
};

/**
 * @brief 
 */
class parser final
{
public:
	static void initialize(void) noexcept;

	/**
	 * @brief 
	 * @param file_path 
	 * @returns void
	 * @throws
	 */
	static void parse_from_file(const char* file_path) noexcept(false);

	/**
	 * @brief
	 * @param void
	 * @returns void
	 * @throws
	 */
	static void parse_from_terminal(void) noexcept(false);

	/**
	 * @brief This method exists to ensure that the registry is constructed when it is used by the
	 * FunctionRegistrar global objects at their construction.
	 * @param void
	 * @returns 
	 * @throws N/A.
	 */
	static std::map<std::string, function_data>& get_registry(void) noexcept;

	/**
	 * @brief 
	 * @param function_name 
	 * @param function 
	 * @param argument_names 
	 * @returns void
	 * @throws
	 */
	static void
	register_function(std::string_view function_name, details::function_prototype function, const std::list<std::string>& argument_names) noexcept(false);

private:
	/**
	 * @brief 
	 * @param command 
	 * @returns void
	 * @throws
	 */
	static void handle_command(const std::string& command) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Converts the command string into internal data format.
	 * @param command: The command that has been inputted by the user.
	 * @returns The arguments splitted by white spaces and quotes.
	 * @throws std::bad_alloc: If the appending of the arguments fails.
	 *************************************************************************************************/
	static std::vector<details::argument> split_arguments(const std::string& command) noexcept(false);

	/** ***********************************************************************************************
	 * @brief This function is used to generate function name matches for rl_completion_matches. This
	 * is not meant to be called.
	 * @param text: The text that is inputted by the user when Tab is being pressed.
	 * @param state: 0 - it the first time this function is being called in the current session.
	 * @returns A dynamically allocated string that is in the ownership of readline library.
	 * @returns nullptr - a match has not been found or a memory allocation error has occured.
	 * @throws N/A.
	 *************************************************************************************************/
	static char* character_name_generator(const char* text, std::int32_t state) noexcept;

	/** ***********************************************************************************************
	 * @brief This is the function that is called whenever Tab is being pressed by the user. This is
	 * not meant to be called.
	 * @param text: The text that is inputted by the user when Tab is being pressed.
	 * @param start: Not used.
	 * @param end: Not used.
	 * @returns An array of strings as documented for rl_completion_matches.
	 * @throws N/A.
	 *************************************************************************************************/
	static char** character_name_completion(const char* text, std::int32_t start, std::int32_t end) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief The message that is composed by the function names and arguments which is printed when
	 * the help menu is requested by the user.
	 *************************************************************************************************/
	static std::string help_string;
};

} /*< namespace hob::apitester */

#endif /*< APITEST_INTERNAL_PARSER_HPP_ */
