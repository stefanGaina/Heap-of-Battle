/******************************************************************************************************
 * @file hobServerInstance_Server.cpp                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 26.07.2023  Gaina Stefan               Initial version.                                            *
 * 25.08.2023  Gaina Stefan               Added const keywords.                                       *
 * @details This file implements the class defined in hobServerInstance_Server.hpp.                   *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <iostream>
#include <exception>
#include <winsock2.h>
#include <plog.h>

#include "hobServerInstance_Server.hpp"
#include "hobServerInstance_Version.hpp"
#include "hobServer_Server.hpp"
#include "hobServer_Version.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hobServerInstance
{

void Server::run(const uint16_t port) noexcept(false)
{
	hobServer::Server server = {};
	int32_t           stop   = 1L;

	plog_trace("Server instance is being ran.");
	try
	{
		init();
		server.runAsync(port);

		while (0L != stop)
		{
			std::cout << std::endl << "Input \"0\" to stop server: ";
			std::cin >> stop;
		}
		server.stop();
	}
	catch (const std::exception& exception)
	{
		deinit();
		throw exception;
	}

	deinit();
}

void Server::init(void) noexcept(false)
{
#ifdef DEVEL_BUILD
	const plog_Version_t plogVersion      = plog_get_version();
#endif /*< DEVEL_BUILD */
	hobServer::Version   serverVersion    = {};
	const WORD           versionRequested = MAKEWORD(2, 2);
	WSADATA              wsaData          = {};
	int32_t              errorCode        = ERROR_SUCCESS;

#ifdef DEVEL_BUILD
	if (PLOG_VERSION_MAJOR != plogVersion.major
	 || PLOG_VERSION_MINOR != plogVersion.minor
	 || PLOG_VERSION_PATCH != plogVersion.patch)
	{
		std::cout << "Plog version mismatch! (compiled version: " << PLOG_VERSION_MAJOR << "." << PLOG_VERSION_MINOR << "." << PLOG_VERSION_PATCH << ")" << std::endl;
		throw std::exception();
	}
	plog_init("hob_server_logs.txt");
	plog_info("Using Plog %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", plogVersion.major, plogVersion.minor, plogVersion.patch);
#endif /*< DEVEL_BUILD */

	plog_info("Running HOB server instance %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);

	plog_info("Using HOB server %" PRIu8 ".%" PRIu8 ".%" PRIu8 "!", serverVersion.getMajor(), serverVersion.getMinor(), serverVersion.getPatch());
	if (hobServer::VERSION_MAJOR != serverVersion.getMajor()
	 || hobServer::VERSION_MINOR != serverVersion.getMinor()
	 || hobServer::VERSION_PATCH != serverVersion.getPatch())
	{
		plog_fatal("HOB server version mismatch! (compiled version: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ")", hobServer::VERSION_MAJOR, hobServer::VERSION_MINOR, hobServer::VERSION_PATCH);
		throw std::exception();
	}

	errorCode = WSAStartup(versionRequested, &wsaData);
	if (ERROR_SUCCESS != errorCode)
	{
		plog_error("WSA failed to be started! (error code: %" PRId32 ")", errorCode);
		throw std::exception();
	}

	if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
	{
		plog_error("Could not find a usable version of Winsock.dll!");
		throw std::exception();
	}
}

void Server::deinit(void) noexcept
{
	int32_t errorCode = ERROR_SUCCESS;

	plog_trace("Server instance is being deinitialized.");

	errorCode = WSACleanup();
	if (ERROR_SUCCESS != errorCode)
	{
		plog_warn("WSA failed to be cleaned! (error code: %" PRId32 ")", errorCode);
	}

#ifdef DEVEL_BUILD
	// plog_info("Plog is being deinitialized!");
	// plog_deinit(); <- Calling this is optional, commented for logs in destructors to appear in file.
#endif /*< DEVEL_BUILD */
}

} /*< namespace hobServerInstance */
