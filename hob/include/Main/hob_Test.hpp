/******************************************************************************************************
 * Heap of Battle Copyright (C) 2024
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the
 * authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
 *    original software. If you use this software in a product, an acknowledgment in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being
 *    the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @file hob_Test.hpp
 * @author Gaina Stefan
 * @date 08.02.2024
 * @brief This file defines the class and method prototypes of the automated testing mechanism.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_TEST_HPP_
#define HOB_TEST_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <iostream>
#include <fstream>
#include <thread>

#include "hob_Socket.hpp"
#include "hobServer_Server.hpp"

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

#ifdef DEVEL_BUILD

/** ***************************************************************************************************
 * @brief Handles the command line arguments for development builds initializing the test mechanism (if
 * possible).
 * @param argc: How many command line arguments have been passed.
 * @param argv: Array of strings of the command line arguments.
 * @return void
 *****************************************************************************************************/
#define handle_arguments(argc, argv)                                                                                                                               \
	do                                                                                                                                                             \
	{                                                                                                                                                              \
		if (1 < argc)                                                                                                                                              \
		{                                                                                                                                                          \
			try                                                                                                                                                    \
			{                                                                                                                                                      \
				hob::Test::init(argv[1]);                                                                                                                          \
			}                                                                                                                                                      \
			catch (...)                                                                                                                                            \
			{                                                                                                                                                      \
				std::cerr << "Failed to start test! (file: " << argv[1] << ")" << std::endl;                                                                       \
				return EXIT_FAILURE;                                                                                                                               \
			}                                                                                                                                                      \
		}                                                                                                                                                          \
		if (2 < argc)                                                                                                                                              \
		{                                                                                                                                                          \
			std::cout << "Extra parameters will be ignored!" << std::endl;                                                                                         \
		}                                                                                                                                                          \
	}                                                                                                                                                              \
	while (false)

/** ***************************************************************************************************
 * @brief Deinitializes the test mechanism for development builds.
 * @param void
 * @return void
 *****************************************************************************************************/
#define test_deinit() hob::Test::deinit();

#else

/** ***************************************************************************************************
 * @brief Handles the command line arguments for production builds.
 * @param argc: How many command line arguments have been passed.
 * @param argv: Array of strings of the command line arguments.
 * @return void
 *****************************************************************************************************/
#define handle_arguments(argc, argv)                                                                                                                               \
	do                                                                                                                                                             \
	{                                                                                                                                                              \
		if (1 < argc)                                                                                                                                              \
		{                                                                                                                                                          \
			std::cout << "Parameters are ignored!" << std::endl;                                                                                                   \
		}                                                                                                                                                          \
		(void)argv;                                                                                                                                                \
	}                                                                                                                                                              \
	while (false)

/** ***************************************************************************************************
 * @brief Does nothing for production builds.
 * @param void
 * @return void
 *****************************************************************************************************/
#define test_deinit()

#endif /*< DEVEL_BUILD */

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

#ifdef DEVEL_BUILD

/** ***************************************************************************************************
 * @brief Static class present only in Debug builds for automated testing purposes.
 * @details Allows the injection of a file (thourgh command line parameter) that contains predefined
 * commands which are being parsed and executed after the game successfully runs.
 *****************************************************************************************************/
class Test final
{
public:
	/** ***********************************************************************************************
	 * @brief Open the file containing the test commands and enables the start() method.
	 * @param file_path: The path of the file containing the test commands.
	 * @return void
	 * @throws std::exception If the file does not exist of any other error occures during its opening.
	 *************************************************************************************************/
	static void init(const char* file_path) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Joins the thread created during the test.
	 * @param void
	 * @return void
	 *************************************************************************************************/
	static void deinit(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Starts the parsing of commands (calls asynchronically parseCommands() method).
	 * @param void
	 * @return void
	 *************************************************************************************************/
	static void start(void) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Parses the file opened during initialization until the end and executes the defined
	 * commands.
	 * @param void
	 * @return void
	 *************************************************************************************************/
	static void parseCommands(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Parses a single command and executes its effect.
	 * @details Syntax of the test commands:
	 * <ul>
	 * <li> wait <milliseconds>: Blocks the parsing for the specified duration. </li>
	 * <li> quit: Sends a quit signal to the game. </li>
	 * </ul>
	 * @param line: A single line from the test command file.
	 * @return void
	 *************************************************************************************************/
	static void parseCommand(std::string& line) noexcept;

	/** ***********************************************************************************************
	 * @brief Overrides the mouse state, mouse x coordinate and mouse y coordinate.
	 * @param line: A single line from the test command file.
	 * @return void
	 *************************************************************************************************/
	static void overrideMouse(const std::string& line) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief The file containing the test commands.
	 *************************************************************************************************/
	static std::ifstream file;

	/** ***********************************************************************************************
	 * @brief Thread created at start() of test and joined at deinitialization on which the parsing of
	 * commands is being done.
	 *************************************************************************************************/
	static std::thread thread;

	/** ***********************************************************************************************
	 * @brief Client socket used for sending test messages.
	 *************************************************************************************************/
	static Socket socket;

	/** ***********************************************************************************************
	 * @brief Server used for hosting the test match.
	 *************************************************************************************************/
	static hobServer::Server server;
};

#endif /*< DEVEL_BUILD */

} /*< namespace hob */

#endif /*< HOB_TEST_HPP_ */
