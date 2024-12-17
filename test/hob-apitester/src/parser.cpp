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
 * @file parser.cpp
 * @author Gaina Stefan
 * @date 26.11.2024
 * @brief This file implements the class defined in internal/parser.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <fstream>
#include <sstream>
#include <print>
#include <cassert>
#include <readline/readline.h>
#include <readline/history.h>

#include "parser.hpp"
#include "invalid_argument.hpp"
#include "out_of_range.hpp"

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

namespace hob::apitester
{

std::string parser::help_string = {};

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

void parser::initialize(void) noexcept
{
	(void)rl_bind_key('\t', rl_complete);
	rl_attempted_completion_function = character_name_completion;
}

void parser::parse_from_file(const char* const file_path) noexcept(false)
{
	std::ifstream file = std::ifstream{ file_path };
	std::string	  line = {};

	assert(nullptr != file_path);

	if (false == file.is_open())
	{
		std::println("Failed to open \"{}\"!", file_path);
		return;
	}

	std::println("Reading from \"{}\"...", file_path);

	while (std::getline(file, line))
	{
		std::print("\n$ ");
		handle_command(line.c_str());
	}
}

void parser::parse_from_terminal(void) noexcept(false)
{
	char* command = nullptr;

	while (true)
	{
		std::println();

		command = readline("$ ");
		if (nullptr == command)
		{
			throw std::bad_alloc{};
		}

		handle_command(command);

		free(command);
		command = nullptr;
	}
}

std::map<std::string, function_data>& parser::get_registry(void) noexcept
{
	static std::map<std::string, function_data> registry = {};
	return registry;
}

void parser::register_function(const std::string_view function_name, details::function_prototype function, const std::list<std::string>& argument_names) noexcept(
	false)
{
	assert(false == function_name.empty());

	help_string += function_name;
	for (const auto& argument_name : argument_names)
	{
		help_string += " <";
		help_string += argument_name;
		help_string += '>';
	}
	help_string += '\n';

	get_registry()[function_name.data()] = { function, argument_names.size() };
}

void parser::handle_command(const std::string& command) noexcept(false)
{
	std::vector<details::argument> arguments	 = {};
	std::string					   function_name = {};

	if ("" == command)
	{
		return;
	}

	add_history(command.c_str());
	std::println("{}", command);

	if ("q" == command || "quit" == command)
	{
		std::println();
		exit(EXIT_SUCCESS);
	}

	if ("h" == command || "help" == command)
	{
		std::print("{}", help_string);
		return;
	}

	arguments = split_arguments(command);
	if (0UL == get_registry().count(static_cast<std::string>(arguments[0])))
	{
		std::println("\"{}\" is an invalid function name! Type \"h\" or \"help\" to display the list of valid function names!",
					 static_cast<std::string>(arguments[0]));
		return;
	}

	function_name = static_cast<std::string>(arguments.front());
	arguments.erase(arguments.begin());

	if (arguments.size() != get_registry()[function_name].arguments_count)
	{
		std::println("{} passed, but {} required! Type \"h\" or \"help\" to display the function parameters!",
					 0UL == arguments.size()   ? "No argument was"
					 : 1UL == arguments.size() ? "1 argument was"
											   : std::format("{} arguments were", arguments.size()),
					 0UL == get_registry()[function_name].arguments_count	? "no argument is"
					 : 1UL == get_registry()[function_name].arguments_count ? "1 argument is"
																			: std::format("{} arguments are", get_registry()[function_name].arguments_count));
		return;
	}

	try
	{
		get_registry()[function_name].function(arguments);
	}
	catch (const invalid_argument& exception)
	{
		std::println("Invalid argument! \"{}\"", exception.what());
	}
	catch (const out_of_range& exception)
	{
		std::println("Out of range! \"{}\"", exception.what());
	}
	catch (const std::bad_alloc& exception)
	{
		std::println("Out of memory!");
	}
	catch (const std::exception& exception)
	{
		std::println("Caught \'std::exception\'! (message: \"{}\")", exception.what());
	}
	catch (...)
	{
		std::println("Caught an unkown exception!");
	}
}

std::vector<details::argument> parser::split_arguments(const std::string& command) noexcept(false)
{
	std::istringstream			   string_stream = std::istringstream{ command };
	std::vector<details::argument> arguments	 = {};
	std::string					   current_word	 = {};
	char						   character	 = '\0';
	bool						   inside_quotes = false;

	while (string_stream.get(character))
	{
		if ((' ' == character || '\t' == character) && false == inside_quotes)
		{
			if (false == current_word.empty())
			{
				arguments.emplace_back(current_word);
				current_word.clear();
			}
			continue;
		}

		if ('\"' == character)
		{
			inside_quotes = !inside_quotes;
			continue;
		}

		current_word += character;
	}

	if (false == current_word.empty())
	{
		arguments.emplace_back(current_word);
	}

	if (true == inside_quotes)
	{
		std::println("Opened quotes have not been closed!");
	}

	return arguments;
}

char* parser::character_name_generator(const char* const text, const std::int32_t state) noexcept
{
	static std::vector<std::string> matches		= {};
	static std::size_t				match_index = 0UL;

	std::map<std::string, function_data>& registry = get_registry();

	if (0 == state)
	{
		matches.clear();
		match_index = 0UL;

		for (const std::pair<std::string, function_data>& entry : registry)
		{
			if (0UL != entry.first.find(text))
			{
				continue;
			}

			try
			{
				matches.push_back(entry.first);
			}
			catch (const std::bad_alloc& exception)
			{
				break;
			}
		}
	}

	return match_index < matches.size() ? strdup(matches[match_index++].c_str()) : nullptr;
}

char** parser::character_name_completion(const char* const text, const std::int32_t start, const std::int32_t end) noexcept
{
	(void)start;
	(void)end;

	rl_attempted_completion_over = 1;
	return rl_completion_matches(text, character_name_generator);
}

} /*< namespace hob::apitester */
