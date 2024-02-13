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
 * @file hobServerInstance_Main.cpp
 * @author Gaina Stefan
 * @date 26.07.2023
 * @brief This file implements the class defined in hobServerInstance_Main.hpp.
 * @todo Support running multiple servers at the same time.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <plog.h>

#include "hobServerInstance_Version.hpp"
#include "hobServerInstance_Server.hpp"

/******************************************************************************************************
 * CONSTANTS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief The port on which the socket will be opened in case there is none entered.
 *****************************************************************************************************/
static constexpr const uint16_t DEFAULT_PORT = 8787U;

/******************************************************************************************************
 * LOCAL FUNCTIONS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Prints to the user what is the default port.
 * @param void
 * @return void
 *****************************************************************************************************/
static void						printDefaultPort(void) noexcept;

/** ***************************************************************************************************
 * @brief Gets the name of the executable from a path (e.g. /home/directory/Executable-Name).
 * @param executablePath: The full path of the executable.
 * @return The name of the executable.
 *****************************************************************************************************/
static const char*				getExecutableName(const char* executablePath);

/******************************************************************************************************
 * ENTRY POINT
 *****************************************************************************************************/

int								main(int argc, char* argv[])
{
	uint16_t port = DEFAULT_PORT;

	std::cout << "Running Heap-of-Battle server " << static_cast<uint16_t>(hobServerInstance::VERSION_MAJOR) << "."
			  << static_cast<uint16_t>(hobServerInstance::VERSION_MINOR) << "." << static_cast<uint16_t>(hobServerInstance::VERSION_PATCH) << "!" << std::endl;

	if (1 == argc)
	{
		printDefaultPort();
		std::cout << "Usage: <" << getExecutableName(argv[0]) << "> <port_number> (optional)" << std::endl;
	}
	else
	{
		if (2 < argc)
		{
			std::cout << "Extra parameters are ignored!" << std::endl;
		}

		port = static_cast<uint16_t>(atoi(argv[0]));
		if (0U == port)
		{
			std::cout << "Invalid port!" << std::endl;
			printDefaultPort();
			port = DEFAULT_PORT;
		}
	}

	try
	{
		hobServerInstance::Server::run(port);
	}
	catch (const std::exception& exception)
	{
		plog_fatal("Server instance failed to run!");
		return EXIT_FAILURE;
	}

	plog_info("Server instance closed successfully!");
	return EXIT_SUCCESS;
}

static void printDefaultPort(void) noexcept
{
	std::cout << "Using default port " << DEFAULT_PORT << "!" << std::endl;
}

static const char* getExecutableName(const char* executablePath)
{
	const char* lastSlash = executablePath;

	while ('\0' != *executablePath)
	{
		if ('/' == *executablePath)
		{
			lastSlash = executablePath;
		}
		++executablePath;
	}

	return lastSlash + 1;
}
