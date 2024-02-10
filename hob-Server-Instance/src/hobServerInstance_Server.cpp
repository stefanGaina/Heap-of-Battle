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
 * @file hobServerInstance_Server.cpp
 * @author Gaina Stefan
 * @date 26.07.2023
 * @brief This file implements the class defined in hobServerInstance_Server.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <iostream>
#include <exception>
#include <plog.h>

#include "hobServerInstance_Server.hpp"
#include "hobServerInstance_Version.hpp"
#include "hobServer_Server.hpp"
#include "hobServer_Version.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hobServerInstance
{

void Server::run(const uint16_t port) noexcept(false)
{
	hobServer::Server server = {};
	int32_t           stop   = 1;

	plog_trace("Server instance is being ran.");
	init();

	try
	{
		server.runAsync(port, 1000U);
	}
	catch (const std::exception& exception)
	{
		deinit();
		throw exception;
	}

	while (0 != stop)
	{
		std::cout << std::endl << "Input \"0\" to stop server: ";
		std::cin >> stop;
	}
	server.stop();
	deinit();
}

void Server::init(void) noexcept
{
#ifndef PLOG_STRIP_ALL
	const plog_Version_t plogVersion   = plog_get_version();
#endif /*< PLOG_STRIP_ALL */
	hobServer::Version   serverVersion = {};

#ifndef PLOG_STRIP_ALL
	if (false == plog_init("hob_server_logs.txt"))
	{
		std::cout << "Failed to initialize logger!" << std::endl;
	}
	plog_info("Using Plog %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", plogVersion.major, plogVersion.minor, plogVersion.patch);

	if (PLOG_VERSION_MAJOR != plogVersion.major
	 || PLOG_VERSION_MINOR != plogVersion.minor
	 || PLOG_VERSION_PATCH != plogVersion.patch)
	{
		plog_warn("Plog version mismatch! (compiled version: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ")\n", PLOG_VERSION_MAJOR, PLOG_VERSION_MINOR, PLOG_VERSION_PATCH);
	}
#endif /*< PLOG_STRIP_ALL */
	plog_info("Running HOB server instance %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
	plog_info("Using HOB server %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", serverVersion.getMajor(), serverVersion.getMinor(), serverVersion.getPatch());

	if (hobServer::VERSION_MAJOR != serverVersion.getMajor()
	 || hobServer::VERSION_MINOR != serverVersion.getMinor()
	 || hobServer::VERSION_PATCH != serverVersion.getPatch())
	{
		plog_warn("HOB server version mismatch! (compiled version: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ")", hobServer::VERSION_MAJOR, hobServer::VERSION_MINOR, hobServer::VERSION_PATCH);
	}
}

void Server::deinit(void) noexcept
{
	plog_trace("Server instance is being deinitialized.");
	plog_info("Plog is being deinitialized!");
#ifndef PLOG_STRIP_ALL
	plog_deinit();
#endif /*< PLOG_STRIP_ALL */
}

} /*< namespace hobServerInstance */
