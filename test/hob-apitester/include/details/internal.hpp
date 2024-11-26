#ifndef HOB_APITESTER_DETAILS_INTERNAL_HPP_
#define HOB_APITESTER_DETAILS_INTERNAL_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <vector>
#include <list>
#include <functional>
#include <type_traits>
#include <cassert>

#include "details/argument.hpp"

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief TODO
 * @param function_name: TODO
 * @param VA_ARGS: TODO
 * @returns N/A.
 * @throws N/A.
 *****************************************************************************************************/
#define HOB_APITEST_INTERNAL(function_name, ...)                                                                                                                   \
	namespace function_name##_apitest_namespace_argument                                                                                                           \
	{                                                                                                                                                              \
		__VA_OPT__(static hob::apitester::details::argument __VA_ARGS__;)                                                                                          \
		static void function_name##_apitest_user_definition(void) noexcept(false);                                                                                 \
		namespace function_name##_apitest_namespace_function                                                                                                       \
		{                                                                                                                                                          \
			static void function_name##_apitest_function(const std::vector<hob::apitester::details::argument>& arguments) noexcept(false)                          \
			{                                                                                                                                                      \
				hob::apitester::details::assign_arguments(arguments __VA_OPT__(, __VA_ARGS__));                                                                    \
				function_name##_apitest_user_definition();                                                                                                         \
			}                                                                                                                                                      \
			static hob::apitester::details::function_registrar function_name##_apitest_obj = { #function_name, function_name##_apitest_function, #__VA_ARGS__ };   \
		} /*< namespace function_name##_apitest_namespace_function */                                                                                              \
	}	  /*< namespace function_name##_apitest_namespace_argument */                                                                                              \
	static void function_name##_apitest_namespace_argument::function_name##_apitest_user_definition(void) noexcept(false)

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob::apitester::details
{

/** ***************************************************************************************************
 * @brief The prototype of the generated function by the HOB_APITEST() macro.
 *****************************************************************************************************/
using function_prototype = std::function<void(std::vector<argument>&)>;

/** ***************************************************************************************************
 * @brief This class serves as the bridge between the user's implementations and the main flow. It is
 * meant only for internal use.
 *****************************************************************************************************/
class function_registrar final
{
public:
	/** ***********************************************************************************************
	 * @brief This object serves only to trigger the contructor so that the user's function is added
	 * into the registry at runtime.
	 * @param name: The name the user needs to input to trigger the function.
	 * @param function: The function that will be called when the name is being matched.
	 * @param argument_names: String of format "argument1, argument2, etc." enumerating the name of the
	 * arguments that need to be inputted by the user to make the function call successfully.
	 * @throws TODO
	 *************************************************************************************************/
	function_registrar(std::string_view name, function_prototype function, std::string_view argument_names) noexcept(false);

private:
	/** ***********************************************************************************************
	 * @brief TODO
	 * @param argument_names: TODO
	 * @returns TODO
	 * @throws std::bad_alloc: If the creation of the list fails.
	 *************************************************************************************************/
	std::list<std::string> split_argument_names(std::string_view argument_names) noexcept(false);
};

/******************************************************************************************************
 * FUNCTION DEFINITIONS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Function used to transform the text inputted in the terminal into objects that can be used
 * by the user. It is meant only for internal use. It is thread-safe.
 * @tparam args: Variable number of hob::apitester::details::argument objects.
 * @param runtime_arguments: The text of the arguments that is got at runtime.
 * @param arguments: The hob::apitester::details::argument objects that are instantiated by the
 * HOB_APITEST() macro.
 * @throws std::bad_alloc: If making the arguments copies fails.
 *****************************************************************************************************/
template<typename... args>
void assign_arguments(const std::vector<argument>& runtime_arguments, args&... arguments) noexcept(false)
{
	std::size_t index = 0UL;

	static_assert((std::is_convertible_v<args, argument> && ...), "All arguments must be convertible to hob::apitester::details::argument!");
	assert(runtime_arguments.size() == sizeof...(arguments));

	((arguments = runtime_arguments[index++]), ...);
}

} /*< namespace hob::apitester::details */

#endif /*< HOB_APITESTER_DETAILS_INTERNAL_HPP_ */
