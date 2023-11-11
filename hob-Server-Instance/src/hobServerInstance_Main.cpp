/******************************************************************************************************
 * @file hobServerInstance_Main.cpp                                                                   *
 * @date:      @author:                   Reason for change:                                          *
 * 26.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added getExecutableName function.                           *
 * @details This file provides the entry point for the Heap-of-Battle server instance.                *
 * @todo Support running multiple servers at the same time.                                           *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <plog.h>

#include "hobServerInstance_Version.hpp"
#include "hobServerInstance_Server.hpp"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief The port on which the socket will be opened in case there is none entered.
*/
static constexpr const uint16_t DEFAULT_PORT = 8787U;

/******************************************************************************************************
 * LOCAL FUNCTIONS                                                                                    *
 *****************************************************************************************************/

/**
 * @brief Prints to the user what is the default port.
 * @param void
 * @return void
*/
static void printDefaultPort(void) noexcept;

/**
 * @brief Gets the name of the executable from a path (e.g. C:\Directory\Executable-Name.exe).
 * @param[in] executablePath: The full path of the executable.
 * @return The name of the executable.
*/
static const char* getExecutableName(const char* executablePath);

/******************************************************************************************************
 * ENTRY POINT                                                                                        *
 *****************************************************************************************************/

int main(int argc, char* argv[])
{
	uint16_t port = DEFAULT_PORT;

	std::cout << "Running Heap-of-Battle server "                      << static_cast<uint16_t>(hobServerInstance::VERSION_MAJOR) << "." <<
		static_cast<uint16_t>(hobServerInstance::VERSION_MINOR) << "." << static_cast<uint16_t>(hobServerInstance::VERSION_PATCH) << "!" << std::endl;

	if (1L == argc)
	{
		printDefaultPort();
		std::cout << "Usage: <" << getExecutableName(argv[0]) << "> <port_number> (optional)" << std::endl;
	}
	else
	{
		if (2L < argc)
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
	const char* lastBackslash = executablePath;

	while ('\0' != *executablePath)
	{
		if ('\\' == *executablePath)
		{
			lastBackslash = executablePath;
		}
		++executablePath;
	}

	return lastBackslash + 1;
}
